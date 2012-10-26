/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>


typedef struct {
    GdkScreen *gscreen;
    //GdkPixmap *bg_pixmap;
    GtkWidget *window;
    GtkWidget *icon_view;
} AmiDesktop;



AmiDesktop *ami_desktop_new(GdkScreen *gscreen) {

    AmiDesktop *desktop;

    g_return_val_if_fail(gscreen, NULL);

    desktop = g_new(AmiDesktop, 1);
    desktop->gscreen = gscreen;
    desktop->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    desktop->icon_view = gtk_icon_view_new();

    return desktop;
}

void ami_desktop_free(AmiDesktop *desktop) {
    g_object_unref(desktop->gscreen);
    g_object_unref(desktop->window);
    g_object_unref(desktop->icon_view);
    g_free(desktop);
}

void ami_desktop_connect_signals(AmiDesktop *desktop) {

    /* Exit when the window is closed */
    g_signal_connect (desktop->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

void ami_desktop_close_button(AmiDesktop *desktop) {

    GtkWidget *box;
    GtkWidget *button;

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 3);
    button = gtk_button_new_with_label("Close");


    //GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file ("/home/ahernandez/ego.png", NULL);
    //GdkPixmap *pixmap;
    //gdk_pixbuf_render_pixmap_and_mask (pixbuf, &pixmap, NULL, 0);
    //gdk_window_set_back_pixmap (GTK_WIDGET(window)->window, pixmap, FALSE);
    //g_object_unref (pixbuf);
    //g_object_unref (pixmap);


    gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
    gtk_container_add (GTK_CONTAINER (desktop->window), box);

    gtk_widget_show_all(box);

    /* Connect signals */
    /* Show open dialog when opening a file */
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

}

void ami_desktop_init(AmiDesktop *desktop) {

    gint sw, sh;

    gtk_window_set_screen(GTK_WINDOW(desktop->window), desktop->gscreen);
    gtk_window_set_title(GTK_WINDOW(desktop->window), "Desktop");
    gtk_window_set_type_hint(GTK_WINDOW(desktop->window), GDK_WINDOW_TYPE_HINT_DESKTOP);
    gtk_window_set_accept_focus(GTK_WINDOW(desktop->window), FALSE);

    sw = gdk_screen_get_width(desktop->gscreen);
    sh = gdk_screen_get_height(desktop->gscreen);

    gtk_widget_set_size_request(GTK_WIDGET(desktop->window), sw, sh);
    gtk_window_fullscreen(GTK_WINDOW(desktop->window));
    //gtk_window_resize(GTK_WINDOW(desktop->window), sw, sh);
    gtk_window_move(GTK_WINDOW(desktop->window), 0, 0);
    gtk_window_set_resizable(GTK_WINDOW(desktop->window), FALSE);

    ami_desktop_connect_signals(desktop);
    ami_desktop_close_button(desktop);

    gtk_widget_show_all(desktop->window);
}
