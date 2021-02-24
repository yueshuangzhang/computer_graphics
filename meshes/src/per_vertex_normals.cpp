#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Compute per vertex normals for a triangle mesh by computing the area-weighted
  // average of normals at incident faces.

  // Similar to per_corner_normals 
  std::vector<std::vector<int>> VF;
  // V.rows() is number of vertices
  vertex_triangle_adjacency(F, V.rows(), VF);

  //Eigen::RowVector3d normal(0, 0, 0);
  // loop throught adjacency list
  for (int i = 0; i < VF.size(); i++){
    Eigen::RowVector3d normal(0, 0, 0);
    for (int j = 0; j < VF[i].size(); j++){
      // get the vf's value at i j position
      normal = normal + triangle_area_normal(V.row(F(VF[i][j], 0)), V.row(F(VF[i][j], 1)), V.row(F(VF[i][j], 2)));
    }
    N.row(i) = normal.normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}
