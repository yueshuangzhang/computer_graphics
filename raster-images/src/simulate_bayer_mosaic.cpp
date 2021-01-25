#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // top left pixel is green, its right neighbor is blue and neighbor below is red, 
  // and its kitty-corner neighbor is also green. (GBRG)

  int track = 0;

  for(int i = 0; i < height; i++){ // vertial
    for(int j = 0; j < width; j++){ // horizontal
      //if the current row(i) is even (0，1，2 ...), GBGB--
      if(i%2 == 0){
        // if the current row is even - G, odd - B
        if (j%2 == 0){
          //take green
          bayer[track] = rgb[width*i*3 + j*3 + 1];
        }
        else{
          //take blue
          bayer[track] = rgb[width*i*3 + j*3 + 2];
        }
      }
      else{//i%2 == 1 
        if (j%2 == 0){
          //take red
          bayer[track] = rgb[width*i*3 + j*3 + 0];
        }
        else{
          //take green
          bayer[track] = rgb[width*i*3 + j*3 + 1];
        }
      }
      track ++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
