#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::Affine3d A, B, C;
  double angle_x  = xzx[0] * M_PI/180;
  double angle_z = xzx[1] * M_PI/180;
  double angle_x2 = xzx[2] * M_PI/180;
  
  A.matrix() << 1, 0, 0, 0,
                0, cos(angle_x), -sin(angle_x), 0,
                0, sin(angle_x), cos(angle_x), 0,
                0, 0, 0, 1; 

  B.matrix() << cos(angle_z), -sin(angle_z), 0, 0,
                sin(angle_z), cos(angle_z), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1;

  C.matrix() << 1, 0, 0, 0,
                0, cos(angle_x2), -sin(angle_x2), 0,
                0, sin(angle_x2), cos(angle_x2), 0,
                0, 0, 0, 1; 

  return C * B * A;
  /////////////////////////////////////////////////////////////////////////////
}
