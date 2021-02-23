#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // find the normal vector: ab cross ac
  Eigen::RowVector3d d = (b-a).cross(c-a);
  double length_d = d.norm() * 0.5;
  return d.normalized() * length_d;
}
