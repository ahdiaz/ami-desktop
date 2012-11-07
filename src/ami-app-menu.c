/**
 * ${license}
 **/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gio/gdesktopappinfo.h>


typedef struct {
    GAppInfo *app_info;
    // Free with g_strfreev(categories)
    gchar **categories;
} AppMenuItem;


gchar **get_app_categories(GAppInfo *app_info, GList **unique_categories) {

    int i;
    const char *s_categories;
    gchar *category;
    gchar **categories;
    GDesktopAppInfo *dapp;

    dapp = g_desktop_app_info_new(g_app_info_get_id(app_info));
    if (dapp) {

        s_categories = g_desktop_app_info_get_categories(dapp);
        categories = g_strsplit(s_categories, ";", 0);

        i = 0;
        category = categories[i];
        while (category != NULL) {

            GList *exists = g_list_find(*unique_categories, category);
            if (exists == NULL) {
                *unique_categories = g_list_prepend(*unique_categories, category);
            }

            category = categories[++i];
        }

        g_object_unref(dapp);
    }

    return categories;
}

void ami_app_menu_item_activated(GtkMenuItem *item, gpointer user_data) {

    GAppInfo *app = (GAppInfo*) user_data;
    g_app_info_launch(app, NULL, NULL, NULL);
}

void ami_app_menu_init(GtkWidget *menu) {

    GList *app_list = NULL;
    GList *node = NULL;
    GList *app_items = NULL;
    GList *unique_categories = NULL;
    AppMenuItem *app_item;
    GAppInfo *app_info;

    app_list = g_app_info_get_all();
    node = g_list_first(app_list);

    // Iterate all the AppInfo structures and find out its categories.
    // The categories are stored in the structure categories.
    while (node != NULL) {

        app_info = (GAppInfo*) node->data;

        if (g_app_info_should_show(app_info)) {

            app_item = g_new(AppMenuItem, 1);

            app_item->app_info = app_info;
            app_item->categories = get_app_categories(app_info, &unique_categories);

            // Faster than append
            app_items = g_list_prepend(app_items, (gpointer)app_item);
            //g_object_unref(item);
        }

        node = g_list_next(node);
    }

    g_list_free(app_list);
    g_list_free(node);


    int i;
    gchar *category;
    GHashTable *categories_menu_items;

    i = 0;
    g_list_free(unique_categories);
    unique_categories = g_list_prepend(NULL, "System");
    unique_categories = g_list_prepend(unique_categories, "Office");
    unique_categories = g_list_prepend(unique_categories, "Multimedia");
    unique_categories = g_list_prepend(unique_categories, "Network");
    unique_categories = g_list_prepend(unique_categories, "Graphics");
    unique_categories = g_list_prepend(unique_categories, "Development");
    unique_categories = g_list_prepend(unique_categories, "Application");
    unique_categories = g_list_prepend(unique_categories, "Utility");
    unique_categories = g_list_prepend(unique_categories, "Settings");

    node = g_list_first(unique_categories);
    categories_menu_items = g_hash_table_new(g_str_hash, g_str_equal);

    // For each unique category create a menu item and
    // store it in an associative array (HashMap)
    while (node != NULL) {

        category = (gchar*) node->data;

        if (!g_hash_table_contains(categories_menu_items, (gconstpointer) category)) {
            GtkWidget *m_item = gtk_menu_item_new_with_label(category);
            GtkWidget *m_item_submenu = gtk_menu_new();
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(m_item), m_item_submenu);
            g_hash_table_insert(categories_menu_items, (gpointer) category, m_item);
        }

        node = g_list_next(node);
    }


    node = g_list_first(app_items);

    while (node != NULL) {

        app_item = (AppMenuItem*) node->data;

        i = 0;
        category = (gchar*)app_item->categories[i];

        while (category != NULL) {


            GtkWidget *m_item = g_hash_table_lookup(categories_menu_items, (gconstpointer) category);
            if (m_item != NULL) {

                GtkWidget *m_item_submenu = gtk_menu_item_get_submenu(GTK_MENU_ITEM(m_item));
                GtkWidget *m_item_app = gtk_menu_item_new_with_label(g_app_info_get_display_name(app_item->app_info));

                g_signal_connect(m_item_app, "activate", G_CALLBACK (ami_app_menu_item_activated), (gpointer)app_item->app_info);
                gtk_menu_shell_append(GTK_MENU_SHELL(m_item_submenu), m_item_app);
            }
            category = app_item->categories[++i];
        }

        node = g_list_next(node);
    }


    app_items = g_hash_table_get_keys(categories_menu_items);
    node = g_list_first(app_items);

    while (node != NULL) {

        GtkWidget *m_item = g_hash_table_lookup(categories_menu_items, node->data);
        if (m_item != NULL) {
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), m_item);
        }

        node = g_list_next(node);
    }


    g_free(category);
    g_hash_table_unref(categories_menu_items);
    g_list_free(app_items);
    g_list_free(node);
    g_list_free(unique_categories);
}

GtkWidget *ami_app_menu_new() {

    GtkWidget *menu;

    menu = gtk_menu_new();
    ami_app_menu_init(menu);
    gtk_widget_show_all(menu);

    return menu;
}

void ami_app_menu_free(GtkWidget *menu) {
    g_object_unref(menu);
}
