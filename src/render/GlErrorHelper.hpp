#ifndef GLERRORHELPER_HPP
#define GLERRORHELPER_HPP

#include "MyGl.hpp"
#include <string>

void checkOpenglErrors(const char *filename, int line_num); 
void checkShaderErrors(GLuint shader, const GLchar*);
void checkProgramErrors(GLuint);

#endif
