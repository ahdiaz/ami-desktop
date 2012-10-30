/**
 * ${license}
 **/

#include <glib.h>
#include "config.h"


void ami_config_init() {

    gchar *config_dir;
    gchar *data_dir;
    GKeyFile *key_file;
    const gchar **dirs;

    //gchar *APP_BASENAME = "amidesktop";
    //gchar *RC_FILE = "amidesktoprc";
    //gchar *RC_GROUP_NAME = "DESKTOP";

    config_dir = g_strconcat(g_get_user_config_dir(), "/amidesktop", NULL);
    data_dir = g_strconcat(g_get_user_data_dir(), "/amidesktop", NULL);

    dirs = g_new (const gchar *, 2);
    dirs[0] = config_dir;
    dirs[1] = NULL;

    key_file = g_key_file_new();
    g_key_file_load_from_dirs(key_file, "amidesktoprc", dirs,
        NULL, G_KEY_FILE_NONE, NULL);

    amiconfig = g_new(AmiConfig, 1);

    amiconfig->config_dir = config_dir;
    amiconfig->data_dir = data_dir;

    amiconfig->wallpaper = g_key_file_get_string(key_file,
        "DESKTOP", "background", NULL);
    amiconfig->wallpaper = g_strconcat(data_dir, "/", amiconfig->wallpaper, NULL);

    amiconfig->bg_panel = g_key_file_get_string(key_file,
        "PANEL", "background", NULL);
    amiconfig->bg_panel = g_strconcat(data_dir, "/", amiconfig->bg_panel, NULL);

    amiconfig->h_panel = g_key_file_get_integer(key_file,
        "PANEL", "height", NULL);

    g_key_file_free(key_file);
}

void ami_config_free() {
    g_free(amiconfig->config_dir);
    g_free(amiconfig->data_dir);
    g_free(amiconfig->wallpaper);
    g_free(amiconfig->bg_panel);
    g_free(amiconfig);
}
