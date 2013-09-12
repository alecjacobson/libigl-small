#include "texture_from_tga.h"
#ifndef IGL_NO_OPENGL

#include "tga.h"
#include "report_gl_error.h"
#include <cstring>

IGL_INLINE bool igl::texture_from_tga(const std::string tga_file, GLuint & id)
{
  using namespace std;
  using namespace igl;

  // read pixels to tga file
  FILE * imgFile;
  // "-" as input file name is code for read from stdin
  imgFile = fopen(tga_file.c_str(),"r");
  if(NULL==imgFile)
  {
    printf("IOError: %s could not be opened...",tga_file.c_str());
    return false;
  }

  // gliReadTGA annoyingly uses char * instead of const char *
  size_t len = tga_file.length();
  char* tga_file_char = new char [ len + 1 ];
  strcpy( tga_file_char, tga_file.c_str() );
  // read image
  gliGenericImage* img = gliReadTGA(imgFile, tga_file_char, 0, 0);
  // clean up filename buffer
  delete[] tga_file_char;
  fclose( imgFile );

  // set up texture mapping parameters and generate texture id
  glGenTextures(1,&id);
  glBindTexture(GL_TEXTURE_2D, id);
  // Texture parameters
  float empty[] = {1.0f,1.0f,1.0f,0.0f};
  glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,empty);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
  //  GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR);

  // OpenGL by default tries to read data in multiples of 4, if our data is
  // only RGB or BGR and the width is not divible by 4 then we need to alert
  // opengl
  if((img->width % 4) != 0 && 
   (img->format == GL_RGB || 
    img->format == GL_BGR))
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    igl::report_gl_error();
  }

  // Load texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width,
    img->height, 0, img->format, GL_UNSIGNED_BYTE,
    img->pixels);
  return id;
}

#endif
