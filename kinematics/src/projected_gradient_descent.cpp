#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < max_iters; i++){
    Eigen::VectorXd diff_z = grad_f(z);
    z = z - diff_z * line_search(f, proj_z, z, diff_z, 10000.0);
    proj_z(z);
  }
  /////////////////////////////////////////////////////////////////////////////
}
