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


CommonForPlanet :: CommonForPlanet()
{}

CommonForPlanet :: ~CommonForPlanet() /* virtual */
{
	delete orbit;
}

void CommonForPlanet :: setPlanetData(PlanetData data_planet) { this->data_planet = data_planet;  }

Orbit* CommonForPlanet :: getOrbit() const { return orbit; }


void CommonForPlanet :: postCreateInit()
{
        this->calcCollisionrRadius();           
        this->createCenter();
        
        orbit = new Orbit();
}

void CommonForPlanet :: createOrbit()
{
	orbit->calcPath(data_planet.radius_A, data_planet.radius_B, data_planet.speed, data_planet.orbit_phi_inD);
}
    		
void CommonForPlanet :: calcCollisionrRadius()
{
        float scale_factor = 5.4;                                            
        int w = scale_factor * data_planet.scale;
        int h = scale_factor * data_planet.scale;
        collision_radius = (w + h)/4; 
        
        points.setWidthHeight(scale_factor*data_planet.scale, scale_factor*data_planet.scale);  // needs for finding visible corners
}

void CommonForPlanet :: postDeathUniqueEvent(bool)  /* virtual */
{}		
		 		
void CommonForPlanet :: render_NEW()
{     	
     	glUseProgram(g_LIGHT_PROGRAM);
     	//printProgramInfoLog(g_LIGHT_PROGRAM);

     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "lightPos") == -1)
         	//printf("shader lightPos fail\n"); 
     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "eyePos") == -1)
         	//printf("shader eyePos fail\n"); 
     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0") == -1)
         	//printf("shader Texture_0 fail\n"); 

     	glUniform4f(glGetUniformLocation(g_LIGHT_PROGRAM, "lightPos"), -g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, -200.0, 0.0);
     	glUniform4f(glGetUniformLocation(g_LIGHT_PROGRAM, "eyePos"), -g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, -200.0, 0.0);

     	glActiveTexture(GL_TEXTURE0);
     	glBindTexture(GL_TEXTURE_2D, texOb->texture);
     	glUniform1i(glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0"), 0);
      
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);

     	//// render atmosphere
     	//glEnable(GL_BLEND);
     	//glActiveTexture(GL_TEXTURE0);                                
     	//glBindTexture(GL_TEXTURE_2D, pTo_atmosphereTexOb->texture);
     	//glUniform1i(glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0"), 0);

	//renderMesh(mesh->glList, center_pos, angle, planet_data.scale*1.05);
	
     	//glDisable(GL_BLEND);
     	//// render atmosphere

     	glUseProgram(0);
     	glActiveTexture(GL_TEXTURE0);
}

void CommonForPlanet :: render_OLD()
{   	
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);
}





