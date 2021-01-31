#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // r = d - 2(d·n)n
  Eigen::Vector3d reflect_ray;
  reflect_ray = (in - 2 * (in.dot(n)) * n).normalized();
  return reflect_ray;
  ////////////////////////////////////////////////////////////////////////////
}
