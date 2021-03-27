#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  

  Eigen::MatrixXd y;
  y.resize(V.rows(), 3);
  y = (M * (2 * Ucur - Uprev)) / pow(delta_t, 2) + fext;

  Eigen::MatrixXd d;
  d.resize(E.rows(), 3);

  Unext = Ucur;

  for(int iter = 0;iter < 50;iter++)
  {
    for (int i = 0; i < E.rows(); i++){
      Eigen::RowVector3d Unext_diff = Unext.row(E(i, 0)) - Unext.row(E(i, 1));
      d.row(i) = r[i] * Unext_diff.normalized();
    }

    double w = 1e10;
    Eigen::MatrixXd p_ver = k * A.transpose() * d + y + w * C.transpose() * C * V;
    // solve
    Unext = prefactorization.solve(p_ver);
  }
  //////////////////////////////////////////////////////////////////////////////
}
