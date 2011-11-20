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


#include "asteroid.hpp"

Asteroid :: Asteroid(IdData _data_id, LifeData _data_life,	
		     TextureOb* _texOb,
		     ObjMeshInstance* _mesh,
		     PlanetData _planet_data)
{ 
       CommonForPlanet_init(_data_id, _data_life,
       			    _texOb, 
    	   		    _mesh, 
    	   	            _planet_data);
   	   			                 
      	damage = 10 * data_life.armor;
      	mass  = getRandInt(10, 30);
}
    
 
Asteroid :: ~Asteroid()
{}
    

int Asteroid :: getArmor() const  { return data_life.armor; }
int Asteroid :: getDamage() const { return damage; }
int Asteroid :: getMass()  const  { return mass; }	
			


void Asteroid :: update_inSpace_inDynamic_TRUE()
{    
     	updatePosition();  
     	updateRotation();

     	if (data_life.is_alive == false)
     	{
        	data_life.dying_time--;
        	if (data_life.dying_time < 0)
        	{
           		death_TRUE();
           	}
     	}   
}

void Asteroid :: update_inSpace_inDynamic_FALSE()
{    
     	updatePosition();  
}

void Asteroid :: collisionEvent_TRUE()
{
	data_life.is_alive = false;
	death_TRUE();
}

void Asteroid :: collisionEvent_FALSE()
{
	data_life.is_alive = false;
	death_FALSE();
}        	

void Asteroid :: hit_TRUE(int damage)
{
     	data_life.armor -= damage;
     	if (data_life.armor <= 0)
     	{
        	data_life.is_alive = false; 
        	data_life.dying_time -= 3;
     	}
}

void Asteroid :: hit_FALSE(int damage)
{
     	data_life.armor -= damage;
     	if (data_life.armor <= 0)
     	{
     	     	data_life.is_alive = false; 
        	death_FALSE();
        }
}

    
void Asteroid :: death_TRUE()
{
     	if (data_life.garbage_ready == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), data.scale/2);
        
        	for (int i = 0; i<3; i++)
    		{
                        Mineral* _mineral = createMineral(points.getCenter());
			starsystem->add(_mineral);			
			//printf("----%i,%i, %f,%f\n", id, i, _mineral->getPoints()->getCenter().x, _mineral->getPoints()->getCenter().y);
   		}
    	   		
        	//self.starsystem.screen_QUAKE_runtime_counter = 50
        	//self.starsystem.screen_QUAKE_amlitudaDiv2 = 5
        	data_life.garbage_ready = true;
     }
}    

void Asteroid :: death_FALSE()
{
     	if (data_life.garbage_ready == false)
     	{  
        	for (int i = 0; i<3; i++)
    		{        		
        		Mineral* _mineral = createMineral(points.getCenter());
			starsystem->add(_mineral);
    		}
        	data_life.garbage_ready = true;
     	}
}




void Asteroid :: updateInfo()
{   
	info.clear();

    	info.addTitleStr("ASTEROID");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
	info.addNameStr("speed x 100:"); info.addValueStr(int2str(int(data.speed*100)));
}     


void Asteroid :: renderInfo() 
{  
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        


Asteroid* createAsteroid()
{
	IdData data_id;
	data_id.id      = g_ASTEROID_ID_GENERATOR.getNextId();
      	data_id.type_id = ASTEROID_ID;
      	
	LifeData data_life;   
	data_life.armor      = 10;
      	data_life.dying_time = 50;
      	
    	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(ASTEROID_SIZE_MIN, ASTEROID_SIZE_MAX);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = getRandInt(300, 1200);
    	planet_data.radius_B      = getRandInt(300, 1200); 
    	planet_data.orbit_phi_inD = getRandInt(0, 360);
    	planet_data.speed         = 0.1;

        TextureOb* texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.asteroid_texOb_pList); 
    
        Asteroid* asteroid = new Asteroid(data_id, data_life, texOb, g_DEFORMED_SPHERE_MESH, planet_data);    	
        asteroid->update_inSpace_inDynamic_FALSE();
        
        return asteroid;        
}


