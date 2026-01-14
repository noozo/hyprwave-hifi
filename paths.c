#include "paths.h"
#include <stdio.h>

gchar* get_icon_path(const gchar *icon_name) {
    gchar *path = NULL;
    
    // Try 1: Local directory (for development - running ./hyprwave)
    path = g_strdup_printf("icons/%s", icon_name);
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("Icon found (local): %s\n", path);
        return path;
    }
    g_free(path);
    
    // Try 2: User local install (~/.local/share/hyprwave/icons/)
    path = g_build_filename(g_get_user_data_dir(), "hyprwave", "icons", icon_name, NULL);
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("Icon found (user): %s\n", path);
        return path;
    }
    g_free(path);
    
    // Try 3: System install (/usr/share/hyprwave/icons/)
    path = g_strdup_printf("/usr/share/hyprwave/icons/%s", icon_name);
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("Icon found (system): %s\n", path);
        return path;
    }
    g_free(path);
    
    // Fallback: return local path anyway (will show broken icon)
    g_printerr("Warning: Icon not found: %s\n", icon_name);
    return g_strdup_printf("icons/%s", icon_name);
}

gchar* get_style_path(void) {
    gchar *path = NULL;
    
    // Try 1: Local directory
    path = g_strdup("style.css");
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("CSS found (local): %s\n", path);
        return path;
    }
    g_free(path);
    
    // Try 2: User local install
    path = g_build_filename(g_get_user_data_dir(), "hyprwave", "style.css", NULL);
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("CSS found (user): %s\n", path);
        return path;
    }
    g_print("Tried user path: %s (not found)\n", path);
    g_free(path);
    
    // Try 3: System install
    path = g_strdup("/usr/share/hyprwave/style.css");
    if (g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("CSS found (system): %s\n", path);
        return path;
    }
    g_free(path);
    
    // Fallback
    g_printerr("Warning: style.css not found in any location\n");
    g_printerr("User data dir: %s\n", g_get_user_data_dir());
    return g_strdup("style.css");
}

void free_path(gchar *path) {
    g_free(path);
}
