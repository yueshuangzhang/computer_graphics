#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  
  double sigma = max_step;
  Eigen::VectorXd new_z = z - sigma * dz;
  proj_z(new_z);

  while (f(new_z) > f(z)) {
    sigma = 0.5 * sigma;
    new_z = z - sigma * dz;
    proj_z(new_z);
  }
  return sigma;

  /////////////////////////////////////////////////////////////////////////////
}
