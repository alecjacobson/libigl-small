#include "full.h"

template <typename T>
IGL_INLINE void igl::full(
  const Eigen::SparseMatrix<T> & A,
  Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & B)
{
  B = Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>::Zero(A.rows(),A.cols());
  // Iterate over outside
  for(int k=0; k<A.outerSize(); ++k)
  {
    // Iterate over inside
    for(typename Eigen::SparseMatrix<T>::InnerIterator it (A,k); it; ++it)
    {
      B(it.row(),it.col()) = it.value();
    }
  }
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
// generated by autoexplicit.sh
template void igl::full<double>(Eigen::SparseMatrix<double, 0, int> const&, Eigen::Matrix<double, -1, -1, 0, -1, -1>&);
#endif
