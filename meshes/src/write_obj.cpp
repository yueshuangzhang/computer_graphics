#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // write to file
  std::ofstream f;
  f.open(filename);
  if(!f.is_open()){
    std::cout<<"Fail to open file"<<std::endl;
    return false;
  }

  for (int i = 0; i < V.rows(); i++){
    f << "v";
    for (int j  = 0; j < V.cols(); j++) {
      f << " " << V(i, j);
    }
    f << std::endl;
  }

  for (int i = 0; i < UV.rows(); i++){
    f << "vt";
    for (int j = 0; j < UV.cols(); j++) {
      f << " " << UV(i, j);
    }
    f << std::endl;
  }


  for (int i = 0; i < NV.rows(); i++){
    f << "vn ";
    for (int j = 0; j < NV.cols(); j++){
       f << NV(i, j);
    }
    f << std::endl;
  }

  for (int i = 0; i < F.rows(); i++){
    f << "f ";
    for (int j = 0; j < F.cols(); j++){
      f << F(i, j) + 1<< "/" << UF(i, j) + 1<< "/" << NF(i, j) + 1<< " ";
    }
    f << std::endl;
  }

  f.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
