#include "td_func.h"
#include "td.h"

void fillCircleCube(color c, int op, double x, double y, double z, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int kmin = (int)(z - r - 1), kmax = (int)(z + r + 1);
  int i, j, k;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
      for(k = kmin; k <= kmax; k++){
        if((x-i)*(x-i) + (y-j)*(y-j) + (z-k)*(z-k) <= r*r) { putPixelCube(c, i, j, k, op); }
      }
    }
  }
}

void fillCone(color c, int op, double x, double y, double z, double h, double r) {
  int i, j, k;
  int jmin, jmax, kmin, kmax;

      for(i = (int)y; i <= (int)(y + h); ++i) {
        double rad = r * (1 - ((i - y)/h));
        jmin = (int)(x - rad - 1); jmax = (int)(x + rad + 1);
        kmin = (int)(z - rad - 1); kmax = (int)(z + rad + 1);
        for(j = jmin; j <= jmax; ++j) {
          for(k = kmin; k <= kmax; ++k) {
            if((x-j)*(x-j) + (z-k)*(z-k) <= rad*rad) { putPixelCube(c, j, i, k, op); }
          }
        }
      }
}

void fillLainCone(color c, int op, double x, double y, double z, double h, double r) {
  int i, j, k;
  int jmin, jmax, kmin, kmax;

      for(i = (int)x; i <= (int)(x + h); ++i) {
        double rad = r * (1 - ((i - x)/h));
        jmin = (int)(y - rad - 1); jmax = (int)(y + rad + 1);
        kmin = (int)(z - rad - 1); kmax = (int)(z + rad + 1);
        for(j = jmin; j <= jmax; ++j) {
          for(k = kmin; k <= kmax; ++k) {
            if((y-j)*(y-j) + (z-k)*(z-k) <= rad*rad) { putPixelCube(c, i, j, k, op); }
          }
        }
      }
}

void fillCylinder(color c, int op, double x, double y, double z, double h, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(z - r - 1), jmax = (int)(z + r + 1);
  int i, j, k;

  for(i = imin; i <= imax; ++i) {
    for(j = jmin; j <= jmax; ++j) {
      for(k = (int)y; k <= (int)(y + h); ++k) {
        if((x-i)*(x-i) + (z-j)*(z-j) <= r*r) { putPixelCube(c, i, k, j, op); }
      }
    }
  }
}

void fillrect(color c, int op, double x, double y, double z, double w, double h, double d) {
  int imin = (int)(x - w/2), imax = (int)(x + w/2);
  int jmin = (int)(y - h/2), jmax = (int)(y + h/2);
  int kmin = (int)(z - d/2), kmax = (int)(z + d/2);
  int i, j, k;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
      for(k = kmin; d <= kmax; ++k) {
        putPixelCube(c, i, j, k, op);
      }
    }
  }
}

void fillPyramid(color c, int op, double x, double y, double z, double w, double h, double d) {
  int i, j, k;
  int imax, imin, kmax, kmin;
  double wid, dep;
    for(j = (int)y; j <= (int)(y + h); ++j) {
      wid = w * (1 - ((j - y)/h));
      dep = d * (1 - ((j - y)/h));
      imin = (int)(x - wid/2); imax = (int)(x + wid/2);
      kmin = (int)(z - wid/2); kmax = (int)(z + wid/2);
      for(i = imin; i <= imax; ++i) {
        for(k = kmin; k <= kmax; ++k) {
          putPixelCube(c, i, j, k, op);
        }
      }
    }
}

void fillLainPyramid(color c, int op, double x, double y, double z, double w, double h, double d) {
  int i, j, k;
  int imax, imin, kmax, kmin;
  double wid, dep;

    for(j = (int)x; j <= (int)(x + h); ++j) {
      wid = w * (1 - ((j - x)/h));
      dep = d * (1 - ((j - x)/h));
      imin = (int)(y - wid/2); imax = (int)(y + wid/2);
      kmin = (int)(z - wid/2); kmax = (int)(z + wid/2);
      for(i = imin; i <= imax; ++i) {
        for(k = kmin; k <= kmax; ++k) {
          putPixelCube(c, j, i, k, op);
        }
      }
    }
}
