//
//  IGL Lib - Simple C++ mesh library 
//
//  Copyright 2011, Daniele Panozzo. All rights reserved.

#include "edgetopology.h"
#include <algorithm>
#include "is_manifold.h"


IGL_INLINE void igl::edgetopology(
  const Eigen::MatrixXd& V, 
  const Eigen::MatrixXi& F, 
  Eigen::MatrixXi& EV, 
  Eigen::MatrixXi& FE, 
  Eigen::MatrixXi& EF)
{
  assert(igl::is_manifold(V,F));
  std::vector<std::vector<int> > ETT;
  for(int f=0;f<F.rows();++f)
    for (int i=0;i<3;++i)
    {
      // v1 v2 f vi 
      int v1 = F(f,i);
      int v2 = F(f,(i+1)%3);
      if (v1 > v2) std::swap(v1,v2);
      std::vector<int> r(4);
      r[0] = v1; r[1] = v2;
      r[2] = f;  r[3] = i;
      ETT.push_back(r);
    }
  std::sort(ETT.begin(),ETT.end());
  
  // count the number of edges (assume manifoldness)
  int En = 1; // the last is always counted
  for(unsigned i=0;i<ETT.size()-1;++i)
    if (!((ETT[i][0] == ETT[i+1][0]) && (ETT[i][1] == ETT[i+1][1])))
      ++En;
  
  EV  = Eigen::MatrixXi::Constant((int)(En),2,-1);
  FE = Eigen::MatrixXi::Constant((int)(F.rows()),3,-1);
  EF = Eigen::MatrixXi::Constant((int)(En),2,-1);
  En = 0;
  
  for(unsigned i=0;i<ETT.size();++i)
  {
    if (i == ETT.size()-1 ||
      !((ETT[i][0] == ETT[i+1][0]) && (ETT[i][1] == ETT[i+1][1]))
      )
    {
      // Border edge
      std::vector<int>& r1 = ETT[i];
      EV(En,0)     = r1[0];
      EV(En,1)     = r1[1];
      EF(En,0)    = r1[2];
      FE(r1[2],r1[3]) = En;
    } 
    else
    {
      std::vector<int>& r1 = ETT[i];
      std::vector<int>& r2 = ETT[i+1];
      EV(En,0)     = r1[0];
      EV(En,1)     = r1[1];
      EF(En,0)    = r1[2];
      EF(En,1)    = r2[2];
      FE(r1[2],r1[3]) = En;
      FE(r2[2],r2[3]) = En;
      ++i; // skip the next one
    }
    ++En;
  }    
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
