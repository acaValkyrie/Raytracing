#include "img.h"
#include "td.h"
#include "td_func.h"
#include "ray.h"
#include <math.h>
#define PI 3.14159265358979

void makeShadowArea(int lxMax, int lxMin, int lyMax, int lyMin, int lzMax, int lzMin){
  for(int lx = lxMin; lx < lxMax; lx++){
    if(lx % 10 == 0){
      for(int ly = lyMin; ly < lyMax; ly++){
        if(ly % 10 == 0){
          for(int lz = lzMin; lz < lzMax; lz++){
            if(lz % 10 == 0){
              makeShadowCube(lx, ly, lz, 2);
            }
          }
        }
      }
    }
  }
}
typedef struct { double x, y, z; } vector;
void addVec(vector *a, vector b){
  a->x += b.x; a->y += b.y; a->z += b.z;
}

int main(void) {
  color bl = { 70, 130, 180};
  color rd = {233, 124, 94};
/*  color c1 = { 30, 255, 0 };
  color c2 = { 255, 0, 0 };
  color cyan = { 0, 255, 255};
  color orange = {255,165,0};
  color green = { 34, 140, 34};*/
  //rd = c1;
  int i;
  double vy0 = 10, y0 =180, vz0 = 4;
  double r[5] = {20, 20, 20, 20, 20};
  double bounce[5] = {1, 0.95, 0.75, 0.5, 0.3};
  vector pos[5] = { { 50, y0, 70}, { 100, y0, 70}, { 150, y0, 70}, { 200, y0, 70}, { 250, y0, 70}};
  vector vel[5] = { { 0, vy0, vz0}, { 0, vy0, vz0}, { 0, vy0, vz0}, { 0, vy0, vz0}, { 0, vy0, vz0}};
  color c[5] = {bl, bl, bl, bl, bl};
  vector g = { 0, -9.8, 0};
  int px1, px2, py1, py2, pz1, pz2;
  px1 = px2 = py1 = py2 = pz1 = pz2 = 0;
  for(i = 0; i < 1; ++i) {
    img_clear(); clearCube();

    //wallCube();
    for(int j = 0; j < 1; j++){
      addVec(&vel[j], g);
      addVec(&pos[j], vel[j]);

      c[j] = bl;
      if(pos[j].x < r[j]){pos[j].x = r[j]; vel[j].x *= -bounce[j];if(px1 == 0){c[j] = rd;px1 = 1;}}else{px1 = 0;}
      if(pos[j].x > WIDTH-r[j]){pos[j].x = WIDTH-r[j]; vel[j].x *= -bounce[j]; if(px2 == 0){c[j] = rd;px2 = 1;}}else{px2 = 0;}

      if(pos[j].y < r[j]){pos[j].y = r[j]; vel[j].y *= -bounce[j]; if(py1 == 0){c[j] = rd;py1 = 1;}}else{py1 = 0;}
      if(pos[j].y > HEIGHT-r[j]){pos[j].y = HEIGHT-r[j]; vel[j].y *= -bounce[j]; if(py2 == 0){c[j] = rd;py2 = 1;}}else{py2 = 0;}

      if(pos[j].z < r[j]){pos[j].z = r[j]; vel[j].z *= -bounce[j]; if(pz1 == 0){c[j] = rd;pz1 = 1;}}else{pz1 = 0;}
      if(pos[j].z > DEPTH-r[j]){pos[j].z = DEPTH-r[j]; vel[j].z *= -bounce[j]; if(pz2 == 0){c[j] = rd;pz2 = 1;}}else{pz2 = 0;}
      fillCircleCube(c[j], 100, pos[j].x, pos[j].y, pos[j].z, r[j]);
    }

    //makeShadowArea(11, 10, HEIGHT-10, HEIGHT-110, 15, 10);
    writeCubetoBuf(); img_write();
  }
}
