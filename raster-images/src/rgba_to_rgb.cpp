#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  
  // ======= rgba-rgba to rgb-rgb, skipping the a(alpha) =======
  // track the position in rgb vector
  int track = 0;

  //loop through all values in rgba, skip the a
  for (int i = 0; i < rgba.size(); i++){
    // skip the position of a
    if ((i+1)%4 != 0){
      // copy the rgb value
      rgb[track] = rgba[i];
      track = track+1;
    }
  }
}
