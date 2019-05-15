#include <QTime>

#include "glwidget.h"
#include "rgl.h"
#include "config.h"
#include "mainwindow.h"
#include "tools.h"

static unsigned DL_Sphere[DL_Sphere_max];

void GLWidget::initializeGL()
{
    GLboolean stereo;
    glGetBooleanv(GL_STEREO, &stereo);

    OpenGlVersion = (char *)glGetString(GL_VERSION);

    //initialization of OpenGL
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // display list for sphere...
    for (int i = 0; i < DL_Sphere_max; i++)
    {
        DL_Sphere[i] = glGenLists(1);
        glNewList(DL_Sphere[i], GL_COMPILE);
        rglDrawSphere(i, 1);
        glEndList();
    }
}


void GLWidget::idPaintGL()
{
    makeCurrent();

    glDrawBuffer(GL_BACK);
    SetColorMode(0);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void GLWidget::paintGL()
{
    if (block_painting) return;

    // openGLErrorTest("paintGL()", __LINE__);

    is_painting = true;

    static long frame_cnt = 1;
    QTime start_time;
    start_time.start();


    GLint x;
    glGetIntegerv(GL_DRAW_BUFFER, &x);
    glDrawBuffer(GL_BACK);
    SetColorMode(0);
    glClearColor(VisualSettings.background_color.r(), VisualSettings.background_color.g(), VisualSettings.background_color.b(), VisualSettings.background_color.a());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    is_painting = false;
}

void GLWidget::openGLErrorTest(QString where, int line)
{
   
}


long GLWidget::findItem(int x, int y)
{
    idPaintGL();

    GLubyte color[4];
    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    return (unsigned(color[0])<<16) + (unsigned(color[1])<<8) + unsigned(color[2]) - 1;
}

void GLWidget::draw_navigator()
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-size().width()/2, size().width()/2, -size().height()/2, size().height()/2, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4fv(VisualSettings.navigator_color.rgba());

    if (mouse_buttons == Qt::LeftButton)
    {
        rglDrawCircle(0, 0, 220);
        glScalef(0.2f, 1, 1);
        rglDrawCircle(0, 0, 200);
        glLineWidth(2);
        rglDrawCircle(0, 0, 200, M_PI, M_PI*2.0f);
        glLineWidth(1);

        glScalef(5, 0.2f, 1);
        rglDrawCircle(0, 0, 200);
        glLineWidth(2);
        rglDrawCircle(0, 0, 200, M_PI*0.5f, M_PI*1.5f);
        glLineWidth(1);
    }
    else if (mouse_buttons == Qt::RightButton)
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2f(-200, 0);
        glVertex2f( 200, 0);
        glVertex2f(0, -200);
        glVertex2f(0, 200);
        glEnd();
        glLineWidth(1);
    }

    glPopAttrib();
}


void GLWidget::user_scene_zoom(QWheelEvent *event)
{
    if (event->delta() < 0)
        VisualSettings.depth += 50;
    else
        VisualSettings.depth -= 50;
}


void GLWidget::scene_move(QMouseEvent *event)
{
    int x, y;
    x = event->pos().x() - size().width()/2;
    y = -(event->pos().y() - size().height()/2);

    mouse_buttons = event->buttons();
    if (event->buttons() & Qt::LeftButton)
    {
        // rotation...
        glMatrixMode(GL_TEXTURE);
        glPushMatrix();
        glLoadMatrixf(VisualSettings.view.matrix);

        if (mouse_press_x*mouse_press_x + mouse_press_y*mouse_press_y > 200*200)
        {
            if (x > y && x < -y)
                glRotatef((x - mouse_last_x)*0.3, VisualSettings.view.matrix[2], VisualSettings.view.matrix[6], VisualSettings.view.matrix[10]);
            else if (x <= y && x >= -y)
                glRotatef((mouse_last_x - x)*0.3, VisualSettings.view.matrix[2], VisualSettings.view.matrix[6], VisualSettings.view.matrix[10]);
            else if (x > y && x > -y)
                glRotatef((y - mouse_last_y)*0.3, VisualSettings.view.matrix[2], VisualSettings.view.matrix[6], VisualSettings.view.matrix[10]);
            else if (x <= y && x <= -y)
                glRotatef((mouse_last_y - y)*0.3, VisualSettings.view.matrix[2], VisualSettings.view.matrix[6], VisualSettings.view.matrix[10]);
        }
        else
        {
            glRotatef(x - mouse_last_x, VisualSettings.view.matrix[1], VisualSettings.view.matrix[5], VisualSettings.view.matrix[9]);
            glRotatef(mouse_last_y - y, VisualSettings.view.matrix[0], VisualSettings.view.matrix[4], VisualSettings.view.matrix[8]);
        }

        glGetFloatv(GL_TEXTURE_MATRIX, VisualSettings.view.matrix);
        glPopMatrix();
    }
    else
    {
     
    }

    mouse_last_x = x;
    mouse_last_y = y;
}


QString GLWidget::getPixel(int x, int y)
{
    GLbyte color[4];
    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    return "Color: " + QString::number(color[0]) + ", " + QString::number(color[1]) + ", " + QString::number(color[2]);
}
