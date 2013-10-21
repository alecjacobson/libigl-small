#ifndef IGL_SORT_TRIANGLES_H
#define IGL_SORT_TRIANGLES_H

#include "igl_inline.h"
#include <Eigen/Core>

namespace igl
{
  // Inputs:
  //   V  #V by **4** list of homogeneous vertex positions
  //   F  #F by 3 list of triangle indices
  //   MV  4 by 4 model view matrix
  //   P  4 by 4 projection matrix
  // Outputs:
  //   FF  #F by 3 list of sorted triangles indices
  //   I  #F list of sorted indices
  template <
    typename DerivedV,
    typename DerivedF,
    typename DerivedMV,
    typename DerivedP,
    typename DerivedFF,
    typename DerivedI>
  IGL_INLINE void sort_triangles(
    const Eigen::PlainObjectBase<DerivedV> & V,
    const Eigen::PlainObjectBase<DerivedF> & F,
    const Eigen::PlainObjectBase<DerivedMV> & MV,
    const Eigen::PlainObjectBase<DerivedP> & P,
    Eigen::PlainObjectBase<DerivedFF> & FF,
    Eigen::PlainObjectBase<DerivedI> & I);
  template <
    typename DerivedV,
    typename DerivedF,
    typename DerivedFF,
    typename DerivedI>
  IGL_INLINE void sort_triangles(
    const Eigen::PlainObjectBase<DerivedV> & V,
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::PlainObjectBase<DerivedFF> & FF,
    Eigen::PlainObjectBase<DerivedI> & I);
  template <
    typename DerivedV,
    typename DerivedF,
    typename DerivedFF,
    typename DerivedI>
  IGL_INLINE void sort_triangles_slow(
    const Eigen::PlainObjectBase<DerivedV> & V,
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::PlainObjectBase<DerivedFF> & FF,
    Eigen::PlainObjectBase<DerivedI> & I);
  //template <
  //  typename DerivedV,
  //  typename DerivedF,
  //  typename DerivedMV,
  //  typename DerivedP,
  //  typename DerivedFF,
  //  typename DerivedI>
  //IGL_INLINE void sort_triangles_robust(
  //  const Eigen::PlainObjectBase<DerivedV> & V,
  //  const Eigen::PlainObjectBase<DerivedF> & F,
  //  const Eigen::PlainObjectBase<DerivedMV> & MV,
  //  const Eigen::PlainObjectBase<DerivedP> & P,
  //  Eigen::PlainObjectBase<DerivedFF> & FF,
  //  Eigen::PlainObjectBase<DerivedI> & I);
  //template <
  //  typename DerivedV,
  //  typename DerivedF,
  //  typename DerivedFF,
  //  typename DerivedI>
  //IGL_INLINE void sort_triangles_robust(
  //  const Eigen::PlainObjectBase<DerivedV> & V,
  //  const Eigen::PlainObjectBase<DerivedF> & F,
  //  Eigen::PlainObjectBase<DerivedFF> & FF,
  //  Eigen::PlainObjectBase<DerivedI> & I);
}

#ifdef IGL_HEADER_ONLY
#  include "sort_triangles.cpp"
#endif

#endif
