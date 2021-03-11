// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient ambient_intensity.
//
// Inputs:
//   ka  rgb ambient color
//   kd  rgb diffuse color
//   ks  rgb specular color
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit direction from point on object to eye
//   l  unit light direction
// Returns rgb color
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  /////////////////////////////////////////////////////////////////////////////
  
  vec3 ambient_intensity = vec3(1, 1, 1);

  return ka * ambient_intensity 
        + kd * ambient_intensity * max(0, dot(n, l)) 
        + ks * ambient_intensity * pow(max(0, dot(n, normalize(v+l))), p);

  /////////////////////////////////////////////////////////////////////////////
}


