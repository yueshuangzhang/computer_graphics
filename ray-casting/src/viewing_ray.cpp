#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // give the ray values. (origin, direction)

  // ray orgin = camara's eye
  ray.origin = camera.e;

  // ray direction
  //u = width/n_x * (j + 1/2) - width/2
  //v = height/n_y * (i + 1/2) - width/2

  double u = camera.width / width * (j + 0.5) - (camera.width / 2);
  double v = (-1) * camera.height / height * (i + 0.5) + (camera.height / 2);

  // ray = e + t(u(i)u + v(j)v + -dw)
  ray.direction = u * camera.u + v * camera.v - camera.d * camera.w;
  ////////////////////////////////////////////////////////////////////////////
}

