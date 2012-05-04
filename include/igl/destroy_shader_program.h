#ifndef IGL_DESTROY_SHADER_PROGRAM_H
#define IGL_DESTROY_SHADER_PROGRAM_H
#include "igl_inline.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#elif defined(_WIN32)
#  define NOMINMAX
#  include <Windows.h>
#  undef NOMINMAX
#  include <GL/gl.h>
#else
#  define GL_GLEXT_PROTOTYPES
#  include <GL/gl.h>
#  include <GL/glext.h>
#endif

namespace igl
{
  // Properly destroy a shader program. Detach and delete each of its shaders
  // and delete it
  // Inputs:
  //   id  index id of created shader, set to 0 on error
  // Returns true on success, false on error
  // 
  // Note: caller is responsible for making sure he doesn't foolishly continue
  // to use id as if it still contains a program
  // 
  // See also: create_shader_program
  IGL_INLINE bool destroy_shader_program(const GLuint id);
}

#ifdef IGL_HEADER_ONLY
#  include "destroy_shader_program.cpp"
#endif

#endif
