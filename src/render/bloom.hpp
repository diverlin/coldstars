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
                
                void pass0(const vec2i&, GLuint, float);
                void restPasses(const vec2i&);
                void combine(const vec2i&, GLuint);
};
 
// HDR http://prideout.net/archive/bloom/  
 
#endif
