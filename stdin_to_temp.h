#ifndef IGL_STDIN_TO_TEMP_H
#define IGL_STDIN_TO_TEMP_H
#include "igl_inline.h"
#include <cstdio>
namespace igl
{
  // Write stdin/piped input to a temporary file which can than be preprocessed as it
  // is (a normal file). This is often useful if you want to process stdin/piped
  // with library functions that expect to be able to fseek(), rewind() etc..
  //
  // If your application is not using fseek(), rewind(), etc. but just reading
  // from stdin then this will likely cause a bottle neck as it defeats the whole
  // purpose of piping.
  //
  // Outputs:
  //   temp_file  pointer to temp file pointer, rewound to beginning of file so
  //     its ready to be read
  // Return true only if no errors were found
  //
  // Note: Caller is responsible for closing the file (tmpfile() automatically
  // unlinks the file so there is no need to remove/delete/unlink the file)
  IGL_INLINE bool stdin_to_temp(FILE ** temp_file);
}

#ifdef IGL_HEADER_ONLY
#  include "stdin_to_temp.cpp"
#endif

#endif
