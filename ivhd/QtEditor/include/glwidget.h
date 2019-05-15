#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <Windows.h> // vc++ needs that
#include "gl\GL.h"
#include <gl\GLU.h> // apt-get install libgl1-mesa-dev libglu1-mesa-dev

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QMouseEvent>

const int DL_Sphere_max = 6;

class GLWidget: public QOpenGLWidget
{
public:
    int mouse_last_x;
    int mouse_last_y;
    int mouse_press_x;
    int mouse_press_y;
    int mouse_buttons;
    bool marked_on_press;
    bool draw_navi;

    bool block_painting;
    bool is_painting;

    GLuint doc_texture;
    bool doc_texture_loaded;

    GLWidget(QWidget *parent): QOpenGLWidget(parent), mouse_buttons(0), draw_navi(false), block_painting(false), is_painting(false)
    {  }

    void setAA(int aa)
    {
        QSurfaceFormat sfm = QSurfaceFormat::defaultFormat();
        sfm.setSamples(aa*aa);
        setFormat(sfm);
    }

    QString getPixel(int x, int y);
    void idPaintGL();
    long findItem(int x, int y);
    QString OpenGlVersion;

protected:
    void initializeGL();
    void paintGL();

    void openGLErrorTest(QString where, int line);

    void draw_navigator();
    void scene_move(QMouseEvent *event);
    void user_scene_zoom(QWheelEvent *event);

    void mousePressEvent(QMouseEvent *event)
    {
      
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        
    }

    void mouseMoveEvent(QMouseEvent *event)
    {

    }

    void wheelEvent(QWheelEvent *event)
    {

    }
};

#endif // GLWIDGET_H
