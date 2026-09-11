#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char icon[64];
    char name[64];
    char desc[128];
    char pkg[256];
    char exec[64];
    char category[32];
    int is_gui;
    GtkWidget *action_button;
    GtkWidget *update_button;
    GtkWidget *uninstall_button;
    GtkWidget *status_label;
} AppEntry;

AppEntry *catalog = NULL;
int catalog_size = 0;
const char *LIST_URL = "https://raw.githubusercontent.com/gulbalamesiyev/xfce-app-store/main/apps.list";
const char *LOCAL_PATH = "/data/data/com.termux/files/usr/var/lib/termux-pro/apps.list";

int is_installed(const char *exec) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "command -v %s >/dev/null 2>&1", exec);
    return system(cmd) == 0;
}

void refresh_status() {
    for (int i = 0; i < catalog_size; i++) {
        if (is_installed(catalog[i].exec)) {
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

void on_action_clicked(GtkWidget *widget, gpointer data) {
    AppEntry *entry = (AppEntry*)data;
    char cmd[4096];
    if (is_installed(entry->exec)) {
        if (entry->is_gui) snprintf(cmd, sizeof(cmd), "DISPLAY=:1 nohup %s >/dev/null 2>&1 &", entry->exec);
        else snprintf(cmd, sizeof(cmd), "DISPLAY=:1 xfce4-terminal -e %s &", entry->exec);
        system(cmd);
    } else {
        const char *install_cmd = strstr(entry->pkg, " ") ? entry->pkg : g_strdup_printf("pkg install -y %s", entry->pkg);
        snprintf(cmd, sizeof(cmd), "DISPLAY=:1 xfce4-terminal --title=\"Installing %s\" --command=\"bash -c '%s; sleep 3'\"", entry->name, install_cmd);
        system(cmd);
        g_timeout_add(4000, (GSourceFunc)refresh_status, NULL);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Sync list from GitHub
    system("mkdir -p /data/data/com.termux/files/usr/var/lib/termux-pro");
    char sync_cmd[512];
    snprintf(sync_cmd, sizeof(sync_cmd), "curl -s -o %s %s", LOCAL_PATH, LIST_URL);
    system(sync_cmd);

    // Parse list
    FILE *fp = fopen(LOCAL_PATH, "r");
    if (!fp) return 1;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) catalog_size++;
    rewind(fp);
    catalog = malloc(sizeof(AppEntry) * catalog_size);
    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        AppEntry *e = &catalog[i++];
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d", e->icon, e->name, e->desc, e->pkg, e->exec, e->category, &e->is_gui);
    }
    fclose(fp);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cloud App Store");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *header = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(header), "<span size='x-large' weight='bold'>Termux Cloud Catalog</span>");
    gtk_box_pack_start(GTK_BOX(vbox), header, FALSE, FALSE, 10);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    GtkWidget *list = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(scroll), list);

    for (int j = 0; j < catalog_size; j++) {
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
        gtk_container_set_border_width(GTK_CONTAINER(row), 10);

        GtkWidget *icon = gtk_image_new_from_icon_name(catalog[j].icon, GTK_ICON_SIZE_DIALOG);
        GtkIconTheme *theme = gtk_icon_theme_get_default();
        if (!gtk_icon_theme_has_icon(theme, catalog[j].icon))
            gtk_image_set_from_icon_name(GTK_IMAGE(icon), catalog[j].is_gui ? "application-x-executable" : "utilities-terminal", GTK_ICON_SIZE_DIALOG);

        GtkWidget *details = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *name = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(name), g_strdup_printf("<b>%s</b>", catalog[j].name));
        gtk_label_set_xalign(GTK_LABEL(name), 0);
        GtkWidget *desc = gtk_label_new(catalog[j].desc);
        gtk_label_set_xalign(GTK_LABEL(desc), 0);
        gtk_box_pack_start(GTK_BOX(details), name, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(details), desc, FALSE, FALSE, 0);

        catalog[j].status_label = gtk_label_new("...");
        catalog[j].action_button = gtk_button_new_with_label("...");
        g_signal_connect(catalog[j].action_button, "clicked", G_CALLBACK(on_action_clicked), &catalog[j]);

        catalog[j].update_button = gtk_button_new_with_label("UP");
        catalog[j].uninstall_button = gtk_button_new_with_label("DEL");

        gtk_box_pack_start(GTK_BOX(row), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row), details, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].status_label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].action_button, FALSE, FALSE, 0);

        gtk_list_box_insert(GTK_LIST_BOX(list), row, -1);
    }

    gtk_widget_show_all(window);
    refresh_status();
    gtk_main();
    return 0;
}
