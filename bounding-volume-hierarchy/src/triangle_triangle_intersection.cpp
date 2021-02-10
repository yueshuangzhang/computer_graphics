#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include "Ray.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d& A0,
  const Eigen::RowVector3d& A1,
  const Eigen::RowVector3d& A2,
  const Eigen::RowVector3d& B0,
  const Eigen::RowVector3d& B1,
  const Eigen::RowVector3d& B2)
{
  ////////////////////////////////////////////////////////////////////////////

  // test edge-tri intersection for all 6 edges

  double t, min_t, max_t;
  min_t = 0;
  max_t = 1;

  // if any of the edge intersect with the triangle plane, then the 2 triangle intersect
  // even if one's edge doesn't intersect with the other one, the other for sure will
  // intersect with it for them to have intersection

  Ray edge_1(A0, A1 - A0), edge_2(A1, A2 - A1), edge_3(A2, A1 - A2); // for tri A
  Ray edge_4(B0, B1 - B0), edge_5(B1, B2 - B1), edge_6(B2, B1 - B2); // for tri B

  if (ray_intersect_triangle(edge_1, B0, B1, B2, min_t, max_t, t) ||
    ray_intersect_triangle(edge_2, B0, B1, B2, min_t, max_t, t) ||
    ray_intersect_triangle(edge_3, B0, B1, B2, min_t, max_t, t) ||
    ray_intersect_triangle(edge_4, A0, A1, A2, min_t, max_t, t) ||
    ray_intersect_triangle(edge_5, A0, A1, A2, min_t, max_t, t) ||
    ray_intersect_triangle(edge_6, A0, A1, A2, min_t, max_t, t)) {
    return true;
  }
  return false; 
  ////////////////////////////////////////////////////////////////////////////
}
