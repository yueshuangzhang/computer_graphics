#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < 3; i++) {
    //in x, y, z axis, if any of the corner dont intersect, then the case fails
    if (A.min_corner[i] > B.max_corner[i] || B.min_corner[i] > A.max_corner[i])
      return false;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

