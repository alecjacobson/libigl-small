// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2016 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "grid.h"

template <
  typename Derivedres,
  typename DerivedGV>
IGL_INLINE void igl::grid(
  const Eigen::MatrixBase<Derivedres> & res, 
  Eigen::PlainObjectBase<DerivedGV> & GV)
{
  using namespace Eigen;
  typedef typename DerivedGV::Scalar Scalar;
  GV.resize(res(0)*res(1)*res(2),3);
  for(int zi = 0;zi<res(2);zi++)
  {
    const auto lerp = 
      [&](const Scalar di, const int d)->Scalar{return di/(Scalar)(res(d)-1);};
    const Scalar z = lerp(zi,2);
    for(int yi = 0;yi<res(1);yi++)
    {
      const Scalar y = lerp(yi,1);
      for(int xi = 0;xi<res(0);xi++)
      {
        const Scalar x = lerp(xi,0);
        GV.row(xi+res(0)*(yi + res(1)*zi)) = 
          Eigen::Matrix<Scalar,1,3>(x,y,z);
      }
    }
  }
}


#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::grid<Eigen::Matrix<float, 1, 3, 1, 1, 3>, Eigen::Matrix<float, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<float, -1, -1, 0, -1, -1> >&);
template void igl::grid<Eigen::Matrix<int, 1, 3, 1, 1, 3>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<int, 1, 3, 1, 1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
#endif
