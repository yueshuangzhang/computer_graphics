#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // From slides, the x_min = min(v_xi), x_max = max(v_xi), so on the so forth

  //get the min corner from a, b, c in each axis

  for (int i = 0; i < 3; i++) {
    // since fmin takes only 2 values, then get the smallest by pair
    B.min_corner[i] = fmin(fmin(B.min_corner[i], a[i]), fmin(b[i], c[i]));
    B.max_corner[i] = fmax(fmax(B.min_corner[i], a[i]), fmax(b[i], c[i]));
  }

  ////////////////////////////////////////////////////////////////////////////
}


