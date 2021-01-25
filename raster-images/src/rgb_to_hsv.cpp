#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>
using namespace std;

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Reference：
  // https://cs.stackexchange.com/questions/64549/convert-hsv-to-rgb-colors
  // https://en.wikipedia.org/wiki/HSL_and_HSV#HSL_to_RGB
  // H = 60 * ((g-b)/(max-min)%6) if max = R
  // H = 60 * (2 + (b-r)/(max-min)) if max = G
  // H = 60 * (4 + (r-g)/(max-min)) if max = B
  // H = H + 360 if H < 0
  // S = (max-min)/max  (S=0 if V=0)
  // V = max(r,g,b),  
  // min = min(rgb)
  
  h = 0;
  s = 0;
  v = 0;

  double max_rgb = max({r,g,b});
  double min_rgb = min({r,g,b});
  double delta = max_rgb - min_rgb;

  // compute v
  v = max_rgb;

  //compute s
  if(v == 0){
    s = 0;
  }
  else{
    s = delta/max_rgb;
  }

  //compute h
  if (delta == 0){
    h = 0;
  }
  else if (max_rgb == r){
    h = (g - b)/delta;
    while(h >= 6){
      h = h - 6;
    }
    //h = int(h)%6;
  }
  else if(max_rgb == g){
    h = (b - r)/delta;
    h = h + 2;
  }
  else if(max_rgb == b){
    h = (r - g)/delta;
    h = h + 4;
  }

  h = h * 60;
  
  while (h < 0){
    h = h + 360;
  }

  while (h > 360){
    h = h - 360;
  }
  ////////////////////////////////////////////////////////////////////////////
  
}
