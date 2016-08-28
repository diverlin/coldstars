#pragma once

#include "MyGl.hpp"
#include <string>

namespace jeti {

GLuint compile_program(const std::string& vertex_fname, const std::string& fragment_fname);
GLuint compile_shader(const GLchar* source, GLenum shader_type);
std::string read_file(const std::string&);

}

