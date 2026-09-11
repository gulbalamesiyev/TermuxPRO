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
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "OPEN");
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Installed");
        } else {
            gtk_button_set_label(GTK_BUTTON(catalog[i].action_button), "INSTALL");
            gtk_label_set_text(GTK_LABEL(catalog[i].status_label), "Available");
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
        snprintf(cmd, sizeof(cmd),
            "DISPLAY=:1 xfce4-terminal --title=\"Installing %s\" --command=\"bash -c ' "
            "echo Installing %s...; "
            "if echo \\\"%s\\\" | grep -q \\\"npm\\\"; then %s; else pkg install -y %s; fi; "
            "RET=\\$?; "
            "if [ \\$RET -eq 0 ]; then "
            "  echo Creating Shortcut...; "
            "  FILE=\\$HOME/Desktop/%s.desktop; "
            "  EXEC_PATH=\\\"%s\\\"; "
            "  if ! echo \\\"\\$EXEC_PATH\\\" | grep -q \\\"/\\\"; then EXEC_PATH=\\$(command -v %s); fi; "
            "  [ -z \\\"\\$EXEC_PATH\\\" ] && EXEC_PATH=%s; "
            "  ICON_NAME=%s; "
            "  [ \\\"%d\\\" -eq 0 ] && EXEC_CMD=\\\"xfce4-terminal -e \\$EXEC_PATH\\\" || EXEC_CMD=\\\"\\$EXEC_PATH\\\"; "
            "  printf \\\"[Desktop Entry]\\\\nVersion=1.0\\\\nType=Application\\\\nName=%s\\\\nExec=\\$EXEC_CMD\\\\nIcon=\\$ICON_NAME\\\\nTerminal=false\\\\nCategories=%s;\\\\n\\\" > \\\"\\$FILE\\\"; "
            "  chmod 755 \\\"\\$FILE\\\"; "
            "  if command -v gio >/dev/null; then gio set -t string \\\"\\$FILE\\\" metadata::xfce-exe-checksum \\\"\\$(sha256sum \\\"\\$FILE\\\" | cut -d \\' \\' -f 1)\\\" 2>/dev/null; fi; "
            "  echo Done. Shortcut created.; sleep 2; "
            "else echo FAILED; read; fi'\"",
            entry->name, entry->name, entry->pkg, entry->pkg, entry->pkg,
            entry->name, entry->exec, entry->exec, entry->exec,
            entry->is_gui, entry->name, entry->icon, entry->category);
        system(cmd);
        g_timeout_add(5000, (GSourceFunc)refresh_ui, NULL);
    }
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
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        catalog[j].row_widget = row;
        gtk_container_set_border_width(GTK_CONTAINER(row), 12);

        GtkWidget *icon = gtk_image_new_from_icon_name(catalog[j].icon, GTK_ICON_SIZE_DIALOG);
        GtkIconTheme *theme = gtk_icon_theme_get_default();
        if (!gtk_icon_theme_has_icon(theme, catalog[j].icon))
            gtk_image_set_from_icon_name(GTK_IMAGE(icon), catalog[j].is_gui ? "application-x-executable" : "utilities-terminal", GTK_ICON_SIZE_DIALOG);

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

        gtk_box_pack_start(GTK_BOX(row), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row), details, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].status_label, FALSE, FALSE, 10);
        gtk_box_pack_start(GTK_BOX(row), catalog[j].action_button, FALSE, FALSE, 0);

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
    widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets.window), "Termux App Store");
    gtk_window_set_icon_from_file(GTK_WINDOW(widgets.window), "/data/data/com.termux/files/usr/share/icons/termux-pro-store.png", NULL);
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
