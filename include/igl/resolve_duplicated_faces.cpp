// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
//

#include "resolve_duplicated_faces.h"

#include "slice.h"
#include "unique_simplices.h"

template<
  typename DerivedF1,
  typename DerivedF2,
  typename DerivedJ >
IGL_INLINE void igl::resolve_duplicated_faces(
    const Eigen::PlainObjectBase<DerivedF1>& F1,
    Eigen::PlainObjectBase<DerivedF2>& F2,
    Eigen::PlainObjectBase<DerivedJ>& J) {

  typedef typename DerivedF1::Scalar Index;
  Eigen::VectorXi IA,IC;
  DerivedF1 uF;
  igl::unique_simplices(F1,uF,IA,IC);

  const size_t num_faces = F1.rows();
  const size_t num_unique_faces = uF.rows();
  assert(IA.rows() == num_unique_faces);
  // faces on top of each unique face
  std::vector<std::vector<int> > uF2F(num_unique_faces);
  // signed counts
  Eigen::VectorXi counts = Eigen::VectorXi::Zero(num_unique_faces);
  Eigen::VectorXi ucounts = Eigen::VectorXi::Zero(num_unique_faces);
  // loop over all faces
  for (size_t i=0; i<num_faces; i++) {
    const size_t ui = IC(i);
    const bool consistent = 
      (F1(i,0) == uF(ui, 0) && F1(i,1) == uF(ui, 1) && F1(i,2) == uF(ui, 2)) ||
      (F1(i,0) == uF(ui, 1) && F1(i,1) == uF(ui, 2) && F1(i,2) == uF(ui, 0)) ||
      (F1(i,0) == uF(ui, 2) && F1(i,1) == uF(ui, 0) && F1(i,2) == uF(ui, 1));
    uF2F[ui].push_back(int(i+1) * (consistent?1:-1));
    counts(ui) += consistent ? 1:-1;
    ucounts(ui)++;
  }

  std::vector<size_t> kept_faces;
  for (size_t i=0; i<num_unique_faces; i++) {
    if (ucounts[i] == 1) {
      kept_faces.push_back(abs(uF2F[i][0])-1);
      continue;
    }
    if (counts[i] == 1) {
      bool found = false;
      for (auto fid : uF2F[i]) {
        if (fid > 0) {
          kept_faces.push_back(abs(fid)-1);
          found = true;
          break;
        }
      }
      assert(found);
    } else if (counts[i] == -1) {
      bool found = false;
      for (auto fid : uF2F[i]) {
        if (fid < 0) {
          kept_faces.push_back(abs(fid)-1);
          found = true;
          break;
        }
      }
      assert(found);
    } else {
      assert(counts[i] == 0);
    }
  }

  const size_t num_kept = kept_faces.size();
  J.resize(num_kept, 1);
  std::copy(kept_faces.begin(), kept_faces.end(), J.data());
  igl::slice(F1, J, 1, F2);
}

#ifdef IGL_STATIC_LIBRARY
template void igl::resolve_duplicated_faces<Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
template void igl::resolve_duplicated_faces<Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<long, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<long, -1, 1, 0, -1, 1> >&);
#endif
