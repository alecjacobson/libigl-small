// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_REORIENT_FACETS_RAYCAST_H
#define IGL_REORIENT_FACETS_RAYCAST_H
#include "../igl_inline.h"
#include <Eigen/Core>
namespace igl
{
  // Orient each component (identified by C) of a mesh (V,F) using ambient occlusion 
  // such that the front side is less occluded than back side
  //
  // Inputs:
  //   V                            #V by 3 list of vertex positions
  //   F                            #F by 3 list of triangle indices
  //   rays_total                   Total number of rays that will be shot
  //   rays_minimum                 Minimum number of rays that each patch should receive
  //   faceg_wise                   Decision made for each face independently, no use of patches (i.e., each face is treated as a patch)
  //   use_parity                   Use parity mode
  //   is_verbose                   Verbose output to cout
  // Outputs:
  //   I                            #F list of whether face has been flipped
  //   C                            #F list of patch ID
  template <
    typename DerivedV, 
    typename DerivedF, 
    typename DerivedI,
    typename DerivedC>
  IGL_INLINE void reorient_facets_raycast(
    const Eigen::PlainObjectBase<DerivedV> & V,
    const Eigen::PlainObjectBase<DerivedF> & F,
    int rays_total,
    int rays_minimum,
    bool facet_wise,
    bool use_parity,
    bool is_verbose,
    Eigen::PlainObjectBase<DerivedI> & I,
    Eigen::PlainObjectBase<DerivedC> & C);
};

#ifdef IGL_HEADER_ONLY
#  include "reorient_facets_raycast.cpp"
#endif

#endif
