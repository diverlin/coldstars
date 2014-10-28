#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include "MyGl.hpp"
#include <string>

GLuint compileProgram(const std::string& vertex_fname, const std::string& fragment_fname);
GLuint compileShader(const GLchar* source, GLenum shader_type);
std::string file2String(const std::string&);

#endif
