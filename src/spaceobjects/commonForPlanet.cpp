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

CommonForPlanet :: ~CommonForPlanet()
{}

void CommonForPlanet :: setPlanetData(PlanetData data_planet) { this->data_planet = data_planet;  }

void CommonForPlanet :: postCreateInit()
{
        this->calcCollisionrRadius();           
        this->createCenter();
}

void CommonForPlanet :: createOrbit()
{
       	this->createEllipceOrbit(); 
        this->createOrbitVisual();  
}
    		
void CommonForPlanet :: calcCollisionrRadius()
{
        float scale_factor = 5.4;                                            
        int w = scale_factor * data_planet.scale;
        int h = scale_factor * data_planet.scale;
        collision_radius = (w + h)/4; 
        
        points.setWidthHeight(scale_factor*data_planet.scale, scale_factor*data_planet.scale);  // needs for finding visible corners
}

void CommonForPlanet :: createOrbitVisual()
{
	orbit_visual.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue->texture, &orbit_vec, 50, 10);
}
       
vec2f CommonForPlanet :: getNextTurnPosition() const 
{ 
        if (orbit_it + TURN_TIME < orbit_len)
        {
                return orbit_vec[orbit_it+TURN_TIME]; 
        }
        else
        {
                int d_orbit = orbit_len-orbit_it;
                return orbit_vec[TURN_TIME - d_orbit]; 
        }
}

void CommonForPlanet :: createEllipceOrbit()
{   
     	float d_angleInRad  = data_planet.speed / 57.295779;
     	float orbitPhiInRad = data_planet.orbit_phi_inD * PI/180;
     	
     	for(float angleInRad = 0; angleInRad < 2*PI; angleInRad += d_angleInRad) 
     	{ 
         	float new_coord_x = data_planet.orbit_center.x + data_planet.radius_A * cos(angleInRad) * cos(orbitPhiInRad) - data_planet.radius_B * sin(angleInRad) * sin(orbitPhiInRad);
         	float new_coord_y = data_planet.orbit_center.y + data_planet.radius_A * cos(angleInRad) * sin(orbitPhiInRad) + data_planet.radius_B * sin(angleInRad) * cos(orbitPhiInRad);
         	orbit_vec.push_back(vec2f(new_coord_x, new_coord_y));
     	}
        orbit_len = orbit_vec.size();
        orbit_it = getRandInt(1, orbit_len);
        
        updatePosition(); // place object to a right position
}    


void CommonForPlanet :: updatePosition()
{   
     	if (orbit_it < orbit_len)
     	{ 
        	points.setCenter(orbit_vec[orbit_it]);
        	//center_pos.set(orbit_vec[orbit_it].x, orbit_vec[orbit_it].y, -500.0f);
        	orbit_it++;
     	}
     	else
        	orbit_it = 0;
}    


void CommonForPlanet :: updateRotation()
{
	angle.x += d_angle.x;  
     	angle.y += d_angle.y;  
     	angle.z += d_angle.z; 
}


void CommonForPlanet :: hit_TRUE(int) 
{}


void CommonForPlanet :: hit_FALSE(int) 
{}
 		
 		 		
void CommonForPlanet :: render_NEW()
{     	
	updateRotation();

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
	updateRotation();

	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);
}

void CommonForPlanet :: drawOrbit()
{   
        orbit_visual.draw();
}





