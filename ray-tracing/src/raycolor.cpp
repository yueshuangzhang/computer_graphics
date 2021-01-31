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

  if (num_recursive_calls > 10){
    return false;
  }

  if (hit){

    // get blinn_phong_shading rgb
    rgb = rgb + blinn_phong_shading(ray, hit_id, t, n, objects, lights);;
    
    // get reflect ray
    Ray reflect_ray;
    reflect_ray.origin = ray.origin + t * ray.direction;
    reflect_ray.direction = reflect(ray.direction, n);

    // get reflect rgb
    Eigen::Vector3d reflect_rgb;
    bool recursive_raycolor;
    recursive_raycolor = raycolor(reflect_ray, 1.0e-6, objects, lights, num_recursive_calls+1, reflect_rgb);
    if (recursive_raycolor){
      rgb += (objects[hit_id]->material->km.array()*reflect_rgb.array()).matrix();
    }
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
