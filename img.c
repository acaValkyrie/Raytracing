#include <stdio.h>
#include <stdlib.h>
#include "img.h"

static unsigned char buf[HEIGHT][WIDTH][4];
static int filecnt = 0;
static char fname[100];

void img_clear(void) {
  int i, j;
  for(j = 0; j < HEIGHT; ++j) {
    for(i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = buf[j][i][3] = 0/*255*/;
    }
  }
}

void img_write(void) {
  sprintf(fname, "img%04d.ppm", ++filecnt);
  FILE *f = fopen(fname, "wb");
  if(f == NULL) { fprintf(stderr, "can't open %s\n", fname); exit(1); }
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  fwrite(buf, sizeof(buf), 1, f);
  fclose(f);
}

void img_putpixel(color c, int x, int y) {
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
  buf[HEIGHT-y-1][x][0] = c.r;
  buf[HEIGHT-y-1][x][1] = c.g;
  buf[HEIGHT-y-1][x][2] = c.b;
}

void img_addpixel(color c, int x, int y){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
  color tmp = {buf[HEIGHT-y-1][x][0], buf[HEIGHT-y-1][x][1], buf[HEIGHT-y-1][x][2]};
  tmp.r = tmp.r + c.r > 255 ? 255 : tmp.r + c.r;
  tmp.g = tmp.g + c.g > 255 ? 255 : tmp.g + c.g;
  tmp.b = tmp.b + c.b > 255 ? 255 : tmp.b + c.b;
  img_putpixel(tmp, x, y);
}

void img_avrpixel(color c, int x, int y){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
  color tmp = {buf[HEIGHT-y-1][x][0], buf[HEIGHT-y-1][x][1], buf[HEIGHT-y-1][x][2]};
  tmp.r = (tmp.r + c.r)/2.0;
  tmp.g = (tmp.g + c.g)/2.0;
  tmp.b = (tmp.b + c.b)/2.0;
  img_putpixel(tmp, x, y);
}

void img_mixPixel(color c, int op, int x, int y){
  color tmp = {buf[HEIGHT-y-1][x][0], buf[HEIGHT-y-1][x][1], buf[HEIGHT-y-1][x][2]};
  tmp = colorMixOp(c, tmp, op, buf[HEIGHT-y-1][x][3]);
  img_addOpacity(op, x, y);
  img_putpixel(tmp, x, y);
}

void img_addOpacity(int op, int x, int y){
  int tmp = buf[HEIGHT-y-1][x][3];
  tmp += op; if(tmp > 100){tmp = 100;};
  buf[HEIGHT-y-1][x][3] = tmp;
}

void img_fillcircle(color c, double x, double y, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
      if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) { img_putpixel(c, i, j); }
    }
  }
}

cmyk cnvRGBtoCMYK(color c){
  double k = c.r;
  if(k < c.g)k = c.g;
  if(k < c.b)k = c.b;
  k = 1-k/255.0;
  cmyk r = {(1 - c.r/255.0 - k)/(1-k),
            (1 - c.g/255.0 - k)/(1-k),
            (1 - c.b/255.0 - k)/(1-k),
            k};
  return r;
}
color cnvCMYKtoRGB(cmyk c){
  color r = {255*(1-c.c)*(1-c.k), 255*(1-c.m)*(1-c.k), 255*(1-c.y)*(1-c.k)};
  return r;
}
color colorMix(color c1, color c2){
  cmyk r1 = cnvRGBtoCMYK(c1), r2 = cnvRGBtoCMYK(c2);
  cmyk r = {r1.c+r2.c, r1.m+r2.m, r1.y+r2.y, r1.k+r2.k};
  r.c /=2; r.m /=2; r.y /=2; r.k /=2;
  return cnvCMYKtoRGB(r);
}

color colorMixOp(color c1, color c2, int op1, int op2){
  cmyk r1 = cnvRGBtoCMYK(c1), r2 = cnvRGBtoCMYK(c2);
  cmyk r = {(r1.c*op1 + r2.c*op2)/(op1+op2), (r1.m*op1 + r2.m*op2)/(op1+op2), (r1.y*op1 + r2.y*op2)/(op1+op2), (r1.k*op1+r2.k*op2)/(op1+op2)};
  color ret = cnvCMYKtoRGB(r);
  return ret;
}
