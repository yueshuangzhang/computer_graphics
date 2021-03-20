#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{

  // recursion
  int hi = 0;
  /////////////////////////////////////////////////////////////////////////////
  if (keyframes.size() == 0){
    return Eigen::Vector3d(0, 0, 0);
  }
  t = fmod(t, keyframes.back().first);

  int i;
  for (i = 0; i < keyframes.size(); i++){
    if (keyframes[i].first > t){
      break;
    }
  }


  Eigen::Vector3d p0, p1, p2, p3;
  double t0, t1, t2, t3;
  Eigen::Vector3d inteprolated_value;
  Eigen::Vector3d a, b, c, d, e;

  // apply offset
  if (i - 2 < 0 || i == keyframes.size() - 1){
    p0 = keyframes[i - 1].second;
    p1 = keyframes[i].second;

    t0 = keyframes[i - 1].first;
    t1 = keyframes[i].first;

    double m, m2;
    m = (t - t0)/(t1 - t0);
    m2 = 0.5 * (1 - cos(m * 3.14));

    return (p0 * (1 - m2) + p1 * m2);

  }else{
    p0 = keyframes[i - 2].second;
    p1 = keyframes[i - 1].second;
    p2 = keyframes[i].second;
    p3 = keyframes[i + 1].second;

    t0 = keyframes[i - 2].first;
    t1 = keyframes[i - 1].first;
    t2 = keyframes[i].first;
    t3 = keyframes[i + 1].first;

    a = ((t1 - t)/(t1 - t0))* p0 + ((t - t0)/(t1 - t0)) * p1;
  	b = ((t2 - t)/(t2 - t1))* p1+((t - t1)/(t2 - t1)) * p2;
  	c = ((t3 - t)/(t3 - t2))* p2+((t - t2)/(t3 - t2)) * p3;

  	d = ((t2 - t)/(t2 - t0))* a + ((t - t0)/(t2 - t0)) * b;
  	e = ((t3 - t)/(t3 - t1))* b + ((t - t1)/(t3 - t1)) * c;
  	inteprolated_value = ((t2 - t)/(t2 - t1)) * d+((t - t1)/(t2 - t1)) * e;

  	return inteprolated_value;
  }




  

  /////////////////////////////////////////////////////////////////////////////
}
