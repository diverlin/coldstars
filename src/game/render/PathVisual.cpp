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

#include "PathVisual.hpp"
#include <cmath>
#include "Render.hpp"
#include "../common/constants.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../common/myVector.hpp"

PathVisual::PathVisual()  
{ 
	gl_list = glGenLists(1); 
}

PathVisual::~PathVisual() 
{
	glDeleteLists(gl_list, sizeof(gl_list));
}

void PathVisual::FillData(TextureOb* textureOb, const std::vector<vec2f>& vec2f_vec, int step, int point_size)
{  
	glDeleteLists(gl_list, sizeof(gl_list));
 
        int i = 0;
        int list_len = vec2f_vec.size();              
                                
        glNewList(gl_list, GL_COMPILE);
        {
                enable_POINTSPRITE();
                glBindTexture(GL_TEXTURE_2D, textureOb->texture);
                while (i < list_len)
                {                    
                        drawParticle(point_size, vec2f_vec[i]);
                        i += step;
                }
                disable_POINTSPRITE();
        }
        glEndList();
}

void PathVisual::FillData(const std::vector<vec2f>& vec2f_vec, int step, int point_size)
{   
	glDeleteLists(gl_list, sizeof(gl_list));

        int i = 0;
        int list_len = vec2f_vec.size();
              
        GLuint texture_green = GuiTextureObCollector::Instance().dot_green->texture;
        GLuint texture_blue = GuiTextureObCollector::Instance().dot_blue->texture;
        GLuint texture;
                                
        glNewList(gl_list, GL_COMPILE);
        {
                enable_POINTSPRITE();
                while (i < list_len)
                {
                        if (i < TURN_TIME)
                        {
                                texture = texture_green;
                        }
                        else
                        {
                                texture = texture_blue;                                
                        }
                        
                        glBindTexture(GL_TEXTURE_2D, texture);
                        drawParticle(point_size, vec2f_vec[i]);

                        i += step;
                }
                disable_POINTSPRITE();
        }
        glEndList();
}

void PathVisual::FillData(TextureOb* textureOb, int radius, int point_size)	
{
	glDeleteLists(gl_list, sizeof(gl_list));

	float da = 4.0f/RADIAN_TO_DEGREE_RATE;// - radius/1000.0f;
	glNewList(gl_list, GL_COMPILE);
        {
                enable_POINTSPRITE();
                glBindTexture(GL_TEXTURE_2D, textureOb->texture);
                for (float a=0.0f; a<=2*PI; a+=da)
      		{
      			drawParticle(point_size, vec2f(radius * cos(a), radius * sin(a)));
		}
                disable_POINTSPRITE();
        }
        glEndList();
}

void PathVisual::FillData(TextureOb* textureOb, const vec2f& start_pos, const vec2f& target_pos, int step, int point_size)
{
	glDeleteLists(gl_list, sizeof(gl_list));
       	
	vec2f new_pos(start_pos);
       	vec2f ll(target_pos - start_pos);	    		
	vec2f vstep = ll.GetNorm() * step;

	unsigned int it = ll.GetLen() / step;
	glNewList(gl_list, GL_COMPILE);
        {
                enable_POINTSPRITE();
                glBindTexture(GL_TEXTURE_2D, textureOb->texture);	
		for (unsigned int i=0; i<it; i++)
		{
       			new_pos += vstep;
       			drawParticle(point_size, new_pos);
    		}
    		disable_POINTSPRITE();
	}
	glEndList();
}
		
void PathVisual::Draw(const vec2f& offset) const
{
        glPushMatrix();
		glTranslatef(offset.x, offset.y, 0.0f);
    		glCallList(gl_list);
	glPopMatrix();
}

void PathVisual::Draw() const
{
	glCallList(gl_list);
}


