#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <iostream>
void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  /////////////////////////////////////////////////////////////////////////////
  // shift given in degrees [-180,180)
  
  double r=0,g=0,b=0,h=0,s=0,v=0;
  for(int i = 0; i < rgb.size(); i+=3){
    //get rgb value [0,1]
    r = rgb[i+0]/double(255);
    g = rgb[i+1]/double(255);
    b = rgb[i+2]/double(255);

    //get corresponding hsv
    rgb_to_hsv(r,g,b,h,s,v);

    //apply the hue shift
    h = h + shift;

    //make sure range h [0,360]
    while (h > 360){
      h = h - 360;
    }
    while (h < 0){
      h = h + 360;
    }

    //convert the new hsv back to rgb
    hsv_to_rgb(h,s,v,r,g,b);
    
    //write new rgb to vector
    unsigned char R,G,B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    shifted[i + 0] = R;
    shifted[i + 1] = G;
    shifted[i + 2] = B;
  }
  ////////////////////////////////////////////////////////////////////////////
}
