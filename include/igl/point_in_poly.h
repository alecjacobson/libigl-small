#ifndef IGL_POINT_IN_POLY_H
#define IGL_POINT_IN_POLY_H
#include "igl_inline.h"

#include <vector>

namespace igl
{
  // Determine if 2d point is inside a 2D polygon
  // Inputs:
  //   poly  vector of polygon points, [0]=x, [1]=y. 
  //         Polyline need not be closed (i.e. first point != last point), 
  //         the line segment between last and first selected points is constructed 
  //         within this function.
  //   x     x-coordinate of query point
  //   y     y-coordinate of query point
  // Returns true if query point is in polygon, false otherwise
  // from http://www.visibone.com/inpoly/
bool IGL_INLINE point_in_poly( const std::vector<std::vector<unsigned int > >&poly, 
            const unsigned int xt, 
            const unsigned int yt);

}

#ifdef IGL_HEADER_ONLY
#  include "point_in_poly.cpp"
#endif

#endif
