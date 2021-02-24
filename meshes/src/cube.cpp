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
  
  // V  8 by 3 list of 3D corner vertex positions
  // F  6 by 4 list of quad face indices into rows of V
  // UV  14 by 2 list of corner parameterization positions
  // UF  6 by 4 list of quad face indices into rows of UV
  // NV  6 by 3 list of 3D unit normal vectors
  // NF  6 by 4 list of quad face indices into rows of NV
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  // V  8 by 3 list of 3D corner vertex positions
  V <<  0, 0, 0,
        0, 0, 1,
        0, 1, 0,
        0, 1, 1,
        1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1;

  //   F  6 by 4 list of quad face indices into rows of V
  F <<  0, 4, 5, 1,
        2, 3, 7, 6,
        7, 3, 1, 5,
        2, 6, 4, 0,
        2, 0, 1, 3,
        6 ,7, 5, 4;

  //   UV  14 by 2 list of corner parameterization positions
  UV << 0.25, 0,
        0.5, 0,
        0, 0.25,
        0.25, 0.25,
        0.5, 0.25,
        0.75, 0.25,
        1, 0.25,
        0, 0.5,
        0.25, 0.5,
        0.5, 0.5,
        0.75, 0.5,
        1, 0.5,    
        0.25, 0.75,
        0.5, 0.75;

  //   UF  6 by 4 list of quad face indices into rows of UV
  UF << 1, 4, 3, 0,
        9, 13, 12, 8,
        5, 10, 9, 4,
        3, 8, 7, 2,
        8, 3, 4, 9,
        10, 5, 6, 11;

  //   NV  6 by 3 list of 3D unit normal vectors
  NV << 1, 0, 0,
        -1, 0, 0,
        0, 1, 0,
        0, -1, 0,
        0, 0, 1,
        0, 0, -1;
  
  //   NF  6 by 4 list of quad face indices into rows of NV
  NF << 3, 3, 3, 3,
        2, 2, 2, 2,
        4, 4, 4, 4,
        5, 5, 5, 5,
        1, 1, 1, 1,
        0, 0, 0, 0;

}
