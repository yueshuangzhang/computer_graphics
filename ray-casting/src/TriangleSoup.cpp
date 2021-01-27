#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // find the first hit object in the soup by calling the first hit helper function
  int hit_id = -1;
  double hit_t;
  Eigen::Vector3d hit_n;
  
  bool hit = first_hit(ray, min_t, triangles, hit_id, hit_t, hit_n);

  if(hit){
    t = hit_t;
    n = hit_n;
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}



