#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  // initialize value
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();

  // find and replace the value
  for (int i = 0; i < points.rows(); i++) {
    //calculate the distance between point & query
    double distance = (points.row(i) - query).squaredNorm();
    if (distance < sqrD) {
      // if a closer neighbour is found:
      // update value
      sqrD = distance;
      I = i;
    }
  }
}
