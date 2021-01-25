#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
    double r=0,g=0,b=0,h=0,s=0,v=0;
    for(int i = 0; i < rgb.size(); i+=3){
    //get rgb value [0,1]
    r = rgb[i+0]/double(255);
    g = rgb[i+1]/double(255);
    b = rgb[i+2]/double(255);

    //get corresponding hsv
    rgb_to_hsv(r,g,b,h,s,v);

    //apply the disaturation, 0-unchange, 1-fully saturated
    s = s*(1-factor);

    //make sure range s in [0 to 1]
    while (s > 1){
      s = s - 1;
    }
    while (s < 0){
      s = s + 1;
    }

    //convert the new hsv back to rgb
    hsv_to_rgb(h,s,v,r,g,b);
    
    //write new rgb to vector
    unsigned char R,G,B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    desaturated[i + 0] = R;
    desaturated[i + 1] = G;
    desaturated[i + 2] = B;
  }
  ////////////////////////////////////////////////////////////////////////////
}
