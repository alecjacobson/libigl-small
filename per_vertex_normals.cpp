#include "per_vertex_normals.h"

#include "per_face_normals.h"
#include "normalize_rows.h"

template <typename DerivedV, typename DerivedF>
IGL_INLINE void igl::per_vertex_normals(
                                   const Eigen::PlainObjectBase<DerivedV>& V,
                                   const Eigen::PlainObjectBase<DerivedF>& F,
                                   Eigen::PlainObjectBase<DerivedV> & N)
{
  Eigen::PlainObjectBase<DerivedV> PFN;
  igl::per_face_normals(V,F,PFN);

  // Resize for output
  N = Eigen::PlainObjectBase<DerivedV>::Zero(V.rows(),3);

  // loop over faces
  for(int i = 0; i < F.rows();i++)
  {
    // throw normal at each corner
    for(int j = 0; j < 3;j++)
    {
      N.row(F(i,j)) += PFN.row(i);
    }
  }
  // normalize each row
  igl::normalize_rows(N,N);
}

template <typename DerivedV, typename DerivedF>
IGL_INLINE void igl::per_vertex_normals(
                                        const Eigen::PlainObjectBase<DerivedV>& V,
                                        const Eigen::PlainObjectBase<DerivedF>& F,
                                        const Eigen::PlainObjectBase<DerivedV>& FN,
                                        Eigen::PlainObjectBase<DerivedV> & N)
{
  // Resize for output
  N = Eigen::PlainObjectBase<DerivedV>::Zero(V.rows(),3);
  
  // loop over faces
  for(int i = 0; i < F.rows();i++)
  {
    // throw normal at each corner
    for(int j = 0; j < 3;j++)
    {
      N.row(F(i,j)) += FN.row(i);
    }
  }
  // normalize each row
  igl::normalize_rows(N,N);
}