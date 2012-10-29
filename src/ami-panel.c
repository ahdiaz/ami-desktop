/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "ami-desktop.h"
#include "ami-app-menu.h"
#include "ami-session-menu.h"

typedef struct {
    //GdkPixmap *bg_pixmap;
    GtkWidget *window;
    AmiDesktop *desktop;
} AmiPanel;



AmiPanel *ami_panel_new(AmiDesktop *desktop) {

    AmiPanel *panel;

    panel = g_new(AmiPanel, 1);
    panel->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    panel->desktop = desktop;

    return panel;
}

void ami_panel_free(AmiPanel *panel) {
    g_free(panel);
}

void ami_panel_set_background(AmiPanel *panel) {

    GdkPixmap *pixmap;
    GdkPixbuf *pixbuf;
    GtkStyle *style;

    pixbuf = gdk_pixbuf_new_from_file("/common/src/AmiDesktop/ami-desktop/graph/bg_panel_22.png", NULL);
    gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);

    style = gtk_style_copy(gtk_widget_get_style(GTK_WIDGET(panel->window)));
    if (style->bg_pixmap[GTK_STATE_NORMAL]) {
        g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);
    }
    style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
    gtk_widget_set_style (GTK_WIDGET(panel->window), style);

    g_object_unref (pixbuf);
    g_object_unref (pixmap);
    g_object_unref (style);
}

void ami_panel_menu_init(AmiPanel *panel) {

    GtkWidget *menubar;
    GtkWidget *ami_menu;
    GtkWidget *session_menu;
    GtkWidget *item;
    GtkWidget *box;

    box = gtk_hbox_new (FALSE, 3);

    menubar = gtk_menu_bar_new();
    item = gtk_menu_item_new_with_label("Menu");
    ami_menu = ami_app_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), ami_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    gtk_box_pack_start (GTK_BOX (box), menubar, FALSE, FALSE, 10);

    menubar = gtk_menu_bar_new();
    item = gtk_menu_item_new_with_label("Session");
    session_menu = ami_session_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), session_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    gtk_box_pack_end (GTK_BOX (box), menubar, FALSE, FALSE, 10);

    gtk_container_add (GTK_CONTAINER (panel->window), box);
    gtk_widget_queue_draw(GTK_WIDGET(panel->window));
}

void ami_panel_init(AmiPanel *panel) {

    GdkScreen *gscreen;
    gint sw, sh;

    gscreen = gdk_display_get_default_screen(gdk_display_get_default());

    gtk_window_set_screen(GTK_WINDOW(panel->window), gscreen);
    gtk_window_set_title(GTK_WINDOW(panel->window), "Panel");
    gtk_window_set_type_hint(GTK_WINDOW(panel->window), GDK_WINDOW_TYPE_HINT_DOCK);
    gtk_window_set_accept_focus(GTK_WINDOW(panel->window), FALSE);

    sw = gdk_screen_get_width(gscreen);
    sh = 22;

    gtk_widget_set_size_request(GTK_WIDGET(panel->window), sw, sh);
    gtk_window_resize(GTK_WINDOW(panel->window), sw, sh);
    gtk_window_move(GTK_WINDOW(panel->window), 0, 0);
    gtk_window_set_resizable(GTK_WINDOW(panel->window), FALSE);

    ami_panel_set_background(panel);
    ami_panel_menu_init(panel);

    gtk_widget_show_all(panel->window);
}
