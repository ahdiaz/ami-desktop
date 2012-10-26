/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "ami-desktop.h"


int main(int argc, char *argv[]) {

    GdkScreen *gscreen;
    AmiDesktop *desktop;

    gtk_init(&argc, &argv);

    gscreen = gdk_display_get_default_screen(gdk_display_get_default());
    desktop = ami_desktop_new(gscreen);

    ami_desktop_init(desktop);

    gtk_main();

    ami_desktop_free(desktop);

    return 0;
}
