#include "ShaderLoader.hpp"
#include <GlErrorHelper.hpp>
#include <iostream>
#include <fstream>
#include <vector>

namespace jeti {

GLuint compile_program(const std::string& fname_vert, const std::string& fname_frag)
{
    GLuint program = glCreateProgram();
    if (program)
    {    
        std::cout<<fname_vert<<" "<<fname_frag<<std::endl;
        std::string vertex_str   = read_file(fname_vert);
        std::string fragment_str = read_file(fname_frag);
                    
        const GLchar* vertex_source   = vertex_str.c_str();
        const GLchar* fragment_source = fragment_str.c_str();
                        
        GLuint vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
        glAttachShader(program, vertex_shader);

        GLuint fragment_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
        glAttachShader(program, fragment_shader);

        glLinkProgram(program);
        checkProgramErrors(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
    else
    {
        std::cout<<"Shader program fail to generate"<<std::endl;
        exit(1);        
    }
    
    return program;
}


GLuint compile_shader(const GLchar* source, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);
    checkShaderErrors(shader, source);

    return shader;
}

std::string read_file(const std::string& fpath)
{
    std::ifstream file(fpath.c_str());
    if (!file.is_open())
    {
        file.close();
        std::cout<<"Failed to open "<<fpath<<std::endl;
        exit(1);
    }

    std::string line;
    std::string result;
    while(getline(file, line))
    {
        result += line + "\n";
    }

    file.close();
    return result;
}

} // namepsace jeti
