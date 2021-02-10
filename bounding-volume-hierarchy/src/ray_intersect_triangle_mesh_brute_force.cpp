#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////

  hit_t = 0;
  hit_f = 0;

  // SAME LOGIC AS RAY CASTING _ TRIANGLE SOUP
  // find the first hit object in the soup by calling the first hit helper function
  int hit_id = -1;
  double t_cal;
  double t_keep = std::numeric_limits<double>::infinity();
  int f_keep = -1;
  bool ever_hit = false;
  //   V  #V by 3 list of mesh vertex positions
  //   F  #F by 3 list of triangle indices into rows of V
  for (int i = 0; i < F.rows(); ++i) {
    bool hit = ray_intersect_triangle(ray, V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, t_cal);

    if (hit && ( t_cal < t_keep)) {
      t_keep = t_cal;
      f_keep = i;
      ever_hit = true;
    }
  }

  if (ever_hit) {
    hit_t = t_keep;
    hit_f = f_keep;
  }
  
  return ever_hit;
  ////////////////////////////////////////////////////////////////////////////
}
