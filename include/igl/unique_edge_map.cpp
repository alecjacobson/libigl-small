#include "unique_edge_map.h"
#include "all_edges.h"
#include "unique_simplices.h"
#include <cassert>
#include <algorithm>
template <
  typename DerivedF,
  typename DerivedE,
  typename DeriveduE,
  typename DerivedEMAP,
  typename uE2EType>
IGL_INLINE void igl::unique_edge_map(
  const Eigen::PlainObjectBase<DerivedF> & F,
  Eigen::PlainObjectBase<DerivedE> & E,
  Eigen::PlainObjectBase<DeriveduE> & uE,
  Eigen::PlainObjectBase<DerivedEMAP> & EMAP,
  std::vector<std::vector<uE2EType> > & uE2E)
{
  using namespace Eigen;
  using namespace std;
  // All occurances of directed edges
  all_edges(F,E);
  const size_t ne = E.rows();
  // This is 2x faster to create than a map from pairs to lists of edges and 5x
  // faster to access (actually access is probably assympotically faster O(1)
  // vs. O(log m)
  Matrix<typename DerivedEMAP::Scalar,Dynamic,1> IA;
  unique_simplices(E,uE,IA,EMAP);
  uE2E.resize(uE.rows());
  // This does help a little
  for_each(uE2E.begin(),uE2E.end(),[](vector<uE2EType > & v){v.reserve(2);});
  assert((size_t)EMAP.size() == ne);
  for(uE2EType e = 0;e<(uE2EType)ne;e++)
  {
    uE2E[EMAP(e)].push_back(e);
  }
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
template void igl::unique_edge_map<Eigen::Matrix<int, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 2, 0, -1, 2>, Eigen::Matrix<int, -1, 2, 0, -1, 2>, Eigen::Matrix<long, -1, 1, 0, -1, 1>, long>(Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 2, 0, -1, 2> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 2, 0, -1, 2> >&, Eigen::PlainObjectBase<Eigen::Matrix<long, -1, 1, 0, -1, 1> >&, std::vector<std::vector<long, std::allocator<long> >, std::allocator<std::vector<long, std::allocator<long> > > >&);
#endif 
