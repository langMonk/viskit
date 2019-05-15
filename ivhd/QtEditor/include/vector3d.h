#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <stdlib.h>
#include <QString>

#include "consts.h"


class anyVector3d
{
public:
    Real x, y, z;

    anyVector3d(Real _x, Real _y, Real _z): x(_x), y(_y), z(_z) { }
    anyVector3d(): x(0), y(0), z(0) { }
    Real length2() const
    {
        return x*x + y*y + z*z;
    }
    Real length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    void normalize()
    {
        Real l = length();
        if (l > 0)
        {
            l = 1/l;
            x *= l;
            y *= l;
            z *= l;
        }
        else
        {
            set_random(3, 1);
            //            x = 1;
            //            y = z = 0;
        }
    }
    Real &at(int i)
    {
        if (i == 0) return x;
        else if (i == 1) return y;
        else return z;
    }
    void z_zero()
    {
        z = 0;
    }
    anyVector3d operator+(anyVector3d const &v) const
    {
        return anyVector3d(x + v.x, y + v.y, z + v.z);
    }
    void operator+=(anyVector3d const &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    void operator-=(anyVector3d const &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    void set(Real _x = 0, Real _y = 0, Real _z = 0)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    anyVector3d operator-(anyVector3d const &v) const
    {
        return anyVector3d(x - v.x, y - v.y, z - v.z);
    }
    anyVector3d operator*(Real n) const
    {
        return anyVector3d(n*x, n*y, n*z);
    }
    anyVector3d operator*(anyVector3d const &v) const
    {
        return anyVector3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    void operator*=(Real n)
    {
        x *= n;
        y *= n;
        z *= n;
    }
    bool operator==(anyVector3d const &v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    bool operator!=(anyVector3d const &v) const
    {
        return x != v.x || y != v.y || z != v.z;
    }
    bool is_zero() const
    {
        return !x && !y && !z;
    }
    void set_random(int dim, Real length)
    {
        do
        {
            x = 2*(rand()/Real(RAND_MAX)) - 1;
            y = 2*(rand()/Real(RAND_MAX)) - 1;
            if (dim == 2)
                z = 0;
            else
                z = 2*(rand()/Real(RAND_MAX)) - 1;
        }
        while (!x && !y && !z);
        normalize();
        x *= length;
        y *= length;
        z *= length;
    }
    QString toString() const
    {
        return QString("(%1, %2, %3)").arg(x).arg(y).arg(z);
    }
    anyVector3d operator*(float *m) const
    {
        Real v = m[3]*x + m[7]*y + m[11]*z + m[15];
        return anyVector3d(m[0]*x + m[4]*y + m[8]*z + m[12],
                         m[1]*x + m[5]*y + m[9]*z + m[13],
                         m[2]*x + m[6]*y + m[10]*z + m[14])*(1/v);
    }
    Real operator |(anyVector3d const &v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
};

class anyVector2d
{
public:
    Real x, y;

    anyVector2d(Real _x, Real _y): x(_x), y(_y) { }
    anyVector2d(): x(0), y(0) { }
    Real length2() const
    {
        return x*x + y*y;
    }
    Real length() const
    {
        return sqrt(x*x + y*y);
    }
    void normalize()
    {
        Real l = length();
        if (l > 0)
        {
            l = 1/l;
            x *= l;
            y *= l;
        }
        else
            set_random(1);
    }
    Real &at(int i)
    {
        if (i == 0) return x;
        else return y;
    }
    anyVector2d operator+(anyVector2d const &v) const
    {
        return anyVector2d(x + v.x, y + v.y);
    }
    void operator+=(anyVector2d const &v)
    {
        x += v.x;
        y += v.y;
    }
    void operator-=(anyVector2d const &v)
    {
        x -= v.x;
        y -= v.y;
    }
    void set(Real _x = 0, Real _y = 0)
    {
        x = _x;
        y = _y;
    }
    anyVector2d operator-(anyVector2d const &v) const
    {
        return anyVector2d(x - v.x, y - v.y);
    }
    anyVector2d operator*(Real n) const
    {
        return anyVector2d(n*x, n*y);
    }
    void operator*=(Real n)
    {
        x *= n;
        y *= n;
    }
    bool operator==(anyVector2d const &v) const
    {
        return x == v.x && y == v.y;
    }
    bool operator!=(anyVector2d const &v) const
    {
        return x != v.x || y != v.y;
    }
    bool is_zero() const
    {
        return !x && !y;
    }
    void set_random(Real length)
    {
        do
        {
            x = 2*(rand()/Real(RAND_MAX)) - 1;
            y = 2*(rand()/Real(RAND_MAX)) - 1;
        }
        while (!x && !y);
        normalize();
        x *= length;
        y *= length;
    }
    QString toString() const
    {
        return QString("(%1, %2)").arg(x).arg(y);
    }
    Real operator |(anyVector2d const &v) const
    {
        return x*v.x + y*v.y;
    }
};

//void SetDistanceParams(Real power);
Real Distance3D(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2, bool cosine);
Real Distance3D(anyVector3d const &v1, anyVector3d const &v2, bool cosine);
Real Distance2D(anyVector3d const &v1, anyVector3d const &v2, bool cosine);
Real DistanceND(Real *c1, Real *c2, int dim, bool cosine);


#endif // VECTOR3D_H
