#include "slice.h"

#include <vector>

template <typename T>
IGL_INLINE void igl::slice(
  const Eigen::SparseMatrix<T>& X,
  const Eigen::Matrix<int,Eigen::Dynamic,1> & R,
  const Eigen::Matrix<int,Eigen::Dynamic,1> & C,
  Eigen::SparseMatrix<T>& Y)
{
  int xm = X.rows();
  int xn = X.cols();
  int ym = R.size();
  int yn = C.size();

  // special case when R or C is empty
  if(ym == 0 || yn == 0)
  {
    Y.resize(ym,yn);
    return;
  }

  assert(R.minCoeff() >= 0);
  assert(R.maxCoeff() < xm);
  assert(C.minCoeff() >= 0);
  assert(C.maxCoeff() < xn);

  // Build reindexing maps for columns and rows, -1 means not in map
  std::vector<std::vector<int> > RI;
  RI.resize(xm);
  for(int i = 0;i<ym;i++)
  {
    RI[R(i)].push_back(i);
  }
  std::vector<std::vector<int> > CI;
  CI.resize(xn);
  // initialize to -1
  for(int i = 0;i<yn;i++)
  {
    CI[C(i)].push_back(i);
  }
  // Resize output
  Eigen::DynamicSparseMatrix<T, Eigen::RowMajor> dyn_Y(ym,yn);
  // Take a guess at the number of nonzeros (this assumes uniform distribution
  // not banded or heavily diagonal)
  dyn_Y.reserve((X.nonZeros()/(X.rows()*X.cols())) * (ym*yn));
  // Iterate over outside
  for(int k=0; k<X.outerSize(); ++k)
  {
    // Iterate over inside
    for(typename Eigen::SparseMatrix<T>::InnerIterator it (X,k); it; ++it)
    {
      std::vector<int>::iterator rit, cit;
      for(rit = RI[it.row()].begin();rit != RI[it.row()].end(); rit++)
      {
        for(cit = CI[it.col()].begin();cit != CI[it.col()].end(); cit++)
        {
          dyn_Y.coeffRef(*rit,*cit) = it.value();
        }
      }
    }
  }
  Y = Eigen::SparseMatrix<T>(dyn_Y);
}

template <typename T, const int W, const int H>
IGL_INLINE void igl::slice(
  const Eigen::Matrix<T,W,H> & X,
  const Eigen::Matrix<int,Eigen::Dynamic,1> & R,
  const Eigen::Matrix<int,Eigen::Dynamic,1> & C,
  Eigen::Matrix<T,W,H> & Y)
{
  int xm = X.rows();
  int xn = X.cols();
  int ym = R.size();
  int yn = C.size();

  // special case when R or C is empty
  if(ym == 0 || yn == 0)
  {
    Y.resize(ym,yn);
    return;
  }

  assert(R.minCoeff() >= 0);
  assert(R.maxCoeff() < xm);
  assert(C.minCoeff() >= 0);
  assert(C.maxCoeff() < xn);

  // Resize output
  Y.resize(ym,yn);
  // loop over output rows, then columns
  for(int i = 0;i<ym;i++)
  {
    for(int j = 0;j<yn;j++)
    {
      Y(i,j) = X(R(i),C(j));
    }
  }
}

template <typename T>
IGL_INLINE void igl::slice(
  const Eigen::Matrix<T,Eigen::Dynamic,1> & X,
  const Eigen::Matrix<int,Eigen::Dynamic,1> & R,
  Eigen::Matrix<T,Eigen::Dynamic,1> & Y)
{
  // phony column indices
  Eigen::Matrix<int,Eigen::Dynamic,1> C;
  C.resize(1);
  C(0) = 0;
  return igl::slice(X,R,C,Y);
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
