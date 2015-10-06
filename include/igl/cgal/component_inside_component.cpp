// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "component_inside_component.h"

#include <cassert>
#include <list>
#include <limits>
#include <vector>

#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_triangle_primitive.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include "order_facets_around_edge.h"
#include "assign_scalar.h"
#include "points_inside_component.h"

template <typename DerivedV, typename DerivedF, typename DerivedI>
IGL_INLINE bool igl::cgal::component_inside_component(
        const Eigen::PlainObjectBase<DerivedV>& V1,
        const Eigen::PlainObjectBase<DerivedF>& F1,
        const Eigen::PlainObjectBase<DerivedI>& I1,
        const Eigen::PlainObjectBase<DerivedV>& V2,
        const Eigen::PlainObjectBase<DerivedF>& F2,
        const Eigen::PlainObjectBase<DerivedI>& I2) {
    if (F1.rows() <= 0 || I1.rows() <= 0 || F2.rows() <= 0 || I2.rows() <= 0) {
        throw "Component inside test cannot be done on empty component!";
    }

    const Eigen::Vector3i& f = F1.row(I1(0, 0));
    const Eigen::Matrix<typename DerivedV::Scalar, 1, 3> query(
            (V1(f[0],0) + V1(f[1],0) + V1(f[2],0))/3.0,
            (V1(f[0],1) + V1(f[1],1) + V1(f[2],1))/3.0,
            (V1(f[0],2) + V1(f[1],2) + V1(f[2],2))/3.0);
    Eigen::VectorXi inside;
    igl::cgal::points_inside_component(V2, F2, I2, query, inside);
    assert(inside.size() == 1);
    return inside[0];
}

template<typename DerivedV, typename DerivedF>
IGL_INLINE bool igl::cgal::component_inside_component(
        const Eigen::PlainObjectBase<DerivedV>& V1,
        const Eigen::PlainObjectBase<DerivedF>& F1,
        const Eigen::PlainObjectBase<DerivedV>& V2,
        const Eigen::PlainObjectBase<DerivedF>& F2) {
    if (F1.rows() <= 0 || F2.rows() <= 0) {
        throw "Component inside test cannot be done on empty component!";
    }
    Eigen::VectorXi I1(F1.rows()), I2(F2.rows());
    I1.setLinSpaced(F1.rows(), 0, F1.rows()-1);
    I2.setLinSpaced(F2.rows(), 0, F2.rows()-1);
    return igl::cgal::component_inside_component(V1, F1, I1, V2, F2, I2);
}


#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
template bool igl::cgal::component_inside_component<
Eigen::Matrix<double, -1, -1, 0, -1, -1>,
Eigen::Matrix<   int, -1, -1, 0, -1, -1>,
Eigen::Matrix<   int, -1, -1, 0, -1, -1> > (
Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&);

template bool igl::cgal::component_inside_component<
Eigen::Matrix<double, -1, -1, 0, -1, -1>,
Eigen::Matrix<   int, -1, -1, 0, -1, -1> > (
Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&,
Eigen::PlainObjectBase<Eigen::Matrix<   int, -1, -1, 0, -1, -1> > const&);
#endif
