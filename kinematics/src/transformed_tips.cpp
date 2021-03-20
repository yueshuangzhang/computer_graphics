#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  
  Eigen::VectorXd transformed_tip = Eigen::VectorXd::Zero(3*b.size());

  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;

  forward_kinematics(skeleton, T);

  for(int i = 0; i < b.rows(); i++){
    int bi = b[i];
    Bone bone = skeleton[bi];

    Eigen::Vector4d tip = T[bi] * bone.rest_T * Eigen::Vector4d(bone.length, 0, 0, 1);
    
    transformed_tip[3 * i + 0] = tip[0] / tip[3];
    transformed_tip[3 * i + 1] = tip[1] / tip[3];
    transformed_tip[3 * i + 2] = tip[2] / tip[3];
  }
  return transformed_tip;
  /////////////////////////////////////////////////////////////////////////////
}
