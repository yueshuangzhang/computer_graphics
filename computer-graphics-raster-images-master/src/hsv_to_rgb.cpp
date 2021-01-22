#include "hsv_to_rgb.h"
#include <cmath>
using namespace std;

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Reference：
  // https://en.wikipedia.org/wiki/HSL_and_HSV#HSL_to_RGB
  // https://cs.stackexchange.com/questions/64549/convert-hsv-to-rgb-colors
  // h_prim = h/60
  // h_det = h_prim % 6

  r = 0;
  g = 0;
  b = 0;

  double c = v * s;
  double h_prim = h / 60;
  double x = c * (1 - fabs( fmod(h_prim, 2) - 1));
  double m = v-c;

  if(h_prim == 0 || h == 0){
    r = 0;
    g = 0;
    b = 0;
  }
  else if (h_prim <= 1 && h_prim > 0){
    r = c;
    g = x;
    b = 0;
  }
  else if(h_prim <= 2 && h_prim > 1){
    r = x;
    g = c;
    b = 0;
  }
  else if(h_prim <= 3 && h_prim > 2){
    r = 0;
    g = c;
    b = x;
  }
  else if(h_prim <= 4 && h_prim > 3){
    r = 0;
    g = x;
    b = c;
  }
  else if(h_prim <= 5 && h_prim > 4){
    r = x;
    g = 0;
    b = c;
  }
  else if(h_prim <= 6 && h_prim > 5){
    r = c;
    g = 0;
    b = x;
  }
  
  r = r + m;
  g = g + m;
  b = b + m;

  ////////////////////////////////////////////////////////////////////////////
  
}
