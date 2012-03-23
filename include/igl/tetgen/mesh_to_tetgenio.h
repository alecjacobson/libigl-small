#ifndef IGL_MESH_TO_TETGENIO_H
#define IGL_MESH_TO_TETGENIO_H
#include "../igl_inline.h"

#define TETLIBRARY 
#include "tetgen.h" // Defined tetgenio, REAL
#include <vector>
#include <Eigen/Core>

namespace igl
{
  // Load a vertex list and face list into a tetgenio object
  // Inputs:
  //   V  #V by 3 vertex position list
  //   F  #F list of polygon face indices into V (0-indexed)
  // Outputs:
  //   in  tetgenio input object
  // Returns true on success, false on error
  IGL_INLINE bool mesh_to_tetgenio(
    const std::vector<std::vector<REAL > > & V, 
    const std::vector<std::vector<int> > & F, 
    tetgenio & in);
  
  // Wrapper with Eigen types
  // Templates:
  //   DerivedV  real-value: i.e. from MatrixXd
  //   DerivedF  integer-value: i.e. from MatrixXi
  template <typename DerivedV, typename DerivedF>
  IGL_INLINE bool mesh_to_tetgenio(
    const Eigen::PlainObjectBase<DerivedV>& V,
    const Eigen::PlainObjectBase<DerivedF>& F,
    tetgenio & in);
}


#ifdef IGL_HEADER_ONLY
#  include "mesh_to_tetgenio.cpp"
#endif

#endif
