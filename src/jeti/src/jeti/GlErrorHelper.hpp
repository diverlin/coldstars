#pragma once

#include "MyGl.hpp"
#include <string>

namespace jeti {

void checkOpenglErrors(const char *filename, int line_num); 
void checkShaderErrors(GLuint shader, const GLchar*);
void checkProgramErrors(GLuint);

} // namespace jeti

