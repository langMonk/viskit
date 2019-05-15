#include <QGLWidget>
#include <math.h>
#include <stdio.h>

#include "consts.h"
#include "vector3d.h"
#include "rgl.h"


// sphere...
static GLfloat sphere_vert[12][3] =
{
    {-.525731112119133606f, 0.0f, .850650808352039932f}, {.525731112119133606f, 0.0f, .850650808352039932f}, {-.525731112119133606f, 0.0f, -.850650808352039932f},
    {.525731112119133606f, 0.0f, -.850650808352039932f}, {0.0f, .850650808352039932f, .525731112119133606f}, {0.0f, .850650808352039932f, -.525731112119133606f},
    {0.0f, -.850650808352039932f, .525731112119133606f}, {0.0f, -.850650808352039932f, -.525731112119133606f}, {.850650808352039932f, .525731112119133606f, 0.0f},
    {-.850650808352039932f, .525731112119133606f, 0.0f}, {.850650808352039932f, -.525731112119133606f, 0.0f}, {-.850650808352039932f, -.525731112119133606f, 0.0f}
};

static GLuint sphere_triangles[20][3] =
{
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };


static
void sphere_normalize(GLfloat *a)
{
    GLfloat d=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    a[0]/=d; a[1]/=d; a[2]/=d;
}


static
void sphere_draw_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int div, float r)
{
    if (div<=0)
    {
        glNormal3fv(a); glVertex3f(a[0]*r, a[1]*r, a[2]*r);
        glNormal3fv(b); glVertex3f(b[0]*r, b[1]*r, b[2]*r);
        glNormal3fv(c); glVertex3f(c[0]*r, c[1]*r, c[2]*r);
    }
    else
    {
        GLfloat ab[3], ac[3], bc[3];
        for (int i=0;i<3;i++)
        {
            ab[i]=(a[i]+b[i])/2;
            ac[i]=(a[i]+c[i])/2;
            bc[i]=(b[i]+c[i])/2;
        }
        sphere_normalize(ab); sphere_normalize(ac); sphere_normalize(bc);
        sphere_draw_triangle(a, ab, ac, div-1, r);
        sphere_draw_triangle(b, bc, ab, div-1, r);
        sphere_draw_triangle(c, ac, bc, div-1, r);
        sphere_draw_triangle(ab, bc, ac, div-1, r);
    }
}


void rglDrawSphere(int ndiv, float radius)
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 20; i++)
        sphere_draw_triangle(sphere_vert[sphere_triangles[i][0]], sphere_vert[sphere_triangles[i][2]], sphere_vert[sphere_triangles[i][1]], ndiv, radius);
    glEnd();
}


void rglDrawCylinder(int ndiv, float radius1, float radius2)
{
    glBegin(GL_QUAD_STRIP);
        float s, c;
        for (int i = 0; i <= ndiv; i++)
        {
            s = sin(i*2*M_PI/ndiv);
            c = cos(i*2*M_PI/ndiv);
            glNormal3f(s, c, 0);
            glVertex3f(radius1*s, radius1*c, 0);
            glNormal3f(s, c, 0);
            glVertex3f(radius2*s, radius2*c, 1);
        }

    glEnd();
}


void rglDrawCone(int ndiv, float radius)
{
    float a;
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 1);
        for (int i = ndiv; i >= 0; i--)
        {
            a = i*2*M_PI/ndiv;
            glVertex3f(radius*sin(a), radius*cos(a), 0);
        }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 0);
        for (int i = 0; i <= ndiv; i++)
        {
            a = i*2*M_PI/ndiv;
            glVertex3f(radius*sin(a), radius*cos(a), 0);
        }
    glEnd();
}


void rglDrawBlendedLine(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color)
{
    anyVector3d d = (p2 - p1)*0.02f;
    glBegin(GL_LINES);
        anyVector3d p3 = p1;
        for (int i = 0; i < 10; i++)
        {
            glColor4f(color.r(), color.g(), color.b(), color.a()*(10 - i)/10.0);
            glVertex3f(p3.x, p3.y, p3.z);
            p3 += d;
            glVertex3f(p3.x, p3.y, p3.z);
        }
        p3 = p2;
        for (int i = 0; i < 10; i++)
        {
            glColor4f(color.r(), color.g(), color.b(), color.a()*(10 - i)/10.0);
            glVertex3f(p3.x, p3.y, p3.z);
            p3 -= d;
            glVertex3f(p3.x, p3.y, p3.z);
        }
    glEnd();
}


void rglDrawLine(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color, int width)
{
    glLineWidth(width);
    glBegin(GL_LINES);
      glColor4f(color.r(), color.g(), color.b(), color.a());
      glVertex3f(p1.x, p1.y, p1.z);
      glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
    glLineWidth(1);
}


void rglDrawGrilledSquare(anyColor const &color)
{
    glNormal3f(0, 0, -1);
    for (int i = 1; i < 10; i++)
    {
        rglDrawBlendedLine(anyVector3d(-0.5 + i*0.1, -0.5, 0), anyVector3d(-0.5 + i*0.1,  0.5, 0), color);
        rglDrawBlendedLine(anyVector3d(-0.5, -0.5 + i*0.1, 0), anyVector3d( 0.5, -0.5 + i*0.1, 0), color);
    }
}


void rglDrawGrilledBox(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color)
{
    int lighting;
    glGetIntegerv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);
    anyVector3d m = (p1 + p2)*0.5;

    glColor4fv(color.rgba());
    glBegin(GL_LINES);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p1.z);

        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p1.z);

        glVertex3f(p2.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p1.z);

        glVertex3f(p1.x, p2.y, p1.z);
        glVertex3f(p1.x, p1.y, p1.z);


        glVertex3f(p1.x, p1.y, p2.z);
        glVertex3f(p2.x, p1.y, p2.z);

        glVertex3f(p2.x, p1.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);

        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p1.x, p2.y, p2.z);

        glVertex3f(p1.x, p2.y, p2.z);
        glVertex3f(p1.x, p1.y, p2.z);


        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p1.x, p1.y, p2.z);

        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p2.z);

        glVertex3f(p2.x, p2.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);

        glVertex3f(p1.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p2.z);
    glEnd();


    glPushMatrix();
        glTranslatef(m.x, m.y, p1.z);
        glScalef(p2.x - p1.x, p2.y - p1.y, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(m.x, m.y, p2.z);
        glRotatef(180, 0, 1, 0);
        glScalef(p2.x - p1.x, p2.y - p1.y, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(p1.x, m.y, m.z);
        glRotatef(90, 0, 1, 0);
        glScalef(p2.z - p1.z, p2.y - p1.y, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(p2.x, m.y, m.z);
        glRotatef(270, 0, 1, 0);
        glScalef(p2.z - p1.z, p2.y - p1.y, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(m.x, p1.y, m.z);
        glRotatef(270, 1, 0, 0);
        glScalef(p2.x - p1.x, p2.z - p1.z, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(m.x, p2.y, m.z);
        glRotatef(90, 1, 0, 0);
        glScalef(p2.x - p1.x, p2.z - p1.z, 1);
        rglDrawGrilledSquare(color);
    glPopMatrix();

    if (lighting)
        glDisable(GL_LIGHTING);
}


void rglDrawWiredBox(anyVector3d const &p1, anyVector3d const &p2)
{
    int lighting;
    glGetIntegerv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p1.z);

        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p1.z);

        glVertex3f(p2.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p1.z);

        glVertex3f(p1.x, p2.y, p1.z);
        glVertex3f(p1.x, p1.y, p1.z);


        glVertex3f(p1.x, p1.y, p2.z);
        glVertex3f(p2.x, p1.y, p2.z);

        glVertex3f(p2.x, p1.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);

        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p1.x, p2.y, p2.z);

        glVertex3f(p1.x, p2.y, p2.z);
        glVertex3f(p1.x, p1.y, p2.z);


        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p1.x, p1.y, p2.z);

        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p2.z);

        glVertex3f(p2.x, p2.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);

        glVertex3f(p1.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p2.z);
    glEnd();

    if (lighting)
        glDisable(GL_LIGHTING);
}


void rglDrawCircle(Real x, Real y, Real r, Real fi1, Real fi2)
{
    glBegin(GL_LINES);
    Real dfi = (fi2 - fi1)/80;
    for (Real fi = fi1; fi <= fi2; fi += dfi)
    {
        glVertex2f(x + r*sin(fi), y + r*cos(fi));
        glVertex2f(x + r*sin(fi + dfi), y + r*cos(fi + dfi));
    }
    glEnd();
}


void rglDrawBox(anyVector3d const &p1, anyVector3d const &p2)
 {
  glBegin(GL_QUADS);

    glNormal3f(0, 0, -1);
    glVertex3f(p1.x, p2.y, p1.z);
    glVertex3f(p2.x, p2.y, p1.z);
    glVertex3f(p2.x, p1.y, p1.z);
    glVertex3f(p1.x, p1.y, p1.z);

    glNormal3f(-1, 0, 0);
    glVertex3f(p1.x, p1.y, p2.z);
    glVertex3f(p1.x, p2.y, p2.z);
    glVertex3f(p1.x, p2.y, p1.z);
    glVertex3f(p1.x, p1.y, p1.z);

    glNormal3f(0, -1, 0);
    glVertex3f(p2.x, p1.y, p1.z);
    glVertex3f(p2.x, p1.y, p2.z);
    glVertex3f(p1.x, p1.y, p2.z);
    glVertex3f(p1.x, p1.y, p1.z);

    glNormal3f(0, 0, 1);
    glVertex3f(p1.x, p2.y, p2.z);
    glVertex3f(p1.x, p1.y, p2.z);
    glVertex3f(p2.x, p1.y, p2.z);
    glVertex3f(p2.x, p2.y, p2.z);

    glNormal3f(1, 0, 0);
    glVertex3f(p2.x, p1.y, p2.z);
    glVertex3f(p2.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);

    glNormal3f(0, 1, 0);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p2.x, p2.y, p1.z);
    glVertex3f(p1.x, p2.y, p1.z);
    glVertex3f(p1.x, p2.y, p2.z);

  glEnd();
 }


struct anyLetter
{
    int l;         ///< letter ascii code
    char m[65];    ///< matrix 8x8
};

#include "letters.h"


float rglDrawLetter(int l, anyVector3d const &p, float size, bool draw)
{
    if (l == ' ') return 6;

    for (int i = 0; rglLetter[i].l; i++)
        if (rglLetter[i].l == l)
        {
        int w = 0;
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if (rglLetter[i].m[j + 8*k] == '@')
                {
                    if (j > w) w = j;
                    if (draw)
                    {
                        glBegin(GL_QUADS);
                            glVertex3f(p.x + j*size, p.y - k*size, p.z);
                            glVertex3f(p.x + j*size - size, p.y - k*size, p.z);
                            glVertex3f(p.x + j*size - size, p.y - k*size - size, p.z);
                            glVertex3f(p.x + j*size, p.y - k*size - size, p.z);

                            glVertex3f(p.x + j*size, p.y - k*size - size, p.z);
                            glVertex3f(p.x + j*size - size, p.y - k*size - size, p.z);
                            glVertex3f(p.x + j*size - size, p.y - k*size, p.z);
                            glVertex3f(p.x + j*size, p.y - k*size, p.z);
                        glEnd();
                    }
                }
        return w*size;
    }
    return -2;
}


float rglStringLength(char const *s, float size)
{
    float w = 0;
    for (int i = 0; s[i]; i++)
        w += rglDrawLetter(s[i], anyVector3d(0, 0, 0), size, false) + size*2;
    return w - size*2;
}


void rglDrawString(char const *s, anyVector3d const &p, float size, float horizontal_align, float vertical_align)
{
    anyVector3d shift(0, 0, 0);

    if (horizontal_align != 0)
    {
        shift.x = -rglStringLength(s, size)*horizontal_align;
    }
    shift.y = size*7*vertical_align;

    float w = 0;
    anyVector3d pc = p + shift;
    for (int i = 0; s[i]; i++)
    {
        w = rglDrawLetter(s[i], pc, size, true) + size*2;
        pc.x += w;
    }
}


void rglDrawSquareOrtho(int size_x, int size_y, anyVector3d const &p1, anyVector3d const &p2)
{
    GLfloat pm[16];
    glGetFloatv(GL_PROJECTION_MATRIX, pm);

    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, size_x, 0, size_y, 0, -1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor4f(1, 0.5, 0, 1);
    glBegin(GL_LINE_LOOP);
       glVertex3f(p1.x, p1.y, p1.z);
       glVertex3f(p2.x, p1.y, p1.z);
       glVertex3f(p2.x, p2.y, p1.z);
       glVertex3f(p1.x, p2.y, p1.z);
    glEnd();

    rglDrawString("ABC", p2, 2);

    glEnable(GL_LIGHTING);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(pm);

    glMatrixMode(GL_MODELVIEW);
}


void rglDrawStringOrtho(char const *s, anyVector3d const &p, float size, float horizontal_align, float vertical_align)
{
    // get feedback position...
    GLfloat feedBuffer[4];
    glFeedbackBuffer(4, GL_3D, feedBuffer);
    glRenderMode(GL_FEEDBACK);

    glBegin(GL_POINTS);
        glVertex3f(p.x, p.y, p.z);
    glEnd();
    if (glRenderMode(GL_RENDER) != 4)
        return; // p is invisible

    // store projection matrix...
    GLfloat pm[16];
    glGetFloatv(GL_PROJECTION_MATRIX, pm);

    // set ortho projection...
    glMatrixMode(GL_PROJECTION);
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    glLoadIdentity();
    glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], 0, -1);

    int lighting;
    glGetIntegerv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // draw string...
    rglDrawString(s, anyVector3d(feedBuffer[1], feedBuffer[2], feedBuffer[3]), size, horizontal_align, vertical_align);

    glPopMatrix();

    // restore projection matrix...
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(pm);
    glMatrixMode(GL_MODELVIEW);
    if (lighting)
        glEnable(GL_LIGHTING);

//    rglDrawSquareOrtho(size().width(), size().height(),
//                       anyVector3d(feedBuffer[1] - 10, feedBuffer[2] - 10, feedBuffer[3]),
//                       anyVector3d(feedBuffer[1] + 10, feedBuffer[2] + 10, feedBuffer[3]));
}

