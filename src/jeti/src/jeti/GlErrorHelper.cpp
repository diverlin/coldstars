#include "GlErrorHelper.hpp"
#include <stdexcept>
#include <vector>
#include <sstream>

namespace jeti {

void checkOpenglErrors(const char *filename, int line_num) 
{
    std::vector<unsigned> errors;
    GLuint error;
    while ((error = glGetError()) and (error != GL_NO_ERROR))
    {
        errors.push_back(error);
    }
    
    if (errors.empty())
    {
        return;
    }
    
    // hack due to GLEW limitation (with current 1.9.0) (GLEW with opengl context 3.2 generate GL_INVALID_ENUM error)
    // should be removed when this will be fixed in glew. More information about glew limitation at http://www.opengl.org/wiki/OpenGL_Loading_Library , glew section
    // hack start
    if (errors.size() == 1)
        if (*errors.begin() == GL_INVALID_ENUM)
            return;
    // hack end
     
    std::stringstream ss;
    ss<<"OpenGL errors:\n";
    for(unsigned int i=0; i<errors.size(); i++)
    {
        ss<<filename<<":"<<line_num<<":"<<error<<std::endl;
    }
    
    throw std::runtime_error(ss.str());
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

}
