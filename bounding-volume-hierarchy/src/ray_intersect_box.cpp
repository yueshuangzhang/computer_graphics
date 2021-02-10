#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // can make it simplier if have time
  // From text book page 299, the formulas are explained
  // get box info
  double x_min, y_min, z_min, x_max, y_max, z_max;
  x_min = box.min_corner[0];
  y_min = box.min_corner[1];
  z_min = box.min_corner[2];
  x_max = box.max_corner[0];
  y_max = box.max_corner[1];
  z_max = box.max_corner[2];

  // get the e & d vector
  double x_e, y_e, z_e;
  x_e = ray.origin[0];
  y_e = ray.origin[1];
  z_e = ray.origin[2];

  double x_d, y_d, z_d; 
  x_d = ray.direction[0];
  y_d = ray.direction[1];
  z_d = ray.direction[2];

  double alpha_x, alpha_y, alpha_z; 
  alpha_x = 1 / x_d;
  alpha_y = 1 / y_d;
  alpha_z = 1 / z_d;

  // define variable to hold return values
  double txmin, txmax, tymin, tymax, tzmin, tzmax;

  // if the x_d or y_d or z_d is negative, then the ray will hit x_max before x_min

  if (x_d >= 0) {
    txmin = alpha_x * (x_min - x_e);
    txmax = alpha_x * (x_max - x_e);
  } 
  else {
    txmin = alpha_x * (x_max - x_e);
    txmax = alpha_x * (x_min - x_e);
  }

  if (y_d >= 0) {
    tymin = alpha_y * (y_min - y_e);
    tymax = alpha_y * (y_max - y_e);
  }
  else {
    tymin = alpha_y * (y_max - y_e);
    tymax = alpha_y * (y_min - y_e);
  }

  if (z_d >= 0) {
    tzmin = alpha_z * (z_min - z_e);
    tzmax = alpha_z * (z_max - z_e);
  }
  else {
    tzmin = alpha_z * (z_max - z_e);
    tzmax = alpha_z * (z_min - z_e);
  }

  // find the interval
  double max_t_min, min_t_max, min_max, max_min;
  max_t_min = fmax(fmax(txmin, tymin), tzmin);
  min_t_max = fmin(fmin(txmax, tymax), tzmax);
  min_max = fmin(max_t, min_t_max);
  max_min = fmax(min_t, max_t_min);
  // must hit
  if (min_t_max < max_t_min) {
    return false;
  }
  else if (min_max < max_min) {
    return false;
  }
  else{
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
