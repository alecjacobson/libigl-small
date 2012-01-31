#ifndef IGL_FIND_H
#define IGL_FIND_H
#include "igl_inline.h"
#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <Eigen/Dense>
#include <Eigen/Sparse>
namespace igl
{
  // Find the non-zero entries and there respective indices in a sparse matrix.
  // Like matlab's [I,J,V] = find(X)
  //
  // Templates:
  //   T  should be a eigen sparse matrix primitive type like int or double
  // Input:
  //   X  m by n matrix whose entries are to be found 
  // Outputs:
  //   I  nnz vector of row indices of non zeros entries in X
  //   J  nnz vector of column indices of non zeros entries in X
  //   V  nnz vector of type T non-zeros entries in X
  //
  template <typename T>
  IGL_INLINE void find(
    const Eigen::SparseMatrix<T>& X,
    Eigen::Matrix<int,Eigen::Dynamic,1> & I,
    Eigen::Matrix<int,Eigen::Dynamic,1> & J,
    Eigen::Matrix<T,Eigen::Dynamic,1> & V);
  // Find the non-zero entries and there respective indices in a sparse vector.
  // Similar to matlab's [I,J,V] = find(X), but instead of [I,J] being
  // subscripts into X, since X is a vector we just return I, a list of indices
  // into X
  //
  // Templates:
  //   T  should be a eigen sparse matrix primitive type like int or double
  // Input:
  //   X  vector whose entries are to be found
  // Outputs:
  //   I  nnz vector of indices of non zeros entries in X
  //   V  nnz vector of type T non-zeros entries in X
  template <typename T>
  IGL_INLINE void find(
    const Eigen::SparseVector<T>& X,
    Eigen::Matrix<int,Eigen::Dynamic,1> & I,
    Eigen::Matrix<T,Eigen::Dynamic,1> & V);
}

#ifdef IGL_HEADER_ONLY
#  include "find.cpp"
#endif

#endif
