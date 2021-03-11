// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  float angle = 0.5 * M_PI * animation_seconds;

  vec4 point_light = view * vec4(4 * cos(angle), 2, 4 * sin(angle), 1);

  vec3 n = normalize(normal_fs_in);
  vec3 v = normalize(view_pos_fs_in.xyz / view_pos_fs_in.w);
  vec3 l = normalize(point_light.xyz / point_light.w - view_pos_fs_in.xyz / view_pos_fs_in.w);


  vec3 ka, kd, ks;
  float p;
  
  if (is_moon){
    ka = vec3(0.05, 0.05, 0.05);
    ks = vec3(0.5, 0.5, 0.5);
    kd = vec3(1, 1, 1);
    p = 1000;

  }
  else{
    ka = vec3(0.05, 0.05, 0.05);
    ks = vec3(0.2, 0.2, 0.8);
    kd = vec3(1, 1, 1);
    p = 500;

  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);

  /////////////////////////////////////////////////////////////////////////////
}
