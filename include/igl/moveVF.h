#ifndef IGL_MOVEVF_H
#define IGL_MOVEVF_H
#include "igl_inline.h"

#include <Eigen/Dense>
namespace igl 
{
  // moveFV 
  // Move a scalar field defined on faces to vertices by averaging
  //
  // Input:
  // V,F: mesh
  // S: scalar field defined on vertices, Vx1
  // 
  // Output:
  // SV: scalar field defined on faces
  template <typename T, typename I>
  IGL_INLINE void moveVF(
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V,
    const Eigen::Matrix<I, Eigen::Dynamic, Eigen::Dynamic> &F,
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &S,
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &SF);
}

#ifdef IGL_HEADER_ONLY
#  include "moveVF.cpp"
#endif

#endif
