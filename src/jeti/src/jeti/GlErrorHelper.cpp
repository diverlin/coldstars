#include "GlErrorHelper.hpp"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>

namespace jeti {

void checkOpenglErrors(const char *filename, int line_num) 
{
    GLenum err;
    std::stringstream ss;
    for(;;) {
        err = glGetError();
        if (err == GL_NO_ERROR)
            break;
        ss<<"Error: "<<glewGetErrorString(err)<<" at file:"<<std::string(filename)<<" at line:"<<line_num;
    }

    if (ss.str() != "") {
        throw std::runtime_error(ss.str());
    }
}

void checkShaderErrors(GLuint shader, const GLchar* source) 
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success)
    {
        return;
    }
    GLchar InfoLog[1024];
    glGetShaderInfoLog(shader, sizeof(InfoLog), nullptr, InfoLog);
    
    std::ostringstream oss;
    oss<<"checkShaderError:"<<InfoLog<<" source="<<source;
    throw std::runtime_error(oss.str());
}

void checkProgramErrors(GLuint program) 
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success)
    {
        return;
    }
    
    GLchar InfoLog[1024];    
    glGetProgramInfoLog(program, sizeof(InfoLog), nullptr, InfoLog);
    
    std::ostringstream oss;
    oss<<"checkProgramError:"<<InfoLog<<std::endl;
    throw std::runtime_error(oss.str());
}

} // namespace jeti
