#include "polar_dec.h"
#include "polar_svd.h"
#ifdef _WIN32
#else
#  include <fenv.h>
#endif
#include <cmath>
#include <Eigen/Eigenvalues>
#include <iostream>

// From Olga's CGAL mentee's ARAP code
template <
  typename DerivedA,
  typename DerivedR,
  typename DerivedT,
  typename DerivedU,
  typename DerivedS,
  typename DerivedV>
IGL_INLINE void igl::polar_dec(
  const Eigen::PlainObjectBase<DerivedA> & A,
  Eigen::PlainObjectBase<DerivedR> & R,
  Eigen::PlainObjectBase<DerivedT> & T,
  Eigen::PlainObjectBase<DerivedU> & U,
  Eigen::PlainObjectBase<DerivedS> & S,
  Eigen::PlainObjectBase<DerivedV> & V)
{
  using namespace std;
 typedef typename DerivedA::Scalar Scalar;

 const Scalar th = std::sqrt(Eigen::NumTraits<Scalar>::dummy_precision());

 Eigen::SelfAdjointEigenSolver<DerivedA> eig;
 feclearexcept(FE_UNDERFLOW);
 eig.computeDirect(A.transpose()*A);
 if(fetestexcept(FE_UNDERFLOW) || eig.eigenvalues()(0)/eig.eigenvalues()(2)<th)
 {
   cout<<"resorting to svd 1..."<<endl;
   return polar_svd(A,R,T,U,S,V);
 }

 S = eig.eigenvalues().cwiseSqrt();

 T = eig.eigenvectors() * S.asDiagonal() * eig.eigenvectors().transpose();
 U = A * eig.eigenvectors();
 V = eig.eigenvectors();
 R = U * S.asDiagonal().inverse() * V.transpose();
 S = S.reverse().eval();
 V = V.rowwise().reverse().eval();
 U = U.rowwise().reverse().eval() * S.asDiagonal().inverse();

 if(std::fabs(R.squaredNorm()-3.) > th)
 {
   cout<<"resorting to svd 2..."<<endl;
   return polar_svd(A,R,T,U,S,V);
 }
}

template <
  typename DerivedA,
  typename DerivedR,
  typename DerivedT>
IGL_INLINE void igl::polar_dec(
  const Eigen::PlainObjectBase<DerivedA> & A,
  Eigen::PlainObjectBase<DerivedR> & R,
  Eigen::PlainObjectBase<DerivedT> & T)
{
  Eigen::PlainObjectBase<DerivedA> U;
  Eigen::PlainObjectBase<DerivedA> V;
  Eigen::Matrix<typename DerivedA::Scalar,DerivedA::RowsAtCompileTime,1> S;
  return igl::polar_dec(A,R,T,U,S,V);
}

#ifndef IGL_HEADER_ONLY
// Explicit template instanciation
template  void igl::polar_dec<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> >&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
#endif
