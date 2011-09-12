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


#include "star.hpp"
   
Star :: Star(TextureOb* _texOb, ObjMeshInstance* _mesh, PlanetData _star_data)
{ 
	type_id = STAR_ID;
	
      	CommonForPlanet_init(_texOb, 
    	   		     _mesh, 
    	   	             _star_data);
    	   		       
   	texture_offset1 = 0.0;
    	texture_offset2 = 0.0;
        
        if (texOb->color_id == YELLOW_COLOR_ID)
	{
		color.r = 255/255.0;
		color.g = 255/255.0;
		color.b = 255/220.0;
		color.a = 1.0;
	}
	
	if (texOb->color_id == BLUE_COLOR_ID)
	{
		color.r = 220/255.0;
		color.g = 255/255.0;
		color.b = 255/255.0;
		color.a = 1.0;
	}
		    
        points.setCenter(0, 0);
        center_pos.set(0, 0, -500.0f);
}
    
Star :: ~Star()
{}
    

Color Star :: getColor() const           { return color; }
int Star :: getColorId() const 		 { return texOb->color_id; }
float Star :: getBrightThreshold() const { return texOb->brightThreshold; }
       
void Star :: update_inSpace_inDynamic()
{}
    
    
void Star :: render_NEW()
{
        texture_offset1 += 0.0002;
        texture_offset2 += 0.0003;

        glUseProgram(g_MULTITEX_PROGRAM);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, texOb->texture);
        glUniform1i(glGetUniformLocation(g_MULTITEX_PROGRAM, "Texture_0"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, texOb->texture);
        glUniform1i(glGetUniformLocation(g_MULTITEX_PROGRAM, "Texture_1"), 1);
        
	glUniform2f(glGetUniformLocation(g_MULTITEX_PROGRAM, "displ"), texture_offset1, texture_offset2);

	renderMesh(mesh->glList, center_pos, angle, data.scale);

        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
}
    
    
void Star :: render_OLD()
{    
	updateRotation();
     	
     	glBindTexture(GL_TEXTURE_2D, texOb->texture);      		
	renderMesh(mesh->glList, center_pos, angle, data.scale);
}


void Star :: updateInfo()
{ 
	info.clear();
    	info.addTitleStr("STAR");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(id) + " / " + int2str(starsystem->id));
}

void Star :: renderInfo()
{ 
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        


    
Star* createStar()
{
 	PlanetData star_data;

	star_data.scale         = randIntInRange(STAR_SIZE_MIN, STAR_SIZE_MAX);  
    	star_data.orbit_center  = vec2f(0, 0); 
    	star_data.radius_A      = 50;
    	star_data.radius_B      = 50; 
    	star_data.orbit_phi_inD = 0;
    	star_data.speed         = 1.8;

    	TextureOb* _starTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.star_texOb_pList);
    	Star* _star = new Star(_starTexOb, pTo_SPHERE_MESH, star_data);
    
    	return _star;
}
        


