/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


void ami_session_menu_item_activated(GtkMenuItem *item, gpointer user_data) {

}

void ami_session_menu_init(GtkWidget *menu) {

    GtkWidget *item;

    item = gtk_menu_item_new_with_label("Logout");
    g_signal_connect(item, "activate", G_CALLBACK (gtk_main_quit), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
}

GtkWidget *ami_session_menu_new() {

    GtkWidget *menu;

    menu = gtk_menu_new();
    ami_session_menu_init(menu);
    gtk_widget_show_all(menu);

    return menu;
}

void ami_session_menu_free(GtkWidget *menu) {
    g_object_unref(menu);
}
