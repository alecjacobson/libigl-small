// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2015 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "all_edges.h"
#include "doublearea.h"
#include "per_edge_normals.h"
#include "get_seconds.h"
#include "per_face_normals.h"
#include "unique_simplices.h"
#include <vector>

template <
  typename DerivedV, 
  typename DerivedF, 
  typename DerivedFN, 
  typename DerivedN,
  typename DerivedE,
  typename DerivedEMAP>
IGL_INLINE void igl::per_edge_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const PerEdgeNormalsWeightingType weighting,
  const Eigen::PlainObjectBase<DerivedFN>& FN,
  Eigen::PlainObjectBase<DerivedN> & N,
  Eigen::PlainObjectBase<DerivedE> & E,
  Eigen::PlainObjectBase<DerivedEMAP> & EMAP)

{
  using namespace Eigen;
  using namespace std;
  assert(F.cols() == 3 && "Faces must be triangles");
  // number of faces
  const int m = F.rows();
  // All occurances of directed edges
  MatrixXi allE;
  all_edges(F,allE);
  // Find unique undirected edges and mapping
  VectorXi _;
  unique_simplices(allE,E,_,EMAP);
  // now sort(allE,2) == E(EMAP,:), that is, if EMAP(i) = j, then E.row(j) is
  // the undirected edge corresponding to the directed edge allE.row(i).

  Eigen::VectorXd W;
  switch(weighting)
  {
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM:
      // Do nothing
      break;
    default:
      assert(false && "Unknown weighting type");
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT:
    case PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA:
    {
      doublearea(V,F,W);
      break;
    }
  }

  N.setZero(E.rows(),3);
  for(int f = 0;f<m;f++)
  {
    for(int c = 0;c<3;c++)
    {
      if(weighting == PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM)
      {
        N.row(EMAP(f+c*m)) += FN.row(f);
      }else
      {
        N.row(EMAP(f+c*m)) += W(f) * FN.row(f);
      }
    }
  }
}

template <
  typename DerivedV, 
  typename DerivedF, 
  typename DerivedN,
  typename DerivedE,
  typename DerivedEMAP>
IGL_INLINE void igl::per_edge_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const PerEdgeNormalsWeightingType weighting,
  Eigen::PlainObjectBase<DerivedN> & N,
  Eigen::PlainObjectBase<DerivedE> & E,
  Eigen::PlainObjectBase<DerivedEMAP> & EMAP)
{
  Eigen::Matrix<typename DerivedN::Scalar,Eigen::Dynamic,3> FN;
  per_face_normals(V,F,FN);
  return per_edge_normals(V,F,weighting,FN,N,E,EMAP);
}

template <
  typename DerivedV, 
  typename DerivedF, 
  typename DerivedN,
  typename DerivedE,
  typename DerivedEMAP>
IGL_INLINE void igl::per_edge_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  Eigen::PlainObjectBase<DerivedN> & N,
  Eigen::PlainObjectBase<DerivedE> & E,
  Eigen::PlainObjectBase<DerivedEMAP> & EMAP)
{
  return 
    per_edge_normals(V,F,PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT,N,E,EMAP);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::per_edge_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
template void igl::per_edge_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, igl::PerEdgeNormalsWeightingType, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
template void igl::per_edge_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, igl::PerEdgeNormalsWeightingType, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
template void igl::per_edge_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, igl::PerEdgeNormalsWeightingType, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
template void igl::per_edge_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
#endif
