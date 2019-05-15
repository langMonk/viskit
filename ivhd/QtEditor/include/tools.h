#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include "consts.h"

QString bytesToStr(int64_t b, int sh = 3);
QString niceInt(int64_t x, QString const group_separator = " ");
int intRand(int min, int max);
Real realRand(Real min, Real max);
void InitRand();
void ChooseRandomly(bool *a, int size, int elems);
QString ShortTime(QTime t);
bool isHost64Bit();
bool isBuild64Bit();

#endif // TOOLS_H
