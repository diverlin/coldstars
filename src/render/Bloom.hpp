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


#ifndef BLOOM_H
#define BLOOM_H

#include "../common/myVector.hpp"

class BloomEffect
{
	public:
		Fbo& GetFboFinal() { return fbo_final; };
		GLuint GetTextureBlured() const { return texture_blured; }
          	
                BloomEffect(int, int);
                ~BloomEffect();
                
                void BindShaderPrograms(GLuint, GLuint, GLuint);
                void Pass0(int, int, GLuint, float);
                void RestPasses(int, int);
                void Combine(int, int, GLuint);
                
	private:
                int pass_max;
                int fbo_max_per_pass;

                int screen_w, screen_h;
                                
                std::vector<std::vector<Fbo*>> vec_vec_fbo;
          	Fbo fbo_final;	

          	GLuint texture_blured;
          	
          	GLuint program_blur;
          	GLuint program_extractBright;
          	GLuint program_combine;
};
 
// HDR http://prideout.net/archive/bloom/  
 
#endif
