// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////

  vec3 t = vec3(0,1,0);

  T = cross(N, t);
  B = cross(T, N);

  T = normalize(T);
  B = normalize(B);
  /////////////////////////////////////////////////////////////////////////////
}
