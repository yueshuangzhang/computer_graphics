#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Rotate an image 90°  counter-clockwise

  //get the right most col info, and save as the first row. and so on
  int track = 0;

  for(int i = width-1; i >= 0; i--){
    for(int j = 0; j < height; j++){
      //last cell of the row is:
      for(int c = 0; c < num_channels; c++){
        rotated[track + c] = input[j*width*num_channels + i*num_channels + c];
      }
      track+=num_channels;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
