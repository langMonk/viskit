#include "config.h"

anyVisualSettings VisualSettings;


anyVisualSettings::anyVisualSettings()
{
    background_color.set(0.0f, 0.0f, 0.0f, 1.0f);
    item_color.set(0.8f, 1.0f, 1.0f, 1.0f);
    cluster_color.set(0.7f, 1.0f, 0.7f, 1.0f);
    selected_color.set(1.0f, 1.0f, 0.0f, 2.0f);
    connection_color.set(1.0f, 1.0f, 0.0f, 1.0f);
    connection_alpha = 0.2f;
    connection_width = 1;
    frozen_color.set(1.0f, 1.0f, 1.0f, 2.0f);
    navigator_color.set(1.0f, 0.5f, 0.0f, 0.5f);
    boundingBox_color.set(1.0f, 1.0f, 0.0f, 0.5f);
    eye.set(0.0f, 0.0f, -1000.0f);
    depth = 0.0f;
    view.identity();
}
