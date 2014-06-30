#include <igl/readOBJ.h>
#include <igl/readDMAT.h>
#include <igl/viewer/Viewer.h>
#include <igl/barycenter.h>
#include <igl/avg_edge_length.h>
#include <vector>
#include <igl/n_polyvector.h>
#include <stdlib.h>

// Input mesh
Eigen::MatrixXd V;
Eigen::MatrixXi F;

// Face barycenters
Eigen::MatrixXd B;

// Scale for visualizing the fields
double global_scale;

// Input constraints
Eigen::VectorXi isConstrained;
std::vector<Eigen::MatrixXd> constraints;

bool key_down(igl::Viewer& viewer, unsigned char key, int modifier)
{
  using namespace std;
  using namespace Eigen;

  if (key <'1' || key >'4')
    return false;

  viewer.clear();
  viewer.set_mesh(V, F);
  viewer.core.show_lines = false;
  viewer.core.show_texture = false;

  int num = key  - '0';

  // Interpolate
  cerr<<"Interpolating N-PolyVector field for N = "<<num<<"... ";

  // Interpolated PolyVector field
  Eigen::MatrixXd pvf;
  igl::n_polyvector(V, F, isConstrained, constraints[num-1], pvf);

  // Highlight in red the constrained faces
  MatrixXd C = MatrixXd::Constant(F.rows(),3,1);
  for (unsigned i=0; i<F.rows();++i)
    if (isConstrained[i])
    C.row(i) << 1, 0, 0;
  viewer.set_colors(C);

  for (int n=0; n<num; ++n)
  {
    // Frame field constraints
    MatrixXd F_t = MatrixXd::Zero(F.rows(),3);
    for (unsigned i=0; i<F.rows();++i)
      if (isConstrained[i])
        F_t.row(i) = constraints[num-1].block(i,n*3,1,3);
    viewer.add_edges (B, B + global_scale*F_t , Eigen::RowVector3d(0,0,1));

    const Eigen::MatrixXd &pvf_t = pvf.block(0,n*3,F.rows(),3);
    for (unsigned i=0; i<F.rows();++i)
      if (isConstrained[i])
        F_t.row(i) *= 0;

    viewer.add_edges (B, B + global_scale*pvf_t , Eigen::RowVector3d(0,0,1));
  }


  return false;
}

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;
  // Load a mesh in OBJ format
  igl::readOBJ("../shared/snail.obj", V, F);

  // Compute face barycenters
  igl::barycenter(V, F, B);

  // Compute scale for visualizing fields
  global_scale =  .2*igl::avg_edge_length(V, F);

  // Allocate constraints and polyvector field
  constraints.resize(4);

  // Load constraints
  MatrixXd temp;
  for (int n =0; n<=3; ++n)
  {
    char cfile[1024]; sprintf(cfile, "../shared/snail%d.dmat",n+1);

    igl::readDMAT(cfile,temp);
    if (n == 0)
      isConstrained = temp.block(0,0,temp.rows(),1).cast<int>();

    constraints[n] = temp.block(0,1,temp.rows(),temp.cols()-1);
  }


  igl::Viewer viewer;

  key_down(viewer,'5',0);

  // Launch the viewer
  viewer.callback_key_down = &key_down;
  viewer.launch();
}
