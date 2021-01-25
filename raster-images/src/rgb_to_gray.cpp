#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  int track = 0;

  //loop through all values in rgb, compute the single value
  for (int i = 0; i < rgb.size(); i+=3){
    // i = 0.2126 r + 0.7152 g + 0.0722 b.
    int r, g, b;
    double gray_cell; 
    r = rgb[i + 0];
    g = rgb[i + 1];
    b = rgb[i + 2];

    gray_cell = 0.2126*r + 0.7152*g + 0.0722*b;
    gray[track] = gray_cell;
    track++;
  }
  ////////////////////////////////////////////////////////////////////////////
}


