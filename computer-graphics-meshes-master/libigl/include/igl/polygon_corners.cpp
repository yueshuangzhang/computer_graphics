// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2020 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "polygon_corners.h"

template <
  typename PType, 
  typename DerivedI,
  typename DerivedC>
IGL_INLINE void igl::polygon_corners(
  const std::vector<std::vector<PType> > & P,
  Eigen::PlainObjectBase<DerivedI> & I,
  Eigen::PlainObjectBase<DerivedC> & C)
{
  typedef typename DerivedI::Scalar IType;
  // JD: Honestly you could do a first loop over P, compute C, and then fill the
  // entries of I directly. No need for guesses and push_back(), or the extra
  // copy at the end. That would be more efficient.
  std::vector<IType> vI;vI.reserve(P.size()*4);
  C.resize(P.size()+1);
  C(0) = 0;
  for(size_t p = 0;p<P.size();p++)
  {
    C(p+1) = C(p)+P[p].size();
    for(size_t c = 0;c<P[p].size();c++)
    {
      vI.push_back(P[p][c]);
    }
  }
  I = Eigen::Map<DerivedI>(vI.data(),vI.size());
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::polygon_corners<int, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
#endif
