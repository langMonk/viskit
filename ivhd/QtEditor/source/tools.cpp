#include <QString>
#include <QLocale>
#include <QThread>
#include <QDateTime>

#include "consts.h"
#include "tools.h"


QString bytesToStr(int64_t b, int sh)
{
    const long kb = 1024;
    const long mb = kb*1024;
    const long gb = mb*1024;

    if (b >= gb && sh > 2)
        return niceInt(b/gb) + " GB";
    if (b >= mb && sh > 1)
        return niceInt(b/mb) + " MB";
    if (b >= kb && sh > 0)
        return niceInt(b/kb) + " KB";
    return niceInt(b) + " B";
}


QString niceInt(int64_t x, QString const group_separator)
{
    const QLocale & cLocale = QLocale::c();
    QString ss = cLocale.toString(x);
    ss.replace(cLocale.groupSeparator(), group_separator);
    return ss;
}


int intRand(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


Real realRand(Real min, Real max)
{
    return Real(rand())/Real(RAND_MAX)*(max - min) + min;
}


void InitRand()
{
    unsigned int seed = (int64_t)QThread::currentThreadId() + QDateTime::currentMSecsSinceEpoch();
    srand(seed);
    rand();
}


void ChooseRandomly(bool *a, int size, int elems)
{
    if (elems >= size)
    {
        for (int i = 0; i < size; i++)
            a[i] = true;
    }
    else
    {
        for (int i = 0; i < size; i++)
            a[i] = false;
        int cnt = 0;
        while (cnt < elems)
        {
            int x = intRand(0, size - 1);
            if (!a[x])
            {
                cnt++;
                a[x] = true;
            }
        }
    }
}


QString ShortTime(QTime t)
{
    if (t.hour() == 0 && t.minute() == 0 && t.second() < 10)
        return t.toString("s.zzz");

    QString s = t.toString();
    if (s.startsWith("00:0"))
        return s.right(4);
    else if (s.startsWith("00:"))
        return s.right(5);
    else if (s.startsWith("0"))
        return s.right(7);
    else
        return s;
}


bool isHost64Bit()
{
    static bool h = QSysInfo::currentCpuArchitecture().contains(QLatin1String("64"));
    return h;
}


bool isBuild64Bit()
{
    static bool b = QSysInfo::buildCpuArchitecture().contains(QLatin1String("64"));
    return b;
}
