#include <qmath.h>

#include "vector3d.h"


static float DistancePower = 2;


//void SetDistanceParams(float power)
//{
//    DistancePower = power;
//}


float Distance3D(float x1, float y1, float z1, float x2, float y2, float z2, bool cosine)
{
    if (cosine)
    {
        float r = x1*x2 + y1*y2 + z1*z2;
        float r1 = x1*x1 + y1*y1 + z1*z1;
        float r2 = x2*x2 + y2*y2 + z2*z2;
        if (r1 == 0 || r2 == 0)
            return 0;
        return 1 - r/sqrt(r1*r2);
    }
    else
    {
        if (DistancePower == 1)
            return qAbs(x1-x2) + qAbs(y1-y2) + qAbs(z1-z2);
        else if (DistancePower == 2)
            return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
        else
            return
                    qPow((qPow(qAbs(x1 - x2), DistancePower)
                          + qPow(qAbs(y1 - y2), DistancePower)
                          + qPow(qAbs(z1 - z2), DistancePower)), 1.0/DistancePower);
    }
}


float Distance3D(anyVector3d const &v1, anyVector3d const &v2, bool cosine)
{
    if (cosine)
    {
        float r = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
        float r1 = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z;
        float r2 = v2.x*v2.x + v2.y*v2.y + v2.z*v2.z;
        if (r1 == 0 || r2 == 0)
            return 0;
        return 1 - r/sqrt(r1*r2);
    }
    else
    {
        if (DistancePower == 1)
            return qAbs(v1.x - v2.x) + qAbs(v1.y - v2.y) + qAbs(v1.z - v2.z);
        else if (DistancePower == 2)
            return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y) + (v1.z - v2.z)*(v1.z - v2.z));
        else
            return
                    qPow((qPow(qAbs(v1.x - v2.x), DistancePower)
                          + qPow(qAbs(v1.y - v2.y), DistancePower)
                          + qPow(qAbs(v1.z - v2.z), DistancePower)), 1.0/DistancePower);
    }
}


float Distance2D(anyVector3d const &v1, anyVector3d const &v2, bool cosine)
{
    if (cosine)
    {
        float r = v1.x*v2.x + v1.y*v2.y;
        float r1 = v1.x*v1.x + v1.y*v1.y;
        float r2 = v2.x*v2.x + v2.y*v2.y;
        if (r1 == 0 || r2 == 0)
            return 0;
        return 1 - r/sqrt(r1*r2);
    }
    else
    {
        if (DistancePower == 1)
            return qAbs(v1.x - v2.x) + qAbs(v1.y - v2.y);
        else if (DistancePower == 2)
            return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
        else
            return qPow((qPow(qAbs(v1.x - v2.x), DistancePower) + qPow(qAbs(v1.y - v2.y), DistancePower)), 1.0/DistancePower);
    }
}


float DistanceND(float *c1, float *c2, int dim, bool cosine)
{
    if (cosine)
    {
        float r, r1, r2;
        r = r1 = r2 = 0;
        for (int i = 0; i < dim; i++)
        {
            r += c1[i]*c2[i];
            r1 += c1[i]*c1[i];
            r2 += c2[i]*c2[i];
        }
        if (r1 == 0 || r2 == 0)
            return 0;
        return 1 - r/sqrt(r1*r2);
    }
    else
    {
        float sum = 0;

        if (DistancePower == 1)
        {
            for (int i = 0; i < dim; i++)
                sum += qAbs(c1[i] - c2[i]);
            return sum;
        }
        else if (DistancePower == 2)
        {
            for (int i = 0; i < dim; i++)
                sum += (c1[i] - c2[i])*(c1[i] - c2[i]);
            return sqrt(sum);
        }
        else
        {
            for (int i = 0; i < dim; i++)
                sum += qPow(qAbs(c1[i] - c2[i]), DistancePower);
            return qPow(sum, 1.0/DistancePower);
        }
    }
}
