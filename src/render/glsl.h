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


#ifndef GLSL_H
#define GLSL_H

void compile_program(const GLchar *vertex_source, const GLchar* fragment_source, GLuint* pTo_program);
GLuint compile_shader(const GLchar *source, GLenum shader_type);
void printProgramInfoLog(GLuint program);


class FBO
{
	public:
      		GLuint texture;
      		int w, h;
      		GLuint depth_buffer;
      		GLuint fbo;

      		FBO(int _w, int _h);
      		~FBO();

      		void activate();
      		void deactivate();
};

typedef std::vector<FBO*> VEC_pFBO_type; 
typedef std::vector<VEC_pFBO_type> VEC_pList_pFBO_type; 

class BloomEffect
{
	public:
                int pass_max;
                int fbo_max_per_pass;
                
                int screen_w, screen_h;
                
                VEC_pList_pFBO_type pTo_fbo_pass_pList;
          	FBO* pTo_fbo_final;

          	GLuint texture_blured;
          	
          	GLuint program_blur;
          	GLuint program_extractBright;
          	GLuint program_combine;
          	
                BloomEffect(int _screen_w, int _screen_h, GLuint _program_blur, GLuint _program_extractBright, GLuint _program_combine, int _pass_max, int _fbo_max_per_pass);
                ~BloomEffect();
                
                void pass0(GLuint _origin_scene_texture, float brightThreshold);
                void restPasses();
                void combine(GLuint _orig_scene_texture);
};
 
 
 
 
 
 
class ShockWaveEffect
{
	public:
		bool is_alive;
          	bool is_alreadyInRemoveQueue;

          	StarSystem* pTo_starsystem;
          	float center_x, center_y;
          	
          	float x, y, z, time, d_x, d_y, d_z, d_time;

      		ShockWaveEffect(StarSystem* _pTo_starsystem, float _center_x, float _center_y, float _x, float _y, float _z, float _time, float _d_x, float _d_y, float _d_z, float d_time);
      		~ShockWaveEffect();
      		
      		void update();
};
typedef std::vector<ShockWaveEffect*> VEC_pShockWaveEffect_type;            
   
// http://www.flashbang.se/archives/48
// HDR http://prideout.net/archive/bloom/  
    
#endif
