#ifndef CONFIG_H
#define CONFIG_H

#include "color.h"
#include "vector3d.h"
#include "transform.h"

class anyVisualSettings
{
public:
    // view...
    anyVector3d eye;
    Real depth;
    anyTransform view;

    // colors...
    anyColor background_color;
    anyColor navigator_color;
    anyColor boundingBox_color;
    anyColor item_color;
    anyColor cluster_color;
    anyColor selected_color;
    anyColor connection_color;
    float    connection_alpha;
    int      connection_width;
    anyColor frozen_color;

    anyVisualSettings();
};

extern anyVisualSettings VisualSettings;

#endif // CONFIG_H
