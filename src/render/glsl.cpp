/*
Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "glsl.hpp"


void compile_program(const GLchar *pTo_vertex_source, const GLchar *pTo_fragment_source, GLuint* pTo_program)
{
	GLuint vertex_shader, fragment_shader;
  
    	if (*pTo_program != 0)
    	{
        	vertex_shader = compile_shader(pTo_vertex_source, GL_VERTEX_SHADER);
        	glAttachShader(*pTo_program, vertex_shader);

        	fragment_shader = compile_shader(pTo_fragment_source, GL_FRAGMENT_SHADER);
        	glAttachShader(*pTo_program, fragment_shader);
 
        	glLinkProgram(*pTo_program);

        	glDeleteShader(vertex_shader);
        	glDeleteShader(fragment_shader);
    	}
    	else
        	printf("program was not generated succesfully\n");

    	printProgramInfoLog(*pTo_program);
}


GLuint compile_shader(const GLchar *source, GLenum shader_type)
{
    	GLuint shader = glCreateShader(shader_type);
    	glShaderSource(shader, 1, &source, NULL);

    	glCompileShader(shader);
    
    	return shader;
}

void printProgramInfoLog(GLuint program)
{
    	char log[256];
    	glGetInfoLogARB(program, 256, NULL, log);
    	printf(" Infolog: %s, program id = %i\n", log, program);
}

