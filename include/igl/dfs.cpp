#include "dfs.h"
#include "list_to_matrix.h"
#include <vector>

template <
  typename AType,
  typename DerivedD,
  typename DerivedP,
  typename DerivedC>
IGL_INLINE void igl::dfs(
  const std::vector<std::vector<AType> > & A,
  const size_t s,
  Eigen::PlainObjectBase<DerivedD> & D,
  Eigen::PlainObjectBase<DerivedP> & P,
  Eigen::PlainObjectBase<DerivedC> & C)
{
  std::vector<typename DerivedD::Scalar> vD;
  std::vector<typename DerivedP::Scalar> vP;
  std::vector<typename DerivedC::Scalar> vC;
  dfs(A,s,vD,vP,vC);
  list_to_matrix(vD,D);
  list_to_matrix(vP,P);
  list_to_matrix(vC,C);
}

template <
  typename AType,
  typename DType,
  typename PType,
  typename CType>
IGL_INLINE void igl::dfs(
  const std::vector<std::vector<AType> > & A,
  const size_t s,
  std::vector<DType> & D,
  std::vector<PType> & P,
  std::vector<CType> & C)
{
  // number of nodes
  int N = s+1;
  for(const auto & Ai : A) for(const auto & a : Ai) N = std::max(N,a+1);
  std::vector<bool> seen(N,false);
  P.resize(N,-1);
  std::function<void(const size_t, const size_t)> dfs_helper;
  dfs_helper = [&D,&P,&C,&dfs_helper,&seen,&A](const size_t s, const size_t p)
  {
    if(seen[s]) return;
    seen[s] = true;
    D.push_back(s);
    P[s] = p;
    for(const auto n : A[s]) dfs_helper(n,s);
    C.push_back(s);
  };
  dfs_helper(s,-1);
}
