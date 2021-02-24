#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // for the vertexes in the triangle, find the normal
  // Outputs:
  //   N  #F*3 by 3 list of mesh vertex 3D normals, where the normal
  //     for corner F(i,j) is at N.row(i*3+j)
  std::vector<std::vector<int>> VF;
  //V.rows() is number of vertices
  vertex_triangle_adjacency(F, V.rows(), VF);

  //computing the area-weighted average of normals at incident faces 
  //whose normals deviate less than the provided threshold.
  
  Eigen::RowVector3d normal;
  Eigen::RowVector3d area_normal, adj_normal;

  for (int i = 0; i < F.rows(); i++){
    for (int j = 0; j < F.cols(); j++){
      area_normal = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
      area_normal = area_normal.normalized();
      
      Eigen::RowVector3d normal(0, 0, 0);
      double area = 0;
      
      std::vector<int> vertex = VF[F(i, j)];
      for (int k : vertex){
        adj_normal = triangle_area_normal(V.row(F(k, 0)), V.row(F(k, 1)), V.row(F(k, 2)));
        adj_normal = adj_normal.normalized();

        //check threshold
        if(area_normal.dot(adj_normal) > (cos(corner_threshold * M_PI / 180.0))){
          area = area + adj_normal.norm();
          normal = normal + adj_normal;
        }
      
      }

    N.row(F.cols() * i + j) = (normal / area).normalized();
    
    }
  }
}
