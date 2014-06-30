#include <igl/readOBJ.h>
#include <igl/readDMAT.h>
#include <igl/viewer/Viewer.h>
#include <igl/barycenter.h>
#include <igl/avg_edge_length.h>
#include <vector>
#include <stdlib.h>
#include <igl/jet.h>
#include <igl/quad_planarity.h>
#include <igl/planarize_quad_mesh.h>
#include <igl/slice.h>

// Quad mesh generated from conjugate field
Eigen::MatrixXd VQC;
Eigen::MatrixXi FQC;
Eigen::MatrixXi FQCtri;
Eigen::MatrixXd PQC0, PQC1, PQC2, PQC3;

// Planarized quad mesh
Eigen::MatrixXd VQCplan;
Eigen::MatrixXi FQCtriplan;
Eigen::MatrixXd PQC0plan, PQC1plan, PQC2plan, PQC3plan;


// Scale for visualizing the fields
double global_scale;


bool key_down(igl::Viewer& viewer, unsigned char key, int modifier)
{
  using namespace std;
  using namespace Eigen;

  // Plot the original quad mesh
  if (key == '1')
  {
    // Draw the triangulated quad mesh
    viewer.set_mesh(VQC, FQCtri);

    // Assign a color to each quad that corresponds to its planarity
    VectorXd planarity;
    igl::quad_planarity( VQC, FQC, planarity);
    MatrixXd Ct;
    igl::jet(planarity, 0, 0.01, Ct);
    MatrixXd C(FQCtri.rows(),3);
    C << Ct, Ct;
    viewer.set_colors(C);

    // Plot a line for each edge of the quad mesh
    viewer.add_edges (PQC0, PQC1, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC1, PQC2, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC2, PQC3, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC3, PQC0, Eigen::RowVector3d(0,0,0));
  }

  // Plot the planarized quad mesh
  if (key == '2')
  {
    // Draw the triangulated quad mesh
    viewer.set_mesh(VQCplan, FQCtri);

    // Assign a color to each quad that corresponds to its planarity
    VectorXd planarity;
    igl::quad_planarity( VQCplan, FQC, planarity);
    MatrixXd Ct;
    igl::jet(planarity, 0, 0.01, Ct);
    MatrixXd C(FQCtri.rows(),3);
    C << Ct, Ct;
    viewer.set_colors(C);

    // Plot a line for each edge of the quad mesh
    viewer.add_edges (PQC0plan, PQC1plan, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC1plan, PQC2plan, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC2plan, PQC3plan, Eigen::RowVector3d(0,0,0));
    viewer.add_edges (PQC3plan, PQC0plan, Eigen::RowVector3d(0,0,0));
  }

  return false;
}

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;

  // Load a quad mesh generated by a conjugate field
  igl::readOFF("../shared/inspired_mesh_quads_Conjugate.off", VQC, FQC);

  // Convert it in a triangle mesh
  FQCtri.resize(2*FQC.rows(), 3);
  FQCtri <<  FQC.col(0),FQC.col(1),FQC.col(2),
             FQC.col(2),FQC.col(3),FQC.col(0);
  igl::slice( VQC, FQC.col(0), 1, PQC0);
  igl::slice( VQC, FQC.col(1), 1, PQC1);
  igl::slice( VQC, FQC.col(2), 1, PQC2);
  igl::slice( VQC, FQC.col(3), 1, PQC3);

  // Planarize it
  igl::planarize_quad_mesh(VQC, FQC, 100, 0.005, VQCplan);

  // Convert the planarized mesh to triangles
  igl::slice( VQCplan, FQC.col(0), 1, PQC0plan);
  igl::slice( VQCplan, FQC.col(1), 1, PQC1plan);
  igl::slice( VQCplan, FQC.col(2), 1, PQC2plan);
  igl::slice( VQCplan, FQC.col(3), 1, PQC3plan);

  // Launch the viewer
  igl::Viewer viewer;
  key_down(viewer,'2',0);
  viewer.core.invert_normals = true;
  viewer.callback_key_down = &key_down;
  viewer.launch();
}
