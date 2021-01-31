#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  rgb = Eigen::Vector3d(0,0,0);

  // check if the object hit
  int hit_id;
  double t;
  Eigen::Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);

  if (hit){

    // get rgb
    rgb = rgb + blinn_phong_shading(ray, hit_id, t, n, objects, lights);;
    
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
