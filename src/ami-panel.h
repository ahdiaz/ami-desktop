/**
 * ${license}
 **/

#include "ami-desktop.h"

typedef struct AmiPanel AmiPanel;

AmiPanel *ami_panel_new(AmiDesktop *desktop);

void ami_panel_free(AmiPanel *panel);

void ami_panel_init(AmiPanel *panel);

void ami_panel_set_background(AmiPanel *panel);
