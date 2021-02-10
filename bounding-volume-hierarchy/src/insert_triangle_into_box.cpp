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
    B.min_corner[i] = std::min({ B.min_corner[i], a[i], b[i], c[i] });
    B.max_corner[i] = std::max({ B.max_corner[i], a[i], b[i], c[i] });
  }

  ////////////////////////////////////////////////////////////////////////////
}


