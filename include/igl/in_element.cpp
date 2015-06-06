#include "in_element.h"

template <typename DerivedV, typename DerivedQ, int DIM>
IGL_INLINE void igl::in_element(
  const Eigen::PlainObjectBase<DerivedV> & V,
  const Eigen::MatrixXi & Ele,
  const Eigen::PlainObjectBase<DerivedQ> & Q,
  const AABB<DerivedV,DIM> & aabb,
  Eigen::VectorXi & I)
{
  using namespace std;
  using namespace Eigen;
  const int Qr = Q.rows();
  I.setConstant(Qr,1,-1);
#pragma omp parallel for if (Qr>10000)
  for(int e = 0;e<Qr;e++)
  {
    // find all
    const auto R = aabb.find(V,Ele,Q.row(e),true);
    if(!R.empty())
    {
      I(e) = R[0];
    }
  }
}

template <typename DerivedV, typename DerivedQ, int DIM, typename Scalar>
IGL_INLINE void igl::in_element(
  const Eigen::PlainObjectBase<DerivedV> & V,
  const Eigen::MatrixXi & Ele,
  const Eigen::PlainObjectBase<DerivedQ> & Q,
  const AABB<DerivedV,DIM> & aabb,
  Eigen::SparseMatrix<Scalar> & I)
{
  using namespace std;
  using namespace Eigen;
  using namespace igl;
  const int Qr = Q.rows();
  std::vector<Triplet<Scalar> > IJV;
  IJV.reserve(Qr);
#pragma omp parallel for if (Qr>10000)
  for(int e = 0;e<Qr;e++)
  {
    // find all
    const auto R = aabb.find(V,Ele,Q.row(e),false);
    for(const auto r : R)
    {
#pragma omp critical
      IJV.push_back(Triplet<Scalar>(e,r,1));
    }
  }
  I.resize(Qr,Ele.rows());
  I.setFromTriplets(IJV.begin(),IJV.end());
}
