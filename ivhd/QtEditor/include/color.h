#ifndef COLOR_H
#define COLOR_H

#include <QString>
#include <qgl.h>

#include "consts.h"
#include "tools.h"

extern int Color_Mode;
extern unsigned int Color_Rand;

void SetColorMode(int cm);
void SetColorRand(unsigned int cr);

#define MIN_RGB_VALUE 0.3f
#define MAX_RGB_VALUE 0.8f

class anyColor
{
public:
    GLfloat rgba_array[4];  ///< rgba_array
    float cnt;                ///< number of colors added

    anyColor(float _r = 0, float _g = 0, float _b = 0, float _a = 1, int _cnt = 0) { set(_r, _g, _b, _a, _cnt); }

    void set(float _r, float _g, float _b, float _a = 1, int _cnt = 1)
    {
        rgba_array[0] = _r;
        rgba_array[1] = _g;
        rgba_array[2] = _b;
        rgba_array[3] = _a;
        cnt = _cnt;
    }

    void set(anyColor const &c, int _cnt = 1)
    {
        for (int i = 0; i < 4; i++)
            rgba_array[i] = c.rgba_array[i];
        cnt = _cnt;
    }

    void set(QString s)
    {
        if (s.at(0) == '#')
            s = s.mid(1);

        for (int i = 0; i < 3; i++)
            rgba_array[i] = s.mid(2*i, 2).toInt(0, 16) / 255.0;

        if (s.mid(6, 2).length() == 2)
            rgba_array[3] = s.mid(6, 2).toInt(0, 16) / 255.0;
    }

    void set_from_name(QString s, Real min, Real max)
    {
        if (s.length() == 0)
            set(0, 0, 0);
        else
        {
            unsigned int x = 0;
            for (int i = 0; i < s.length(); i++)
                x = 100*x + s.at(i).cell();
            srand(x + Color_Rand);
            rand();
            set(realRand(min, max), realRand(min, max), realRand(min, max));
        }
    }

    void set_skip_alpha(anyColor const &c, int _cnt = 1)
    {
        for (int i = 0; i < 3; i++)
            rgba_array[i] = c.rgba_array[i];
        cnt = _cnt;
    }

    void add(float _r, float _g, float _b, float _a = 1)
    {
        rgba_array[0] = (cnt*rgba_array[0] + _r)/(cnt + 1);
        rgba_array[1] = (cnt*rgba_array[1] + _g)/(cnt + 1);
        rgba_array[2] = (cnt*rgba_array[2] + _b)/(cnt + 1);
        rgba_array[3] = (cnt*rgba_array[3] + _a)/(cnt + 1);
        cnt++;
    }

    void add(anyColor const &c)
    {
        rgba_array[0] = (cnt*rgba_array[0] + c.rgba_array[0])/(cnt + 1);
        rgba_array[1] = (cnt*rgba_array[1] + c.rgba_array[1])/(cnt + 1);
        rgba_array[2] = (cnt*rgba_array[2] + c.rgba_array[2])/(cnt + 1);
        rgba_array[3] = (cnt*rgba_array[3] + c.rgba_array[3])/(cnt + 1);
        cnt++;
    }

    void rgb_mul(float x)
    {
        for (int i = 0; i < 3; i++)
            rgba_array[i] *= x;
    }

    QString to_string_rgba(bool alpha = false) const
    {
        QString s = "<";

        for (int i = 0; i < 3 + int(alpha); i++)
            s += (i ? ", ": "") +  QString::number(rgba_array[i]);
        return s + ">";
    }

    QString to_html(bool alpha = false) const
    {
        QString s = "#";
        for (int i = 0; i < 3 + int(alpha); i++)
            s += QString::number(int(255*rgba_array[i]), 16).rightJustified(2, '0');

        return s;
    }

    GLfloat const *rgba() const
    {
        static GLfloat rgba_mod[4];

        switch (Color_Mode)
        {
        case 1:
            rgba_mod[0] = rgba_mod[1] = rgba_mod[2] = (rgba_array[0]*0.299 + rgba_array[1]*0.587 + rgba_array[2]*0.114);
            rgba_mod[3] = rgba_array[3];
            return rgba_mod;
        default:
            return rgba_array;
        }

    }

    void set_r(float r)
    {
        rgba_array[0] = r;
    }
    void set_g(float g)
    {
        rgba_array[1] = g;
    }
    void set_b(float b)
    {
        rgba_array[2] = b;
    }
    void set_a(float a)
    {
        rgba_array[3] = a;
    }

    float r() const { return rgba()[0]; }
    float g() const { return rgba()[1]; }
    float b() const { return rgba()[2]; }
    float a() const { return rgba()[3]; }

    int r255() const { return r()*255; }
    int g255() const { return g()*255; }
    int b255() const { return b()*255; }
};

#endif // COLOR_H
