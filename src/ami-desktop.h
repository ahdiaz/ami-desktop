/**
 * ${license}
 **/

#include <gdk/gdkx.h>
#include <gtk/gtk.h>

typedef struct AmiDesktop AmiDesktop;

AmiDesktop *ami_desktop_new(GdkScreen *gscreen);

void ami_desktop_free(AmiDesktop *desktop);

void ami_desktop_init(AmiDesktop *desktop);
