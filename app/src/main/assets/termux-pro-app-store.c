#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

typedef struct {
    char icon[128];
    char name[128];
    char desc[256];
    char pkg[2048];
    char exec[128];
    char category[64];
    int is_gui;
    GtkWidget *row_widget;
    GtkWidget *action_button;
    GtkWidget *uninstall_button;
    GtkWidget *status_label;
} AppEntry;

typedef struct {
    GtkWidget *window;
    GtkWidget *stack;
    GtkWidget *list_box;
    GtkWidget *search_entry;
    GtkWidget *loading_label;
    GtkWidget *spinner;
    GtkWidget *cat_box;
} AppWidgets;

AppEntry *catalog = NULL;
int catalog_size = 0;
int widgets_created = 0;
AppWidgets widgets;
const char *LIST_URL_MAIN = "https://raw.githubusercontent.com/gulbalamesiyev/xfce-app-store/main/apps.list";
const char *LIST_URL_MASTER = "https://raw.githubusercontent.com/gulbalamesiyev/xfce-app-store/master/apps.list";
const char *LOCAL_PATH = "/data/data/com.termux/files/usr/var/lib/termux-pro/apps.list";
char *current_category = "ALL";

int is_app_installed_robust(AppEntry *app) {
    const char *home = getenv("HOME");
    if (!home) home = "/data/data/com.termux/files/home";
    const char *prefix = "/data/data/com.termux/files/usr";
    char path[1024];

    // Special check for Java/JAR based apps like Burp Suite
    if (strcmp(app->name, "Burp Suite") == 0) {
        snprintf(path, sizeof(path), "%s/burp.jar", home);
        if (access(path, F_OK) == 0) return 1;
        return 0;
    }

    // 1. APT / Dpkg Package Status Check (Primary source of truth for package installation state)
    if (app->pkg[0] != '\0' && !strstr(app->pkg, " ")) {
        char check_cmd[1024];
        snprintf(check_cmd, sizeof(check_cmd), "dpkg-query -W -f='${Status}' \"%s\" 2>/dev/null | grep -q \"install ok installed\"", app->pkg);
        if (system(check_cmd) == 0) return 1;
        // If package is not installed via dpkg, return 0 immediately (do not rely on leftover desktop shortcuts)
        return 0;
    }

    // 2. Binary Executable Check in $PREFIX/bin (for standalone tools)
    if (app->exec[0] != '\0') {
        char cmd_exec[256];
        strncpy(cmd_exec, app->exec, 255); cmd_exec[255] = '\0';
        char *space = strchr(cmd_exec, ' '); if (space) *space = '\0';

        snprintf(path, sizeof(path), "%s/bin/%s", prefix, cmd_exec);
        if (access(path, X_OK) == 0) return 1;
    }

    // 3. Desktop file check as last resort
    snprintf(path, sizeof(path), "%s/Desktop/%s.desktop", home, app->name);
    if (access(path, F_OK) == 0) return 1;

    return 0;
}

gboolean refresh_ui(gpointer data) {
    if (!catalog || !widgets_created) return TRUE;

    for (int i = 0; i < catalog_size; i++) {
        if (!catalog[i].row_widget || !catalog[i].action_button) continue;

        int installed = is_app_installed_robust(&catalog[i]);

        // System/Core runtimes or apps like Burp Suite should not show UNINSTALL button (or user requested Burp Suite to have uninstall)
        // Wait, user asked: "burp un uninstall i niye yoxdu" -> Burp Suite must have UNINSTALL!
        int is_system_runtime = (
            (strstr(catalog[i].name, "Java") || strstr(catalog[i].name, "Python") ||
             strstr(catalog[i].name, "Git") || strstr(catalog[i].name, "Node") ||
             strstr(catalog[i].pkg, "openjdk") || strstr(catalog[i].pkg, "python") ||
             strstr(catalog[i].pkg, "git") || strstr(catalog[i].pkg, "nodejs")) &&
            strcmp(catalog[i].name, "Burp Suite") != 0
        );

        if (installed) {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "UPDATE");
            if (catalog[i].uninstall_button) {
                if (is_system_runtime) gtk_widget_hide(catalog[i].uninstall_button);
                else gtk_widget_show(catalog[i].uninstall_button);
            }
            if (catalog[i].status_label) gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Installed");
        } else {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "INSTALL");
            if (catalog[i].uninstall_button) gtk_widget_hide(catalog[i].uninstall_button);
            if (catalog[i].status_label) gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Available");
        }
    }
    return TRUE;
}

void update_filter() {
    const char *search_text = gtk_entry_get_text(GTK_ENTRY(widgets.search_entry));
    if (!catalog) return;
    for (int i = 0; i < catalog_size; i++) {
        if (!catalog[i].row_widget) continue;
        int match_cat = (strcmp(current_category, "ALL") == 0 || strcasecmp(catalog[i].category, current_category) == 0);
        int match_search = (strlen(search_text) == 0 || strcasestr(catalog[i].name, search_text) || strcasestr(catalog[i].desc, search_text));
        GtkWidget *parent_row = gtk_widget_get_parent(catalog[i].row_widget);
        if (match_cat && match_search) {
            gtk_widget_show(catalog[i].row_widget);
            if (parent_row) gtk_widget_show(parent_row);
        } else {
            gtk_widget_hide(catalog[i].row_widget);
            if (parent_row) gtk_widget_hide(parent_row);
        }
    }
}

void on_category_clicked(GtkButton *btn, gpointer data) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(widgets.cat_box));
    for (GList *l = children; l != NULL; l = l->next) {
        gtk_style_context_remove_class(gtk_widget_get_style_context(GTK_WIDGET(l->data)), "suggested-action");
    }
    g_list_free(children);
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(btn)), "suggested-action");
    current_category = (char *)data;
    update_filter();
}

void on_uninstall_clicked(GtkWidget *widget, gpointer data) {
    if (!data) return;
    AppEntry *entry = (AppEntry*)data;
    char cmd[4096];
    snprintf(cmd, sizeof(cmd),
             "DISPLAY=:1 xfce4-terminal --title \"Uninstalling %s\" -x bash -c ' "
             "pkill -9 -x apt 2>/dev/null; pkill -9 -x dpkg 2>/dev/null; rm -f /data/data/com.termux/files/usr/var/lib/dpkg/lock* /data/data/com.termux/files/usr/var/lib/apt/lists/lock 2>/dev/null; "
             "dpkg --configure -a 2>/dev/null || true; "
             "echo \"Uninstalling %s...\"; PKG_NAME=\"%s\"; EXEC_NAME=\"%s\"; "
             "if [ \"%s\" = \"Burp Suite\" ]; then rm -f \"$HOME/burp.jar\"; fi; "
             "apt remove -y \"$PKG_NAME\" 2>/dev/null || apt remove -y \"$EXEC_NAME\" 2>/dev/null || pkg remove -y \"$PKG_NAME\" 2>/dev/null; "
             "rm -f \"$HOME/Desktop/%s.desktop\" 2>/dev/null; EXEC_BASE=$(basename \"$EXEC_NAME\" 2>/dev/null | cut -d\" \" -f1); "
             "if [ -n \"$EXEC_BASE\" ] && [ \"$EXEC_BASE\" != \".\" ]; then for d in \"$HOME/Desktop\"/*.desktop; do [ -f \"$d\" ] && grep -qiE \"^Exec=(.*[/ ])?$EXEC_BASE( |%%|$)\" \"$d\" 2>/dev/null && rm -f \"$d\"; done; fi; "
             "sync; xfdesktop --reload 2>/dev/null; touch \"$HOME/.cache/termux-pro-install/.refresh_ui\" 2>/dev/null; echo \"done\"; sleep 3' &",
             entry->name, entry->name, entry->pkg, entry->exec, entry->name, entry->name);
    system(cmd);
    refresh_ui(NULL);
}

void on_action_clicked(GtkWidget *widget, gpointer data) {
    if (!data) return;
    AppEntry *entry = (AppEntry*)data;

    // Create a temporary installer script to avoid shell quoting issues
    char script_path[512];
    snprintf(script_path, sizeof(script_path), "/data/data/com.termux/files/usr/tmp/app_install_%s.sh", entry->name);

    FILE *fp = fopen(script_path, "w");
    if (fp) {
        fprintf(fp, "#!/bin/bash\n");
        fprintf(fp, "export PREFIX=/data/data/com.termux/files/usr\n");
        fprintf(fp, "export PATH=\"$PREFIX/bin:$PATH\"\n");
        fprintf(fp, "export HOME=\"${HOME:-/data/data/com.termux/files/home}\"\n");
        fprintf(fp, "echo \"Installing %s...\"\n", entry->name);

        // Auto-resolve any background dpkg/apt locks and fix configure errors
        fprintf(fp, "clear_locks() {\n");
        fprintf(fp, "  local count=0\n");
        fprintf(fp, "  while [ $count -lt 3 ]; do\n");
        fprintf(fp, "    if ! pgrep -x \"apt\" >/dev/null && ! pgrep -x \"dpkg\" >/dev/null; then break; fi\n");
        fprintf(fp, "    sleep 1\n");
        fprintf(fp, "    count=$((count + 1))\n");
        fprintf(fp, "  done\n");
        fprintf(fp, "  pkill -9 -x \"apt\" 2>/dev/null || true\n");
        fprintf(fp, "  pkill -9 -x \"dpkg\" 2>/dev/null || true\n");
        fprintf(fp, "  rm -f \"$PREFIX/var/lib/dpkg/lock\"* 2>/dev/null || true\n");
        fprintf(fp, "  rm -f \"$PREFIX/var/lib/apt/lists/lock\" 2>/dev/null || true\n");
        fprintf(fp, "  dpkg --configure -a 2>/dev/null || true\n");
        fprintf(fp, "}\n");
        fprintf(fp, "clear_locks\n");

        // Self-heal broken curl/libcurl linkage (ngtcp2 symbol mismatch)
        fprintf(fp, "if ! curl --version >/dev/null 2>&1; then\n");
        fprintf(fp, "  echo \"[System Self-Heal] curl is broken due to library mismatch.\"\n");
        fprintf(fp, "  echo \"[System Self-Heal] Repairing curl and libcurl via apt...\"\n");
        fprintf(fp, "  apt update && apt install -y curl libcurl 2>/dev/null || true\n");
        fprintf(fp, "fi\n");
        // Self-heal C++ symbol / libhunspell / libc++ linkage issues
        fprintf(fp, "echo \"[System Self-Heal] Checking and repairing library linkages (libhunspell, libc++)...\"\n");
        fprintf(fp, "DEBIAN_FRONTEND=noninteractive apt-get install -y --reinstall libhunspell libc++ 2>/dev/null || true\n");

        // Override 'pkg' command to bypass curl dependency and route directly to apt
    fprintf(fp, "pkg() {\n");
    fprintf(fp, "  local cmd=\"$1\"\n");
    fprintf(fp, "  if [ \"$cmd\" = \"install\" ]; then\n");
    fprintf(fp, "    shift\n");
    fprintf(fp, "    local args=()\n");
    fprintf(fp, "    for arg in \"$@\"; do\n");
    fprintf(fp, "      [ \"$arg\" != \"-y\" ] && args+=(\"$arg\")\n");
    fprintf(fp, "    done\n");
    fprintf(fp, "    DEBIAN_FRONTEND=noninteractive apt-get install -y -o Dpkg::Options::=\"--force-confdef\" -o Dpkg::Options::=\"--force-confold\" \"${args[@]}\"\n");
    fprintf(fp, "    return ${PIPESTATUS[0]}\n");
    fprintf(fp, "  elif [ \"$cmd\" = \"uninstall\" ] || [ \"$cmd\" = \"remove\" ]; then\n");
    fprintf(fp, "    shift\n");
    fprintf(fp, "    local args=()\n");
    fprintf(fp, "    for arg in \"$@\"; do\n");
    fprintf(fp, "      [ \"$arg\" != \"-y\" ] && args+=(\"$arg\")\n");
    fprintf(fp, "    done\n");
    fprintf(fp, "    DEBIAN_FRONTEND=noninteractive apt-get remove -y \"${args[@]}\"\n");
    fprintf(fp, "  elif [ \"$cmd\" = \"upgrade\" ]; then\n");
    fprintf(fp, "    shift\n");
    fprintf(fp, "    DEBIAN_FRONTEND=noninteractive apt-get upgrade -y \"$@\"\n");
    fprintf(fp, "    return ${PIPESTATUS[0]}\n");
    fprintf(fp, "  else\n");
    fprintf(fp, "    command pkg \"$@\"\n");
    fprintf(fp, "  fi\n");
    fprintf(fp, "}\n");
    fprintf(fp, "export -f pkg 2>/dev/null || true\n");

    // Ensure repos are enabled and updated
    fprintf(fp, "pkg install -y x11-repo tur-repo glibc-repo || true\n");
    fprintf(fp, "apt-get update -y || true\n");

    // Execute the package command (Real Upgrade / Full-Upgrade for system runtimes to ensure latest version)
    if (strcmp(entry->name, "Burp Suite") == 0) {
        fprintf(fp, "echo \"Installing OpenJDK and downloading Burp Suite Community JAR...\"\n");
        fprintf(fp, "DEBIAN_FRONTEND=noninteractive apt-get install -y openjdk-21 wget\n");
        fprintf(fp, "wget -c -O \"$HOME/burp.jar\" \"https://portswigger.net/burp/releases/download?product=community&version=2024.2.1.3&type=Jar\"\n");
        fprintf(fp, "RET=$?\n");
    } else if (strstr(entry->pkg, "openjdk") || strcmp(entry->name, "Python 3") == 0 || strcmp(entry->name, "Node.js") == 0 || strstr(entry->pkg, "python") || strstr(entry->pkg, "nodejs")) {
        fprintf(fp, "echo \"Performing real latest version upgrade/install...\"\n");
        if (strcmp(entry->name, "Java 21 (OpenJDK)") == 0) {
            fprintf(fp, "DEBIAN_FRONTEND=noninteractive apt-get install -y openjdk-21 || DEBIAN_FRONTEND=noninteractive apt-get install -y openjdk-17 || DEBIAN_FRONTEND=noninteractive apt-get install -y default-jdk\n");
        } else {
            fprintf(fp, "DEBIAN_FRONTEND=noninteractive apt-get install -y --only-upgrade \"%s\" 2>/dev/null || DEBIAN_FRONTEND=noninteractive apt-get install -y \"%s\"\n", entry->pkg, entry->pkg);
        }
        fprintf(fp, "RET=${PIPESTATUS[0]}\n");
    } else {
        if (strchr(entry->pkg, ' ') == NULL) {
            fprintf(fp, "DEBIAN_FRONTEND=noninteractive apt-get install -y \"%s\"\n", entry->pkg);
            fprintf(fp, "RET=${PIPESTATUS[0]}\n");
        } else {
            fprintf(fp, "%s\n", entry->pkg);
            fprintf(fp, "RET=$?\n");
        }
    }

    // Shortcut creation logic (Skip shortcuts for pure core system runtimes like Java, Python, Git, Node.js)
    fprintf(fp, "if [ $RET -eq 0 ]; then\n");
    fprintf(fp, "  echo \"installing was successfully\"\n");
    fprintf(fp, "  if echo \"%s\" | grep -qiE \"openjdk\" || echo \"%s\" | grep -qiE \"^Java\"; then\n", entry->pkg, entry->name);
    fprintf(fp, "    echo \"Linking Java binaries to $PREFIX/bin...\"\n");
    fprintf(fp, "    JAVA_BIN=$(find \"$PREFIX/opt\" \"$PREFIX/lib\" -name \"java\" -type f 2>/dev/null | head -n 1)\n");
    fprintf(fp, "    if [ -n \"$JAVA_BIN\" ]; then\n");
    fprintf(fp, "      JDK_BIN_DIR=$(dirname \"$JAVA_BIN\")\n");
    fprintf(fp, "      for bin in \"$JDK_BIN_DIR\"/*; do\n");
    fprintf(fp, "        [ -f \"$bin\" ] && ln -sf \"$bin\" \"$PREFIX/bin/$(basename \"$bin\")\" 2>/dev/null || true\n");
    fprintf(fp, "      done\n");
    fprintf(fp, "      echo \"Java binaries linked successfully.\"\n");
    fprintf(fp, "    fi\n");
    fprintf(fp, "  fi\n");
    fprintf(fp, "  if echo \"%s\" | grep -qiE \"openjdk|python|git|nodejs\" || echo \"%s\" | grep -qiE \"^Java|^Python|^Git|^Node\"; then\n", entry->pkg, entry->name);
    fprintf(fp, "    echo \"Core system runtime installed successfully. Skipping Desktop shortcut creation.\"\n");
    fprintf(fp, "  else\n");
    fprintf(fp, "    echo \"Creating Shortcut...\"\n");
        fprintf(fp, "    CATALOG_FILE=\"$HOME/Desktop/%s.desktop\"\n", entry->name);
        fprintf(fp, "    EXEC_RAW=\"%s\"\n", entry->exec);
        fprintf(fp, "    EXEC_BIN_NAME=$(echo \"$EXEC_RAW\" | cut -d' ' -f1)\n");
        fprintf(fp, "    if [[ \"$EXEC_RAW\" == /* ]]; then\n");
        fprintf(fp, "      EXEC_PATH=\"$EXEC_RAW\"\n");
        fprintf(fp, "    else\n");
        fprintf(fp, "      EXEC_PATH=$(command -v \"$EXEC_BIN_NAME\" 2>/dev/null)\n");
        fprintf(fp, "      [ -z \"$EXEC_PATH\" ] && [ -f \"$PREFIX/bin/$EXEC_BIN_NAME\" ] && EXEC_PATH=\"$PREFIX/bin/$EXEC_BIN_NAME\"\n");
        fprintf(fp, "      [ -z \"$EXEC_PATH\" ] && EXEC_PATH=\"/data/data/com.termux/files/usr/bin/$EXEC_BIN_NAME\"\n");
        fprintf(fp, "    fi\n");
        fprintf(fp, "    EXEC_BASE=$(basename \"$EXEC_PATH\" 2>/dev/null | cut -d\" \" -f1)\n");

        fprintf(fp, "  pick_native() {\n");
        fprintf(fp, "    # Do not copy native desktop files to Desktop to avoid %U or duplicate script generation conflicts\n");
        fprintf(fp, "    NATIVE_DESKTOP=\"\"\n");
        fprintf(fp, "  }\n");
        fprintf(fp, "  pick_native\n");

        fprintf(fp, "  RESOLVED_ICON=\"\"\n");
        fprintf(fp, "  find_icon() {\n");
        fprintf(fp, "    local name=\"$1\"; [ -z \"$name\" ] && return\n");
        fprintf(fp, "    [ -f \"$name\" ] && RESOLVED_ICON=\"$name\" && return\n");
        fprintf(fp, "    # If it is a simple icon name, let XFCE resolve it from the active theme (e.g. Papirus SVG)\n");
        fprintf(fp, "    if [[ \"$name\" != */* && \"$name\" != *.* ]]; then\n");
        fprintf(fp, "      RESOLVED_ICON=\"$name\"\n");
        fprintf(fp, "      return\n");
        fprintf(fp, "    fi\n");
        fprintf(fp, "    # Otherwise search for high-res SVG or scalable PNG files\n");
        fprintf(fp, "    local found=$(find \"$PREFIX/share/icons\" -name \"*$name*.svg\" 2>/dev/null | head -n 1)\n");
        fprintf(fp, "    [ -z \"$found\" ] && found=$(find \"$PREFIX/share/icons\" -name \"*$name*.png\" 2>/dev/null | grep -E \"scalable|512x512|256x256|128x128\" | head -n 1)\n");
        fprintf(fp, "    [ -z \"$found\" ] && found=$(find \"$PREFIX/share/icons\" -name \"*$name*.png\" 2>/dev/null | head -n 1)\n");
        fprintf(fp, "    RESOLVED_ICON=\"${found:-security-high}\"\n");
        fprintf(fp, "  }\n");
        fprintf(fp, "  find_icon \"%s\"\n", entry->icon);

        fprintf(fp, "  if [ -n \"$NATIVE_DESKTOP\" ]; then\n");
        fprintf(fp, "    echo \"Removing old shortcut...\"\n");
        fprintf(fp, "    rm -f \"$HOME/Desktop/$(basename \"$NATIVE_DESKTOP\")\"\n");
        fprintf(fp, "    rm -f \"$HOME/Desktop/%s.desktop\"\n", entry->name);
        fprintf(fp, "    for old_d in \"$HOME/Desktop\"/*.desktop; do\n");
        fprintf(fp, "      [ -f \"$old_d\" ] || continue\n");
        fprintf(fp, "      if grep -qiE \"^Name=%s$\" \"$old_d\" 2>/dev/null || grep -qiE \"^Exec=.*%s.*\" \"$old_d\" 2>/dev/null; then\n", entry->name, entry->exec);
        fprintf(fp, "        rm -f \"$old_d\"\n");
        fprintf(fp, "      fi\n");
        fprintf(fp, "    done\n");
        fprintf(fp, "    sync; xfdesktop --reload 2>/dev/null\n");
        fprintf(fp, "  fi\n");
        fprintf(fp, "  FILE=\"$PREFIX/share/applications/%s.desktop\"\n", entry->name);
        fprintf(fp, "  rm -f \"$FILE\"\n");
        fprintf(fp, "  EXTRA_FLAGS=\"\"\n");
        fprintf(fp, "  [[ \"$EXEC_BASE\" == *\"chromium\"* || \"$EXEC_BASE\" == *\"code-oss\"* ]] && EXTRA_FLAGS=\"--no-sandbox\"\n");
        fprintf(fp, "  if [[ \"$EXEC_BASE\" == *\"vlc\"* ]] || [[ \"%s\" == \"VLC Player\" ]]; then\n", entry->name);
        fprintf(fp, "    EXEC_CMD=\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH vlc\"\n");
        fprintf(fp, "    TERM_FLAG=\"false\"\n");
        fprintf(fp, "  elif [[ \"$EXEC_BASE\" == *\"chromium\"* || \"$EXEC_BASE\" == *\"code-oss\"* ]]; then\n", entry->name);
        fprintf(fp, "    EXTRA_FLAGS=\"--no-sandbox\"\n");
        fprintf(fp, "    [ \"%d\" -eq 0 ] && EXEC_CMD=\"xfce4-terminal --hold -e \\\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH $EXEC_PATH $EXTRA_FLAGS\\\"\" || EXEC_CMD=\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH $EXEC_PATH $EXTRA_FLAGS\"\n", entry->is_gui);
        fprintf(fp, "    [ \"%d\" -eq 0 ] && TERM_FLAG=\"true\" || TERM_FLAG=\"false\"\n", entry->is_gui);
        fprintf(fp, "  elif [[ \"%s\" == *\"burp\"* ]] || [[ \"%s\" == *\"Burp\"* ]] || [[ \"%s\" == *\"java\"* ]]; then\n", entry->name, entry->name, entry->exec);
        fprintf(fp, "    EXEC_CMD=\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH java -jar /data/data/com.termux/files/home/burp.jar\"\n");
        fprintf(fp, "    TERM_FLAG=\"false\"\n");
        fprintf(fp, "  else\n");
        fprintf(fp, "    [ \"%d\" -eq 0 ] && EXEC_CMD=\"xfce4-terminal --hold -e \\\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH $EXEC_PATH $EXTRA_FLAGS\\\"\" || EXEC_CMD=\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH $EXEC_PATH $EXTRA_FLAGS\"\n", entry->is_gui);
        fprintf(fp, "    [ \"%d\" -eq 0 ] && TERM_FLAG=\"true\" || TERM_FLAG=\"false\"\n", entry->is_gui);
        fprintf(fp, "  fi\n");
        fprintf(fp, "  if [[ \"%s\" == \"Telegram\" ]]; then\n", entry->name);
        fprintf(fp, "    EXEC_PATH=\"$PREFIX/bin/telegram-desktop\"\n");
        fprintf(fp, "    EXEC_CMD=\"env DISPLAY=:1 LD_LIBRARY_PATH=$PREFIX/lib PATH=$PREFIX/bin:/data/data/com.termux/files/usr/bin:\\$PATH telegram-desktop\"\n");
        fprintf(fp, "  fi\n");
        fprintf(fp, "  printf \"[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=%s\\nExec=$EXEC_CMD\\nIcon=${RESOLVED_ICON:-utilities-terminal}\\nTerminal=$TERM_FLAG\\nCategories=%s;\\n\" > \"$FILE\"\n", entry->name, entry->category);
        fprintf(fp, "  chmod 755 \"$FILE\"\n");
        fprintf(fp, "  cp -f \"$FILE\" \"$HOME/Desktop/%s.desktop\"\n", entry->name);
        fprintf(fp, "  chmod 755 \"$HOME/Desktop/%s.desktop\"\n", entry->name);
        fprintf(fp, "  sync; xfdesktop --reload 2>/dev/null\n");
        fprintf(fp, "  fi\n");
        fprintf(fp, "fi\n");

        fprintf(fp, "touch \"$HOME/.cache/termux-pro-install/.refresh_ui\" 2>/dev/null\n");
        fprintf(fp, "if [ $RET -eq 0 ]; then\n");
        fprintf(fp, "  echo \"installing was successfully\"\n");
        fprintf(fp, "  echo \"done\"\n");
        fprintf(fp, "  if echo \"%s\" | grep -qiE \"openjdk|python|git|nodejs\" || echo \"%s\" | grep -qiE \"^Java|^Python|^Git|^Node\"; then\n", entry->pkg, entry->name);
        fprintf(fp, "    read -p \"Press Enter to close...\"\n");
        fprintf(fp, "  else\n");
        fprintf(fp, "    sleep 3\n");
        fprintf(fp, "  fi\n");
        fprintf(fp, "else\n");
        fprintf(fp, "  echo \"FAILED\"\n");
        fprintf(fp, "  read -p \"Press Enter to close...\"\n");
        fprintf(fp, "fi\n");
        fclose(fp);
        chmod(script_path, 0755);
    }

    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "DISPLAY=:1 xfce4-terminal --title \"Installing %s\" -x bash \"%s\" &", entry->name, script_path);
    system(cmd);
    refresh_ui(NULL);
}

void on_search_changed(GtkEditable *editable, gpointer user_data) { update_filter(); }

void populate_list() {
    for (int j = 0; j < catalog_size; j++) {
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        catalog[j].row_widget = row;
        gtk_container_set_border_width(GTK_CONTAINER(row), 12);
        char icon_name[128]; strncpy(icon_name, catalog[j].icon, 127); icon_name[127] = '\0';
        char *dot = strrchr(icon_name, '.'); if (dot && (strcmp(dot, ".png") == 0 || strcmp(dot, ".svg") == 0 || strcmp(dot, ".xpm") == 0)) *dot = '\0';
        GtkIconTheme *theme = gtk_icon_theme_get_default(); GtkWidget *icon = NULL;
        const char *candidates[] = { icon_name, catalog[j].exec, catalog[j].pkg, NULL };
        for (int k = 0; candidates[k] != NULL; k++) { if (strlen(candidates[k]) > 0 && gtk_icon_theme_has_icon(theme, candidates[k])) { icon = gtk_image_new_from_icon_name(candidates[k], GTK_ICON_SIZE_DIALOG); break; } }
        if (!icon) icon = gtk_image_new_from_icon_name(catalog[j].is_gui ? "application-x-executable" : "utilities-terminal", GTK_ICON_SIZE_DIALOG);
        gtk_image_set_pixel_size(GTK_IMAGE(icon), 48);
        GtkWidget *details = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *name = gtk_label_new(NULL);
        char *markup = g_strdup_printf("<span size='large' weight='bold'>%s</span> <span size='small' alpha='50%%'>[%s]</span>", catalog[j].name, catalog[j].category);
        gtk_label_set_markup(GTK_LABEL(name), markup); g_free(markup);
        gtk_label_set_xalign(GTK_LABEL(name), 0);
        GtkWidget *desc = gtk_label_new(catalog[j].desc); gtk_label_set_xalign(GTK_LABEL(desc), 0);
        gtk_box_pack_start(GTK_BOX(details), name, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(details), desc, FALSE, FALSE, 0);
        catalog[j].status_label = gtk_label_new("Checking...");
        catalog[j].action_button = gtk_button_new_with_label("...");
        gtk_widget_set_size_request(catalog[j].action_button, 100, -1);
        g_signal_connect(catalog[j].action_button, "clicked", G_CALLBACK(on_action_clicked), &catalog[j]);
        catalog[j].uninstall_button = gtk_button_new_with_label("UNINSTALL");
        gtk_widget_set_size_request(catalog[j].uninstall_button, 100, -1);
        g_signal_connect(catalog[j].uninstall_button, "clicked", G_CALLBACK(on_uninstall_clicked), &catalog[j]);
        gtk_widget_hide(catalog[j].uninstall_button);
        gtk_box_pack_start(GTK_BOX(row), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row), details, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].status_label, FALSE, FALSE, 10);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].action_button, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].uninstall_button, FALSE, FALSE, 0);
        gtk_list_box_insert(GTK_LIST_BOX(widgets.list_box), row, -1);
    }
    gtk_widget_show_all(widgets.list_box);
    widgets_created = 1;
    update_filter();
    refresh_ui(NULL);
}

static gboolean on_load_finished(gpointer data) {
    int success = GPOINTER_TO_INT(data);
    gtk_spinner_stop(GTK_SPINNER(widgets.spinner));
    if (success && catalog_size > 0) { populate_list(); gtk_stack_set_visible_child_name(GTK_STACK(widgets.stack), "catalog"); }
    else { gtk_label_set_text(GTK_LABEL(widgets.loading_label), "Connection Error.\nPlease verify xfce-app-store repo branch."); }
    return FALSE;
}

static void* load_catalog_thread(void* data) {
    system("mkdir -p /data/data/com.termux/files/usr/var/lib/termux-pro");

    // First, try loading local apps.list (packaged in APK assets and copied at startup).
    // If local apps.list doesn't exist, fetch from online repo.
    FILE *fp = fopen(LOCAL_PATH, "r");
    if (!fp) {
        char sync_cmd[2048];
        long timestamp = (long)time(NULL);
        snprintf(sync_cmd, sizeof(sync_cmd), "curl -f -L -s -k --connect-timeout 10 --retry 2 -o %s \"%s?t=%ld\"", LOCAL_PATH, LIST_URL_MAIN, timestamp);
        if (system(sync_cmd) != 0) {
            snprintf(sync_cmd, sizeof(sync_cmd), "curl -f -L -s -k --connect-timeout 10 --retry 2 -o %s \"%s?t=%ld\"", LOCAL_PATH, LIST_URL_MASTER, timestamp);
            system(sync_cmd);
        }
        fp = fopen(LOCAL_PATH, "r");
    }
    if (fp) {
        char line[2048];
        while (fgets(line, sizeof(line), fp)) {
            if (strlen(line) > 10 && strchr(line, '|')) catalog_size++;
        }
        rewind(fp);
        if (catalog_size > 0) {
            catalog = calloc(catalog_size, sizeof(AppEntry));
            int i = 0;
            while (fgets(line, sizeof(line), fp) && i < catalog_size) {
                char *lptr = line;
                if ((unsigned char)line[0] == 0xEF) lptr += 3; // Skip BOM
                char *token; int field = 0;
                char *saveptr;
                char *tmp_line = strdup(lptr);
                char *curr = tmp_line;
                while ((token = strsep(&curr, "|")) != NULL && field < 7) {
                    token[strcspn(token, "\r\n")] = 0;
                    if (field == 0) strncpy(catalog[i].icon, token, 127);
                    else if (field == 1) strncpy(catalog[i].name, token, 127);
                    else if (field == 2) strncpy(catalog[i].desc, token, 255);
                    else if (field == 3) strncpy(catalog[i].pkg, token, 2047);
                    else if (field == 4) strncpy(catalog[i].exec, token, 127);
                    else if (field == 5) strncpy(catalog[i].category, token, 63);
                    else if (field == 6) catalog[i].is_gui = atoi(token);
                    field++;
                }
                free(tmp_line);
                if (field >= 4) i++; // Minimum required fields
            }
            catalog_size = i; // Adjust to actual count
            fclose(fp); g_idle_add(on_load_finished, GINT_TO_POINTER(1));
        } else { fclose(fp); g_idle_add(on_load_finished, GINT_TO_POINTER(0)); }
    } else { g_idle_add(on_load_finished, GINT_TO_POINTER(0)); }
    return NULL;
}

gboolean check_refresh_trigger(gpointer data) {
    char path[256]; snprintf(path, sizeof(path), "%s/.cache/termux-pro-install/.refresh_ui", getenv("HOME"));
    if (access(path, F_OK) == 0) {
        unlink(path);
        refresh_ui(NULL);
    }
    // Avtomatik olaraq dövri olaraq da UI-ı təzələyir ki, heç bir manual refresh-ə ehtiyac qalmasın
    static int tick = 0;
    if (++tick >= 3) {
        tick = 0;
        refresh_ui(NULL);
    }
    return TRUE;
}

void on_manual_refresh_clicked(GtkWidget *widget, gpointer data) { refresh_ui(NULL); }

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Ultra-lightweight Minimalist Flat CSS Styling (Zero hover shadows or background changes)
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "window { background-color: #ffffff; }"
        "list, listbox { background-color: #ffffff; border: none; outline: none; box-shadow: none; }"
        "row, list row { padding: 8px; border: none; border-bottom: none; background-color: #ffffff; box-shadow: none; outline: none; border-radius: 0px; }"
        "row:hover, row:selected, row:focus { background-color: #ffffff; border: none; border-bottom: none; box-shadow: none; outline: none; }"
        "separator { border: none; background: transparent; min-height: 0px; }"
        "button { border-radius: 3px; padding: 4px 10px; background-image: none; background-color: #f5f5f5; border: 1px solid #cccccc; color: #333333; box-shadow: none; }"
        "button:hover { background-color: #e8e8e8; box-shadow: none; }"
        "button.suggested-action { background-color: #007acc; color: #ffffff; border: 1px solid #005999; box-shadow: none; }"
        "button.suggested-action:hover { background-color: #005999; box-shadow: none; }"
        "entry { border: 1px solid #cccccc; border-radius: 3px; padding: 4px 8px; background: #ffffff; color: #000000; box-shadow: none; }"
        "label { color: #222222; text-shadow: none; }", -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_timeout_add(1000, (GSourceFunc)check_refresh_trigger, NULL);

    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-icon-theme-name", "Papirus", NULL);
    GtkIconTheme *theme = gtk_icon_theme_get_default();
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/icons");
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/icons/Papirus");
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/pixmaps");
    widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets.window), "App Store (Simplified)");
    gtk_window_set_icon_name(GTK_WINDOW(widgets.window), "software-center");
    gtk_window_set_default_size(GTK_WINDOW(widgets.window), 850, 600);
    gtk_window_set_position(GTK_WINDOW(widgets.window), GTK_WIN_POS_CENTER);
    g_signal_connect(widgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(widgets.window), main_vbox);
    GtkWidget *search_bar = gtk_search_bar_new();
    GtkWidget *search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    widgets.search_entry = gtk_search_entry_new();
    gtk_box_pack_start(GTK_BOX(search_box), widgets.search_entry, TRUE, TRUE, 0);
    GtkWidget *refresh_btn = gtk_button_new_from_icon_name("view-refresh-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_relief(GTK_BUTTON(refresh_btn), GTK_RELIEF_NONE);
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(on_manual_refresh_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(search_box), refresh_btn, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(search_bar), search_box);
    gtk_search_bar_set_search_mode(GTK_SEARCH_BAR(search_bar), TRUE);
    gtk_box_pack_start(GTK_BOX(main_vbox), search_bar, FALSE, FALSE, 5);
    g_signal_connect(widgets.search_entry, "changed", G_CALLBACK(on_search_changed), NULL);
    widgets.cat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_container_set_border_width(GTK_CONTAINER(widgets.cat_box), 10);
    gtk_box_pack_start(GTK_BOX(main_vbox), widgets.cat_box, FALSE, FALSE, 0);
    const char *cats[] = {"ALL", "SOCIAL", "CYBER", "INTERNET", "TOOLS", "DEV", "GRAPHICS", "OFFICE", "AI"};
    for (int i=0; i<9; i++) {
        GtkWidget *btn = gtk_button_new_with_label(cats[i]);
        if (i == 0) gtk_style_context_add_class(gtk_widget_get_style_context(btn), "suggested-action");
        g_signal_connect(btn, "clicked", G_CALLBACK(on_category_clicked), (gpointer)cats[i]);
        gtk_box_pack_start(GTK_BOX(widgets.cat_box), btn, TRUE, TRUE, 0);
    }
    widgets.stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(widgets.stack), GTK_STACK_TRANSITION_TYPE_NONE);
    gtk_box_pack_start(GTK_BOX(main_vbox), widgets.stack, TRUE, TRUE, 0);
    GtkWidget *load_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_set_border_width(GTK_CONTAINER(load_box), 50);
    widgets.spinner = gtk_spinner_new();
    gtk_widget_set_size_request(widgets.spinner, 64, 64);
    widgets.loading_label = gtk_label_new("Establishing Cloud Connection...");
    gtk_box_pack_start(GTK_BOX(load_box), widgets.spinner, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(load_box), widgets.loading_label, FALSE, FALSE, 0);
    gtk_stack_add_named(GTK_STACK(widgets.stack), load_box, "loading");
    gtk_spinner_start(GTK_SPINNER(widgets.spinner));
    GtkWidget *catalog_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(catalog_vbox), 5);
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(catalog_vbox), scroll, TRUE, TRUE, 0);
    widgets.list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(widgets.list_box), GTK_SELECTION_NONE);
    gtk_container_add(GTK_CONTAINER(scroll), widgets.list_box);
    gtk_stack_add_named(GTK_STACK(widgets.stack), catalog_vbox, "catalog");
    gtk_widget_show_all(widgets.window);
    pthread_t tid; pthread_create(&tid, NULL, load_catalog_thread, NULL);
    gtk_main();
    return 0;
}
