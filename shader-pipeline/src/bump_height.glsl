// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  vec3 bump; 
  float bump_height;
  if (is_moon){
    bump = vec3(10, 10, -10);
    bump_height = 0.8;
  }
    
  else{
    bump = vec3(1, -1, 1);
    bump_height = 0.2;
  }
    
  float height = improved_perlin_noise(vec3(improved_perlin_noise(bump * s)));

  return bump_height * smooth_heaviside(height, length(bump));

  /////////////////////////////////////////////////////////////////////////////
}
