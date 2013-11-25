// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_LIST_TO_MATRIX_H
#define IGL_LIST_TO_MATRIX_H
#include "igl_inline.h"
#include <vector>
namespace igl
{
  // Convert a list (std::vector) of row vectors of the same length to a matrix
  // Template: 
  //   T  type that can be safely cast to type in Mat via '='
  //   Mat  Matrix type, must implement:
  //     .resize(m,n)
  //     .row(i) = Row
  // Inputs:
  //   V  a m-long list of vectors of size n
  // Outputs:
  //   M  an m by n matrix
  // Returns true on success, false on errors
  template <typename T, class Mat>
  IGL_INLINE bool list_to_matrix(
    const std::vector<std::vector<T > > & V,
    Mat & M);
  // Vector wrapper
  template <typename T, class Mat>
  IGL_INLINE bool list_to_matrix(const std::vector<T > & V,Mat & M);
}

#ifdef IGL_HEADER_ONLY
#  include "list_to_matrix.cpp"
#endif

#endif
