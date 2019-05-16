#include <QTime>

#include "glwidget.h"
#include "rgl.h"
#include "config.h"
#include "tools.h"
#include "mainwindow.h"

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

	drawParticleSystem(MainWindow::instance()->interactiveVizualization()->particleSystem(), 0, false);

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

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	mouse_last_x = mouse_press_x = event->pos().x() - size().width() / 2;
	mouse_last_y = mouse_press_y = -(event->pos().y() - size().height() / 2);

	if ((event->buttons() & Qt::LeftButton) && (event->modifiers() & Qt::ShiftModifier))
	{
		long i = findItem(event->pos().x(), size().height() - event->pos().y());
		marked_on_press = true;
		draw_navi = false;
		MainWindow::instance()->repaint3D();
	}
	else
	{
		mouse_buttons = event->buttons();
		marked_on_press = false;
		draw_navi = true;
		MainWindow::instance()->repaint3D();
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	bool do_repaint = false;
	if (draw_navi)
	{
		draw_navi = false;
		do_repaint = true;
	}
	mouse_buttons = 0;

	if (!marked_on_press && (mouse_press_x == event->pos().x() - size().width() / 2) && mouse_press_y == -(event->pos().y() - size().height() / 2))
	{
		long i = findItem(event->pos().x(), size().height() - event->pos().y());
		do_repaint = true;
	}

	if (do_repaint)
		MainWindow::instance()->repaint3D();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
	int x = event->pos().x() - size().width() / 2;
	int y = -(event->pos().y() - size().height() / 2);
	mouse_buttons = event->buttons();

	if (!(event->modifiers() & Qt::ShiftModifier))
		scene_move(event);

	mouse_last_x = x;
	mouse_last_y = y;

	MainWindow::instance()->repaint3D();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
	user_scene_zoom(event);
	MainWindow::instance()->repaint3D();
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

void GLWidget::drawParticleSystem(ivhd::IParticleSystem& universe, float eye_shift, bool store_ids)
{
	QSize qs = size();
    glViewport(0, 0, qs.width(), qs.height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,
                   float(qs.width())/float(qs.height()),
                   1,
                   (VisualSettings.eye.z + 500)*1.5 + VisualSettings.depth); // http://www.opengl.org/sdk/docs/man/xhtml/gluPerspective.xml

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(VisualSettings.eye.x + eye_shift, VisualSettings.eye.y, VisualSettings.eye.z + VisualSettings.depth,
              0, 0, VisualSettings.depth,
              0, 1, 0);  // http://www.opengl.org/sdk/docs/man/xhtml/gluLookAt.xml

    // light...
    GLfloat ambientLight[] = { 0, 0, 0, 1.0 };
    GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 500, 500, 1500, 1.0f };

    if (!store_ids)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
        glDisable(GL_LIGHTING);

    glDisable(GL_CLIP_PLANE0);
    glEnable(GL_CULL_FACE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMultMatrixf(VisualSettings.view.matrix);

    float scale;
	auto mainWindow = MainWindow::instance();

    int sphere_points = DL_Sphere[mainWindow->getSpherePrec(true)];
    int sphere_clusters = DL_Sphere[mainWindow->getSpherePrec(false)];

    int coloring = mainWindow->getItemColoring();

    int step = mainWindow->get10th() ? 10 : 1;

	auto dataPoints = mainWindow->interactiveVizualization()->particleSystem().dataPoints();

	for (auto dataPoint : dataPoints)
	{
		int i = 0;
		if (dataPoint.visible && !dataPoint.removed)
		{
			glPushMatrix();

			// color...
			if (store_ids)
			{
				GLubyte cc[4];
				unsigned u = i + 1;
				cc[0] = (u >> 16) & 0xff;
				cc[1] = (u >> 8) & 0xff;
				cc[2] = u & 0xff;
				cc[3] = 255;
				glColor4ubv(cc);
			}
			else if (dataPoint.marked)
			{
				glColor4fv(VisualSettings.selected_color.rgba());
			}
			else if (dataPoint.frozen)
				glColor4fv(VisualSettings.frozen_color.rgba());
			else
				glColor4fv(VisualSettings.item_color.rgba());

			glTranslatef(dataPoint.pos.x, dataPoint.pos.y, dataPoint.pos.z);
		
			scale = 10 * mainWindow->getViewScale() / 1000;
			glScalef(dataPoint.size * scale, dataPoint.size * scale, dataPoint.size * scale);
			glCallList(sphere_points);
		
			glPopMatrix();
		}
		i++;
	}

    if (!store_ids)
    {
        if (draw_navi) draw_navigator();
    }
}

QString GLWidget::getPixel(int x, int y)
{
    GLbyte color[4];
    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    return "Color: " + QString::number(color[0]) + ", " + QString::number(color[1]) + ", " + QString::number(color[2]);
}
