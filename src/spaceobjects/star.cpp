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


#include "star.h"
   
Star :: Star(TextureOb* _pTo_texOb, ObjMeshInstance* _pTo_mesh, StarSystem* _pTo_starsystem, float _size)
{ 
	id = g_ENTITY_ID_GENERATOR.returnNextId();
     
	pTo_starsystem = _pTo_starsystem;
	pTo_texOb      = _pTo_texOb;
	
	scale = _size;
	pos_x = 0;
	pos_y = 0;
	pos_z = -500.0f;

	angle_x        = 0.0;
	angle_y        = 0.0;
	angle_z        = 0.0;
	d_angle_x      = 0.2;
	d_angle_y      = 0.0;
	d_angle_z      = 0.0;
            
	// !!!!
	float rate = 5.4;                                            
	w = rate * scale;
	h = rate * scale;
	collision_radius = (w + h)/2; 
	// !!!!

    	texture = pTo_texOb->texture;
    	texture_offset1 = 0.0;
    	texture_offset2 = 0.0;
    
    	pTo_mesh = _pTo_mesh; 
}
    
Star :: ~Star()
{}
    
   
        
void Star :: update_inSpace_inDynamic()
{}
    
    
void Star :: render_NEW()
{
	//angle_x += d_angle_x;  
     	//angle_y += d_angle_y;  
     	//angle_z += d_angle_z; 
     	
        texture_offset1 += 0.0002;
        texture_offset2 += 0.0003;

        glUseProgram(g_MULTITEX_PROGRAM);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, pTo_texOb->texture);
        glUniform1i(glGetUniformLocation(g_MULTITEX_PROGRAM, "Texture_0"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, pTo_texOb->texture);
        glUniform1i(glGetUniformLocation(g_MULTITEX_PROGRAM, "Texture_1"), 1);
        
	glUniform2f(glGetUniformLocation(g_MULTITEX_PROGRAM, "displ"), texture_offset1, texture_offset2);

        glPushMatrix();
	        glTranslatef(pos_x, pos_y, pos_z);
        	glScalef(scale, scale, scale); 
        	glRotatef(angle_x, 1.0, 0.0, 0.0);
        	glRotatef(angle_y, 0.0, 1.0, 0.0);
        	glRotatef(angle_z, 0.0, 0.0, 1.0);

      		glCallList(pTo_mesh->glList);
        glPopMatrix();

        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
}
    
    
void Star :: render_OLD()
{    
	angle_x += d_angle_x;  
     	angle_y += d_angle_y;  
     	angle_z += d_angle_z;  
     		
	glPushMatrix();
      		glBindTexture(GL_TEXTURE_2D, texture);   
      		glTranslatef(pos_x, pos_y, pos_z);
     		glScalef(scale, scale, scale); 
        	glRotatef(angle_x, 1.0, 0.0, 0.0);
        	glRotatef(angle_y, 0.0, 1.0, 0.0);
        	glRotatef(angle_z, 0.0, 0.0, 1.0);
        	
      		glCallList(pTo_mesh->glList);
	glPopMatrix();
}

void Star :: renderInfo()
{ 
    printf("planet, id = %i \n", id);
    printf("planet SS_id = %i \n", (*pTo_starsystem).id);
}

        


    

        


