#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////

  ////Hint:
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  //   V  8 by 3 list of 3D corner vertex positions
  V <<  0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1;

  //   F  6 by 4 list of quad face indices into rows of V
  F <<  0, 3, 2, 1, // bottom
        0, 4, 7, 3, // left
        3, 7, 6, 2, // front
        2, 6, 5, 1, // right 
        0, 1, 5, 4, // back
        4, 5, 6, 7; // top

  //   UV  14 by 2 list of corner parameterization positions
  UV << 0, 0.25,
        0, 0.5,
        0.25, 0,
        0.25, 0.25,
        0.25, 0.5,
        0.25, 0.75,
        0.5, 0,
        0.5, 0.25,
        0.5, 0.5,
        0.5, 0.75,
        0.75, 0.25,
        0.75, 0.5,
        1, 0.25,
        1, 0.5;

  //   UF  6 by 4 list of quad face indices into rows of UV
  UF << 4, 8, 7, 3, // bottom
        4, 3, 0, 1, // left
        8, 11, 10, 9, // right
        3, 7, 8, 2, // front
        5, 9, 8, 4, // back
        12, 1, 11, 13; // top

  //   NV  6 by 3 list of 3D unit normal vectors
  NV << 1, 0, 0,
        -1, 0, 0,
        0, 1, 0,
        0, -1, 0,
        0, 0, 1,
        0, 0, -1;
  
  //   NF  6 by 4 list of quad face indices into rows of NV
  NF << 3, 3, 3, 3,
        1, 1, 1, 1,
        0, 0, 0, 0,
        4, 4, 4, 4,
        5, 5, 5, 5,
        2, 2, 2, 2;

}
