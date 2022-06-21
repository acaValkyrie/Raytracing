#ifndef IMG_H
#define IMG_H

#define WIDTH 300
#define HEIGHT 200
typedef struct { unsigned char r, g, b; } color;
typedef struct { double c, m, y, k; } cmyk;
cmyk cnvRGBtoCMYK(color c);
color cnvCMYKtoRGB(cmyk c);
color colorMix(color c1, color c2);
color colorMixOp(color c1, color c2, int op1, int op2);
void img_clear(void);
void img_write(void);
void img_putpixel(color c, int x, int y);
void img_addpixel(color c, int x, int y);
void img_avrpixel(color c, int x, int y);

void img_addOpacity(int op, int x, int y);
void img_mixPixel(color c, int op, int x, int y);

void img_fillcircle(color c, double x, double y, double r);

#endif
