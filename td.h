#ifndef TD_H
#define TD_H

#define DEPTH 100
#include "img.h"

void clearCube();
void putPixelCube(color c, int x, int y, int z, int op);
void setPixelDarkerCube(int x, int y, int z, int op);
void debugColorfulWallCube();
void wallCube();
void wallCubeV2();
void writeCubetoBuf();

int showHitableCube(int x, int y, int z);
color showColorCube(int x, int y, int z);

#endif
