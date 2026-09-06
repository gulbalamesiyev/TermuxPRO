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
    const char *category;
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
    {"firefox", "Firefox", "Web Browser", "firefox", "Recommended"},
    {"mousepad", "Mousepad", "Text Editor", "mousepad", "Recommended"},
    {"ristretto", "Ristretto", "Image Viewer", "ristretto", "Recommended"},
    {"xarchiver", "Xarchiver", "Archive Manager", "xarchiver", "Recommended"},
    {"geany", "Geany", "Lightweight IDE", "geany", "Development"},
    {"parole", "Parole", "Media Player", "parole", "Multimedia"},
    {"gvim", "Vim", "Advanced Editor", "vim", "Development"},
    {"git", "Git", "Version Control", "git", "Development"},
    {"python", "Python", "Programming Language", "python", "Development"},
    {"nodejs", "Node.js", "JS Runtime", "nodejs", "Development"}
};

const int catalog_size = sizeof(catalog) / sizeof(AppEntry);

int is_installed(const char *pkg) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "command -v %s >/dev/null 2>&1", pkg);
    return system(cmd) == 0;
}

void refresh_status() {
    for (int i = 0; i < catalog_size; i++) {
        if (is_installed(catalog[i].pkg)) {
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
        entry->name, entry->name, entry->pkg, entry->pkg);
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
    if (is_installed(entry->pkg)) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "DISPLAY=:1 nohup %s >/dev/null 2>&1 &", entry->pkg);
        system(cmd);
    } else {
        char cmd[2048];
        // Requirement: Open CLI terminal, install, then auto-trust launcher
        // Using --command instead of -e for better reliability in some XFCE versions
        snprintf(cmd, sizeof(cmd),
            "DISPLAY=:1 xfce4-terminal --title=\"Installing %s\" --command=\"bash -c ' "
            "export PREFIX=/data/data/com.termux/files/usr; "
            "export PATH=\\$PREFIX/bin:\\$PATH; "
            "echo ========================================; "
            "echo Installing %s...; "
            "echo ========================================; "
            "pkg install -y %s; "
            "RET=\\$?; "
            "if [ \"\\$RET\" -eq 0 ]; then "
            "  echo; echo Done. Searching for desktop file...; "
            "  FILE=\\$(find \\$PREFIX/share/applications -name \"*%s*.desktop\" 2>/dev/null | head -n 1); "
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
            "fi'\"", entry->name, entry->name, entry->pkg, entry->pkg);

        system(cmd);
        // Refresh after a small delay to allow installation to start/finish
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
    gtk_label_set_markup(GTK_LABEL(header), "<span size='x-large' weight='bold'>Termux Pro App Catalog</span>");
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

        // Icon handling with fallback
        const char *icon_name = catalog[i].icon;
        GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
        if (!gtk_icon_theme_has_icon(icon_theme, icon_name)) {
            icon_name = "application-x-executable"; // Standard generic icon
        }

        GtkWidget *icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG);
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
