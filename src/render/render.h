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

void drawFlatQuadPerVertexIn2D(float bottomLeft_x, float bottomLeft_y, float bottomRight_x, float bottomRight_y, float topRight_x, float topRight_y, float topLeft_x, float topLeft_y, float z_pos, float texCoord_bottomLeft_x = 0, float texCoord_bottomLeft_y = 0, float texCoord_bottomRight_x = 1, float texCoord_bottomRight_y = 0, float texCoord_topRight_x = 1, float texCoord_topRight_y = 1, float texCoord_topLeft_x = 0, float texCoord_topLeft_y = 1)
{       
    glBegin(GL_QUADS);
      glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(bottomLeft_x,  bottomLeft_y , z_pos);
      glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(bottomRight_x, bottomRight_y, z_pos);
      glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(topRight_x,    topRight_y   , z_pos);
      glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(topLeft_x,     topLeft_y    , z_pos);
    glEnd();
}

void drawDynamic(float center_x, float center_y, float angleInDegree, int minus_half_w, int minus_half_h, int plus_half_w, int plus_half_h, float pos_z, float texCoord_bottomLeft_x = 0, float texCoord_bottomLeft_y = 0, float texCoord_bottomRight_x = 1, float texCoord_bottomRight_y = 0, float texCoord_topRight_x = 1, float texCoord_topRight_y = 1, float texCoord_topLeft_x = 0, float texCoord_topLeft_y = 1)
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



void drawRect(Rect rect, float z_pos, float texCoord_bottomLeft_x = 0, float texCoord_bottomLeft_y = 0, float texCoord_bottomRight_x = 1, float texCoord_bottomRight_y = 0, float texCoord_topRight_x = 1, float texCoord_topRight_y = 1, float texCoord_topLeft_x = 0, float texCoord_topLeft_y = 1) // the drawrect function was inverted by Y axis
{
    glBegin(GL_QUADS);
      glTexCoord3f(texCoord_bottomLeft_x,  texCoord_bottomLeft_y,  0); glVertex3f(rect.bottomLeft_x,           rect.bottomLeft_y + rect.h, z_pos);
      glTexCoord3f(texCoord_bottomRight_x, texCoord_bottomRight_y, 0); glVertex3f(rect.bottomLeft_x + rect.w,  rect.bottomLeft_y + rect.h, z_pos);
      glTexCoord3f(texCoord_topRight_x,    texCoord_topRight_y,    0); glVertex3f(rect.bottomLeft_x + rect.w,  rect.bottomLeft_y,          z_pos);
      glTexCoord3f(texCoord_topLeft_x,     texCoord_topLeft_y,     0); glVertex3f(rect.bottomLeft_x,           rect.bottomLeft_y,          z_pos);
    glEnd();
}

void drawTexturedRect(GLuint tex, Rect rect, float z_pos)   //# z_pos = -1
{
    glBindTexture(GL_TEXTURE_2D, tex);
    drawRect(rect, z_pos);
}



void drawLine(GLuint texture, float start_pos_x, float start_pos_y, float z_pos, float len, float angle_inD, int half_h, float texCoord_bottomLeft_x = 0, float texCoord_bottomLeft_y = 0, float texCoord_bottomRight_x = 1, float texCoord_bottomRight_y = 0, float texCoord_topRight_x = 1, float texCoord_topRight_y = 1, float texCoord_topLeft_x = 0, float texCoord_topLeft_y = 1)
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
                VEC_pString_type* pTo_info_title_pList, 
                VEC_pString_type* pTo_info_value_pList, 
                float center_x, float center_y,
                float scroll_x = g_SCROLL_COORD_X,
                float scroll_y = g_SCROLL_COORD_Y)
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

     TextureOb* pTo_textbg_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.textBackground_texOb_pList);
     Rect rect = Rect(center_x - char_w, center_y - info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);

     glEnable(GL_BLEND);
     drawTexturedRect(pTo_textbg_texOb->texture, rect, -2);
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
    


#endif /* RECT_H */


