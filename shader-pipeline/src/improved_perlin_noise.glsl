// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  vec3 min_st = floor(st);
  vec3 max_st = ceil(st);
  vec3 f = fract(st);
  vec3 interpolate_f = improved_smooth_step(f);

  vec3 vertice1 = vec3(min_st.x, min_st.y, min_st.z);
  vec3 vertice2 = vec3(max_st.x, min_st.y, min_st.z);
  vec3 vertice3 = vec3(min_st.x, max_st.y, min_st.z);
  vec3 vertice4 = vec3(min_st.x, min_st.y, max_st.z);
  vec3 vertice5 = vec3(max_st.x, max_st.y, min_st.z);
  vec3 vertice6 = vec3(max_st.x, min_st.y, max_st.z);
  vec3 vertice7 = vec3(min_st.x, max_st.y, max_st.z);
  vec3 vertice8 = vec3(max_st.x, max_st.y, max_st.z);

  vec3 D1 = normalize(st - vertice1);
  vec3 D2 = normalize(st - vertice2);
  vec3 D3 = normalize(st - vertice3);
  vec3 D4 = normalize(st - vertice4);
  vec3 D5 = normalize(st - vertice5);
  vec3 D6 = normalize(st - vertice6);
  vec3 D7 = normalize(st - vertice7);
  vec3 D8 = normalize(st - vertice8);

  vec3 G1 = random_direction(vertice1);
  vec3 G2 = random_direction(vertice2);
  vec3 G3 = random_direction(vertice3);
  vec3 G4 = random_direction(vertice4);
  vec3 G5 = random_direction(vertice5);
  vec3 G6 = random_direction(vertice6);
  vec3 G7 = random_direction(vertice7);
  vec3 G8 = random_direction(vertice8);

  float I1 = dot(D1, G1);
  float I2 = dot(D2, G2);
  float I3 = dot(D3, G3);
  float I4 = dot(D4, G4);
  float I5 = dot(D5, G5);
  float I6 = dot(D6, G6);
  float I7 = dot(D7, G7);
  float I8 = dot(D8, G8);

  float mix1 = mix(I1, I2, interpolate_f.x);
  float mix2 = mix(I3, I4, interpolate_f.x);
  float mix3 = mix(I5, I6, interpolate_f.x);
  float mix4 = mix(I7, I8, interpolate_f.x);

  float mix5 = mix(mix1, mix2, interpolate_f.y);
  float mix6 = mix(mix3, mix4, interpolate_f.y);

  float mix_end = mix(mix5, mix6, interpolate_f.z);

  return mix_end/sqrt(3);
  /////////////////////////////////////////////////////////////////////////////
}

