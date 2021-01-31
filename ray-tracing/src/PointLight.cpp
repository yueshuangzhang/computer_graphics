#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  
  //d  3D direction from point toward light as a vector. d = qp
  d = p - q;
  d = d.normalized();

  //max_t  parametric distance from q along d to light (may be inf)
  max_t = d.norm();

  ////////////////////////////////////////////////////////////////////////////
}
