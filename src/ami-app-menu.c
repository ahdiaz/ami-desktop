/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


void ami_app_menu_item_activated(GtkMenuItem *item, gpointer user_data) {

    GAppInfo *app = (GAppInfo*) user_data;
    g_app_info_launch(app, NULL, NULL, NULL);
}

void ami_app_menu_init(GtkWidget *menu) {

    GList *list;
    GList *node;

    list = g_app_info_get_all();

    node = g_list_first(list);

    while (node != NULL) {

        GAppInfo *app = (GAppInfo*)node->data;

        if (g_app_info_should_show(app)) {

            GtkWidget *item = gtk_menu_item_new_with_label(g_app_info_get_display_name(app));
            g_signal_connect(item, "activate", G_CALLBACK (ami_app_menu_item_activated), (gpointer)app);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
        }

        node = g_list_next(node);
    }

    g_list_free(list);
    g_list_free(node);
}

GtkWidget *ami_app_menu_new() {

    GtkWidget *menu;

    menu = gtk_menu_new();
    ami_app_menu_init(menu);
    gtk_widget_show_all(menu);

    return menu;
}

void ami_app_menu_free(GtkWidget *menu) {
    g_object_unref(menu);
}
