#include "ShaderLoader.hpp"
#include "GlErrorHelper.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void compileProgram(const std::string& fname_vert, const std::string& fname_frag, GLuint program)
{
    if (program)
    {    
        std::cout<<fname_vert<<" "<<fname_frag<<std::endl;
        std::string vertex_str   = file2String(fname_vert);
        std::string fragment_str = file2String(fname_frag);
                    
        const GLchar* vertex_source   = vertex_str.c_str();
        const GLchar* fragment_source = fragment_str.c_str();
                        
        GLuint vertex_shader = compileShader(vertex_source, GL_VERTEX_SHADER);
        glAttachShader(program, vertex_shader);

        GLuint fragment_shader = compileShader(fragment_source, GL_FRAGMENT_SHADER);
        glAttachShader(program, fragment_shader);

        glLinkProgram(program);
        checkProgramErrors(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}


GLuint compileShader(const GLchar* source, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);
    checkShaderErrors(shader, source);

    return shader;
}

std::string file2String(const std::string& fpath)
{
    std::ifstream file(fpath.c_str());
    if (!file.is_open())
    {
        std::cout<<"Failed to open "<<fpath<<std::endl;
        file.close();
        return " ";
    }

    std::string line = "";
    std::string result = "";
    while(getline(file, line))
    {
        if(line.find("//") != std::string::npos)
        {
              line.replace(line.find("//"), line.length(), "");
        }
        //std::cout<<line<<std::endl;
        result += line;
        result += "\n";
    }

    file.close();
    return result;
}
