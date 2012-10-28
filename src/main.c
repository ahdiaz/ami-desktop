/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "ami-desktop.h"
#include "ami-panel.h"


int main(int argc, char *argv[]) {

    GdkScreen *gscreen;
    AmiDesktop *desktop;
    AmiPanel *panel;

    gtk_init(&argc, &argv);

    gscreen = gdk_display_get_default_screen(gdk_display_get_default());

    desktop = ami_desktop_new(gscreen);
    ami_desktop_init(desktop);
    panel = ami_panel_new(desktop);
    ami_panel_init(panel);

    gtk_main();

    ami_panel_free(panel);
    ami_desktop_free(desktop);

    return 0;
}
