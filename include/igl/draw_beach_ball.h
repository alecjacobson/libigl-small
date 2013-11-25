// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_DRAW_BEACH_BALL_H
#define IGL_DRAW_BEACH_BALL_H
#ifndef IGL_NO_OPENGL
#include "igl_inline.h"

namespace igl
{
  // Draw a beach ball icon/glyph (from AntTweakBar) at the current origin
  // according to the current orientation: ball has radius 0.75 and axis have
  // length 1.15
  IGL_INLINE void draw_beach_ball();
  #ifdef IGL_HEADER
  #  include "draw_beach_ball.cpp"
  #endif
}

#endif
#endif
