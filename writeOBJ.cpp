#include "writeOBJ.h"

#include <iostream>
#include <fstream>
#include <cstdio>

template <typename DerivedV, typename DerivedF>
IGL_INLINE bool igl::writeOBJ(
                              const std::string str,
                              const Eigen::PlainObjectBase<DerivedV>& V,
                              const Eigen::PlainObjectBase<DerivedF>& F)
{
  std::ofstream s(str.c_str());

  if(!s.is_open())
  {
    fprintf(stderr,"IOError: writeOBJ() could not open %s\n",str.c_str());
    return false;
  }

  for(int i=0;i<V.rows();++i)
      s << "v " << V(i,0) << " " << V(i,1) << " " << V(i,2) << std::endl;
  
  for(int i=0;i<F.rows();++i)
      s << "f " << F(i,0)+1 << " " << F(i,1)+1 << " " << F(i,2)+1 << std::endl;
  
  s.close();
  return true;
}

template <typename DerivedV, typename DerivedF, typename DerivedT>
IGL_INLINE bool igl::writeOBJ(
                         const std::string str,
                         const Eigen::PlainObjectBase<DerivedV>& V,
                         const Eigen::PlainObjectBase<DerivedF>& F,
                         const Eigen::PlainObjectBase<DerivedV>& CN,
                         const Eigen::PlainObjectBase<DerivedF>& FN,
                         const Eigen::PlainObjectBase<DerivedT>& TC,
                         const Eigen::PlainObjectBase<DerivedF>& FTC)
{
  FILE * obj_file = fopen(str.c_str(),"w");
  if(NULL==obj_file)
  {
    printf("IOError: %s could not be opened for writing...",str.c_str());
    return false;                                              
  }
  // Loop over V
  for(size_t i = 0;i<V.rows();i++)
  {
    fprintf(obj_file,"v %0.15g %0.15g %0.15g\n",
            V(i,0),
            V(i,1),
            V(i,2)
            );
  }
  bool write_N = CN.rows() >0;
  
  if(write_N)
  {
    for(size_t i = 0;i<CN.rows();i++)
    {
      fprintf(obj_file,"v %0.15g %0.15g %0.15g\n",
              CN(i,0),
              CN(i,1),
              CN(i,2)
              );
    }
    fprintf(obj_file,"\n");
  }
  
  bool write_texture_coords = TC.rows() >0;
  
  if(write_texture_coords)
  {
    for(size_t i = 0;i<TC.rows();i++)
    {
      fprintf(obj_file, "vt %0.15g %0.15g\n",TC(i,0),1-TC(i,1));
    }
    fprintf(obj_file,"\n");
  }
  
  // loop over F
  for(size_t i = 0;i<F.rows();++i)
  {
    fprintf(obj_file,"f");
    for(size_t j = 0; j<F.cols();++j)
    {
      // OBJ is 1-indexed
      fprintf(obj_file," %u",F(i,j)+1);
      
      if(write_texture_coords)
        fprintf(obj_file,"/%u",FTC(i,j)+1);
      if(write_N)
        if (write_texture_coords)
          fprintf(obj_file,"/%u",FN(i,j)+1);
        else
          fprintf(obj_file,"//%u",FN(i,j)+1);
      
    }
    fprintf(obj_file,"\n");
  }
  fclose(obj_file);
  return true;  
}
