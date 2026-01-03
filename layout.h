#ifndef LAYOUT_H
#define LAYOUT_H

#include <gtk/gtk.h>
#include <gtk4-layer-shell.h>

// Edge configuration
typedef enum {
    EDGE_RIGHT,
    EDGE_LEFT,
    EDGE_TOP,
    EDGE_BOTTOM
} EdgePosition;

// Layout configuration
typedef struct {
    EdgePosition edge;
    int margin;
    gboolean is_vertical;
} LayoutConfig;

// Widget structure for expanded section
typedef struct {
    GtkWidget *album_cover;
    GtkWidget *source_label;
    GtkWidget *track_title;
    GtkWidget *artist_label;
    GtkWidget *progress_bar;
    GtkWidget *time_remaining;
} ExpandedWidgets;

// Function declarations
LayoutConfig* layout_load_config(void);
void layout_free_config(LayoutConfig *config);

void layout_setup_window_anchors(GtkWindow *window, LayoutConfig *config);

GtkWidget* layout_create_control_bar(LayoutConfig *config,
                                      GtkWidget **prev_btn,
                                      GtkWidget **play_btn,
                                      GtkWidget **next_btn,
                                      GtkWidget **expand_btn);

GtkWidget* layout_create_expanded_section(LayoutConfig *config,
                                           ExpandedWidgets *widgets);

GtkWidget* layout_create_main_container(LayoutConfig *config,
                                         GtkWidget *control_bar,
                                         GtkWidget *revealer);

const gchar* layout_get_expand_icon(LayoutConfig *config, gboolean is_expanded);

GtkRevealerTransitionType layout_get_transition_type(LayoutConfig *config);

#endif // LAYOUT_H
