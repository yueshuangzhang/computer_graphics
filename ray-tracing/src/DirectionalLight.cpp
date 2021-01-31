#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  //    d  3D direction from point toward light as a vector.
  // in this: d = Direction _from_ light toward scene.
  d = ((-1) * this->d).normalized();
  
  //    max_t  parametric distance from q along d to light (may be inf)
  max_t = std::numeric_limits<double>::infinity();
  
  ////////////////////////////////////////////////////////////////////////////
}

