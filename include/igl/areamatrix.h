// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2014 Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_AREAMATRIX_H
#define IGL_AREAMATRIX_H
#include "igl_inline.h"

#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace igl
{
  // Constructs the symmetric area matrix A, s.t.  [V.col(0)' V.col(1)'] * A *
  // [V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).
  //
  // Templates:
  //   DerivedV  derived type of eigen matrix for V (e.g. derived from
  //     MatrixXd)
  //   DerivedF  derived type of eigen matrix for F (e.g. derived from
  //     MatrixXi)
  //   Scalar  scalar type for eigen sparse matrix (e.g. double)
  // Inputs:
  //   F  #F by 3 list of mesh faces (must be triangles)
  // Outputs:
  //   A  #Vx2 by #Vx2 area matrix
  //
  template <typename DerivedF, typename Scalar>
  IGL_INLINE void areamatrix(
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::SparseMatrix<Scalar>& A);
}

#ifdef IGL_HEADER_ONLY
#  include "areamatrix.cpp"
#endif

#endif
