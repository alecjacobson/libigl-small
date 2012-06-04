//
//  IGL Lib - Simple C++ mesh library 
//
//  Copyright 2011, Daniele Panozzo. All rights reserved.

// History:
//  return type changed from void to bool  Alec 18 Sept 2011


#ifndef IGL_READ_H
#define IGL_READ_H
#include "igl_inline.h"

#ifndef IGL_NO_EIGEN
#  include <Eigen/Core>
#endif
#include <string>
#include <vector>

namespace igl 
{
  // read mesh from an ascii file with automatic detection of file format. supported: obj, off)
  // Templates:
  //   Scalar  type for positions and vectors (will be read as double and cast
  //     to Scalar)
  //   Index  type for indices (will be read as int and cast to Index)
  // Inputs:
  // Inputs:
  //   str  path to .obj/.off file
  // Outputs:
  //   V  eigen double matrix #V by 3
  //   F  eigen int matrix #F by 3
  template <typename Scalar, typename Index>
  IGL_INLINE bool read(
    const std::string str,
    std::vector<std::vector<Scalar> > & V,
    std::vector<std::vector<Index> > & F);
#ifndef IGL_NO_EIGEN
  template <typename DerivedV, typename DerivedF>
  IGL_INLINE bool read(
    const std::string str,
    Eigen::PlainObjectBase<DerivedV>& V,
    Eigen::PlainObjectBase<DerivedF>& F);
#endif
}

#ifdef IGL_HEADER_ONLY
#  include "read.cpp"
#endif

#endif
