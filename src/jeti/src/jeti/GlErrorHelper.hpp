#pragma once

#include "MyGl.hpp"
#include <string>

#define USE_OPENGL_DEBUG
#ifdef USE_OPENGL_DEBUG
    #define CHECK_OPENGL_ERRORS jeti::checkOpenglErrors(__FILE__,__LINE__);
#else
    #define CHECK_OPENGL_ERRORS
#endif

namespace jeti {

void checkOpenglErrors(const char *filename, int line_num); 
void checkShaderErrors(GLuint shader, const GLchar*);
void checkProgramErrors(GLuint);

} // namespace jeti

