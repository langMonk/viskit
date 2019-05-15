#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QString>

#include "vector3d.h"

class anyTransform
{
public:
    float matrix[16];
    /*
      OpenGL order:
      0  4  8 12
      1  5  9 13
      2  6 10 14
      3  7 11 15
    */

    anyTransform()
    {
        identity();
    }

    anyTransform(float t0, float t1, float t2, float t3, float t4, float t5, float t6, float t7, float t8, float t9, float t10, float t11, float t12, float t13, float t14, float t15)
    {
        matrix[0] = t0;
        matrix[1] = t1;
        matrix[2] = t2;
        matrix[3] = t3;
        matrix[4] = t4;
        matrix[5] = t5;
        matrix[6] = t6;
        matrix[7] = t7;
        matrix[8] = t8;
        matrix[9] = t9;
        matrix[10] = t10;
        matrix[11] = t11;
        matrix[12] = t12;
        matrix[13] = t13;
        matrix[14] = t14;
        matrix[15] = t15;
    }

    void identity()
    {
        for (int i = 0; i < 16; i++)
            matrix[i] = 0;
        matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;
    }
    void zero()
    {
        for (int i = 0; i < 16; i++)
            matrix[i] = 0;
    }
    float &at(int i, int j)
    {
        return matrix[i + 4*j];
    }
    void rotation_x(float fi)
    {
        float sfi = sin(fi);
        float cfi = cos(fi);
        identity();
        matrix[5] = cfi;
        matrix[9] = sfi;
        matrix[6] = -sfi;
        matrix[10] = cfi;
    }

    void rotation_y(float fi)
    {
        float sfi = sin(fi);
        float cfi = cos(fi);
        identity();
        matrix[0] = cfi;
        matrix[8] = sfi;
        matrix[2] = -sfi;
        matrix[10] = cfi;
    }

    void rotation_z(float fi)
    {
        float sfi = sin(fi);
        float cfi = cos(fi);
        identity();
        matrix[0] = cfi;
        matrix[4] = -sfi;
        matrix[1] = sfi;
        matrix[5] = cfi;
    }
    void translation(anyVector3d const &d)
    {
        identity();
        matrix[12] = d.x;
        matrix[13] = d.y;
        matrix[14] = d.z;
    }
    void scale(anyVector3d const &d)
    {
        identity();
        matrix[0] = d.x;
        matrix[5] = d.y;
        matrix[10] = d.z;
    }
    void rotate(anyVector3d const &v1, anyVector3d const &v2, anyVector3d const &v3);

    anyVector3d operator*(anyVector3d const &v) const
    {
        return anyVector3d(matrix[0]*v.x + matrix[4]*v.y + matrix[8]*v.z  + matrix[12],
                           matrix[1]*v.x + matrix[5]*v.y + matrix[9]*v.z  + matrix[13],
                           matrix[2]*v.x + matrix[6]*v.y + matrix[10]*v.z + matrix[14]);
    }
    anyTransform operator*(Real x) const
    {
        return anyTransform(matrix[0]*x, matrix[1]*x, matrix[2]*x, matrix[3]*x,
                            matrix[4]*x, matrix[5]*x, matrix[6]*x, matrix[7]*x,
                            matrix[8]*x, matrix[9]*x, matrix[10]*x, matrix[11]*x,
                            matrix[12]*x, matrix[13]*x, matrix[14]*x, matrix[15]*x);
    }
    anyVector3d operator*(anyVector3d v)
    {
        anyVector3d r;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                r.at(i) += matrix[i*4 + j]*v.at(j);

        return r;
    }

    anyTransform operator+(anyTransform const &t) const
    {
        return anyTransform(matrix[0]+t.matrix[0], matrix[1]+t.matrix[1], matrix[2]+t.matrix[2], matrix[3]+t.matrix[3],
                            matrix[4]+t.matrix[4], matrix[5]+t.matrix[5], matrix[6]+t.matrix[6], matrix[7]+t.matrix[7],
                            matrix[8]+t.matrix[8], matrix[9]+t.matrix[9], matrix[10]+t.matrix[10], matrix[11]+t.matrix[11],
                            matrix[12]+t.matrix[12], matrix[13]+t.matrix[13], matrix[14]+t.matrix[14], matrix[15]+t.matrix[15]);
    }
    anyTransform operator-(anyTransform const &t) const
    {
        return anyTransform(matrix[0]-t.matrix[0], matrix[1]-t.matrix[1], matrix[2]-t.matrix[2], matrix[3]-t.matrix[3],
                            matrix[4]-t.matrix[4], matrix[5]-t.matrix[5], matrix[6]-t.matrix[6], matrix[7]-t.matrix[7],
                            matrix[8]-t.matrix[8], matrix[9]-t.matrix[9], matrix[10]-t.matrix[10], matrix[11]-t.matrix[11],
                            matrix[12]-t.matrix[12], matrix[13]-t.matrix[13], matrix[14]-t.matrix[14], matrix[15]-t.matrix[15]);
    }
    anyTransform operator*(anyTransform const &t) const
    {
        return anyTransform(matrix[0]*t.matrix[0] + matrix[1]*t.matrix[4] + matrix[2]*t.matrix[8] + matrix[3]*t.matrix[12],
                            matrix[0]*t.matrix[1] + matrix[1]*t.matrix[5] + matrix[2]*t.matrix[9] + matrix[3]*t.matrix[13],
                            matrix[0]*t.matrix[2] + matrix[1]*t.matrix[6] + matrix[2]*t.matrix[10] + matrix[3]*t.matrix[14],
                            matrix[0]*t.matrix[3] + matrix[1]*t.matrix[7] + matrix[2]*t.matrix[11] + matrix[3]*t.matrix[15],

                            matrix[4]*t.matrix[0] + matrix[5]*t.matrix[4] + matrix[6]*t.matrix[8] + matrix[7]*t.matrix[12],
                            matrix[4]*t.matrix[1] + matrix[5]*t.matrix[5] + matrix[6]*t.matrix[9] + matrix[7]*t.matrix[13],
                            matrix[4]*t.matrix[2] + matrix[5]*t.matrix[6] + matrix[6]*t.matrix[10] + matrix[7]*t.matrix[14],
                            matrix[4]*t.matrix[3] + matrix[5]*t.matrix[7] + matrix[6]*t.matrix[11] + matrix[7]*t.matrix[15],

                            matrix[8]*t.matrix[0] + matrix[9]*t.matrix[4] + matrix[10]*t.matrix[8] + matrix[11]*t.matrix[12],
                            matrix[8]*t.matrix[1] + matrix[9]*t.matrix[5] + matrix[10]*t.matrix[9] + matrix[11]*t.matrix[13],
                            matrix[8]*t.matrix[2] + matrix[9]*t.matrix[6] + matrix[10]*t.matrix[10] + matrix[11]*t.matrix[14],
                            matrix[8]*t.matrix[3] + matrix[9]*t.matrix[7] + matrix[10]*t.matrix[11] + matrix[11]*t.matrix[15],

                            matrix[12]*t.matrix[0] + matrix[13]*t.matrix[4] + matrix[14]*t.matrix[8] + matrix[15]*t.matrix[12],
                            matrix[12]*t.matrix[1] + matrix[13]*t.matrix[5] + matrix[14]*t.matrix[9] + matrix[15]*t.matrix[13],
                            matrix[12]*t.matrix[2] + matrix[13]*t.matrix[6] + matrix[14]*t.matrix[10] + matrix[15]*t.matrix[14],
                            matrix[12]*t.matrix[3] + matrix[13]*t.matrix[7] + matrix[14]*t.matrix[11] + matrix[15]*t.matrix[15]
                            );
    }

    QString toString() const
    {
        QString s = "<";
        for (int i = 0; i < 16; i++)
            s += (i ? ", ": "") + QString::number(matrix[i]);
        return s + ">";
    }

    Real det()
    {
        return
                matrix[12]*matrix[9]*matrix[6]*matrix[3]  - matrix[8]*matrix[13]*matrix[6]*matrix[3]  - matrix[12]*matrix[5]*matrix[10]*matrix[3] + matrix[4]*matrix[13]*matrix[10]*matrix[3] +
                matrix[8]*matrix[5]*matrix[14]*matrix[3]  - matrix[4]*matrix[9]*matrix[14]*matrix[3]  - matrix[12]*matrix[9]*matrix[2]*matrix[7]  + matrix[8]*matrix[13]*matrix[2]*matrix[7]  +
                matrix[12]*matrix[1]*matrix[10]*matrix[7] - matrix[0]*matrix[13]*matrix[10]*matrix[7] - matrix[8]*matrix[1]*matrix[14]*matrix[7]  + matrix[0]*matrix[9]*matrix[14]*matrix[7]  +
                matrix[12]*matrix[5]*matrix[2]*matrix[11] - matrix[4]*matrix[13]*matrix[2]*matrix[11] - matrix[12]*matrix[1]*matrix[6]*matrix[11] + matrix[0]*matrix[13]*matrix[6]*matrix[11] +
                matrix[4]*matrix[1]*matrix[14]*matrix[11] - matrix[0]*matrix[5]*matrix[14]*matrix[11] - matrix[8]*matrix[5]*matrix[2]*matrix[15]  + matrix[4]*matrix[9]*matrix[2]*matrix[15]  +
                matrix[8]*matrix[1]*matrix[6]*matrix[15]  - matrix[0]*matrix[9]*matrix[6]*matrix[15]  - matrix[4]*matrix[1]*matrix[10]*matrix[15] + matrix[0]*matrix[5]*matrix[10]*matrix[15];
    }

    anyTransform inverse()
    {
        anyTransform v;
        Real x = det();

        if (x != 0)
        {
            v.matrix[0]  = matrix[9]*matrix[14]*matrix[7]  - matrix[13]*matrix[10]*matrix[7] + matrix[13]*matrix[6]*matrix[11] - matrix[5]*matrix[14]*matrix[11] - matrix[9]*matrix[6]*matrix[15] + matrix[5]*matrix[10]*matrix[15];
            v.matrix[4]  = matrix[12]*matrix[10]*matrix[7] - matrix[8]*matrix[14]*matrix[7]  - matrix[12]*matrix[6]*matrix[11] + matrix[4]*matrix[14]*matrix[11] + matrix[8]*matrix[6]*matrix[15] - matrix[4]*matrix[10]*matrix[15];
            v.matrix[8]  = matrix[8]*matrix[13]*matrix[7]  - matrix[12]*matrix[9]*matrix[7]  + matrix[12]*matrix[5]*matrix[11] - matrix[4]*matrix[13]*matrix[11] - matrix[8]*matrix[5]*matrix[15] + matrix[4]*matrix[9]*matrix[15];
            v.matrix[12] = matrix[12]*matrix[9]*matrix[6]  - matrix[8]*matrix[13]*matrix[6]  - matrix[12]*matrix[5]*matrix[10] + matrix[4]*matrix[13]*matrix[10] + matrix[8]*matrix[5]*matrix[14] - matrix[4]*matrix[9]*matrix[14];
            v.matrix[1]  = matrix[13]*matrix[10]*matrix[3] - matrix[9]*matrix[14]*matrix[3]  - matrix[13]*matrix[2]*matrix[11] + matrix[1]*matrix[14]*matrix[11] + matrix[9]*matrix[2]*matrix[15] - matrix[1]*matrix[10]*matrix[15];
            v.matrix[5]  = matrix[8]*matrix[14]*matrix[3]  - matrix[12]*matrix[10]*matrix[3] + matrix[12]*matrix[2]*matrix[11] - matrix[0]*matrix[14]*matrix[11] - matrix[8]*matrix[2]*matrix[15] + matrix[0]*matrix[10]*matrix[15];
            v.matrix[9]  = matrix[12]*matrix[9]*matrix[3]  - matrix[8]*matrix[13]*matrix[3]  - matrix[12]*matrix[1]*matrix[11] + matrix[0]*matrix[13]*matrix[11] + matrix[8]*matrix[1]*matrix[15] - matrix[0]*matrix[9]*matrix[15];
            v.matrix[13] = matrix[8]*matrix[13]*matrix[2]  - matrix[12]*matrix[9]*matrix[2]  + matrix[12]*matrix[1]*matrix[10] - matrix[0]*matrix[13]*matrix[10] - matrix[8]*matrix[1]*matrix[14] + matrix[0]*matrix[9]*matrix[14];
            v.matrix[2]  = matrix[5]*matrix[14]*matrix[3]  - matrix[13]*matrix[6]*matrix[3]  + matrix[13]*matrix[2]*matrix[7]  - matrix[1]*matrix[14]*matrix[7]  - matrix[5]*matrix[2]*matrix[15] + matrix[1]*matrix[6]*matrix[15];
            v.matrix[6]  = matrix[12]*matrix[6]*matrix[3]  - matrix[4]*matrix[14]*matrix[3]  - matrix[12]*matrix[2]*matrix[7]  + matrix[0]*matrix[14]*matrix[7]  + matrix[4]*matrix[2]*matrix[15] - matrix[0]*matrix[6]*matrix[15];
            v.matrix[10] = matrix[4]*matrix[13]*matrix[3]  - matrix[12]*matrix[5]*matrix[3]  + matrix[12]*matrix[1]*matrix[7]  - matrix[0]*matrix[13]*matrix[7]  - matrix[4]*matrix[1]*matrix[15] + matrix[0]*matrix[5]*matrix[15];
            v.matrix[14] = matrix[12]*matrix[5]*matrix[2]  - matrix[4]*matrix[13]*matrix[2]  - matrix[12]*matrix[1]*matrix[6]  + matrix[0]*matrix[13]*matrix[6]  + matrix[4]*matrix[1]*matrix[14] - matrix[0]*matrix[5]*matrix[14];
            v.matrix[3]  = matrix[9]*matrix[6]*matrix[3]   - matrix[5]*matrix[10]*matrix[3]  - matrix[9]*matrix[2]*matrix[7]   + matrix[1]*matrix[10]*matrix[7]  + matrix[5]*matrix[2]*matrix[11] - matrix[1]*matrix[6]*matrix[11];
            v.matrix[7]  = matrix[4]*matrix[10]*matrix[3]  - matrix[8]*matrix[6]*matrix[3]   + matrix[8]*matrix[2]*matrix[7]   - matrix[0]*matrix[10]*matrix[7]  - matrix[4]*matrix[2]*matrix[11] + matrix[0]*matrix[6]*matrix[11];
            v.matrix[11] = matrix[8]*matrix[5]*matrix[3]   - matrix[4]*matrix[9]*matrix[3]   - matrix[8]*matrix[1]*matrix[7]   + matrix[0]*matrix[9]*matrix[7]   + matrix[4]*matrix[1]*matrix[11] - matrix[0]*matrix[5]*matrix[11];
            v.matrix[15] = matrix[4]*matrix[9]*matrix[2]   - matrix[8]*matrix[5]*matrix[2]   + matrix[8]*matrix[1]*matrix[6]   - matrix[0]*matrix[9]*matrix[6]   - matrix[4]*matrix[1]*matrix[10] + matrix[0]*matrix[5]*matrix[10];

            x = 1/x;
            for (int i = 0; i < 16; i++)
                v.matrix[i] *= x;
        }
        return v;
    }

    void eigensolver(Real &eig1, Real &eig2, Real &eig3, anyVector3d &ev1, anyVector3d &ev2, anyVector3d &ev3);
};

#endif // TRANSFORM_H
