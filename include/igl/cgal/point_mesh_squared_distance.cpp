// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2014 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "point_mesh_squared_distance.h"
#include "mesh_to_cgal_triangle_list.h"

template <typename Kernel>
IGL_INLINE void igl::point_mesh_squared_distance(
  const Eigen::MatrixXd & P,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::VectorXd & sqrD,
  Eigen::VectorXi & I,
  Eigen::MatrixXd & C)
{
  using namespace std;
  typedef CGAL::Point_3<Kernel>    Point_3;
  typedef CGAL::Triangle_3<Kernel> Triangle_3; 
  typedef typename std::vector<Triangle_3>::iterator Iterator;
  typedef CGAL::AABB_triangle_primitive<Kernel, Iterator> Primitive;
  typedef CGAL::AABB_traits<Kernel, Primitive> AABB_triangle_traits;
  typedef CGAL::AABB_tree<AABB_triangle_traits> Tree;
  typedef typename Tree::Point_and_primitive_id Point_and_primitive_id;

  // Must be 3D
  assert(V.cols() == 3);
  assert(P.cols() == 3);
  // Must be triangles
  assert(F.cols() == 3);
  // Make list of cgal triangles
  Tree tree;
  vector<Triangle_3> T;
  mesh_to_cgal_triangle_list(V,F,T);
  tree.insert(T.begin(),T.end());

  tree.accelerate_distance_queries();
  const int n = P.rows();
  sqrD.resize(n,1);
  I.resize(n,1);
  C.resize(n,P.cols());
  for(int p = 0;p < n;p++)
  {
    Point_3 query(P(p,0),P(p,1),P(p,2));
    // Find closest point and primitive id
    Point_and_primitive_id pp = tree.closest_point_and_primitive(query);
    Point_3 closest_point = pp.first;
    C(p,0) = CGAL::to_double(closest_point[0]);
    C(p,1) = CGAL::to_double(closest_point[1]);
    C(p,2) = CGAL::to_double(closest_point[2]);
    sqrD(p) = CGAL::to_double((closest_point-query).squared_length());
    I(p) = pp.second - T.begin();
  }
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
template void igl::point_mesh_squared_distance<CGAL::Epeck>( const Eigen::MatrixXd & P, const Eigen::MatrixXd & V, const Eigen::MatrixXi & F, Eigen::VectorXd & sqrD, Eigen::VectorXi & I, Eigen::MatrixXd & C);

#endif
