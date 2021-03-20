#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd t_tips = transformed_tips(copy, b);

    double squared = 0;
    double temp = 0;
    for (int i = 0; i < b.size(); i++){
      Eigen::Vector3d t_tips_v = Eigen::Vector3d(t_tips[3 * i], t_tips[3 * i + 1], t_tips[3 * i + 2]);
      Eigen::Vector3d xb0_v = Eigen::Vector3d(xb0[3 * i], xb0[3 * i + 1], xb0[3 * i + 2]);
      temp = (t_tips_v - xb0_v).squaredNorm();
      squared = squared + temp;
    }

    return squared;

  };


  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {

    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd t_tips = transformed_tips(copy, b);

    // get jacobian
    Eigen::MatrixXd jacob;
    kinematics_jacobian(copy, b, jacob);

    Eigen::VectorXd t_value = Eigen::VectorXd::Zero(A.size());

    double dedx;
    
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j < 3; j++) {
            t_value = t_value + 2 * (t_tips[3 * i + j] - xb0[3 * i + j]) * jacob.row(3 * i + j).transpose();
        }
    }

    return t_value;

  };


  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size() * 3 == A.size());
    
    for (int i = 0; i < skeleton.size(); i++) {
        for (int j = 0; j < 3; j++) {
            A[i * 3 + j] = std::max(skeleton[i].xzx_min[j],
                            std::min(skeleton[i].xzx_max[j], A[3 * i + j]));
        }
    }

    assert(skeleton.size()*3 == A.size());

  };
  /////////////////////////////////////////////////////////////////////////////
}
