#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  
  // check image size
  if (width == 0 || height == 0){
    std::cout<<"Image has no width or height attribute, save failed"<<std::endl;
    return false;
  }

  //create a ppm file
  std::ofstream f;
  f.open(filename, std::ifstream::binary | std::ifstream::out);
  if(!f.is_open()){
    std::cout<<"Fail to open file"<<std::endl;
    return false;
  }

  //write header
  if(num_channels == 1){
    f << "P5\n" << width << " " << height << "\n255\n";
  }
  else if(num_channels == 3){
    f << "P6\n" << width << " " << height << "\n255\n";
  }
  else{
    std::cout<<"num_channels incorrect"<<std::endl;
    return false;
  }
  
  //write data
  for(int i = 0; i < data.size(); i++){
      f << data[i];
  }

  f.close();
  return true;
  
  ////////////////////////////////////////////////////////////////////////////
}
