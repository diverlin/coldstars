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

void clearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void resetRenderTransformation() { glLoadIdentity(); }


void camera(float x, float y) { glTranslatef(-x, -y, 0.0); }

void setColor(Color4f color) { glColor4f(color.r, color.g, color.b, color.a); }

void enable_BLEND()  { glEnable(GL_BLEND);  }
void disable_BLEND() { glDisable(GL_BLEND); }

void enable_DEPTH()  { glEnable(GL_DEPTH_TEST); }
void disable_DEPTH() { glDisable(GL_DEPTH_TEST); }

void enable_POINTSPRITE()  { glEnable(GL_POINT_SPRITE);  }
void disable_POINTSPRITE() { glDisable(GL_POINT_SPRITE); }

void drawFlatQuadPerVertexIn2D(TextureOb* texOb, 
			       vec2f bottomLeft, 
			       vec2f bottomRight, 
			       vec2f topRight, 
			       vec2f topLeft, 
			       float z_pos)
{       
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
    	glBegin(GL_QUADS);
      		glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(bottomLeft.x,  bottomLeft.y , z_pos);
      		glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(bottomRight.x, bottomRight.y, z_pos);
      		glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(topRight.x,    topRight.y   , z_pos);
      		glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(topLeft.x,     topLeft.y    , z_pos);
    	glEnd();
}


void drawDynamic(TextureOb* texOb,
		 vec2f center, 
		 float angleInDegree, 
		 float pos_z)
{
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
    	glPushMatrix();
    		glTranslatef(center.x, center.y, 0.0);
    		glRotatef(angleInDegree, 0.0, 0.0, 1.0);

    		glBegin(GL_QUADS);
    			glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-texOb->getFrameWidth()/2, -texOb->getFrameHeight()/2, pos_z);
    			glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( texOb->getFrameWidth()/2, -texOb->getFrameHeight()/2, pos_z);
   			glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( texOb->getFrameWidth()/2,  texOb->getFrameHeight()/2,  pos_z);
    			glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-texOb->getFrameWidth()/2,  texOb->getFrameHeight()/2,  pos_z);
    		glEnd();
    	glPopMatrix();
}



void drawRect(Rect rect, float z_pos) // the drawrect function was inverted by Y axis
{
    	glBegin(GL_QUADS);
      		glTexCoord3f(0, 0, 0); glVertex3f(rect.getBottomLeft().x,           	        rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(1, 0, 0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(),     rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(1, 1, 0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(),     rect.getBottomLeft().y,           	 z_pos);
     		glTexCoord3f(0, 1, 0); glVertex3f(rect.getBottomLeft().x,           	        rect.getBottomLeft().y,         	         z_pos);
    	glEnd();
}

void drawTexturedRect(TextureOb* texOb, Rect rect, float z_pos)
{
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
    	glBegin(GL_QUADS);
      		glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(rect.getBottomLeft().x,           	  rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(), rect.getBottomLeft().y + rect.getHeight(), z_pos);
      		glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(rect.getBottomLeft().x + rect.getWidth(), rect.getBottomLeft().y,          	     z_pos);
     		glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(rect.getBottomLeft().x,           	  rect.getBottomLeft().y,          	     z_pos);
    	glEnd();
}



void drawTexturedPoint(GLuint texture, vec2f center, float size, float pos_z)
{
    	glBindTexture(GL_TEXTURE_2D, texture);
    	
     	glPointSize(size);
        	
        glBegin(GL_POINTS);
     		glVertex3f(center.x, center.y, pos_z);
     	glEnd();
}



void drawLine(TextureOb* texOb, 
              vec2f start_pos, 
              float z_pos, 
              float len, 
              float angle_inD, 
              int half_h)
{
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	int frame = texOb->updateAnimationFrame();
    		
    	glPushMatrix();
    		glTranslatef(start_pos.x, start_pos.y, 0.0);
    		glRotatef(angle_inD, 0.0, 0.0, 1.0);

    		glBegin(GL_QUADS);
      			glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(0,   -half_h, z_pos);
      			glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(len, -half_h, z_pos);
      			glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(len,  half_h, z_pos);
      			glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(0,    half_h, z_pos);
    		glEnd();
    	glPopMatrix();
}





void drawSimpleColoredText(std::string str, vec2f pos, Color4i color, vec2f scroll_coord)
{
     	 int font_size = 12;
         sf::String s(str, Gui::GetFont(), font_size);
              	
          /* SHADOW */
     	 //s.SetColor(sf::Color(0, 0, 0));
         //s.SetPosition(pos.x - scroll_x - 2, (g_VIEW_HEIGHT - pos.y) + scroll_y + 2); 
         //GetWindows().Draw(s);
         
         s.SetColor(sf::Color(color.r, color.g, color.b));
         s.SetPosition(pos.x - scroll_coord.x, (Gui::GetWindow().GetHeight() - pos.y) + scroll_coord.y); 
         Gui::GetWindow().Draw(s);        
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

     	TextureOb* texOb_textBg = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::TEXT_BACKGROUND_ID);
     	Rect rect = Rect(center_x - char_w, center_y - info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);

     	glEnable(GL_BLEND);
     	drawTexturedRect(texOb_textBg, rect, -2);
     	glDisable(GL_BLEND);

     	sf::String s((*pInfo_title_list)[0], Gui::GetFont(), (font_size+1));
     	s.SetColor(sf::Color(255, 255, 255));
     	s.SetPosition(center_x - scroll_x + info_total_string_w/3, (Gui::GetWindow().GetHeight() - center_y) + scroll_y); 
      Gui::GetWindow().Draw(s);

     	for (unsigned int i = 1; i < pInfo_title_list->size(); i++)
     	{
         	sf::String s((*pInfo_title_list)[i], Gui::GetFont(), font_size);
         	s.SetColor(sf::Color(255, 255, 255));
         	s.SetPosition(center_x - scroll_x, (Gui::GetWindow().GetHeight() - center_y) + char_h*i + scroll_y); 
          Gui::GetWindow().Draw(s);
     	}       


     	for (unsigned int i = 0; i < pInfo_value_list->size(); i++)
     	{
         	sf::String s((*pInfo_value_list)[i], Gui::GetFont(), font_size);
         	s.SetColor(sf::Color(250, 250, 0));
         	s.SetPosition(center_x - scroll_x + max_info_title_str_size * (char_w - 1.2), (Gui::GetWindow().GetHeight() - center_y) + char_h*i + char_h + scroll_y); 
          Gui::GetWindow().Draw(s);
     	}  
}










void drawSimpleText(std:: string str, int font_size, float pos_x, float pos_y)
{
     	sf::String s(str, Gui::GetFont(), font_size);
     	s.SetColor(sf::Color(255, 255, 255));
     	s.SetPosition(pos_x, (Gui::GetWindow().GetHeight() - pos_y)); 
      Gui::GetWindow().Draw(s);
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

