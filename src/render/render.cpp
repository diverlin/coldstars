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

#include "render.hpp"

void clearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void resetRenderTransformation() { glLoadIdentity(); }


void camera(float x, float y) { glTranslatef(-x, -y, 0.0); }

void setColor(Color color) { glColor4f(color.r, color.g, color.b, color.a); }

void enable_BLEND()  { glEnable(GL_BLEND);  }
void disable_BLEND() { glDisable(GL_BLEND); }

void enable_DEPTH()  { glEnable(GL_DEPTH_TEST); }
void disable_DEPTH() { glDisable(GL_DEPTH_TEST); }

void enable_POINTSPRITE()  { glEnable(GL_POINT_SPRITE);  }
void disable_POINTSPRITE() { glDisable(GL_POINT_SPRITE); }

void drawFlatQuadPerVertexIn2D(vec2f bottomLeft, 
			       vec2f bottomRight, 
			       vec2f topRight, 
			       vec2f topLeft, 
			       float z_pos, 
			       float texCoord_bottomLeft_x, 
			       float texCoord_bottomLeft_y, 
			       float texCoord_bottomRight_x, 
			       float texCoord_bottomRight_y, 
			       float texCoord_topRight_x, 
			       float texCoord_topRight_y, 
			       float texCoord_topLeft_x, 
			       float texCoord_topLeft_y)
{       
    	glBegin(GL_QUADS);
      		glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(bottomLeft.x,  bottomLeft.y , z_pos);
      		glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(bottomRight.x, bottomRight.y, z_pos);
      		glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(topRight.x,    topRight.y   , z_pos);
      		glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(topLeft.x,     topLeft.y    , z_pos);
    	glEnd();
}


void drawDynamic(float center_x, 
		 float center_y, 
		 float angleInDegree, 
		 int minus_half_w, 
		 int minus_half_h, 
		 int plus_half_w, 
		 int plus_half_h, 
		 float pos_z, 
		 float texCoord_bottomLeft_x, 
		 float texCoord_bottomLeft_y, 
		 float texCoord_bottomRight_x, 
		 float texCoord_bottomRight_y, 
		 float texCoord_topRight_x, 
		 float texCoord_topRight_y, 
		 float texCoord_topLeft_x, 
		 float texCoord_topLeft_y)
{
    	glPushMatrix();
    		glTranslatef(center_x, center_y, 0.0);
    		glRotatef(angleInDegree, 0.0, 0.0, 1.0);

    		glBegin(GL_QUADS);
    			glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(minus_half_w, minus_half_h, pos_z);
    			glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(plus_half_w,  minus_half_h, pos_z);
   			glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(plus_half_w,  plus_half_h,  pos_z);
    			glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(minus_half_w, plus_half_h,  pos_z);
    		glEnd();
    	glPopMatrix();
}



void drawRect(Rect rect, 
              float z_pos, 
              float texCoord_bottomLeft_x, 
              float texCoord_bottomLeft_y, 
              float texCoord_bottomRight_x, 
              float texCoord_bottomRight_y, 
              float texCoord_topRight_x, 
              float texCoord_topRight_y, 
              float texCoord_topLeft_x, 
              float texCoord_topLeft_y) // the drawrect function was inverted by Y axis
{
    	glBegin(GL_QUADS);
      		glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(rect.getBottomLeft().x,           	       rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(),  rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(),  rect.getBottomLeft().y,          	  z_pos);
     		glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(rect.getBottomLeft().x,           	       rect.getBottomLeft().y,          	  z_pos);
    	glEnd();
}

void drawTexturedRect(GLuint tex, Rect rect, float z_pos)   //# z_pos = -1
{
    	glBindTexture(GL_TEXTURE_2D, tex);
    	drawRect(rect, z_pos);
}



void drawLine(GLuint texture, 
              float start_pos_x, 
              float start_pos_y, 
              float z_pos, 
              float len, 
              float angle_inD, 
              int half_h, 
              float texCoord_bottomLeft_x, 
              float texCoord_bottomLeft_y, 
              float texCoord_bottomRight_x, 
              float texCoord_bottomRight_y, 
              float texCoord_topRight_x, 
              float texCoord_topRight_y, 
              float texCoord_topLeft_x, 
              float texCoord_topLeft_y)
{
    	glBindTexture(GL_TEXTURE_2D, texture);
    	glPushMatrix();

    		glTranslatef(start_pos_x, start_pos_y, 0.0);
    		glRotatef(angle_inD, 0.0, 0.0, 1.0);

    		glBegin(GL_QUADS);
      			glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(0,   -half_h, z_pos);
      			glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(len, -half_h, z_pos);
      			glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(len,  half_h, z_pos);
      			glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(0,    half_h, z_pos);
    		glEnd();

    	glPopMatrix();
}






void drawInfoIn2Column(
                std::vector<std::string*>* pTo_info_title_pList, 
                std::vector<std::string*>* pTo_info_value_pList, 
                float center_x, float center_y,
                float scroll_x,
                float scroll_y)
{
     	int font_size = 13;
     	float char_h = 25;
     	float char_w = 10;

     	float max_info_total_str_size = 0;
     	float max_info_title_str_size = 0;

     	for (unsigned int i = 1; i < pTo_info_title_pList->size(); i++)
     	{
         	int total_length = (*pTo_info_title_pList)[i]->length() + (*pTo_info_value_pList)[i-1]->length();
         	int title_length = (*pTo_info_title_pList)[i]->length(); 

         	if (total_length > max_info_total_str_size)
            		max_info_total_str_size = total_length;

         	if (title_length > max_info_title_str_size)
           		max_info_title_str_size = title_length;
     	}    

     	float info_total_string_w = char_w * max_info_total_str_size;
     	float info_total_string_h = char_h * pTo_info_title_pList->size();

     	TextureOb* texOb_textBoard = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.textBackground_texOb_pList);
     	Rect rect = Rect(center_x - char_w, center_y - info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);

     	glEnable(GL_BLEND);
     		drawTexturedRect(texOb_textBoard->texture, rect, -2);
     	glDisable(GL_BLEND);

     	sf::String s((*(*pTo_info_title_pList)[0]), g_FONT, (font_size+1));
     	s.SetColor(sf::Color(255, 255, 255));
     	s.SetPosition(center_x - scroll_x + info_total_string_w/3, (g_VIEW_HEIGHT - center_y) + scroll_y); 
     	g_APP.Draw(s);

     	for (unsigned int i = 1; i < pTo_info_title_pList->size(); i++)
     	{
         	sf::String s((*(*pTo_info_title_pList)[i]), g_FONT, font_size);
         	s.SetColor(sf::Color(255, 255, 255));
         	s.SetPosition(center_x - scroll_x, (g_VIEW_HEIGHT - center_y) + char_h*i + scroll_y); 
         	g_APP.Draw(s);
     	}       


     	for (unsigned int i = 0; i < pTo_info_value_pList->size(); i++)
     	{
         	sf::String s((*(*pTo_info_value_pList)[i]), g_FONT, font_size);
         	s.SetColor(sf::Color(250, 250, 0));
         	s.SetPosition(center_x - scroll_x + max_info_title_str_size * (char_w - 1.2), (g_VIEW_HEIGHT - center_y) + char_h*i + char_h + scroll_y); 
         	g_APP.Draw(s);
     	}      
}




void drawInfoIn2Column(
                std::vector<std::string>* pInfo_title_list, 
                std::vector<std::string>* pInfo_value_list, 
                float center_x, 
                float center_y,
                float scroll_x,
                float scroll_y)
{
     	int font_size = 13;
     	float char_h = 25;
     	float char_w = 10;

     	float max_info_total_str_size = 0;
     	float max_info_title_str_size = 0;

     	for (unsigned int i = 1; i < pInfo_title_list->size(); i++)
     	{
         	int total_length = (*pInfo_title_list)[i].length() + (*pInfo_value_list)[i-1].length();
         	int title_length = (*pInfo_title_list)[i].length(); 

         	if (total_length > max_info_total_str_size)
            		max_info_total_str_size = total_length;

         	if (title_length > max_info_title_str_size)
           		max_info_title_str_size = title_length;
     	}    

     	float info_total_string_w = char_w * max_info_total_str_size;
     	float info_total_string_h = char_h * pInfo_title_list->size();

     	TextureOb* pTo_textbg_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.textBackground_texOb_pList);
     	Rect rect = Rect(center_x - char_w, center_y - info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);

     	glEnable(GL_BLEND);
     	drawTexturedRect(pTo_textbg_texOb->texture, rect, -2);
     	glDisable(GL_BLEND);

     	sf::String s((*pInfo_title_list)[0], g_FONT, (font_size+1));
     	s.SetColor(sf::Color(255, 255, 255));
     	s.SetPosition(center_x - scroll_x + info_total_string_w/3, (g_VIEW_HEIGHT - center_y) + scroll_y); 
     	g_APP.Draw(s);

     	for (unsigned int i = 1; i < pInfo_title_list->size(); i++)
     	{
         	sf::String s((*pInfo_title_list)[i], g_FONT, font_size);
         	s.SetColor(sf::Color(255, 255, 255));
         	s.SetPosition(center_x - scroll_x, (g_VIEW_HEIGHT - center_y) + char_h*i + scroll_y); 
         	g_APP.Draw(s);
     	}       


     	for (unsigned int i = 0; i < pInfo_value_list->size(); i++)
     	{
         	sf::String s((*pInfo_value_list)[i], g_FONT, font_size);
         	s.SetColor(sf::Color(250, 250, 0));
         	s.SetPosition(center_x - scroll_x + max_info_title_str_size * (char_w - 1.2), (g_VIEW_HEIGHT - center_y) + char_h*i + char_h + scroll_y); 
         	g_APP.Draw(s);
     	}  
}










void drawSimpleText(std:: string str, int font_size, float pos_x, float pos_y)
{
     	sf::String s(str, g_FONT, font_size);
     	s.SetColor(sf::Color(255, 255, 255));
     	s.SetPosition(pos_x, (g_VIEW_HEIGHT - pos_y)); 
     	g_APP.Draw(s);
}



void drawFullScreenQuad(int w, int h, float pos_z)
{
    	glBegin(GL_QUADS);
    		glTexCoord3f(0, 0, 0); glVertex3f(0, 0, pos_z);
    		glTexCoord3f(1, 0, 0); glVertex3f(w, 0, pos_z);
    		glTexCoord3f(1, 1, 0); glVertex3f(w, h, pos_z);
    		glTexCoord3f(0, 1, 0); glVertex3f(0, h, pos_z);    
    	glEnd();
}


void drawFullScreenTexturedQuad(GLuint texture, int w, int h, float pos_z)
{
    	glBindTexture(GL_TEXTURE_2D, texture);
    	drawFullScreenQuad(w, h, pos_z);
}


void drawFullScreenTexturedQuadBlurred(GLuint texture, int w, int h, float pos_z, GLuint program_blur)
{
    	glUseProgram(program_blur);

    	glActiveTexture(GL_TEXTURE0);                              
    	glBindTexture(GL_TEXTURE_2D, texture);

    	glUniform1i(glGetUniformLocation(program_blur, "sceneTex"), 0);

    	glUniform1f(glGetUniformLocation(program_blur, "rt_w"), 3*w); 
    	glUniform1f(glGetUniformLocation(program_blur, "rt_h"), 3*h);
    	glUniform1f(glGetUniformLocation(program_blur, "vx_offset"), 1.0);

    	drawFullScreenQuad(w, h, pos_z);
    
    	glUseProgram(0);
}
    
    
void renderMesh(GLuint glList, vec3f center, vec3f angle, float scale)
{
     	glPushMatrix();
       		glTranslatef(center.x, center.y, center.z);
       		glScalef(scale, scale, scale); 
       		glRotatef(-angle.x, 1.0, 0.0, 0.0); 
       		glRotatef(-angle.y, 0.0, 1.0, 0.0); 
       		glRotatef(-angle.z, 0.0, 0.0, 1.0); 

       		glCallList(glList);
     	glPopMatrix();

}




void initGL(int width, int height)
{   
  	// Set color and depth clear value
  	//glClearDepth(1.f);
  	glClearColor(0.f, 0.f, 0.f, 0.f);

  	// Enable Z-buffer read and write
  	//glEnable(GL_DEPTH_TEST);
  	//glDepthMask(GL_TRUE);

  	// Setup a perspective projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	//gluPerspective(90.f, 1.f, 1.f, 500.f);
  	glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  	glMatrixMode(GL_MODELVIEW);
            
  	glEnable(GL_TEXTURE_2D);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  
      	//glShadeModel(GL_SMOOTH);
      	//glDisable(GL_LIGHTING);  
}   




