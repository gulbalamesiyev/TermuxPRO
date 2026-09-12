#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    char icon[128];
    char name[128];
    char desc[256];
    char pkg[512];
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
} AppWidgets;

AppEntry *catalog = NULL;
int catalog_size = 0;
AppWidgets widgets;
const char *LIST_URL_MAIN = "https://raw.githubusercontent.com/gulbalamesiyev/xfce-app-store/main/apps.list";
const char *LIST_URL_MASTER = "https://raw.githubusercontent.com/gulbalamesiyev/xfce-app-store/master/apps.list";
const char *LOCAL_PATH = "/data/data/com.termux/files/usr/var/lib/termux-pro/apps.list";

int is_installed(const char *exec) {
    if (!exec || strlen(exec) == 0) return 0;
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "command -v %s >/dev/null 2>&1", exec);
    return system(cmd) == 0;
}

void refresh_ui() {
    if (!catalog) return;
    for (int i = 0; i < catalog_size; i++) {
        if (is_installed(catalog[i].exec)) {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "UPDATE");
            gtk_widget_show(catalog[i].uninstall_button);
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Installed");
        } else {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "INSTALL");
            gtk_widget_hide(catalog[i].uninstall_button);
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Available");
        }
    }
}

void on_uninstall_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    char cmd[4096];
    snprintf(cmd, sizeof(cmd),
        "DISPLAY=:1 xfce4-terminal --title \"Uninstalling %s\" -x bash -c ' "
        "echo \"Uninstalling %s...\"; "
        "if echo \"%s\" | grep -q \"npm\"; then "
        "  cmd=\"%s\"; uninstall_cmd=${cmd/install/uninstall}; eval $uninstall_cmd; "
        "else pkg uninstall -y %s; fi; "
        "rm -f \"$HOME/Desktop/%s.desktop\"; "
        "xfdesktop --reload 2>/dev/null; "
        "echo \"Done.\"; sleep 2' &",
        entry->name, entry->name, entry->pkg, entry->pkg, entry->pkg, entry->name);
    system(cmd);
    g_timeout_add(2000, (GSourceFunc)refresh_ui, NULL);
}

void on_action_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    char cmd[8192];

    snprintf(cmd, sizeof(cmd),
        "DISPLAY=:1 xfce4-terminal --title \"Installing %s\" -x bash -c ' "
        "echo \"Installing %s...\"; "
        "if echo \"%s\" | grep -q \" \"; then %s; else pkg install -y %s; fi; "
        "RET=$?; "
        "if [ $RET -eq 0 ]; then "
        "  echo \"Creating Shortcut...\"; "
        "  FILE=\"$HOME/Desktop/%s.desktop\"; "
        "  EXEC_PATH=\"%s\"; "
        "  if ! echo \"$EXEC_PATH\" | grep -q \"/\"; then EXEC_PATH=$(command -v %s); fi; "
        "  [ -z \"$EXEC_PATH\" ] && EXEC_PATH=%s; "
        "  ICON_NAME=\"%s\"; ICON_NAME=${ICON_NAME%%%%.*}; "
        "  FOUND_ICON=$(find \"$PREFIX/share/icons\" \"$HOME/.local/share/icons\" \"$PREFIX/share/pixmaps\" -maxdepth 3 ! -name \"*.desktop\" -iname \"$ICON_NAME.*\" 2>/dev/null | head -n 1); "
        "  if [ -z \"$FOUND_ICON\" ]; then "
        "    case \"%s\" in Internet) M=web-browser;; Security) M=security-high;; Multimedia) M=multimedia-audio-player;; Development) M=edit-code;; Graphics) M=applications-graphics;; Office) M=x-office-document;; System) M=system-run;; AI) M=utilities-terminal;; *) M=application-x-executable;; esac; "
        "    SRC=$(find \"$PREFIX/share/icons/Papirus\" \"$PREFIX/share/icons/hicolor\" ! -name \"*.desktop\" -name \"$M.*\" 2>/dev/null | head -n 1); "
        "    if [ -n \"$SRC\" ]; then ICON_DIR=\"$HOME/.local/share/icons/hicolor/48x48/apps\"; mkdir -p \"$ICON_DIR\"; cp \"$SRC\" \"$ICON_DIR/$ICON_NAME.svg\" 2>/dev/null; ICON_NAME=\"$ICON_DIR/$ICON_NAME.svg\"; fi; "
        "  fi; "
        "  if [ \"%d\" -eq 0 ]; then EXEC_CMD=\"xfce4-terminal --hold -e $EXEC_PATH\"; else EXEC_CMD=\"$EXEC_PATH\"; fi; "
        "  printf \"[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=%s\\nExec=$EXEC_CMD\\nIcon=$ICON_NAME\\nTerminal=false\\nCategories=%s;\\n\" > \"$FILE\"; "
        "  chmod 755 \"$FILE\"; sync; "
        "  if command -v gio >/dev/null; then gio set -t string \"$FILE\" metadata::xfce-exe-checksum \"$(sha256sum \"$FILE\" | cut -d\" \" -f1)\" 2>/dev/null; gio set \"$FILE\" metadata::trusted true 2>/dev/null; fi; "
        "  gtk-update-icon-cache -f /data/data/com.termux/files/usr/share/icons/hicolor 2>/dev/null; "
        "  xfdesktop --reload 2>/dev/null; "
        "  echo \"Done.\"; sleep 2; "
        "else echo \"FAILED\"; read -p \"Press Enter to close...\"; fi' &",
        entry->name, entry->name, entry->pkg, entry->pkg, entry->pkg,
        entry->name, entry->exec, entry->exec, entry->exec,
        entry->icon, entry->category, entry->is_gui, entry->name, entry->category);
    system(cmd);
    g_timeout_add(5000, (GSourceFunc)refresh_ui, NULL);
}

void on_search_changed(GtkEditable *editable, gpointer user_data) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(editable));
    if (!catalog) return;
    for (int i = 0; i < catalog_size; i++) {
        if (strlen(text) == 0 || strcasestr(catalog[i].name, text) || strcasestr(catalog[i].category, text))
            gtk_widget_show(catalog[i].row_widget);
        else
            gtk_widget_hide(catalog[i].row_widget);
    }
}

void populate_list() {
    for (int j = 0; j < catalog_size; j++) {
        // Skip core system tools to prevent accidental breakage and redundancy
        if (strcasestr(catalog[j].pkg, "python") ||
            strcasestr(catalog[j].pkg, "node") ||
            strcasestr(catalog[j].pkg, "git") ||
            strcasestr(catalog[j].pkg, "vim") ||
            strcasestr(catalog[j].pkg, "clang") ||
            strcasestr(catalog[j].pkg, "pkg-config")) {
            continue;
        }

        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        catalog[j].row_widget = row;
        gtk_container_set_border_width(GTK_CONTAINER(row), 12);

        // Advanced Icon Resolution
        char icon_name[128];
        strncpy(icon_name, catalog[j].icon, 127);
        icon_name[127] = '\0';

        // Strip extension if present (e.g. "chrome.png" -> "chrome")
        char *dot = strrchr(icon_name, '.');
        if (dot && (strcmp(dot, ".png") == 0 || strcmp(dot, ".svg") == 0 || strcmp(dot, ".xpm") == 0)) {
            *dot = '\0';
        }

        GtkIconTheme *theme = gtk_icon_theme_get_default();
        GtkWidget *icon = NULL;

        // Try multiple candidates for native icons: listed name, exec name, or package name
        const char *candidates[] = { icon_name, catalog[j].exec, catalog[j].pkg, NULL };
        for (int k = 0; candidates[k] != NULL; k++) {
            if (strlen(candidates[k]) > 0 && gtk_icon_theme_has_icon(theme, candidates[k])) {
                icon = gtk_image_new_from_icon_name(candidates[k], GTK_ICON_SIZE_DIALOG);
                break;
            }
        }

        if (!icon) {
            icon = gtk_image_new_from_icon_name(catalog[j].is_gui ? "application-x-executable" : "utilities-terminal", GTK_ICON_SIZE_DIALOG);
        }

        gtk_image_set_pixel_size(GTK_IMAGE(icon), 48);

        GtkWidget *details = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *name = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(name), g_strdup_printf("<span size='large' weight='bold'>%s</span> <span size='small' alpha='50%%'>[%s]</span>", catalog[j].name, catalog[j].category));
        gtk_label_set_xalign(GTK_LABEL(name), 0);
        GtkWidget *desc = gtk_label_new(catalog[j].desc);
        gtk_label_set_xalign(GTK_LABEL(desc), 0);
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
    refresh_ui();
}

static gboolean on_load_finished(gpointer data) {
    int success = GPOINTER_TO_INT(data);
    gtk_spinner_stop(GTK_SPINNER(widgets.spinner));
    if (success && catalog_size > 0) {
        populate_list();
        gtk_stack_set_visible_child_name(GTK_STACK(widgets.stack), "catalog");
    } else {
        gtk_label_set_text(GTK_LABEL(widgets.loading_label), "Connection Error.\nPlease verify xfce-app-store repo branch.");
    }
    return FALSE;
}

static void* load_catalog_thread(void* data) {
    system("mkdir -p /data/data/com.termux/files/usr/var/lib/termux-pro");
    char sync_cmd[1024];
    // Try main branch first
    snprintf(sync_cmd, sizeof(sync_cmd), "curl -f -L -s -k --connect-timeout 20 --retry 3 -o %s %s", LOCAL_PATH, LIST_URL_MAIN);
    int res = system(sync_cmd);

    // Fallback to master if main fails
    if (res != 0) {
        snprintf(sync_cmd, sizeof(sync_cmd), "curl -f -L -s -k --connect-timeout 20 --retry 3 -o %s %s", LOCAL_PATH, LIST_URL_MASTER);
        res = system(sync_cmd);
    }

    FILE *fp = fopen(LOCAL_PATH, "r");
    if (fp) {
        char line[1024];
        while (fgets(line, sizeof(line), fp)) if(strlen(line) > 5) catalog_size++;
        rewind(fp);
        if (catalog_size > 0) {
            catalog = calloc(catalog_size, sizeof(AppEntry));
            int i = 0;
            while (fgets(line, sizeof(line), fp) && i < catalog_size) {
                char *lptr = line;
                if ((unsigned char)line[0] == 0xEF) lptr += 3; // BOM
                char *token; int field = 0;
                while ((token = strsep(&lptr, "|")) != NULL) {
                    token[strcspn(token, "\r\n")] = 0;
                    if (field == 0) strncpy(catalog[i].icon, token, 127);
                    else if (field == 1) strncpy(catalog[i].name, token, 127);
                    else if (field == 2) strncpy(catalog[i].desc, token, 255);
                    else if (field == 3) strncpy(catalog[i].pkg, token, 511);
                    else if (field == 4) strncpy(catalog[i].exec, token, 127);
                    else if (field == 5) strncpy(catalog[i].category, token, 63);
                    else if (field == 6) catalog[i].is_gui = atoi(token);
                    field++;
                }
                i++;
            }
            fclose(fp);
            g_idle_add(on_load_finished, GINT_TO_POINTER(1));
        } else { fclose(fp); g_idle_add(on_load_finished, GINT_TO_POINTER(0)); }
    } else { g_idle_add(on_load_finished, GINT_TO_POINTER(0)); }
    return NULL;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Force GTK to use the Papirus icon theme
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-icon-theme-name", "Papirus", NULL);

    // Ensure GTK looks in the correct icon directories
    GtkIconTheme *theme = gtk_icon_theme_get_default();
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/icons");
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/icons/Papirus");
    gtk_icon_theme_append_search_path(theme, "/data/data/com.termux/files/usr/share/pixmaps");

    widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets.window), "Termux App Store");
    gtk_window_set_icon_name(GTK_WINDOW(widgets.window), "software-center");
    gtk_window_set_default_size(GTK_WINDOW(widgets.window), 800, 550);
    gtk_window_set_position(GTK_WINDOW(widgets.window), GTK_WIN_POS_CENTER);
    g_signal_connect(widgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(widgets.window), main_vbox);

    GtkWidget *search_bar = gtk_search_bar_new();
    widgets.search_entry = gtk_search_entry_new();
    gtk_container_add(GTK_CONTAINER(search_bar), widgets.search_entry);
    gtk_search_bar_set_search_mode(GTK_SEARCH_BAR(search_bar), TRUE);
    gtk_box_pack_start(GTK_BOX(main_vbox), search_bar, FALSE, FALSE, 5);
    g_signal_connect(widgets.search_entry, "changed", G_CALLBACK(on_search_changed), NULL);

    widgets.stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(widgets.stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
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

    GtkWidget *catalog_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(catalog_vbox), 15);
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
