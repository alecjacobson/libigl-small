#include "adjacency_list.h"

#include "verbose.h"
#include <algorithm>

template <typename T, typename M>
IGL_INLINE void igl::adjacency_list(
    const M & F, 
    std::vector<std::vector<T> >& A,
    bool sorted)
{
  A.clear(); 
  A.resize(F.maxCoeff()+1);
  
  // Loop over faces
  for(int i = 0;i<F.rows();i++)
  {
    // Loop over this face
    for(int j = 0;j<F.cols();j++)
    {
      // Get indices of edge: s --> d
      int s = F(i,j);
      int d = F(i,(j+1)%F.cols());
      A.at(s).push_back(d);
      A.at(d).push_back(s);
    }
  }
  
  // Remove duplicates
  for(int i=0; i<(int)A.size();++i)
  {
    std::sort(A[i].begin(), A[i].end());
    A[i].erase(std::unique(A[i].begin(), A[i].end()), A[i].end());
  }
  
  // If needed, sort every VV
  if (sorted)
  {
    // Loop over faces
    
    // for every vertex v store a set of ordered edges not incident to v that belongs to triangle incident on v.
    std::vector<std::vector<std::vector<int> > > SR; 
    SR.resize(A.size());
    
    for(int i = 0;i<F.rows();i++)
    {
      // Loop over this face
      for(int j = 0;j<F.cols();j++)
      {
        // Get indices of edge: s --> d
        int s = F(i,j);
        int d = F(i,(j+1)%F.cols());
        // Get index of opposing vertex v
        int v = F(i,(j+2)%F.cols());
        
        std::vector<int> e(2);
        e[0] = d;
        e[1] = v;
        SR[s].push_back(e);
      }
    }
    
    for(int v=0; v<(int)SR.size();++v)
    {
      std::vector<T>& vv = A.at(v);
      std::vector<std::vector<int> >& sr = SR[v];
      
      std::vector<std::vector<int> > pn = sr;
      
      // Compute previous/next for every element in sr
      for(int i=0;i<(int)sr.size();++i)
      {
        int a = sr[i][0];
        int b = sr[i][1];
        
        // search for previous
        int p = -1;
        for(int j=0;j<(int)sr.size();++j)
          if(sr[j][1] == a)
            p = j;
        pn[i][0] = p;
        
        // search for next
        int n = -1;
        for(int j=0;j<(int)sr.size();++j)
          if(sr[j][0] == b)
            n = j;
        pn[i][1] = n;
        
      }
      
      // assume manifoldness (look for beginning of a single chain)
      int c = 0;
      for(int j=0; j<=(int)sr.size();++j)
        if (pn[c][0] != -1)
          c = pn[c][0];
      
      if (pn[c][0] == -1) // border case
      {
        // finally produce the new vv relation
        for(int j=0; j<(int)sr.size();++j)
        {
          vv[j] = sr[c][0];
          if (pn[c][1] != -1)
            c = pn[c][1];
        }
        vv.back() = sr[c][1];
      }
      else
      {
        // finally produce the new vv relation
        for(int j=0; j<(int)sr.size();++j)
        {
          vv[j] = sr[c][0];
          
          c = pn[c][1];
        }
      }
    }
  }
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
template void igl::adjacency_list<unsigned int, Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> >(Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> const&, std::vector<std::vector<unsigned int, std::allocator<unsigned int> >, std::allocator<std::vector<unsigned int, std::allocator<unsigned int> > > >&, bool);
#endif
