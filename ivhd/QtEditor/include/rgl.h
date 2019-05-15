#ifndef RGL_H
#define RGL_H

#include "vector3d.h"
#include "color.h"


void rglDrawSphere(int ndiv, float radius = 1);
void rglDrawCylinder(int ndiv, float radius1, float radius2);
void rglDrawCone(int ndiv, float radius);
void rglDrawLine(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color, int width = 1);
void rglDrawBlendedLine(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color);
void rglDrawGrilledSquare(anyColor const &color);
void rglDrawGrilledBox(anyVector3d const &p1, anyVector3d const &p2, anyColor const &color);
void rglDrawWiredBox(anyVector3d const &p1, anyVector3d const &p2);
void rglDrawCircle(Real x, Real y, Real r, Real fi1 = 0, Real fi2 = 6.283185307179586476925286766559);
void rglDrawBox(anyVector3d const &p1, anyVector3d const &p2);
float rglDrawLetter(int l, anyVector3d const &p, float size, bool draw);
float rglStringLength(char const *s, float size);
void rglDrawString(char const *s, anyVector3d const &p, float size, float horizontal_align = 0, float vertical_align = 0);
void rglDrawSquareOrtho(int size_x, int size_y, anyVector3d const &p1, anyVector3d const &p2);
void rglDrawStringOrtho(char const *s, anyVector3d const &p, float size, float horizontal_align = 0, float vertical_align = 0);


#endif // RGL_H
