#include "cat.h"

// Sparse matrices need to be handled carefully. Because C++ does not 
// Template:
//   Scalar  sparse matrix scalar type, e.g. double
template <typename Scalar>
IGL_INLINE void igl::cat(
    const int dim, 
    const Eigen::SparseMatrix<Scalar> & A, 
    const Eigen::SparseMatrix<Scalar> & B, 
    Eigen::SparseMatrix<Scalar> & C)
{
  assert(dim == 1 || dim == 2);
  using namespace Eigen;
  // Special case if B or A is empty
  if(A.size() == 0)
  {
    C = B;
    return;
  }
  if(B.size() == 0)
  {
    C = A;
    return;
  }

  DynamicSparseMatrix<Scalar, RowMajor> dyn_C;
  if(dim == 1)
  {
    assert(A.cols() == B.cols());
    dyn_C.resize(A.rows()+B.rows(),A.cols());
  }else if(dim == 2)
  {
    assert(A.rows() == B.rows());
    dyn_C.resize(A.rows(),A.cols()+B.cols());
  }else
  {
    fprintf(stderr,"cat.h: Error: Unsupported dimension %d\n",dim);
  }

  dyn_C.reserve(A.nonZeros()+B.nonZeros());

  // Iterate over outside of A
  for(int k=0; k<A.outerSize(); ++k)
  {
    // Iterate over inside
    for(typename SparseMatrix<Scalar>::InnerIterator it (A,k); it; ++it)
    {
      dyn_C.coeffRef(it.row(),it.col()) += it.value();
    }
  }

  // Iterate over outside of B
  for(int k=0; k<B.outerSize(); ++k)
  {
    // Iterate over inside
    for(typename SparseMatrix<Scalar>::InnerIterator it (B,k); it; ++it)
    {
      int r = (dim == 1 ? A.rows()+it.row() : it.row());
      int c = (dim == 2 ? A.cols()+it.col() : it.col());
      dyn_C.coeffRef(r,c) += it.value();
    }
  }

  C = SparseMatrix<Scalar>(dyn_C);
}

template <typename Derived, class MatC>
IGL_INLINE void igl::cat(
  const int dim,
  const Eigen::MatrixBase<Derived> & A, 
  const Eigen::MatrixBase<Derived> & B,
  MatC & C)
{
  assert(dim == 1 || dim == 2);
  // Special case if B or A is empty
  if(A.size() == 0)
  {
    C = B;
    return;
  }
  if(B.size() == 0)
  {
    C = A;
    return;
  }

  if(dim == 1)
  {
    assert(A.cols() == B.cols());
    C.resize(A.rows()+B.rows(),A.cols());
    C << A,B;
  }else if(dim == 2)
  {
    assert(A.rows() == B.rows());
    C.resize(A.rows(),A.cols()+B.cols());
    C << A,B;
  }else
  {
    fprintf(stderr,"cat.h: Error: Unsupported dimension %d\n",dim);
  }
}

template <class Mat>
IGL_INLINE Mat igl::cat(const int dim, const Mat & A, const Mat & B)
{
  assert(dim == 1 || dim == 2);
  Mat C;
  igl::cat(dim,A,B,C);
  return C;
}

template <class Mat>
IGL_INLINE void cat(const std::vector<std::vector< Mat > > & A, Mat & C)
{
  using namespace igl;
  using namespace std;
  // Start with empty matrix
  C.resize(0,0);
  for(typename vector<vector< Mat > >::const_iterator rit = A.begin(); rit != A.end(); rit++)
  {
    // Concatenate each row horizontally
    // Start with empty matrix
    Mat row(0,0);
    for(typename vector<vector< Mat > >::iterator cit = A.begin(); rit != A.end(); rit++)
    {
      row = cat(2,row,*cit);
    }
    // Concatenate rows vertically
    C = cat(1,C,row);
  }
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
