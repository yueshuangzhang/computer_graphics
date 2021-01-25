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

  // When t=1, then ray.origin + t*ray.direction
  // 3d vector [0][1][2]
  ray.direction[0] = 0;

  //land exactly on the center of the pixel (i,j)

  ////////////////////////////////////////////////////////////////////////////
}

