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

PathVisual::PathVisual()  
{ 
	gl_list = glGenLists(1); 
}

PathVisual::~PathVisual() 
{
	glDeleteLists(gl_list, sizeof(gl_list));
}
                
void PathVisual::FillData(GLuint texture, std::vector<float>* pVec_x, std::vector<float>* pVec_y, float step, int point_size)
{   
        int i = 0;
        int list_len = pVec_x->size();
                        
        glNewList(gl_list, GL_COMPILE);
                glBindTexture(GL_TEXTURE_2D, texture);
                while (i < list_len)
                {
                        Rect rect((*pVec_x)[i] - point_size/2.0f, (*pVec_y)[i] - point_size/2.0f, point_size, point_size);
                        drawRect(rect, -1.0);
                        i += step;
                }
        glEndList();
}

void PathVisual::FillData(GLuint texture, std::vector<vec2f>* pVec2f, float step, int point_size)
{   
        int i = 0;
        int list_len = pVec2f->size();
                        
        glNewList(gl_list, GL_COMPILE);
                glBindTexture(GL_TEXTURE_2D, texture);
                while (i < list_len)
                {
                        Rect rect((*pVec2f)[i].x - point_size/2.0f, (*pVec2f)[i].y - point_size/2.0f, point_size, point_size);
                        drawRect(rect, -1.0);
                        i += step;
                }
        glEndList();
}

void PathVisual::Draw() const
{
       	glCallList(gl_list);
}


