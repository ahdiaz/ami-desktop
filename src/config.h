/**
 * ${license}
 **/

#include <glib.h>

typedef struct {
    gchar *config_dir;
    gchar *data_dir;
    gchar *wallpaper;
    gchar *bg_panel;
    gint h_panel;
} AmiConfig;

AmiConfig *amiconfig;

void ami_config_init();

void ami_config_free();
