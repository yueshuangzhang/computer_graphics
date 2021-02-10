#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // can make it simplier if have time
  // textbook P78: intersection occur when: e + td = a + beta(b-a) + gamma(c-a)
  // a, b, c vertices of tri
  // if and only if beta > 0, gamma > 0, beta + gamma < 1. 

  // GET THE CODE FROM PREVIOUS LAB _ RAY CASTING
  // === get tri vertices ===//
  Eigen::Vector3d v_a, v_b, v_c;
  v_a = A;
  v_b = B;
  v_c = C;

  // solve beta and gamma from cramer's rule:
  double x_a, x_b, x_c, y_a, y_b, y_c, z_a, z_b, z_c;
  x_a = v_a[0];
  x_b = v_b[0];
  x_c = v_c[0];
  y_a = v_a[1];
  y_b = v_b[1];
  y_c = v_c[1];
  z_a = v_a[2];
  z_b = v_b[2];
  z_c = v_c[2];

  double x_d, y_d, z_d, x_e, y_e, z_e;
  x_d = ray.direction[0];
  y_d = ray.direction[1];
  z_d = ray.direction[2];
  x_e = ray.origin[0];
  y_e = ray.origin[1];
  z_e = ray.origin[2];

  double a, b, c, d, e, f, g, h, i, j, k, l;
  a = x_a - x_b;
  b = y_a - y_b;
  c = z_a - z_b;
  d = x_a - x_c;
  e = y_a - y_c;
  f = z_a - z_c;
  g = x_d;
  h = y_d;
  i = z_d;
  j = x_a - x_e;
  k = y_a - y_e;
  l = z_a - z_e;

  double M;
  M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

  double beta, gamma, t_cal;
  beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
  gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
  t_cal = (-1) * (f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;

  // determine intersection
  if (t_cal < min_t) {//check if t in interval
    return false;
  }

  // check gamma range
  if (gamma < 0 || gamma > 1) {
    return false;
  }

  //check beta
  if (beta < 0 || beta >(1 - gamma)) {
    return false;
  }

  // modify values
  t = t_cal;

  return true;
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
}

