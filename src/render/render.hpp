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


void drawFlatQuadPerVertexIn2D(vec2f bottomLeft, 
			       vec2f bottomRight, 
			       vec2f topRight, 
			       vec2f topLeft, 
			       float z_pos, 
			       float texCoord_bottomLeft_x = 0, 
			       float texCoord_bottomLeft_y = 0, 
			       float texCoord_bottomRight_x = 1, 
			       float texCoord_bottomRight_y = 0, 
			       float texCoord_topRight_x = 1, 
			       float texCoord_topRight_y = 1, 
			       float texCoord_topLeft_x = 0,
			       float texCoord_topLeft_y = 1);
			       

void drawDynamic(float center_x, 
		 float center_y, 
		 float angleInDegree, 
		 int minus_half_w, 
		 int minus_half_h, 
		 int plus_half_w, 
		 int plus_half_h, 
		 float pos_z, 
		 float texCoord_bottomLeft_x = 0, 
		 float texCoord_bottomLeft_y = 0, 
		 float texCoord_bottomRight_x = 1, 
		 float texCoord_bottomRight_y = 0, 
		 float texCoord_topRight_x = 1, 
		 float texCoord_topRight_y = 1, 
		 float texCoord_topLeft_x = 0, 
		 float texCoord_topLeft_y = 1);




void drawRect(Rect rect, 
	      float z_pos, 
	      float texCoord_bottomLeft_x = 0, 
	      float texCoord_bottomLeft_y = 0, 
	      float texCoord_bottomRight_x = 1, 
	      float texCoord_bottomRight_y = 0, 
	      float texCoord_topRight_x = 1, 
	      float texCoord_topRight_y = 1, 
	      float texCoord_topLeft_x = 0, 
	      float texCoord_topLeft_y = 1); // the drawrect function was inverted by Y axis


void drawTexturedRect(GLuint tex, Rect rect, float z_pos);   //# z_pos = -1


void drawTexturedPoint(GLuint texture, vec2f _center, float size, float pos_z);


void drawLine(GLuint texture, 
              float start_pos_x, 
              float start_pos_y, 
              float z_pos, 
              float len, 
              float angle_inD, 
              int half_h, 
              float texCoord_bottomLeft_x = 0, 
              float texCoord_bottomLeft_y = 0, 
              float texCoord_bottomRight_x = 1, 
              float texCoord_bottomRight_y = 0, 
              float texCoord_topRight_x = 1, 
              float texCoord_topRight_y = 1, 
              float texCoord_topLeft_x = 0, 
              float texCoord_topLeft_y = 1);



void drawSimpleColoredText(std::string str, 
			   vec2f pos, 
			   Color4i color,
			   float scroll_x = g_SCROLL_COORD_X, 
			   float scroll_y = g_SCROLL_COORD_Y);



void drawInfoIn2Column(
                std::vector<std::string>* pInfo_title_list, 
                std::vector<std::string>* pInfo_value_list, 
                float center_x, 
                float center_y,
                float scroll_x = g_SCROLL_COORD_X,
                float scroll_y = g_SCROLL_COORD_Y);


void drawSimpleText(std:: string str, int font_size, float pos_x, float pos_y);


void drawFullScreenQuad(int w, int h, float pos_z);


void drawFullScreenTexturedQuad(GLuint texture, int w, int h, float pos_z);


void drawFullScreenTexturedQuadBlurred(GLuint texture, int w, int h, float pos_z, GLuint program_blur);


void renderMesh(GLuint glList, vec3f center, vec3f angle, float scale);


#endif 


