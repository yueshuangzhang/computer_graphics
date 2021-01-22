#include "demosaic.h"
#include <iostream>

#include <fstream>
#include <cassert>
#include <iostream>

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // given GBRG bayer pattern
  //seperate the r,g,b to 3 vector
  std::vector<unsigned char> r;
  std::vector<unsigned char> g;
  std::vector<unsigned char> b;
  r.resize(width*height*3);
  g.resize(width*height*3);
  b.resize(width*height*3);
  for (int i = 0; i < width*height*3; i ++){
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
  }
  //keep track of the color in bayer
  int track = 0;
  
  for(int row = 0; row < height; row++){
    if(row % 2 == 0){ // GBGBGBGB--
      for(int col = 0; col < width; col++){
        if(col % 2 == 0){//G
          r[row*width*3 + col*3 + 0] = 0;
          g[row*width*3 + col*3 + 1] = bayer[track];
          b[row*width*3 + col*3 + 2] = 0;
          track++;
        }else{ //B
          r[row*width*3 + col*3 + 0] = 0;
          g[row*width*3 + col*3 + 1] = 0;
          b[row*width*3 + col*3 + 2] = bayer[track];
          track++;
        }
      }
    }else{ //RGRGRG---
      for(int col = 0; col < width; col++){
        if(col % 2 == 0){//R
          r[row*width*3 + col*3 + 0] = bayer[track];
          g[row*width*3 + col*3 + 1] = 0;
          b[row*width*3 + col*3 + 2] = 0;
          track++;
        }else{ //G
          r[row*width*3 + col*3 + 0] = 0;
          g[row*width*3 + col*3 + 1] = bayer[track];
          b[row*width*3 + col*3 + 2] = 0;
          track++;
        }
      }
    }
  }
  
  double new_r=0, new_g=0, new_b=0;
  int count_add = 0;
  //compute the r,g,b layer with linear averaging the neibours
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){

      if(r[row*width*3 + col*3 + 0] == 0){
        //compute <>r
        if(row%2 == 0){ 
          if(col%2 == 0){ // row even， col even
            // top & bot add up
            if (row-1 > 0){
              new_r = new_r + r[(row-1)*width*3 + col*3 + 0];
              count_add++;
            }if (row+1 < height){
              new_r = new_r + r[(row+1)*width*3 + col*3 + 0];
              count_add++;
            }

          }else{ // row even, col odd -> take the four corner
            if ((row-1 > 0) && (col-1 > 0)){
              new_r = new_r + r[(row-1)*width*3 + (col-1)*3 + 0];
              count_add++;
            }if ((row-1 > 0) && (col+1 < width)){
              new_r = new_r + r[(row-1)*width*3 + (col+1)*3 + 0];
              count_add++;
            }if ((row+1 < height) && (col-1 > 0)){
              new_r = new_r + r[(row+1)*width*3 + (col-1)*3 + 0];
              count_add++;
            }if ((row+1 < height) && (col+1<width)){
              new_r = new_r + r[(row+1)*width*3 + (col+1)*3 + 0];
              count_add++;
            }
          }
        }else{
          if(col%2 == 0){ // row odd, col even
            continue;
          }else{ // row odd, col odd
            // left & right add up
            if (col-1 > 0){
              new_r = new_r + r[row*width*3 + (col-1)*3 + 0];
              count_add++;
            }if (col+1 < width){
              new_r = new_r + r[row*width*3 + (col+1)*3 + 0];
              count_add++;
            }
          }
        }
        new_r = new_r/double(count_add);
        r[row*width*3 + col*3 + 0] = new_r;
        new_r = 0;
        count_add = 0;
      }
      if(g[row*width*3 + col*3 + 1] == 0){
        //compute <>g
        if (row-1 > 0){
          new_g = new_g + g[(row-1)*width*3 + col*3 + 1];
          count_add++;
          //std::cout<<"left"<<int(g[(row-1)*width*3 + col*3 + 1]);
          //std::cout<<"new_g"<<int(new_g);
        }if (col-1 > 0){
          new_g = new_g + g[row*width*3 + (col-1)*3 + 1];
          //std::cout<<"top"<<int(g[row*width*3 + (col-1)*3 + 1]);
          //std::cout<<"new_g"<<int(new_g);
          count_add++;
        }if (row+1 < height){
          new_g = new_g + g[(row+1)*width*3 + col*3 + 1];
          //std::cout<<"down"<<int(g[(row+1)*width*3 + col*3 + 1]);
          //std::cout<<"new_g"<<int(new_g);
          count_add++;
        }if (col+1 <width){
          new_g = new_g + g[row*width*3 + (col+1)*3 + 1];
          //std::cout<<"right"<<int(g[row*width*3 + (col+1)*3 + 1]);
          //std::cout<<"new_g"<<int(new_g);
          count_add++;
        }
        new_g = new_g/double(count_add);
        //std::cout<<"new_g"<<int(new_g)<<"count:"<<count_add<<std::endl;
        g[row*width*3 + col*3 + 1] = new_g;
        new_g = 0;
        count_add = 0;
      }
      if(b[row*width*3 + col*3 + 2] == 0){
        //compute <>b
        if(row%2 == 0){ 
          if(col%2 == 0){ // row even， col even
            // left & right add up
            if (col-1 > 0){
              new_b = new_b + b[row*width*3 + (col-1)*3 + 2];
              count_add++;
            }if (col+1 < width){
              new_b = new_b + b[row*width*3 + (col+1)*3 + 2];
              count_add++;
            }
          }else{ // row even, col odd
            //it's the original place, ignore
            continue;
          }
        }else{
          if(col%2 == 0){ // row odd, col even -> take 4 cornor
            if ((row-1 > 0) && (col-1 > 0)){
              new_b = new_b + b[(row-1)*width*3 + (col-1)*3 + 2];
              count_add++;
            }if ((row-1 > 0) && (col+1 < width)){
              new_b = new_b + b[(row-1)*width*3 + (col+1)*3 + 2];
              count_add++;
            }if ((row+1 < height) && (col-1 > 0)){
              new_b = new_b + b[(row+1)*width*3 + (col-1)*3 + 2];
              count_add++;
            }if ((row+1 < height) && (col+1<width)){
              new_b = new_b + b[(row+1)*width*3 + (col+1)*3 + 2];
              count_add++;
            }
            
          }else{ // row odd, col odd
            // top & bot add up
            if (row-1 > 0){
              new_b = new_b + b[(row-1)*width*3 + col*3 + 2];
              count_add++;
            }if (row+1 < height){
              new_b = new_b + b[(row+1)*width*3 + col*3 + 2];
              count_add++;
            }
          }
        }
        new_b = new_b/double(count_add);
        b[row*width*3 + col*3 + 2] = new_b;
        new_b = 0;
        count_add = 0;
      }
    }
  }


  //combine r,g,b to rgb
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      rgb[row*width*3 + col*3 + 0] = r[row*width*3 + col*3 + 0] + g[row*width*3 + col*3 + 0] +b[row*width*3 + col*3 + 0];
      rgb[row*width*3 + col*3 + 1] = r[row*width*3 + col*3 + 1] + g[row*width*3 + col*3 + 1] +b[row*width*3 + col*3 + 1];
      rgb[row*width*3 + col*3 + 2] = r[row*width*3 + col*3 + 2] + g[row*width*3 + col*3 + 2] +b[row*width*3 + col*3 + 2];
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
