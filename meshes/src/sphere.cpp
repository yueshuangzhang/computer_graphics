#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  //   num_faces_u  number of faces in the longitudinal direction ( num row)
  //   num_faces_v  number of faces in the latitudinal direction ( num col)
  int num_face = num_faces_u * num_faces_v;
  int num_face_vertex = (num_faces_u + 1) * (num_faces_v+1);

  //   V  #V by 3 list of 3D corner vertex positions
  //   UV  #UV by 2 list of corner parameterization positions
  //   NV  #NV  by 3 list of 3D unit normal vectors
  V.resize(num_face_vertex , 3);
  UV.resize(num_face_vertex, 2);
  NV.resize(num_face_vertex, 3);
  
  // find the coordinat of the vertex
  // phi(x, y, z) = ([pi + atan2(y, x)] / (2 * pi), [pi - acos(z/x.norm)] / pi)
  // atan2(y, x) = tan-1(y/x)
  // reverse the formula: y/x = tan(u - pi) ------ z/|x| = cos(pi - v)* pi
  
  // formula: theta: z-r     phi: x - (r sin(theta))
  // x = r sin(theta) cos(phi)
  // y = r sin(theta) sin(phi)
  // z = r cos(theta)
  
  double r = 1;
  double delta_theta = M_PI / num_faces_u; // /#row
  double delta_phi = 2 * M_PI / num_faces_v;// /#col

  int track = 0;

  for (int u = 0; u < num_faces_u + 1; u++){ // row
    for (int v = 0; v < num_faces_v + 1; v++){ // col
      double theta, phi;
      theta = u * delta_theta;
      phi = v * delta_phi;

      double x, y, z;
      x = r * sin(theta) * cos(phi);
      y = r * sin(theta) * sin(phi);
      z = r * cos(theta);

      
      V.row(track) = Eigen::RowVector3d(x, y, z);
      UV.row(track) = Eigen::RowVector2d(static_cast<double>(u) / num_faces_u, static_cast<double>(v) / num_faces_v);
      NV.row(track) = Eigen::RowVector3d(x, y, z);
      
      track ++;
    }
  }
  //   F  #F by 4 list of quad face indices into rows of V
  //   UF  #F by 4 list of quad face indices into rows of UV
  //   NF  #F by 4 list of quad face indices into rows of NV

  F.resize(num_face, 4);
  UF.resize(num_face, 4);
  NF.resize(num_face, 4);
 
  track = 0;
  
  for (int u = 0; u < num_faces_u; u++) {
    for (int v = 0; v < num_faces_v; v++) {
      
      int v1, v2, v3, v4;
      v1 = u * (num_faces_v + 1) + v;
      v2 = (u + 1) * (num_faces_v + 1) + v;
      v3 = v2 + 1;
      v4 = v1 + 1;

      F.row(track) = Eigen::RowVector4i(v1, v2, v3, v4);
      UF.row(track) = Eigen::RowVector4i(v1, v2, v3, v4);
      NF.row(track) = Eigen::RowVector4i(v1, v2, v3, v4);
      
      track++;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
