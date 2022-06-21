#include "td.h"
#include <stdio.h>
#include "img.h"

enum cInfo{red, green, blue, opacity, physics};
static unsigned char cube[HEIGHT][WIDTH][DEPTH][5];

enum cInfo r = red, g = green, b = blue, o = opacity/*0:invisible, 100:visible*/, p = physics;

void clearCube(){//reset cube.
  for(int i = 0; i < HEIGHT; i++){
    for(int i2 = 0; i2 < WIDTH; i2++){
      for(int i3 = 0; i3 < DEPTH; i3++){
        //white
        cube[i][i2][i3][r] = 255;
        cube[i][i2][i3][g] = 255;
        cube[i][i2][i3][b] = 255;

        //invisible
        cube[i][i2][i3][o] =   0;
        cube[i][i2][i3][p] =   0;
      }
    }
  }
}

void putPixelCube(color c, int x, int y, int z, int op){//put pixel in cube.
  if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT && 0 <= z && z < DEPTH){
    if(cube[y][x][z][p] == 0){
      cube[y][x][z][r] = c.r;
      cube[y][x][z][g] = c.g;
      cube[y][x][z][b] = c.b;
      cube[y][x][z][o] = op;
      cube[y][x][z][p] = 1;
    }else{/*
      color tmp = {cube[y][x][z][r], cube[y][x][z][g], cube[y][x][z][b]};
      tmp = colorMixOp(c, tmp, op, cube[y][x][z][o]);
      cube[y][x][z][r] = tmp.r;
      cube[y][x][z][g] = tmp.g;
      cube[y][x][z][b] = tmp.b;
      cube[y][x][z][o] += op;
      if(cube[y][x][z][o] > 100)cube[y][x][z][o] = 100;*/
      cube[y][x][z][r] = (cube[y][x][z][r]*cube[y][x][z][o] + c.r*op)/(float)(cube[y][x][z][o] + op);
      cube[y][x][z][g] = (cube[y][x][z][g]*cube[y][x][z][o] + c.g*op)/(float)(cube[y][x][z][o] + op);
      cube[y][x][z][b] = (cube[y][x][z][b]*cube[y][x][z][o] + c.b*op)/(float)(cube[y][x][z][o] + op);
      cube[y][x][z][o] += op;
      if(cube[y][x][z][o] > 100)cube[y][x][z][o] = 100;
      //cube[HEIGHT-y-1][x][z][p] = 1;
    }
  }
}

void setPixelDarkerCube(int x, int y, int z, int op){
  color black = { 0, 0, 0 };
  putPixelCube(black, x, y, z, op);
}

int showHitableCube(int x, int y, int z){
  return cube[y][x][z][p];
}

color showColorCube(int x, int y, int z){
  color c = { cube[y][x][z][r], cube[y][x][z][g], cube[y][x][z][b] };
  return c;
}

void debugColorfulWallCube(){
  color blue = {0, 100, 200}, lightblue = {0, 150, 250}, yellow = {200, 200, 0}, purple = {100, 0, 100}, lightpurple = { 250, 0, 250};
  for(int i = 0; i < HEIGHT; i++){
    for(int i2 = 0; i2 < WIDTH; i2++){
      for(int i3 = 0; i3 < DEPTH; i3++){
        putPixelCube(       blue,      i2,        0,      i3, 100);
        putPixelCube(  lightblue,      i2, HEIGHT-1,      i3, 100);
        putPixelCube(     purple,       0,        i,      i3, 100);
        putPixelCube(lightpurple, WIDTH-1,        i,      i3, 100);
        putPixelCube(     yellow,      i2,        i, DEPTH-1, 100);
      }
    }
  }
}

void wallCube(){
  color white = {240, 240, 240}, black = {20, 20, 50};
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
      for(int z = 0; z < DEPTH; z++){
        if(x == 0 || x == WIDTH -1 ){
          if((y >= 5 && y <= 8) || (y <= HEIGHT-1-5 && y >= HEIGHT-1-8) || (z >= 5 && z <= 8) || (z <= DEPTH-1-5 && z >= DEPTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
        if(y == 0 || y == HEIGHT-1 ){
          if((x >= 5 && x <= 8) || (x <= WIDTH-1-5 && x >= WIDTH-1-8) || (z >= 5 && z <= 8) || (z <= DEPTH-1-5 && z >= DEPTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
        if(z == DEPTH -1 ){
          if((y >= 5 && y <= 8) || (y <= HEIGHT-1-5 && y >= HEIGHT-1-8) || (x >= 5 && x <= 8) || (x <= WIDTH-1-5 && x >= WIDTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
      }
    }
  }
}

void wallCubeV2(){
  color white = {39, 67, 101}, black = {63, 192, 189};
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
      for(int z = 0; z < DEPTH; z++){
        if(x == 0 || x == WIDTH -1 ){
          if((y >= 5 && y <= 8) || (y <= HEIGHT-1-5 && y >= HEIGHT-1-8) || (z >= 5 && z <= 8) || (z <= DEPTH-1-5 && z >= DEPTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
        if(y == 0 || y == HEIGHT-1 ){
          if((x >= 5 && x <= 8) || (x <= WIDTH-1-5 && x >= WIDTH-1-8) || (z >= 5 && z <= 8) || (z <= DEPTH-1-5 && z >= DEPTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
        if(z == DEPTH -1 ){
          if((y >= 5 && y <= 8) || (y <= HEIGHT-1-5 && y >= HEIGHT-1-8) || (x >= 5 && x <= 8) || (x <= WIDTH-1-5 && x >= WIDTH-1-8)){
            putPixelCube( black, x, y, z, 100);
          }else{
            putPixelCube( white, x, y, z, 100);
          }
        }
      }
    }
  }
}

void writeCubetoBuf(){
  for(int i3 = 0; i3 < DEPTH; i3++){
    for(int i = 0; i < HEIGHT; i++){
      for(int i2 = 0; i2 < WIDTH; i2++){
        int z = DEPTH - i3 -1;
        int x = i2*(WIDTH-z)/(float)WIDTH + 0.5*z;
        int y = i*(HEIGHT-z)/(float)HEIGHT + 0.7*z;
        color c = {cube[i][i2][z][r], cube[i][i2][z][g], cube[i][i2][z][b]};
        c.r *= cube[i][i2][z][o]/100.0;
        c.g *= cube[i][i2][z][o]/100.0;
        c.b *= cube[i][i2][z][o]/100.0;
        if(cube[i][i2][z][p] == 1){
          if(cube[i][i2][z][o] == 100){
            img_putpixel(c, x, y);
            //img_addOpacity(100, x, y);
          }else{
            //img_mixPixel(c, cube[i][i2][z][o], x, y);
            img_addpixel(c, x, y);
          }
        }
      }
    }
  }
}
