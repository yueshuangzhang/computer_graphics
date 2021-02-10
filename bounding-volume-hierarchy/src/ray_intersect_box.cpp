#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
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

  // define variable to hold return values
  double txmin, txmax, tymin, tymax, tzmin, tzmax;

  // if the x_d or y_d or z_d is negative, then the ray will hit x_max before x_min
  double p_inf = std::numeric_limits<double>::infinity();
  double n_inf = (-1)*std::numeric_limits<double>::infinity();

  if (x_d == 0) {
    if (x_min - x_e > 0)  return false;
    else txmin = n_inf;
    if (x_max - x_e < 0)  return false;
    else txmax = p_inf;
  }
  else if (x_d > 0) {
    txmin = (x_min - x_e) / x_d;
    txmax = (x_max - x_e) / x_d;
  } 
  else {
    txmin = (x_max - x_e) / x_d;
    txmax = (x_min - x_e) / x_d;
  }

  if (y_d == 0) {
    if (y_min - y_e > 0)  return false;
    else tymin = n_inf;
    if (y_max - y_e < 0)  return false;
    else tymax = p_inf;
  }
  else if (y_d > 0) {
    tymin = (y_min - y_e) / y_d;
    tymax = (y_max - y_e) / y_d;
  }
  else {
    tymin = (y_max - y_e) / y_d;
    tymax = (y_min - y_e) / y_d;
  }

  if (z_d == 0) {
    if (z_min - z_e > 0)  return false;
    else tzmin = n_inf;
    if (z_max - z_e < 0)  return false;
    else tzmax = p_inf;
  }
  else if (z_d > 0) {
    tzmin = (z_min - z_e) / z_d;
    tzmax = (z_max - z_e) / z_d;
  }
  else {
    tzmin = (z_max - z_e) / z_d;
    tzmax = (z_min - z_e) / z_d;
  }

  // find the interval
  double max_t_min, min_t_max;
  max_t_min = fmax(fmax(txmin, tymin), tzmin);
  min_t_max = fmin(fmin(txmax, tymax), tzmax);

  // must hit
  if (min_t_max < max_t_min) {
    return false;
  }
  else if (min_t_max < max_t || max_t_min > min_t) {
    return false;
  }
  else{
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
