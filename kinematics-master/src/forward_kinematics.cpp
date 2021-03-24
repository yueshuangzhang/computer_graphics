#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

/////////////////////////////////////////////////////////////////////////////
// define the recursive function to call 
Eigen::Affine3d compute_T_new(const Skeleton & skeleton, int i);
/////////////////////////////////////////////////////////////////////////////
  
void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  // resize the skeleton vector
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());

  for (int i = 1; i < skeleton.size(); i++){
    T[i] = compute_T_new(skeleton, i);
  }
  /////////////////////////////////////////////////////////////////////////////
}

Eigen::Affine3d compute_T_new(const Skeleton & skeleton, int i){

  if (skeleton[i].parent_index != -1){
    // then get the parent
    Eigen::Affine3d parent = compute_T_new(skeleton, skeleton[i].parent_index);
    Eigen::Affine3d inverse = skeleton[i].rest_T.inverse();
    Eigen::Affine3d euler_transform = skeleton[i].rest_T * euler_angles_to_transform(skeleton[i].xzx);

    return parent * euler_transform * inverse;
    
  }else{
    // parent index == 1, return the identity matrix
    return Eigen::Affine3d::Identity();
  }

}
