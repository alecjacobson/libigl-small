#ifndef IGL_MANIFOLD_PATCHES_H
#define IGL_MANIFOLD_PATCHES_H
#include <igl/igl_inline.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
namespace igl
{
  //  Compute connected components of facets connected by manifold edges.
  // 
  //  Known bugs: This will detect a moebius strip as a single patch (manifold,
  //  non-orientable) and also non-manfiold, yet orientable patches. 
  // 
  //  Q: Does this find exactly (manifold || orientable) patches?
  // 
  //  Inputs:
  //    F  #F by simplex-size list of facets
  //  Outputs:
  //    C  #F list of component ids
  //    A  #F by #F adjacency matrix
  // 
  template <typename DerivedF, typename DerivedC, typename AScalar>
  IGL_INLINE void manifold_patches(
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::PlainObjectBase<DerivedC> & C,
    Eigen::SparseMatrix<AScalar> & A);
};
#ifdef IGL_HEADER_ONLY
#  include "manifold_patches.cpp"
#endif
#endif
