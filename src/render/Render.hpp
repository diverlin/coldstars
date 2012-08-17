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


#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include "../resources/textureOb.hpp"
#include "../common/rect.hpp"

void initGl(int, int);
void resizeGl(int, int);

void clearScreen();
void resetRenderTransformation();

void camera(float x, float y);
void setColor(Color4f);	

void enable_BLEND();
void disable_BLEND();

void enable_DEPTH();
void disable_DEPTH();

void enable_POINTSPRITE();
void disable_POINTSPRITE();


void drawFlatQuadPerVertexIn2D(TextureOb* texOb,
			       vec2f bottomLeft, 
			       vec2f bottomRight, 
			       vec2f topRight, 
			       vec2f topLeft, 
			       float z_pos);
			       

void drawDynamic(TextureOb* texOb, 
		 vec2f center, 
		 float angleInDegree, 
		 float pos_z);





void drawRect(const Rect& rect, float z_pos); // the drawrect function was inverted by Y axis
void drawTexturedRect(TextureOb* texOb, const Rect& rect, float z_pos);   


void drawTexturedPoint(GLuint texture, vec2f _center, float size, float pos_z);



void drawLine(TextureOb* texOb, 
              vec2f start_pos, 
              float z_pos, 
              float len, 
              float angle_inD, 
              int half_h);


             
void drawSimpleColoredText(std::string str, 
			   vec2f pos, 
			   Color4i color,
			   float scroll_x = 0.0, 
			   float scroll_y = 0.0);



void drawInfoIn2Column(
                std::vector<std::string>* pInfo_title_list, 
                std::vector<std::string>* pInfo_value_list, 
                float center_x, 
                float center_y);


void drawSimpleText(std:: string str, int font_size, float pos_x, float pos_y);


void drawFullScreenQuad(int w, int h, float pos_z);


void drawFullScreenTexturedQuad(GLuint texture, int w, int h, float pos_z);


void drawFullScreenTexturedQuadBlurred(GLuint texture, int w, int h, float pos_z, GLuint program_blur);


void renderMesh(GLuint glList, const vec3f& center, const vec3f& angle, float scale);

void drawParticle(float, const Color4f&, const vec2f&);
void drawParticle(float, const vec2f&);

#endif 


