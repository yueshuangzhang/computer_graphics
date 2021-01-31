#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // check which object is hit, if the hit object the closest
  bool hit = false;
  double hit_closest_distance;
  Eigen::Vector3d hit_closest_normal;
  int hit_closest_id;

  //output from intersect functin
  double hit_distance;
  Eigen::Vector3d hit_normal;

  // loop throught all object to detect
  for (int i = 0; i < objects.size(); i++){
    //check if the current object is hit by the ray
    if (objects[i]->intersect(ray, min_t, hit_distance, hit_normal) == true){
      if (hit == false){//first time hitting
        hit = true;
        hit_closest_distance = hit_distance;
        hit_closest_normal = hit_normal;
        hit_closest_id = i;
      }
      else{ //2nd and on
        // found a closer hit point
        if (hit_distance < hit_closest_distance){
          //update variables
          hit_closest_distance = hit_distance;
          hit_closest_normal = hit_normal;
          hit_closest_id = i;
        }
      }
    }
  }

  // update output
  if (hit){
    hit_id = hit_closest_id;
    t = hit_closest_distance;
    n = hit_closest_normal;
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

