// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2014 Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "vertex_triangle_adjacency.h"

template <typename DerivedF, typename VFType, typename VFiType>
IGL_INLINE void igl::vertex_triangle_adjacency(
  const typename DerivedF::Scalar n,
  const Eigen::PlainObjectBase<DerivedF>& F,
  std::vector<std::vector<VFType> >& VF,
  std::vector<std::vector<VFiType> >& VFi)
{
  VF.clear();
  VFi.clear();

  VF.resize(n);
  VFi.resize(n);

  typedef typename DerivedF::Index Index;
  for(Index fi=0; fi<F.rows(); ++fi)
  {
    for(Index i = 0; i < F.cols(); ++i)
    {
      VF[F(fi,i)].push_back(fi);
      VFi[F(fi,i)].push_back(i);
    }
  }
}


template <typename DerivedV, typename DerivedF, typename IndexType>
IGL_INLINE void igl::vertex_triangle_adjacency(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  std::vector<std::vector<IndexType> >& VF,
  std::vector<std::vector<IndexType> >& VFi)
{
  return vertex_triangle_adjacency(V.rows(),F,VF,VFi);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
// generated by autoexplicit.sh
template void igl::vertex_triangle_adjacency<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, int>(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >&, std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >&);
template void igl::vertex_triangle_adjacency<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1>, unsigned int>(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> > const&, std::vector<std::vector<unsigned int, std::allocator<unsigned int> >, std::allocator<std::vector<unsigned int, std::allocator<unsigned int> > > >&, std::vector<std::vector<unsigned int, std::allocator<unsigned int> >, std::allocator<std::vector<unsigned int, std::allocator<unsigned int> > > >&);
template void igl::vertex_triangle_adjacency<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3>, int>(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >&, std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >&);
template void igl::vertex_triangle_adjacency<Eigen::Matrix<double, -1, -1, 0, -1, -1>, long, long>(Eigen::Matrix<double, -1, -1, 0, -1, -1>::Scalar, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, std::vector<std::vector<long, std::allocator<long> >, std::allocator<std::vector<long, std::allocator<long> > > >&, std::vector<std::vector<long, std::allocator<long> >, std::allocator<std::vector<long, std::allocator<long> > > >&);
template void igl::vertex_triangle_adjacency<Eigen::Matrix<int, -1, -1, 0, -1, -1>, long, long>(Eigen::Matrix<int, -1, -1, 0, -1, -1>::Scalar, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, std::vector<std::vector<long, std::allocator<long> >, std::allocator<std::vector<long, std::allocator<long> > > >&, std::vector<std::vector<long, std::allocator<long> >, std::allocator<std::vector<long, std::allocator<long> > > >&);
template void igl::vertex_triangle_adjacency<Eigen::Matrix<int, -1, -1, 0, -1, -1>, unsigned long, unsigned long>(Eigen::Matrix<int, -1, -1, 0, -1, -1>::Scalar, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, std::__1::vector<std::__1::vector<unsigned long, std::__1::allocator<unsigned long> >, std::__1::allocator<std::__1::vector<unsigned long, std::__1::allocator<unsigned long> > > >&, std::__1::vector<std::__1::vector<unsigned long, std::__1::allocator<unsigned long> >, std::__1::allocator<std::__1::vector<unsigned long, std::__1::allocator<unsigned long> > > >&);
#endif
