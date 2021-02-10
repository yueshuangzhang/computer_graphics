#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // sqrd distance = x^2 + y^2 + z^2
  double distance = 0;
  double sq_d = 0;
  for (int i = 0; i < 3; i++){
    //by x,y,z
    if (query[i] > box.max_corner[i]){
      // max corner to the point
      distance = query[i] - box.max_corner[i];
    } 
    else if (query[i] < box.min_corner[i]){
      // min corner to the point
      distance = box.min_corner[i] - query[i];
    }else{
      distance = 0;
    }
    //sum up the distance
    sq_d = pow(distance,2);
  }
  ////////////////////////////////////////////////////////////////////////////
}
