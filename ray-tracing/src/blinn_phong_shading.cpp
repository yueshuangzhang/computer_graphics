#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // hard-coded value of ia=0.1 for ambient light
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);

  // Ambient Light: k_a * I_a
  // rgb + Ambient
  rgb = rgb + 0.1 * objects[hit_id]->material->ka;

  //ray from point to light (l)
  Ray l ;
  l.origin= ray.origin + t * ray.direction;

  for (int i = 0; i < lights.size(); i++){

    // find max t   
    double max_t;
    lights[i]->direction(l.origin, l.direction, max_t);

    // check if the object is hit   
    int hit_i;
    double hit_t;
    Eigen::Vector3d hit_n;
    bool hit = first_hit(l, 1.0e-6, objects, hit_i, hit_t, hit_n);

    if(!hit || hit_t >= max_t){
      
      // Lambertian Light: k_d*I*max(0,n dot l)
      // k_d*max(0,n dot l)
      Eigen::Vector3d lambertian = objects[hit_id]->material->kd * (fmax(0, n.dot(l.direction)));
      // rgb + Lambertian
      rgb = rgb + (lambertian.array() * lights[i]->I.array()).matrix();

      // Specular Light: k_s*I*max(0,n dot h)^n  
      Eigen::Vector3d h = (-1) * ray.direction + l.direction;
      h = h.normalized();
      // k_s*max(0,n dot h)^n 
      Eigen::Vector3d specular = (objects[hit_id]->material->ks) * (pow(fmax(0, n.dot(h)), objects[hit_id]->material->phong_exponent));

      // rgb + Specular 
      rgb = rgb + (specular.array() * lights[i]->I.array()).matrix();

    }
  }
  
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
