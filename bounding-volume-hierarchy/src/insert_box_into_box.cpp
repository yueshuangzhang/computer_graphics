#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Grow a box `B` by inserting a box `A`.
  
  for (int i = 0; i < 3; i++) {
    // for x & y & z 0,1,2
    B.min_corner[i] = fmin(A.min_corner[i], B.min_corner[i]);
    B.max_corner[i] = fmin(A.max_corner[i], B.max_corner[i]);
  }

  ////////////////////////////////////////////////////////////////////////////
}

