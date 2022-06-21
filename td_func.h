#ifndef TDFUNC_H
#define TDFUNC_H

#include "img.h"

void fillCircleCube(color c, int op, double x, double y, double z, double r);
void fillCone(color c, int op, double x, double y, double z, double h, double r);
void fillLainCone(color c, int op, double x, double y, double z, double h, double r);
void fillCylinder(color c, int op, double x, double y, double z, double h, double r);
void fillPyramid(color c, int op, double x, double y, double z, double w, double h, double d);
void fillLainPyramid(color c, int op, double x, double y, double z, double w, double h, double d);

#endif
