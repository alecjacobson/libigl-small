// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2014 Wenzel Jacob <wenzel@inf.ethz.ch>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

/* This class extends the font rendering code in AntTweakBar
   so that it can be used to render text at arbitrary 3D positions */

#ifndef IGL_TEXT_RENDERER_H
#define IGL_TEXT_RENDERER_H

#include <igl/igl_inline.h>
#include <map>
#include <nanogui/opengl.h>

namespace igl
{

class TextRenderer
{
public:
  IGL_INLINE TextRenderer();

  IGL_INLINE virtual int Init();
  IGL_INLINE virtual int Shut();

  IGL_INLINE void BeginDraw(const Eigen::Matrix4f &view, const Eigen::Matrix4f &proj,
    const Eigen::Vector4f &_viewport, float _object_scale);

  IGL_INLINE void EndDraw();

  IGL_INLINE void DrawText(Eigen::Vector3d pos, Eigen::Vector3d normal, const std::string &text);

protected:
  std::map<std::string, void *> m_textObjects;
  Eigen::Matrix4f view_matrix, proj_matrix;
  Eigen::Vector4f viewport;
  float object_scale;
  float mPixelRatio;
  NVGcontext *ctx;
};

}

#ifndef IGL_STATIC_LIBRARY
#  include "TextRenderer.cpp"
#endif

#endif
