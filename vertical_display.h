#ifndef VERTICAL_DISPLAY_H
#define VERTICAL_DISPLAY_H

#include <gtk/gtk.h>
#include <gio/gio.h>


typedef enum {
    DISPLAY_MODE_TIME,
    DISPLAY_MODE_SCROLL_TRACK,
    DISPLAY_MODE_STATUS_PAUSED,
    DISPLAY_MODE_STATUS_PLAYING,
    DISPLAY_MODE_STATUS_SKIPPING
} DisplayMode;

typedef struct {
    GtkWidget *container;
    GtkWidget *label;
    
    gboolean is_showing;
    
    gchar *current_title;
    gchar *current_artist;
    gint64 current_position;
    gint64 track_length;
    
    guint scroll_timer;
    guint update_timer;
    guint status_animation_timer;
    
    gint scroll_index;
    gdouble fade_opacity;
    
    DisplayMode current_mode;      // NEW
    gboolean is_paused;            // NEW
    gint animation_frame;          // NEW
} VerticalDisplayState;


// Initialize vertical display
VerticalDisplayState* vertical_display_init();

// Add these function declarations
void vertical_display_set_paused(VerticalDisplayState *state, gboolean paused);
void vertical_display_notify_skip(VerticalDisplayState *state);

// Show/hide display
void vertical_display_show(VerticalDisplayState *state);
void vertical_display_hide(VerticalDisplayState *state);

// Update track info (triggers scroll)
void vertical_display_update_track(VerticalDisplayState *state,
                                   const gchar *title,
                                   const gchar *artist);

// Update position (for timer)
void vertical_display_update_position(VerticalDisplayState *state,
                                      gint64 position,
                                      gint64 length);
                                      
void vertical_display_set_paused(VerticalDisplayState *state, gboolean paused);
void vertical_display_notify_skip(VerticalDisplayState *state);

// Cleanup
void vertical_display_cleanup(VerticalDisplayState *state);

#endif // VERTICAL_DISPLAY_H
