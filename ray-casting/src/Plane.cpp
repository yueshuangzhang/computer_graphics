#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  
  // do projecton of the ray onto the plane
  double projection;
  double numerator = (point - ray.origin).dot(normal);
  double demoinator = (ray.direction).dot(normal);

  //check if value valid
  if (demoinator == 0){
    return false;
  }

  //calculate projection value
  projection = numerator/demoinator;

  if(projection >= min_t){
    t = projection;
    n = normal.normalized();
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

