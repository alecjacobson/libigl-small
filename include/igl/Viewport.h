#ifndef IGL_VIEWPORT_H
#define IGL_VIEWPORT_H

#include "Camera.h"

namespace igl
{
  struct Viewport
  {
    int x,y,width,height;
    igl::Camera camera;
    // Constructors
    Viewport():
      x(0),y(0),width(0),height(0),camera(){};
    Viewport(
      const int x, 
      const int y, 
      const int width,
      const int height, 
      const igl::Camera & camera):
      x(x),
      y(y),
      width(width),
      height(height),
      camera(camera)
    {
    };
    void reshape(
      const int x, 
      const int y, 
      const int width,
      const int height)
    {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
    };
    // Given mouse_x,mouse_y on the entire window return mouse_x, mouse_y in
    // this viewport.
    //
    // Inputs:
    //   my  mouse y-coordinate
    //   wh  window weight
    // Returns y-coordinate in viewport
    int mouse_y(const int my,const int wh)
    {
      return my - (wh - height - y);
    }
    // Inputs:
    //   mx  mouse x-coordinate
    // Returns x-coordinate in viewport
    int mouse_x(const int mx)
    {
      return mx - x;
    }
  };
}

#endif
