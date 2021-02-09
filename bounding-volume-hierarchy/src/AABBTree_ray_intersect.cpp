#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////

  // get the e & d vector
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;

  // define empty variable to hold 


  return false;
  ////////////////////////////////////////////////////////////////////////////
}

