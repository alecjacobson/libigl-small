#ifndef IGL_EXTRACT_MANIFOLD_PATCHES
#define IGL_EXTRACT_MANIFOLD_PATCHES

#include "igl_inline.h"
#include <Eigen/Dense>
#include <vector>

namespace igl {
    // Extract a set of maximal manifold patches from a given mesh.
    // A maximal manifold patch is a subset of the input faces that is
    // connected and manifold, and it cannot be expanded further by
    // including more faces.
    //
    // Assumes the input mesh have all self-intersection resolved.  See
    // ``igl::cgal::remesh_self_intersection`` for more details.
    //
    // Inputs:
    //   F  #F by 3 list representing triangles.
    //   EMAP  #F*3 list of indices of unique undirected edges.
    //   uE2E  #uE list of lists of indices into E of coexisting edges.
    //
    // Output:
    //   P  #F list of patch incides.
    //
    // Returns:
    //   number of manifold patches.
    template <
        typename DerivedF,
        typename DerivedEMAP,
        typename uE2EType,
        typename DerivedP>
    IGL_INLINE size_t extract_manifold_patches(
            const Eigen::PlainObjectBase<DerivedF>& F,
            const Eigen::PlainObjectBase<DerivedEMAP>& EMAP,
            const std::vector<std::vector<uE2EType> >& uE2E,
            Eigen::PlainObjectBase<DerivedP>& P);
}
#ifndef IGL_STATIC_LIBRARY
#  include "extract_manifold_patches.cpp"
#endif

#endif
