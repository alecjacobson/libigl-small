#include <igl/readOFF.h>
#include <igl/viewer/Viewer.h>
#include <igl/per_vertex_normals.h>
#include <igl/avg_edge_length.h>
#include <iostream>

#include "igl/lim/lim.h"

using namespace Eigen;
using namespace std;

// Mesh
Eigen::MatrixX3d V0;
Eigen::MatrixX3d V1;
Eigen::MatrixXi F;

SparseMatrix<double> C;
Eigen::VectorXd b;

int energyType;
bool barriersEnabled;

// This function is called every time a keyboard button is pressed
// keys: 0:Original Mesh / 1:Harmonic / 2:Biharmonic / 3:Green / 4:ARAP
bool key_down(igl::Viewer& viewer,unsigned char key,int modifier)
{
  using namespace std;
  using namespace Eigen;

  if(key >= '0' && key <= '5' || key == 'B')
  {
    // compute locally injective map
    int energy = key - '1';

    V1 = V0;

    if(key == 'B')
    {
      barriersEnabled = !barriersEnabled;
    }
    else
    {
      if(energy >= 0)
        energyType = energy;
    }

    if(key != '0')
      igl::lim(V1,V0,F,C,b,energyType,1e-8,100,true,true,barriersEnabled,true,-1,-1);

    // set mesh
    viewer.data.set_vertices(V1);

    return true;
  }

  return false;
}

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace Eigen;

  energyType = 0;
  barriersEnabled = true;

  // load a mesh in OFF format
  igl::readOFF("../shared/grid.off",V0,F);
  V1 = V0;

  // find bottom and left boundary vertices
  vector<int> fixedVertices;
  for(int i=0;i<V0.rows();i++)
  {
    if(V0.row(i)[0] == 0 || V0.row(i)[1] == 0)
      fixedVertices.push_back(i);
  }

  // fix boundaries
  C.resize(2*fixedVertices.size()+2,V0.rows()*2);
  for(int i=0;i<fixedVertices.size();i++)
  {
    C.insert(2*i,2*fixedVertices[i]) = 1;
    C.insert(2*i+1,2*fixedVertices[i]+1) = 1;
  }

  // constraint targets
  b.resize(2*fixedVertices.size()+2);

  for(int i=0;i<fixedVertices.size();i++)
  {
    b(2*i) = V0.row(fixedVertices[i])[0];
    b(2*i+1) = V0.row(fixedVertices[i])[1];
  }

  // drag top left corner vertex to the center
  int id = 2;
  C.insert(2*fixedVertices.size(),2*id) = 1;
  C.insert(2*fixedVertices.size()+1,2*id+1) = 1;
  b(2*fixedVertices.size()) = 0.2;
  b(2*fixedVertices.size()+1) = 0.2;

  // compute locally injective map
  igl::lim(V1,V0,F,C,b,energyType,1e-8,100,true,true,barriersEnabled,true,-1,-1);

  // Show mesh
  igl::Viewer viewer;
  viewer.callback_key_down = &key_down;
  viewer.data.set_mesh(V1, F);
  viewer.core.show_lines = true;
  viewer.core.lighting_factor = 0.0f;
  viewer.launch();
}
