#pragma once

#include "MyGl.hpp"
#include <string>

namespace jeti {

GLuint compileProgram(const std::string& vertex_fname, const std::string& fragment_fname);
GLuint compileShader(const GLchar* source, GLenum shader_type);
std::string file2String(const std::string&);

}

