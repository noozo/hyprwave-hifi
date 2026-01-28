#ifndef PATHS_H
#define PATHS_H

#include <glib.h>

/**
 * Volume control method configuration.
 * Determines how HyprWave controls player volume.
 */
typedef enum {
    VOLUME_METHOD_AUTO,      // Try PipeWire first, fall back to MPRIS
    VOLUME_METHOD_PIPEWIRE,  // PipeWire sink-input only (fails for network players)
    VOLUME_METHOD_MPRIS      // MPRIS Volume property only (fails for Chromium/Roon)
} VolumeMethod;

// Get the volume control method from config file
// Returns VOLUME_METHOD_AUTO if not configured
VolumeMethod get_config_volume_method(void);

// Get the path to an icon file
// Tries in order: ./icons/, ~/.local/share/hyprwave/icons/, /usr/share/hyprwave/icons/
gchar* get_icon_path(const gchar *icon_name);

// Get the path to style.css
// Tries in order: ./style.css, ~/.local/share/hyprwave/style.css, /usr/share/hyprwave/style.css
gchar* get_style_path(void);

// Get the path to a theme CSS file (e.g., themes/dark.css)
// Returns NULL for "light" theme (uses base styles only)
gchar* get_theme_path(const gchar *theme);

// Get the theme name from config file
// Returns "light" if not configured
gchar* get_config_theme(void);

// Free path string
void free_path(gchar *path);

#endif // PATHS_H
