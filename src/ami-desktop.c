/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
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
    g_free(desktop);
}

void ami_desktop_connect_signals(AmiDesktop *desktop) {

    /* Exit when the window is closed */
    g_signal_connect (desktop->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

void ami_desktop_set_background(AmiDesktop *desktop) {

    GdkPixmap *pixmap;
    GdkPixbuf *pixbuf;
    GtkStyle *style;

    pixbuf = gdk_pixbuf_new_from_file("/home/ahernandez/ego.png", NULL);
    gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);

    style = gtk_style_copy(gtk_widget_get_style(GTK_WIDGET(desktop->window)));
    if (style->bg_pixmap[GTK_STATE_NORMAL]) {
        g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);
    }
    style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
    gtk_widget_set_style (GTK_WIDGET(desktop->window), style);

    g_object_unref (pixbuf);
    g_object_unref (pixmap);
    g_object_unref (style);
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
    gtk_window_resize(GTK_WINDOW(desktop->window), sw, sh);
    gtk_window_move(GTK_WINDOW(desktop->window), 0, 0);
    gtk_window_set_resizable(GTK_WINDOW(desktop->window), FALSE);

    ami_desktop_connect_signals(desktop);
    ami_desktop_set_background(desktop);

    gtk_widget_show_all(desktop->window);
    gtk_widget_queue_draw(GTK_WIDGET(desktop->window));

    gtk_window_set_decorated(GTK_WINDOW(desktop->window), FALSE);
}
