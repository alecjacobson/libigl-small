// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2015 Qingnan Zhou <qnzhou@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include "outer_facet.h"
#include "../outer_element.h"
#include "order_facets_around_edge.h"
#include <algorithm>

template<
    typename DerivedV,
    typename DerivedF,
    typename DerivedI,
    typename IndexType
    >
IGL_INLINE void igl::cgal::outer_facet(
        const Eigen::PlainObjectBase<DerivedV> & V,
        const Eigen::PlainObjectBase<DerivedF> & F,
        const Eigen::PlainObjectBase<DerivedI> & I,
        IndexType & f,
        bool & flipped) {

    // Algorithm:
    //
    //    1. Find an outer edge (s, d).
    //
    //    2. Order adjacent facets around this edge. Because the edge is an
    //    outer edge, there exists a plane passing through it such that all its
    //    adjacent facets lie on the same side. The implementation of
    //    order_facets_around_edge() will find a natural start facet such that
    //    The first and last facets according to this order are on the outside.
    //
    //    3. Because the vertex s is an outer vertex by construction (see
    //    implemnetation of outer_edge()). The first adjacent facet is facing
    //    outside (i.e. flipped=false) if it contains directed edge (s, d).  
    //
    typedef typename DerivedV::Scalar Scalar; typedef typename DerivedV::Index
        Index; const size_t INVALID = std::numeric_limits<size_t>::max();

    Index s,d;
    Eigen::Matrix<Index,Eigen::Dynamic,1> incident_faces;
    outer_edge(V, F, I, s, d, incident_faces);
    assert(incident_faces.size() > 0);

    auto convert_to_signed_index = [&](size_t fid) -> int{
        if ((F(fid, 0) == s && F(fid, 1) == d) ||
            (F(fid, 1) == s && F(fid, 2) == d) ||
            (F(fid, 2) == s && F(fid, 0) == d) ) {
            return int(fid+1) * -1;
        } else {
            return int(fid+1);
        }
    };

    auto signed_index_to_index = [&](int signed_id) -> size_t {
        return size_t(abs(signed_id) - 1);
    };

    std::vector<int> adj_faces(incident_faces.size());
    std::transform(incident_faces.data(),
            incident_faces.data() + incident_faces.size(),
            adj_faces.begin(),
            convert_to_signed_index);

    Eigen::VectorXi order;
    order_facets_around_edge(V, F, s, d, adj_faces, order);

    f = signed_index_to_index(adj_faces[order[0]]);
    flipped = adj_faces[order[0]] > 0;
}
