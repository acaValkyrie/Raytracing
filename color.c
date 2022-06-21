#include <stdio.h>

typedef struct { unsigned char r, g, b; } color;
typedef struct { double c, m, y, k; } cmyk;

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
  return cnvCMYKtoRGB(r);
}

color readcolor(void) {
  int r, g, b;
  printf("r(0-255)> "); scanf("%d", &r);
  printf("g(0-255)> "); scanf("%d", &g);
  printf("b(0-255)> "); scanf("%d", &b);
  color ret = { r, g, b  }; return ret;
}

int main(void){
  color c1, c2;
  c1 = readcolor();
  c2 = readcolor();
  color mc1, mc2;
  mc1 = colorMix(c1, c2);
  mc2 = colorMixOp(c1, c2, 50, 10);
  printf("cmy:%d %d %d\nrgb:%d %d %d\n", mc1.r, mc1.g, mc1.b, mc2.r, mc2.g, mc2.b);
}
