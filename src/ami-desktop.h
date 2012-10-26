/**
 * ${license}
 **/


typedef struct AmiDesktop AmiDesktop;

AmiDesktop *ami_desktop_new(GdkScreen *gscreen);

void ami_desktop_free(AmiDesktop *desktop);

void ami_desktop_init(AmiDesktop *desktop);

void ami_desktop_set_background(AmiDesktop *desktop);
