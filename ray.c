#include "img.h"
#include "td.h"
#include "ray.h"
#include <stdio.h>
#include <math.h>

double absl(double n){
  return n > 0 ? n : -1*n;
}

int isHit(int x1, int y1, int z1, int x2, int y2, int z2){
  int len[3] = {x2 - x1, y2 - y1, z2 - z1};
  int maxLenN = 0;
  if(absl(len[maxLenN]) < absl(len[1])){maxLenN = 1;}
  if(absl(len[maxLenN]) < absl(len[2])){maxLenN = 2;}
  float grad[3];//最も始点から終点までの距離が長い成分(x, y, z)が 1 動いたとき他がどれくらい動くか。
  for(int i = 0; i < 3; i++){ grad[i] = (float)len[i]/absl(len[maxLenN]); }

  float pos[3] = {x1, y1, z1};

  /*int initState = showHitableCube(x1, y1, z1);
  int outObjectFlag = initState == 0 ? 1 : 0;

  for(int i = 0; i < abs(len[maxLenN]); i++){
    for(int i2 = 0; i2 < 3; i2++){ pos[i2] += grad[i2]; }
    int tmpx = (int)pos[0], tmpy = (int)pos[1], tmpz = (int)pos[2];
    if(outObjectFlag == 0){
      if(showHitableCube(tmpx, tmpy, tmpz) == 0){outObjectFlag = 1;}
    }else{
      if(showHitableCube(tmpx, tmpy, tmpz) == 1){
        return 1;
      }
    }
  }*/

  for(int i = 0; i < absl(len[maxLenN]); i++){
    for(int i2 = 0; i2 < 3; i2++){ pos[i2] += grad[i2]; }
    int tmpx = (int)pos[0], tmpy = (int)pos[1], tmpz = (int)pos[2];

    if(showHitableCube(tmpx, tmpy, tmpz) == 1 && (tmpx != x1 || tmpy != y1 || tmpz != z1)){
      return 1;
    }
  }
  return 0;
}

void makeShadowCube(const int lx, const int ly, const int lz, const int lSt){
  //const int lx = 10, ly = HEIGHT-10, lz = 10;
  for(int z = 0; z < DEPTH; z++){
    for(int x = 0; x < WIDTH; x++){
      for(int y = 0; y < HEIGHT; y++){
        if(showHitableCube(x, y, z) == 1){
          if(isHit(x, y, z, lx, ly, lz) == 1){
            setPixelDarkerCube(x, y, z, lSt);
          }
        }
      }
    }
  }
}
