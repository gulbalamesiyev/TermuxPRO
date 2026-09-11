#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    const char *icon;
    const char *name;
    const char *desc;
    const char *pkg;
    const char *exec; // Executable name for checking installation and launching
    const char *category;
    int is_gui;       // 1 for GUI apps, 0 for CLI apps
    GtkWidget *action_button;
    GtkWidget *update_button;
    GtkWidget *uninstall_button;
    GtkWidget *status_label;
} AppEntry;

typedef struct {
    GtkWidget *window;
    GtkWidget *stack;
    GtkWidget *bootstrap_box;
    GtkWidget *catalog_box;
    GtkWidget *progress_bar;
    GtkWidget *bootstrap_status;
    GtkWidget *finish_button;
} AppWidgets;

AppEntry catalog[] = {
    {"firefox", "Firefox", "Web Browser", "firefox", "firefox", "Recommended", 1},
    {"tor-browser", "Tor Browser", "Anonymity & Privacy", "tor-browser", "tor-browser", "Security", 1},
    {"mousepad", "Mousepad", "Text Editor", "mousepad", "mousepad", "Recommended", 1},
    {"ristretto", "Ristretto", "Image Viewer", "ristretto", "ristretto", "Recommended", 1},
    {"xarchiver", "Xarchiver", "Archive Manager", "xarchiver", "xarchiver", "Recommended", 1},
    {"geany", "Geany", "Lightweight IDE", "geany", "geany", "Development", 1},
    {"parole", "Parole", "Media Player", "parole", "parole", "Multimedia", 1},
    {"vlc", "VLC Player", "Universal Media Player", "vlc", "vlc", "Multimedia", 1},
    {"inkscape", "Inkscape", "Vector Graphics Editor", "inkscape", "inkscape", "Graphics", 1},
    {"gimp", "GIMP", "Image Manipulation Program", "gimp", "gimp", "Graphics", 1},
    {"libreoffice", "LibreOffice", "Full Office Suite", "libreoffice", "libreoffice", "Office", 1},
    {"transmission-gtk", "Transmission", "BitTorrent Client", "transmission-gtk", "transmission-gtk", "Network", 1},
    {"audacity", "Audacity", "Audio Editor", "audacity", "audacity", "Multimedia", 1},
    {"hexchat", "HexChat", "IRC Client", "hexchat", "hexchat", "Network", 1},
    {"wireshark-gtk", "Wireshark", "Network Analyzer", "wireshark-gtk", "wireshark-gtk", "Security", 1},
    {"openvpn", "OpenVPN", "Secure VPN Tunneling", "openvpn", "openvpn", "Security", 0},
    {"ollama", "Ollama", "Run AI models locally", "ollama", "ollama", "AI", 0},
    {"claude-cli", "Claude CLI", "Anthropic's Terminal Agent", "npm install -g @anthropic-ai/claude-code", "claude", "AI", 0},
    {"python-ai", "AI Toolkit", "Python AI libraries (PyTorch/TF)", "python", "python", "AI", 0},
    {"htop", "Htop", "Interactive Process Viewer", "htop", "htop", "System", 0}
};

int is_installed(AppEntry *entry) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "command -v %s >/dev/null 2>&1", entry->exec);
    return system(cmd) == 0;
}

void refresh_status() {
    for (int i = 0; i < catalog_size; i++) {
        if (is_installed(&catalog[i])) {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "OPEN");
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Installed");
            gtk_widget_show(catalog[i].update_button);
            gtk_widget_show(catalog[i].uninstall_button);
        } else {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "INSTALL");
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Available");
            gtk_widget_hide(catalog[i].update_button);
            gtk_widget_hide(catalog[i].uninstall_button);
        }
    }
}

static gboolean delayed_refresh(gpointer data) {
    refresh_status();
    return FALSE;
}

void on_uninstall_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "DISPLAY=:1 xfce4-terminal --title=\"Uninstalling %s\" --command=\"bash -c ' "
        "echo Uninstalling %s...; "
        "pkg uninstall -y %s; "
        "echo Cleaning up desktop shortcuts...; "
        "rm -f \\$HOME/Desktop/*%s*.desktop; "
        "echo Finished. Closing in 2 seconds...; sleep 2; '\"",
        entry->name, entry->name, entry->pkg, entry->exec);
    system(cmd);
    g_timeout_add(2500, delayed_refresh, NULL);
}

void on_update_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "DISPLAY=:1 xfce4-terminal --title=\"Updating %s\" --command=\"bash -c ' "
        "echo Updating %s...; "
        "pkg upgrade -y %s; "
        "echo Finished. Closing in 2 seconds...; sleep 2; '\"",
        entry->name, entry->name, entry->pkg);
    system(cmd);
}

void on_action_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    if (is_installed(entry)) {
        char cmd[512];
        if (entry->is_gui) {
            snprintf(cmd, sizeof(cmd), "DISPLAY=:1 nohup %s >/dev/null 2>&1 &", entry->exec);
        } else {
            snprintf(cmd, sizeof(cmd), "DISPLAY=:1 xfce4-terminal -e %s &", entry->exec);
        }
        system(cmd);
    } else {
        char cmd[4096];
        const char *install_cmd;

        // Handle special install commands like npm
        if (strstr(entry->pkg, "npm") != NULL) {
            install_cmd = entry->pkg;
        } else {
            static char pkg_buf[512];
            snprintf(pkg_buf, sizeof(pkg_buf), "pkg install -y %s", entry->pkg);
            install_cmd = pkg_buf;
        }

        snprintf(cmd, sizeof(cmd),
            "DISPLAY=:1 xfce4-terminal --title=\"Installing %s\" --command=\"bash -c ' "
            "export PREFIX=/data/data/com.termux/files/usr; "
            "export PATH=\\$PREFIX/bin:\\$PATH; "
            "echo ========================================; "
            "echo Installing %s...; "
            "echo ========================================; "
            "%s; "
            "RET=\\$?; "
            "if [ \"\\$RET\" -eq 0 ]; then "
            "  echo; echo Done. Searching for desktop file...; "
            "  FILE=\\$(find \\$PREFIX/share/applications -name \"*%s*.desktop\" 2>/dev/null | head -n 1); "
            "  if [ -z \"\\$FILE\" ] && [ \"%d\" -eq 0 ]; then "
            "    echo No system desktop file found for CLI app. Generating one...; "
            "    FILE=\"\\$PREFIX/share/applications/%s-custom.desktop\"; "
            "    printf \"[Desktop Entry]\\nVersion=1.0\\nType=Application\\nName=%s\\nExec=xfce4-terminal -e %s\\nIcon=%s\\nTerminal=false\\nCategories=Development;\\n\" > \"\\$FILE\"; "
            "  fi; "
            "  if [ -n \"\\$FILE\" ]; then "
            "    cp \"\\$FILE\" \"\\$HOME/Desktop/\"; "
            "    BN=\\$(basename \"\\$FILE\"); "
            "    TARGET=\"\\$HOME/Desktop/\\$BN\"; "
            "    chmod 755 \"\\$TARGET\"; "
            "    if command -v gio >/dev/null; then "
            "      SHA=\\$(sha256sum \"\\$TARGET\"); SHA=\\${SHA%%%% *}; "
            "      gio set -t string \"\\$TARGET\" metadata::xfce-exe-checksum \"\\$SHA\" 2>/dev/null; "
            "    fi; "
            "    echo Shortcut created on Desktop: \\$BN; "
            "  else "
            "    echo No desktop file found, but package is installed.; "
            "  fi; "
            "  echo; echo Finished. Closing in 3 seconds...; sleep 3; "
            "else "
            "  echo; echo FAILED with exit code \\$RET; "
            "  echo Press ENTER to close this window; read; "
            "fi'\"", entry->name, entry->name, install_cmd, entry->exec, entry->is_gui, entry->exec, entry->name, entry->exec, entry->icon);

        system(cmd);
        g_timeout_add(3000, delayed_refresh, NULL);
    }
}

void show_catalog(AppWidgets *widgets) {
    gtk_stack_set_visible_child_full(GTK_STACK(widgets->stack), "catalog", GTK_STACK_TRANSITION_TYPE_SLIDE_UP);
    refresh_status();
}

static gboolean bootstrap_update(gpointer data) {
    struct { AppWidgets *w; double f; } *ud = data;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ud->w->progress_bar), ud->f);

    char buf[64];
    snprintf(buf, sizeof(buf), "Bootstrapping App Store... %d%%", (int)(ud->f * 100));
    gtk_label_set_text(GTK_LABEL(ud->w->bootstrap_status), buf);

    if (ud->f >= 1.0) {
        gtk_label_set_text(GTK_LABEL(ud->w->bootstrap_status), "Ready to explore!");
        gtk_widget_set_sensitive(ud->w->finish_button, TRUE);
        system("mkdir -p $PREFIX/var/lib/termux-pro && touch $PREFIX/var/lib/termux-pro/app-store-provisioned");
    }

    free(ud);
    return FALSE;
}

static void* bootstrap_thread(void* data) {
    AppWidgets *widgets = (AppWidgets*)data;
    for (int i = 0; i <= 100; i += 10) {
        usleep(150000);
        struct { AppWidgets *w; double f; } *ud = malloc(sizeof(*ud));
        ud->w = widgets;
        ud->f = i / 100.0;
        g_idle_add(bootstrap_update, ud);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    AppWidgets *widgets = g_new0(AppWidgets, 1);
    widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "App Store");
    gtk_window_set_icon_name(GTK_WINDOW(widgets->window), "mintinstall");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 800, 500);
    gtk_window_set_position(GTK_WINDOW(widgets->window), GTK_WIN_POS_CENTER);
    g_signal_connect(widgets->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    widgets->stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(widgets->stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(widgets->stack), 400);
    gtk_container_add(GTK_CONTAINER(widgets->window), widgets->stack);

    // Bootstrap View
    widgets->bootstrap_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_set_border_width(GTK_CONTAINER(widgets->bootstrap_box), 40);
    widgets->bootstrap_status = gtk_label_new("Initializing...");
    widgets->progress_bar = gtk_progress_bar_new();
    widgets->finish_button = gtk_button_new_with_label("Enter Catalog");
    gtk_widget_set_sensitive(widgets->finish_button, FALSE);
    g_signal_connect_swapped(widgets->finish_button, "clicked", G_CALLBACK(show_catalog), widgets);

    gtk_box_pack_start(GTK_BOX(widgets->bootstrap_box), widgets->bootstrap_status, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widgets->bootstrap_box), widgets->progress_bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widgets->bootstrap_box), widgets->finish_button, FALSE, FALSE, 0);
    gtk_stack_add_named(GTK_STACK(widgets->stack), widgets->bootstrap_box, "bootstrap");

    // Catalog View
    widgets->catalog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *header = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(header), "<span size='x-large' weight='bold'>Termux App Catalog</span>");
    gtk_box_pack_start(GTK_BOX(widgets->catalog_box), header, FALSE, FALSE, 10);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(widgets->catalog_box), scrolled, TRUE, TRUE, 0);

    GtkWidget *list = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list), GTK_SELECTION_NONE);
    gtk_container_add(GTK_CONTAINER(scrolled), list);

    for (int i = 0; i < catalog_size; i++) {
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        gtk_container_set_border_width(GTK_CONTAINER(row), 12);

        const char *icon_name = catalog[i].icon;
        GtkWidget *icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG);

        // Requirement: Show default icons even before installation
        GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
        if (!gtk_icon_theme_has_icon(icon_theme, icon_name)) {
            const char *fallback = catalog[i].is_gui ? "application-x-executable" : "utilities-terminal";
            gtk_image_set_from_icon_name(GTK_IMAGE(icon), fallback, GTK_ICON_SIZE_DIALOG);
        }
        GtkWidget *details = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *name = gtk_label_new(NULL);
        gtk_label_set_xalign(GTK_LABEL(name), 0);
        gtk_label_set_markup(GTK_LABEL(name), g_strdup_printf("<b>%s</b>", catalog[i].name));
        GtkWidget *desc = gtk_label_new(catalog[i].desc);
        gtk_label_set_xalign(GTK_LABEL(desc), 0);

        GtkStyleContext *context = gtk_widget_get_style_context(desc);
        gtk_style_context_add_class(context, "dim-label");

        gtk_box_pack_start(GTK_BOX(details), name, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(details), desc, FALSE, FALSE, 0);

        catalog[i].status_label = gtk_label_new("Checking...");
        catalog[i].action_button = gtk_button_new_with_label("...");
        gtk_widget_set_size_request(catalog[i].action_button, 80, -1);
        g_signal_connect(catalog[i].action_button, "clicked", G_CALLBACK(on_action_clicked), &catalog[i]);

        catalog[i].update_button = gtk_button_new_with_label("UPDATE");
        gtk_widget_set_size_request(catalog[i].update_button, 80, -1);
        g_signal_connect(catalog[i].update_button, "clicked", G_CALLBACK(on_update_clicked), &catalog[i]);

        catalog[i].uninstall_button = gtk_button_new_with_label("UNINSTALL");
        gtk_widget_set_size_request(catalog[i].uninstall_button, 80, -1);
        g_signal_connect(catalog[i].uninstall_button, "clicked", G_CALLBACK(on_uninstall_clicked), &catalog[i]);

        gtk_box_pack_start(GTK_BOX(row), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row), details, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), catalog[i].status_label, FALSE, FALSE, 10);

        GtkWidget *btn_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(btn_group), catalog[i].action_button, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(btn_group), catalog[i].update_button, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(btn_group), catalog[i].uninstall_button, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row), btn_group, FALSE, FALSE, 0);

        gtk_list_box_insert(GTK_LIST_BOX(list), row, -1);
    }
    gtk_stack_add_named(GTK_STACK(widgets->stack), widgets->catalog_box, "catalog");

    gtk_widget_show_all(widgets->window);

    if (access("/data/data/com.termux/files/usr/var/lib/termux-pro/app-store-provisioned", F_OK) == 0) {
        show_catalog(widgets);
    } else {
        pthread_t tid;
        pthread_create(&tid, NULL, bootstrap_thread, widgets);
    }

    gtk_main();
    return 0;
}
