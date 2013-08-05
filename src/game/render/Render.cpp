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


#include "Render.hpp"
#include "Screen.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <resources/GuiTextureObCollector.hpp>
#include <resources/ShaderCollector.hpp>

#include "Mesh.hpp"
#include "../common/constants.hpp"


void initGl(int width, int height)
{   
  	// Set color and depth clear value
  	//glClearDepth(1.f);
  	glClearColor(0.f, 0.f, 0.f, 0.f);

  	// Enable Z-buffer read and write
  	//glEnable(GL_DEPTH_TEST);
  	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
    
  	glEnable(GL_TEXTURE_2D);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  
	glShadeModel(GL_SMOOTH);
	//glDisable(GL_LIGHTING); 
	
	resizeGl(width, height); 
	
	glCullFace(GL_BACK); 
}   

void resizeGl(int width, int height)
{
  	// Setup a perspective projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	//gluPerspective(60.f, 4./3., 1.f, 1000.f);
   	glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  	
  	glMatrixMode(GL_MODELVIEW);
}

void clearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void resetRenderTransformation() { glLoadIdentity(); }


void camera(float x, float y, float z) { glTranslatef(-x, -y, -z); }

void setColor4f(const Color4<float>& color) { glColor4f(color.r, color.g, color.b, color.a); }
void setColor4f(float r, float g, float b, float a) { glColor4f(r, g, b, a); }

void enable_BLEND()  { glEnable(GL_BLEND);  }
void disable_BLEND() { glDisable(GL_BLEND); }

void enable_CULLFACE()  { glEnable(GL_CULL_FACE); }
void disable_CULLFACE() { glDisable(GL_CULL_FACE); }

void enable_DEPTH()  { glEnable(GL_DEPTH_TEST); }
void disable_DEPTH() { glDisable(GL_DEPTH_TEST); }

void enable_POINTSPRITE()  { glEnable(GL_POINT_SPRITE);  }
void disable_POINTSPRITE() { glDisable(GL_POINT_SPRITE); }


void drawQuad(TextureOb* texOb,
		 const Vec3<float>& center, 
		 const Vec3<float>& size,
		 float angle)
{
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
	glPushMatrix();
	{
		glTranslatef(center.x, center.y, center.z);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glScalef(size.x, size.y, size.z);
									
		glBegin(GL_QUADS);
        {   
			glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
			glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
			glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
			glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
		}
        glEnd();
	}
	glPopMatrix();
}

void drawQuad(TextureOb* texOb,
		 const Vec2<float>& center, 
		 const Vec2<float>& size,
		 float angle)
{
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
	glPushMatrix();
	{
		glTranslatef(center.x, center.y, GUI::POS_Z);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glScalef(size.x, size.y, 1.0);
									
		glBegin(GL_QUADS);
        {   
			glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
			glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
			glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
			glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
		}
        glEnd();
	}
	glPopMatrix();
}


void drawQuad(TextureOb* texOb,
		 const Vec2<float>& center, 
		 const Vec2<float>& size,
		 float angle,
		 TextureOb* texOb_mask,
		 float threshold)
{
	glUseProgram(ShaderCollector::Instance().mask);
	{	
		int frame = 0;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texOb_mask->texture);
		glUniform1i(glGetUniformLocation(ShaderCollector::Instance().mask, "u_TextureMask"), 0);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texOb->texture);		
		glUniform1i(glGetUniformLocation(ShaderCollector::Instance().mask, "u_TextureTarget"), 1);

		glUniform1f(glGetUniformLocation(ShaderCollector::Instance().mask, "u_Threshold"), threshold);
						
		glPushMatrix();
		{
			glTranslatef(center.x, center.y, GUI::POS_Z);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glScalef(size.x, size.y, 1.0);
										
			glBegin(GL_QUADS);
	        {   
				glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
				glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
				glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
				glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
			}
	        glEnd();
		}
		glPopMatrix();
	}
	glUseProgram(0);
	glActiveTexture(GL_TEXTURE0);
}

void drawQuad(TextureOb* texOb, const Box2D& box)
{
	drawQuad(texOb, box.GetCenter(), box.GetSize()*box.GetScale(), box.GetAngle());
}

void drawQuadMasked(TextureOb* texOb, const Box2D& box, TextureOb* texOb_mask, float threshold)
{
	drawQuad(texOb, box.GetCenter(), box.GetSize()*box.GetScale(), box.GetAngle(), texOb_mask, threshold);
}

void drawTexturedRect(TextureOb* texOb, const Rect& rect, float z_pos)
{
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
	
	glBegin(GL_QUADS);
		glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(rect.GetBottomLeft().x,           	 		rect.GetBottomLeft().y + rect.GetHeight(), 	z_pos);
		glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(rect.GetBottomLeft().x + rect.GetWidth(), 	rect.GetBottomLeft().y + rect.GetHeight(), 	z_pos);
		glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(rect.GetBottomLeft().x + rect.GetWidth(), 	rect.GetBottomLeft().y,          	     	z_pos);
		glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(rect.GetBottomLeft().x,           	  		rect.GetBottomLeft().y,          	    	z_pos);
	glEnd();
}


void drawLine(TextureOb* texOb, 
              const Vec3<float>& start_pos, 
              float len, 
              float angle_inD, 
              int half_h)
{
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	int frame = texOb->updateAnimationFrame();
		
	glPushMatrix();
		glTranslatef(start_pos.x, start_pos.y, start_pos.z);
		glRotatef(angle_inD, 0.0, 0.0, 1.0);
	
		glBegin(GL_QUADS);
			glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(0,   -half_h, 0.0);
			glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(len, -half_h, 0.0);
			glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(len,  half_h, 0.0);
			glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(0,    half_h, 0.0);
		glEnd();
	glPopMatrix();
}

void drawColoredTextWithBackground(const std::string& str, int font_size, const Vec2<float>& pos, const Color4<int>& color)
{
	float char_w = font_size;
	float char_h = font_size;
			
	float string_w = char_w * str.size();

	TextureOb* texOb_textBg = GuiTextureObCollector::Instance().text_background;
	Rect rect(pos.x - char_w, pos.y - char_h, string_w, 2*char_h);
    	
    enable_BLEND();
    {
        drawTexturedRect(texOb_textBg, rect, GUI::POS_Z);
    }
    disable_BLEND();
	
    Screen::Instance().DrawText(str, font_size, pos, color);
}

void drawColoredText(const std::string& str, int font_size, const Vec2<float>& pos, const Color4<int>& color)
{
    glPushMatrix();
    {
        glLoadIdentity();
	    Screen::Instance().DrawText(str, font_size, pos, color);
    }
    glPopMatrix();
}

void drawInfoIn2Column(
                	const std::vector<std::string>& info_title_list, 
                	const std::vector<std::string>& info_value_list, 
                	const Vec2<float>& pos)
{    	
	int font_size = 13;
	float char_w = font_size;
	float char_h = 2*font_size;
	
	float max_info_total_str_size = 0;
	float max_info_title_str_size = 0;
	
	for (unsigned int i=1; i<info_title_list.size(); i++)
	{
		int total_length = info_title_list[i].length() + info_value_list[i-1].length();
		int title_length = info_title_list[i].length(); 
	
		if (total_length > max_info_total_str_size)
			max_info_total_str_size = total_length;
	
		if (title_length > max_info_title_str_size)
			max_info_title_str_size = title_length;
	}    

	float info_total_string_w = char_w * max_info_total_str_size;
	float info_total_string_h = char_h * info_title_list.size();
		
	Rect rect(-char_w, -info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);
	
	Color4<int> color_title(250, 250, 250, 255);
	Color4<int> color_info(250, 250, 0, 255);

	TextureOb* texOb_textBg = GuiTextureObCollector::Instance().text_background;
									
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, 0.0);
	
		drawTexturedRect(texOb_textBg, rect, -2);
	
		Vec2<float> curpos(info_total_string_w/3, 0.0); 
		Screen::Instance().DrawText(info_title_list[0], font_size+1, curpos);

		for (unsigned int i=1; i<info_title_list.size(); i++)
		{
			Vec2<float> curpos(0.0, -char_h*i); 
			Screen::Instance().DrawText(info_title_list[i], font_size, curpos, color_title);
		
		}		
		for (unsigned int i=0; i<info_value_list.size(); i++)
		{
			Vec2<float> curpos(max_info_title_str_size * (char_w - 1.2), -(char_h*(i + 1))); 
			Screen::Instance().DrawText(info_value_list[i], font_size, curpos, color_info);
		}
	}  
	glPopMatrix();
}

void drawFullScreenQuad(int w, int h, float pos_z)
{
	glBegin(GL_QUADS);
	{
		glTexCoord3f(0, 0, 0); glVertex3f(0, 0, pos_z);
		glTexCoord3f(1, 0, 0); glVertex3f(w, 0, pos_z);
		glTexCoord3f(1, 1, 0); glVertex3f(w, h, pos_z);
		glTexCoord3f(0, 1, 0); glVertex3f(0, h, pos_z); 
	}   
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
    
    
void renderMesh(const Mesh* const mesh, const Vec3<float>& center, const Vec3<float>& size, const Vec3<float>& angle, bool ZYX)
{
	glPushMatrix();
	{
		glTranslatef(center.x, center.y, center.z);		
		glScalef(size.x, size.y, size.z); 
		if (ZYX) 	{	rotateZYX(angle); } // animation rotation along axis X
		else		{	rotateXYZ(angle); } // animation rotation along axis z
						
		mesh->Draw();
	}
	glPopMatrix();

}

void rotateZYX(const Vec3<float>& angle)
{
	glRotatef(angle.z, 0.0, 0.0, 1.0); 
	glRotatef(angle.y, 0.0, 1.0, 0.0); 
	glRotatef(angle.x, 1.0, 0.0, 0.0); 
}

void rotateXYZ(const Vec3<float>& angle)
{
	glRotatef(angle.x, 1.0, 0.0, 0.0); 
	glRotatef(angle.y, 0.0, 1.0, 0.0); 
	glRotatef(angle.z, 0.0, 0.0, 1.0); 
}

void drawParticleTextured(GLuint texture, const Vec2<float>& center, float size, float pos_z)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glPointSize(size);
		
	glBegin(GL_POINTS);
		glVertex3f(center.x, center.y, pos_z);
	glEnd();
}

void drawParticle(const Vec2<float>& center, float size, float r, float g, float b, float a)
{		
	glPointSize(size);
        	
	glBegin(GL_POINTS);  
	{         		
		glColor4f(r, g, b, a);
		glVertex3f(center.x, center.y, -2);
	}
	glEnd();
}

void drawParticle(const Vec2<float>& center, float size, const Color4<float>& color)
{	
	glPointSize(size);
        	
	glBegin(GL_POINTS);   
	{        	
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex3f(center.x, center.y, -2);
	}
	glEnd();
}

void drawParticle(const Vec2<float>& center, float size)
{
	glPointSize(size);
        	
	glBegin(GL_POINTS); 
	{          		
		glVertex3f(center.x, center.y, -2);
	}
	glEnd();
}
