#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
   
  // Horizontally flip the image -> flip each row
  // dont flip the channel, so jump by channel size

  // i keep track of the position in the <vector>input
  int i = 0;

  // do this operation for height times

  for (int j = 0; j < height; j++){
    // right to left for width times
    for(int k = width-1; k >= 0 ; k--){
      // no matter how many channel are there, loop for num_channal time
      // dont swap rgb
      for(int c = 0; c < num_channels; c++){
        reflected[j*num_channels*width + k*num_channels + c] = input[i + c];
      }
      i+=num_channels;
    }
  }
}
