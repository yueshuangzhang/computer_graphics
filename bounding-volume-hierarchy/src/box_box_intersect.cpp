#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  for (int i=0; i<3; ++i) {
    if (A.min_corner[i] > B.max_corner[i] || B.min_corner[i] > A.max_corner[i])
      return false; // Boxes dont intersect because it doesn't intersect on the current axis i.
  }

  // Boxes intersect on all axes.
  return true;
}

