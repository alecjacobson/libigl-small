#include "igl/matlab/MatlabWorkspace.h"

// IGL
#include "igl/list_to_matrix.h"

// MATLAB
#include "mat.h"

// STL
#include <iostream>
#include <algorithm>

IGL_INLINE igl::MatlabWorkspace::MatlabWorkspace()
{
}

IGL_INLINE igl::MatlabWorkspace::~MatlabWorkspace()
{
  // clean up data
  clear();
}

IGL_INLINE void igl::MatlabWorkspace::clear()
{
  for_each(data.begin(),data.end(),&mxDestroyArray);
  data.clear();
  names.clear();
}

IGL_INLINE bool igl::MatlabWorkspace::write(const std::string & path) const
{
  using namespace std;
  MATFile * mat_file = matOpen(path.c_str(), "w");
  assert(names.size() == data.size());
  // loop over names and data
  for(int i = 0;i < (int)names.size(); i++)
  {
    // Put variable as LOCAL variable
    int status = matPutVariable(mat_file,names[i].c_str(), data[i]);
    if(status != 0) 
    {
      cerr<<"^MatlabWorkspace::save Error: matPutVariable ("<<names[i]<<
        ") failed"<<endl;
      return false;
    } 
  }
  if(matClose(mat_file) != 0)
  {
    fprintf(stderr,"Error closing file %s\n",path.c_str());
    return false;
  }
  return true;
}

IGL_INLINE bool igl::MatlabWorkspace::read(const std::string & path)
{
  using namespace std;

  MATFile * mat_file;

  mat_file = matOpen(path.c_str(), "r");
  if (mat_file == NULL) 
  {
    cerr<<"Error: failed to open "<<path<<endl;
    return false;
  }

  int ndir;
  const char ** dir = (const char **)matGetDir(mat_file, &ndir);
  if (dir == NULL) {
    cerr<<"Error reading directory of file "<< path<<endl;
    return false;
  }
  mxFree(dir);

  // Must close and reopen
  if(matClose(mat_file) != 0)
  {
    cerr<<"Error: failed to close file "<<path<<endl;
    return false;
  }
  mat_file = matOpen(path.c_str(), "r");
  if (mat_file == NULL) 
  {
    cerr<<"Error: failed to open "<<path<<endl;
    return false;
  }
  

  /* Read in each array. */
  for (int i=0; i<ndir; i++) 
  {
    const char * name;
    mxArray * mx_data = matGetNextVariable(mat_file, &name);
    if (mx_data == NULL) 
    {
      cerr<<"Error: matGetNextVariable failed in "<<path<<endl;
      return false;
    } 
    const int dims = mxGetNumberOfDimensions(mx_data);
    assert(dims == 2);
    if(dims != 2)
    {
      fprintf(stderr,"Variable '%s' has %d ≠ 2 dimensions. Skipping\n",
          name,dims);
      mxDestroyArray(mx_data);
      continue;
    }
    // don't destroy
    names.push_back(name);
    data.push_back(mx_data);
  }

  if(matClose(mat_file) != 0)
  {
    cerr<<"Error: failed to close file "<<path<<endl;
    return false;
  }

  return true;
}

// Treat everything as a double
template <typename DerivedM>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save(
  const Eigen::PlainObjectBase<DerivedM>& M,
  const std::string & name)
{
  using namespace std;
  const int m = M.rows();
  const int n = M.cols();
  mxArray * mx_data = mxCreateDoubleMatrix(m,n,mxREAL);
  data.push_back(mx_data);
  names.push_back(name);
  // Copy data immediately
  // Q: Won't this be incorrect for integers?
  copy(M.data(),M.data()+M.size(),mxGetPr(mx_data));
  return *this;
}

// Treat everything as a double
template <typename MT>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save(
  const Eigen::SparseMatrix<MT>& M,
  const std::string & name)
{
  using namespace std;
  const int m = M.rows();
  const int n = M.cols();
  // THIS WILL NOT WORK FOR ROW-MAJOR
  assert(n==M.outerSize());
  const int nzmax = M.nonZeros();
  mxArray * mx_data = mxCreateSparse(m, n, nzmax, mxREAL);
  data.push_back(mx_data);
  names.push_back(name);
  // Copy data immediately
  double * pr = mxGetPr(mx_data);
  mwIndex * ir = mxGetIr(mx_data);
  mwIndex * jc = mxGetJc(mx_data);

  // Iterate over outside
  int k = 0;
  for(int j=0; j<M.outerSize();j++)
  {
    jc[j] = k;
    // Iterate over inside
    for(typename Eigen::SparseMatrix<MT>::InnerIterator it (M,j); it; ++it)
    {
      pr[k] = it.value();
      ir[k] = it.row();
      k++;
    }
  }
  jc[M.outerSize()] = k;

  return *this;
}

template <typename ScalarM>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save(
  const std::vector<std::vector<ScalarM> > & vM,
  const std::string & name)
{
  Eigen::MatrixXd M;
  list_to_matrix(vM,M);
  return this->save(M,name);
}

template <typename ScalarV>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save(
  const std::vector<ScalarV> & vV,
  const std::string & name)
{
  Eigen::MatrixXd V;
  list_to_matrix(vV,V);
  return this->save(V,name);
}

template <typename DerivedM>
IGL_INLINE igl::MatlabWorkspace& 
  igl::MatlabWorkspace::save_index(
    const Eigen::PlainObjectBase<DerivedM>& M,
    const std::string & name)
{
  DerivedM Mp1 = M;
  Mp1.array() += 1;
  return this->save(Mp1,name);
}

template <typename ScalarM>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save_index(
  const std::vector<std::vector<ScalarM> > & vM,
  const std::string & name)
{
  Eigen::MatrixXd M;
  list_to_matrix(vM,M);
  return this->save_index(M,name);
}

template <typename ScalarV>
IGL_INLINE igl::MatlabWorkspace& igl::MatlabWorkspace::save_index(
  const std::vector<ScalarV> & vV,
  const std::string & name)
{
  Eigen::MatrixXd V;
  list_to_matrix(vV,V);
  return this->save_index(V,name);
}

template <typename DerivedM>
IGL_INLINE bool igl::MatlabWorkspace::find( 
  const std::string & name,
  Eigen::PlainObjectBase<DerivedM>& M)
{
  using namespace std;
  const int i = std::find(names.begin(), names.end(), name)-names.begin();
  if(i>=(int)names.size())
  {
    return false;
  }
  assert(i<=(int)data.size());
  mxArray * mx_data = data[i];
  assert(!mxIsSparse(mx_data));
  assert(mxGetNumberOfDimensions(mx_data) == 2);
  //cout<<name<<": "<<mxGetM(mx_data)<<" "<<mxGetN(mx_data)<<endl;
  const int m = mxGetM(mx_data);
  const int n = mxGetN(mx_data);

  // Handle vectors
  if(DerivedM::IsVectorAtCompileTime)
  {
    assert(m==1 || n==1);
    M.resize(m*n);
  }else
  {
    M.resize(m,n);
  }
  copy(
    mxGetPr(mx_data),
    mxGetPr(mx_data)+mxGetNumberOfElements(mx_data),
    M.data());
  return true;
}

template <typename MT>
IGL_INLINE bool igl::MatlabWorkspace::find( 
  const std::string & name,
  Eigen::SparseMatrix<MT>& M)
{
  using namespace std;
  using namespace Eigen;
  const int i = std::find(names.begin(), names.end(), name)-names.begin();
  if(i>=(int)names.size())
  {
    return false;
  }
  assert(i<=(int)data.size());
  mxArray * mx_data = data[i];
  assert(mxIsSparse(mx_data));
  assert(mxGetNumberOfDimensions(mx_data) == 2);
  //cout<<name<<": "<<mxGetM(mx_data)<<" "<<mxGetN(mx_data)<<endl;
  const int m = mxGetM(mx_data);
  const int n = mxGetN(mx_data);

  // Copy data immediately
  double * pr = mxGetPr(mx_data);
  mwIndex * ir = mxGetIr(mx_data);
  mwIndex * jc = mxGetJc(mx_data);

  vector<Triplet<MT> > MIJV;
  MIJV.reserve(mxGetNumberOfElements(mx_data));

  // Iterate over outside
  int k = 0;
  for(int j=0; j<n;j++)
  {
    // Iterate over inside
    while(k<(int)jc[j+1])
    {
      //cout<<ir[k]<<" "<<j<<" "<<pr[k]<<endl;
      assert((int)ir[k]<m);
      assert((int)j<n);
      MIJV.push_back(Triplet<MT >(ir[k],j,pr[k]));
      k++;
    }
  }
  M.resize(m,n);
  M.setFromTriplets(MIJV.begin(),MIJV.end());
  return true;

}

template <typename DerivedM>
IGL_INLINE bool igl::MatlabWorkspace::find_index( 
  const std::string & name,
  Eigen::PlainObjectBase<DerivedM>& M)
{
  if(!find(name,M))
  {
    return false;
  }
  M.array() -= 1;
  return true;
}


//template <typename Data>
//bool igl::MatlabWorkspace::save(const Data & M, const std::string & name)
//{
//  using namespace std;
//  // If I don't know the type then I can't save it
//  cerr<<"^MatlabWorkspace::save Error: Unknown data type. "<<
//    name<<" not saved."<<endl;
//  return false;
//}
