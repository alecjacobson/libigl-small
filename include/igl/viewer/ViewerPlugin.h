// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2014 Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IGL_VIEWER_PLUGIN_H
#define IGL_VIEWER_PLUGIN_H
#include <string>
#include <igl/igl_inline.h>

#ifdef ENABLE_XML_SERIALIZATION
  #include <igl/xml/XMLSerializer.h>
  #include <igl/xml/XMLSerialization.h>
#endif

namespace igl
{

// Abstract class for plugins
// All plugins MUST have this class as their parent and may implement any/all
// the callbacks marked `virtual` here.
//
// /////For an example of a basic plugins see plugins/skeleton.h
//
// Return value of callbacks: returning true to any of the callbacks tells
// Viewer that the event has been handled and that it should not be passed to
// other plugins or to other internal functions of Viewer

// Forward declaration of the viewer
class Viewer;

class ViewerPlugin
#ifdef ENABLE_XML_SERIALIZATION
: public ::igl::XMLSerialization
#endif
{
public:
  IGL_INLINE ViewerPlugin()
  #ifdef ENABLE_XML_SERIALIZATION
  : XMLSerialization("dummy")
  #endif
  {plugin_name = "dummy";}

  virtual ~ViewerPlugin(){}

  // This function is called when the viewer is initialized (no mesh will be loaded at this stage)
  IGL_INLINE virtual void init(igl::Viewer *_viewer)
  {
    viewer = _viewer;
  }

  // This function is called before shutdown
  IGL_INLINE virtual void shutdown()
  {
  }

  // This function is called before a mesh is loaded
  IGL_INLINE virtual bool load(std::string filename)
  {
    return false;
  }

  // This function is called before a mesh is saved
  IGL_INLINE virtual bool save(std::string filename)
  {
    return false;
  }

  // Runs immediately after a new mesh had been loaded.
  IGL_INLINE virtual bool post_load()
  {
    return false;
  }

  // This function is called before the draw procedure of Preview3D
  IGL_INLINE virtual bool pre_draw()
  {
    return false;
  }

  // This function is called after the draw procedure of Preview3D
  IGL_INLINE virtual bool post_draw()
  {
    return false;
  }

  // This function is called when the mouse button is pressed
  // - button can be GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON
  // - modifiers is a bitfield that might one or more of the following bits Preview3D::NO_KEY, Preview3D::SHIFT, Preview3D::CTRL, Preview3D::ALT;
  IGL_INLINE virtual bool mouse_down(int button, int modifier)
  {
    return false;
  }

  // This function is called when the mouse button is released
  // - button can be GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON
  // - modifiers is a bitfield that might one or more of the following bits Preview3D::NO_KEY, Preview3D::SHIFT, Preview3D::CTRL, Preview3D::ALT;
  IGL_INLINE virtual bool mouse_up(int button, int modifier)
  {
    return false;
  }

  // This function is called every time the mouse is moved
  // - mouse_x and mouse_y are the new coordinates of the mouse pointer in screen coordinates
  IGL_INLINE virtual bool mouse_move(int mouse_x, int mouse_y)
  {
    return false;
  }

  // This function is called every time the scroll wheel is moved
  // Note: this callback is not working with every glut implementation
  IGL_INLINE virtual bool mouse_scroll(float delta_y)
  {
    return false;
  }

  // This function is called when a keyboard key is pressed
  // - modifiers is a bitfield that might one or more of the following bits Preview3D::NO_KEY, Preview3D::SHIFT, Preview3D::CTRL, Preview3D::ALT;
  IGL_INLINE virtual bool key_down(unsigned char key, int modifiers)
  {
    return false;
  }

  // This function is called when a keyboard key is release
  // - modifiers is a bitfield that might one or more of the following bits Preview3D::NO_KEY, Preview3D::SHIFT, Preview3D::CTRL, Preview3D::ALT;
  IGL_INLINE virtual bool key_up(unsigned char key, int modifiers)
  {
    return false;
  }

  std::string plugin_name;
protected:
  // Pointer to the main Viewer class
  Viewer *viewer;
};

}

#endif
