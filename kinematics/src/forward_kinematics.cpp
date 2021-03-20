#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  Eigen::Affine3d cal_T(const Skeleton & skeleton, int i);
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for (int i = 1; i < skeleton.size(); i++){
    T[i] = cal_T(skeleton, i);
  }
  /////////////////////////////////////////////////////////////////////////////
}

Eigen::Affine3d cal_T(const Skeleton & skeleton, int i){
  if (skeleton[i].parent_index == -1){
    return Eigen::Affine3d::Identity();
  }
  Eigen::Affine3d T_parent = cal_T(skeleton, skeleton[i].parent_index);
  return T_parent * skeleton[i].rest_T * euler_angles_to_transform(skeleton[i].xzx) * (skeleton[i].rest_T).inverse();
  // change this
}
