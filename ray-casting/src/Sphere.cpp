#include "Sphere.h"
#include "Ray.h"
#include <cmath>
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Eigen::Vector3d center;
  // double radius;
  // textbook P 76.
  // ray p=e+td, sphere: center x_c, y_c, z_c, radius R. 
  // (e+td-c) dot (e+td-c) -R^2 = 0
  // t = -b +- sqrt(b^2 - 4ac) / 2a
  
  Eigen::Vector3d d, e, c;
  d = ray.direction;
  e = ray.origin;
  c = center;

  double A, B, C;
  A = d.dot(d);
  B = 2*d.dot(e - c);
  C = (e - c).dot((e - c)) - pow(radius,2);

  double discriminant = pow(B,2) - 4*A*C;

  if(discriminant < 0){
    // root img, no intersection
    return false;
  }
  else if(discriminant == 0){ // one solution, touch one point
    double t_cal = ((-1)*B + sqrt(discriminant)) / (2*A);
    if(t_cal >= min_t){
      t = t_cal;
      n = ((e + t*d) - c) / radius;
      n = n.normalized();
      return true;
    }
  }else{
    // find in & out
    double t_cal_1 = ((-1)*B + sqrt(discriminant)) / (2*A);
    double t_cal_2 = ((-1)*B - sqrt(discriminant)) / (2*A);

    if(t_cal_1 < t_cal_2 && t_cal_1 >= min_t){
      t = t_cal_1;
      n = ((e + t*d) - c) / radius;
      n = n.normalized();
      return true;
    }else if(t_cal_2 < t_cal_1 && t_cal_2 >= min_t){
      t = t_cal_2;
      n = ((e + t*d) - c) / radius;
      n = n.normalized();
      return true;
    }
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

