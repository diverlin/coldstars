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


void CommonForPlanet :: CommonForPlanet_init(IdData data_id,
					     LifeData data_life,
					     TextureOb* texOb, 
    	   				     ObjMeshInstance* mesh, 
					     PlanetData data)
{
	this->data_id   = data_id;
	this->data_life = data_life;
	this->data      = data;
              
        this->texOb = texOb;
        this->mesh  = mesh; 
      
        angle.x        = getRandInt(10, 40);
        angle.y        = getRandInt(10, 40);
      	angle.z        = 0.0;
      	
      	d_angle.x      = 0.0;
      	d_angle.y      = 0.0;
      	d_angle.z      = getRandInt(10, 100)*0.01;     

     
        // !!!!
        float rate = 5.4;                                            
        w = rate * this->data.scale;
        h = rate * this->data.scale;
        collision_radius = (w + h)/4; 
        // !!!!
                
        //////
	points.initCenterPoint();
	points.addCenterPoint();
	
	points.setWidthHeight(w, h);  
	//////
      
       	detailedEllipceOrbitFormation();
       	
        updatePosition();        
                
        place_type_id = SPACE_ID;
                        
        starsystem = NULL;
        
        orbit_visual.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue->texture, &orbit_vector_x, &orbit_vector_y, 50, 10);
}


void CommonForPlanet :: setStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }

int CommonForPlanet :: getId()        const { return data_id.id; }   
int CommonForPlanet :: getTypeId()    const { return data_id.type_id; }
int CommonForPlanet :: getSubTypeId() const { return data_id.subtype_id; }

Points* CommonForPlanet :: getPoints() { return &points; }
           
int CommonForPlanet :: getCollisionRadius() const { return collision_radius; }
StarSystem* CommonForPlanet :: getStarSystem() { return starsystem; }           

bool CommonForPlanet :: getGarbageReady() const  { return data_life.garbage_ready; }            
bool CommonForPlanet :: getAlive() const  { return data_life.is_alive; }
bool* CommonForPlanet :: getpAlive()      { return &data_life.is_alive; }
int* CommonForPlanet :: getpPlaceTypeId() { return &place_type_id; }
       
vec2f CommonForPlanet :: getNextTurnPosition() const 
{ 
        if (orbit_it + TURN_TIME < orbit_len)
        {
                return vec2f(orbit_vector_x[orbit_it+TURN_TIME], orbit_vector_y[orbit_it+TURN_TIME]); 
        }
        else
        {
                int d_orbit = orbit_len-orbit_it;
                return vec2f(orbit_vector_x[TURN_TIME - d_orbit], orbit_vector_y[TURN_TIME - d_orbit]); 
        }
}
                                                                    


                

void CommonForPlanet :: detailedEllipceOrbitFormation()
{   
     	float d_angleInRad  = data.speed / 57.295779;
     	float orbitPhiInRad = data.orbit_phi_inD * PI/180;
     	
     	for(float angleInRad = 0; angleInRad < 2*PI; angleInRad += d_angleInRad) 
     	{ 
         	float new_coord_x = data.orbit_center.x + data.radius_A * cos(angleInRad) * cos(orbitPhiInRad) - data.radius_B * sin(angleInRad) * sin(orbitPhiInRad);
         	float new_coord_y = data.orbit_center.y + data.radius_A * cos(angleInRad) * sin(orbitPhiInRad) + data.radius_B * sin(angleInRad) * cos(orbitPhiInRad);
         	orbit_vector_x.push_back(new_coord_x);
         	orbit_vector_y.push_back(new_coord_y);
     	}
        orbit_len = orbit_vector_x.size();
        orbit_it = getRandInt(1, orbit_len);
}    


void CommonForPlanet :: updatePosition()
{   
     	if (orbit_it < orbit_len)
     	{ 
        	points.setCenter(orbit_vector_x[orbit_it], orbit_vector_y[orbit_it]);
        	center_pos.set(orbit_vector_x[orbit_it], orbit_vector_y[orbit_it], -500.0f);
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
      
	renderMesh(mesh->glList, center_pos, angle, data.scale);

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
	renderMesh(mesh->glList, center_pos, angle, data.scale);
}

void CommonForPlanet :: drawOrbit()
{   
        orbit_visual.draw();
}





