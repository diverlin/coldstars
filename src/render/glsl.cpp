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


#include "glsl.h"
#include "GL/glew.h" 


BloomEffect :: BloomEffect(int _screen_w, 
			   int _screen_h, 
			   GLuint _program_blur, 
			   GLuint _program_extractBright, 
			   GLuint _program_combine, 
			   int _pass_max, 
			   int _fbo_max_per_pass)
{
	pass_max = 3; 	      //_pass_max;
	fbo_max_per_pass = 4; //_fbo_max_per_pass;
            
	screen_w = _screen_w;
	screen_h = _screen_h;
            
        for (int pass_num = 0; pass_num < pass_max; pass_num++) 
        {   
        	VEC_pFBO_type fbo_pList;
        	int div = 1;    
		for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
		{
                	FBO* pTo_fbo = new FBO(screen_w/div, screen_h/div); 
			fbo_pList.push_back(pTo_fbo);
			div *= 2;
		}
		pTo_fbo_pass_pList.push_back(fbo_pList);
	}

        pTo_fbo_final = new FBO(screen_w, screen_h);

	program_blur =          _program_blur;
	program_extractBright = _program_extractBright;
	program_combine =       _program_combine;
}


void BloomEffect :: pass0(GLuint _orig_scene_texture, float brightThreshold)
{
	// RENDER TO FBO0
        (pTo_fbo_pass_pList[0])[0]->activate();

	// render background
	glUseProgram(program_extractBright);
	glActiveTexture(GL_TEXTURE0);                                
	glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
	glUniform1i(glGetUniformLocation(program_extractBright, "source"), 0);

	glUniform1f(glGetUniformLocation(program_extractBright, "threshold"), brightThreshold);
	
	drawFullScreenQuad(screen_w, screen_h, -999.0);
	glUseProgram(0);

        (pTo_fbo_pass_pList[0])[0]->deactivate();
        
        int div = 2;    
	for(int fbo_num = 1; fbo_num < fbo_max_per_pass; fbo_num++)
	{
	        (pTo_fbo_pass_pList[0])[fbo_num]->activate();
        	drawFullScreenTexturedQuad((pTo_fbo_pass_pList[0])[0]->texture, screen_w/div, screen_h/div, -999.0);
		(pTo_fbo_pass_pList[0])[fbo_num]->deactivate();
         
		div *= 2;
	}
		
        
}       
                
void BloomEffect :: restPasses()
{
	for (int pass_num = 1; pass_num < pass_max; pass_num++) 
        {   
        	int div = 1;    
		for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
		{
		        (pTo_fbo_pass_pList[pass_num])[fbo_num]->activate();
          		drawFullScreenTexturedQuadBlurred((pTo_fbo_pass_pList[pass_num-1])[fbo_num]->texture, screen_w/div, screen_h/div, -999.0, program_blur);
          		(pTo_fbo_pass_pList[pass_num])[fbo_num]->deactivate();
          
			div *= 2;
		}
	}	
}



void BloomEffect :: combine(GLuint _orig_scene_texture)
{
          // RENDER TO final FBO
          pTo_fbo_final->activate();

          glUseProgram(program_combine);

          glActiveTexture(GL_TEXTURE0);                                
          glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
          glUniform1i(glGetUniformLocation(program_combine, "Scene"), 0);


          glActiveTexture(GL_TEXTURE1);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[0]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex1"), 1);

          glActiveTexture(GL_TEXTURE2);        
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[1]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex2"), 2);

          glActiveTexture(GL_TEXTURE3);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[2]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex3"), 3);

          glActiveTexture(GL_TEXTURE4);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[3]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex4"), 4);


          glActiveTexture(GL_TEXTURE5);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[0]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex1"), 5);

          glActiveTexture(GL_TEXTURE6);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[1]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex2"), 6);

          glActiveTexture(GL_TEXTURE7);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[2]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex3"), 7);

          glActiveTexture(GL_TEXTURE8);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[3]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex4"), 8);


          glActiveTexture(GL_TEXTURE9);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[0]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex1"), 9);

          glActiveTexture(GL_TEXTURE10);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[1]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex2"), 10);

          glActiveTexture(GL_TEXTURE11);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[2]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex3"), 11);

          glActiveTexture(GL_TEXTURE12);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[3]->texture);
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex4"), 12);

          drawFullScreenQuad(screen_w, screen_h, -999.0);

          pTo_fbo_final->deactivate();
          //texture_blured = pTo_fbo_final->texture; //(pTo_fbo_pass_pList[pass_num])[fbo_num]->texture; // improove, blured texture is needed for volumetric shader
          texture_blured = (pTo_fbo_pass_pList[2])[3]->texture; // improove, blured texture is needed for volumetric shader
}


















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


FBO :: FBO(int _w, int _h)
{
      w = _w;
      h = _h;
      // create a color texture
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  w, h, 0, GL_RGBA, GL_INT, NULL); // no data transferred


      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);

      // create depth renderbuffer
      glGenRenderbuffers(1, &depth_buffer); // putcom
      glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buffer);
      glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32, w, h);

      // create FBO
      glGenFramebuffers(1, &fbo);   // putcom
      glBindFramebuffer(GL_FRAMEBUFFER, fbo);  // putcom     // switch to our fbo so we can bind stuff to it
      glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture, 0);
      glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

      // Go back to regular frame buffer rendering
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO :: activate()
{
     glBindTexture(GL_TEXTURE_2D, 0);            // unbind texture
     glBindFramebuffer(GL_FRAMEBUFFER, fbo);    // putcom // bind fbo

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();

     glPushAttrib(GL_VIEWPORT_BIT);               // viewport is shared with the main context
     glViewport(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
}

void FBO :: deactivate()
{
     glActiveTexture(GL_TEXTURE0);                // debug
     glPopAttrib();                               // restore viewport
}




ShockWaveEffect :: ShockWaveEffect(vec2f _center_pos, 
 				   float _x, float _y, float _z, float _time, 
 				   float _d_x, float _d_y, float _d_z, float _d_time)
{
          is_alive = true;
          is_alreadyInRemoveQueue = false;

          starsystem = NULL;
          center_x = _center_pos.x/float(g_VIEW_WIDTH);
          center_y = _center_pos.y/float(g_VIEW_HEIGHT);

          x = _x;
          y = _y;
          z = _z;
          time = _time; 

          d_x = _d_x;
          d_y = _d_y;
          d_z = _d_z;
          d_time = _d_time; 
}

ShockWaveEffect :: ~ShockWaveEffect()
{}


void ShockWaveEffect :: setStarSystem(StarSystem* _starsystem)
{
	starsystem = _starsystem;
}

      		
void ShockWaveEffect :: update()
{
	x -= d_x;

	if (y > 0)
		y -= d_y;
	else
            	is_alive = false;

     	z -= d_z;
      	time -= d_time;

    	if (is_alive == false)
      	{
          	if (is_alreadyInRemoveQueue == false)
            	{
                	//pTo_starsystem.effect_SHOCKWAVE_remove_queue.append();
                	is_alreadyInRemoveQueue = true;
             	}   
	}	         
}
             
// http://www.flashbang.se/archives/48
// HDR http://prideout.net/archive/bloom/  
