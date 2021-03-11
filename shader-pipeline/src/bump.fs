// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  vec3 T, B;
  tangent(normalize(sphere_fs_in), T, B);

  vec3 bp = bump_position(is_moon, sphere_fs_in);

  vec3 bump1 = (bump_position(is_moon, sphere_fs_in + 0.0001 * T) - bp) / 0.0001;
  vec3 bump2 = (bump_position(is_moon, sphere_fs_in + 0.0001 * B) - bp) / 0.0001;


  vec3 n = normalize(cross(bump1, bump2));

  // n
  if(dot(n, sphere_fs_in) < 0){
    n = (-1) * n;
  }

  //vec3 blinn_phong(ka, kd, ks, p, n, v, l)

  // v
  vec3 v = normalize ((-1) * view_pos_fs_in.xyz / view_pos_fs_in.w);

  // l 
  vec3 l = point_light.xyz / point_light.w - view_pos_fs_in.xyz / view_pos_fs_in.w;

  vec3 ka, ks, kd;
  float p;
  if (is_moon){
    ka = vec3(0.12, 0.1, 0.1);
    ks = vec3(0.9, 0.9, 0.9);
    kd = vec3(0.475, 0.4, 0.4);
    p = 1000;

  }else{
    ka = vec3(0.2, 0.3, 0.5);
    ks = vec3(0.6, 0.7, 0.7);
    kd = vec3(0.1, 0.3, 0.8);
    p = 500;
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
