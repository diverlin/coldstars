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


#include "asteroid.h"

Asteroid :: Asteroid(TextureOb* _texOb,
		     ObjMeshInstance* _mesh,
		     float _size, 
		     vec2f _orbit_center, 
		     int _radius_A, 
		     int _radius_B, 
		     float _orbit_phi_inD, 
		     float _speed)
{ 
       CommonForPlanet_init(_texOb, 
    	   		    _mesh, 
    	   	            _size, 
    	   		    _orbit_center, 
    	   		    _radius_A,
    	   		    _radius_B, 
    	   		    _orbit_phi_inD,
    	   		    _speed);
    	   			                 
      is_alive = true;
      is_dying = false;
      is_explosed = false;
      
      dying_time = 50;

      type_id = ASTEROID_ID;

      armor = 10;
      mass  = randIntInRange(10, 30);
}
    
 
Asteroid :: ~Asteroid()
{}
    
   
   

void Asteroid :: hit_TRUE(int damage)
{
     armor -= damage;
     if (armor <= 0)
     {
        is_dying = true; 
        dying_time -= 3;
     }
}

void Asteroid :: hit_FALSE(int damage)
{
     armor -= damage;
     if (armor <= 0)
        death_FALSE();
}

void Asteroid :: update_inSpace_inDynamic_TRUE()
{    
     updatePosition();  

     if (is_dying == true)
     {
        dying_time--;
        if (dying_time < 0)
           death_TRUE();
     }   
}

void Asteroid :: update_inSpace_inDynamic_FALSE()
{    
     updatePosition();  
}

  
    
void Asteroid :: death_TRUE()
{
     	is_alive = false; 

     	if (is_explosed == false)
     	{   
        	starsystem->createExplosion(points.getCenter(), scale/2);
        
        	Mineral* _mineral;
        	TextureOb* _mTexOb;
        	for (int i = 0; i<3; i++)
    		{
        		_mTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.mineral_texOb_pList); 
        		_mineral = new Mineral(_mTexOb, points.getCenter());
			starsystem->addMineral(_mineral);
			
			printf("----%i,%i, %f,%f\n", id, i, _mineral->getPoints()->getCenter().x, _mineral->getPoints()->getCenter().y);
			
    		}
    		printf("asteroid.death_TRUE ******\n");
    	   		
        	//self.starsystem.screen_QUAKE_runtime_counter = 50
        	//self.starsystem.screen_QUAKE_amlitudaDiv2 = 5
        	is_explosed = true;
     }
}
    

void Asteroid :: death_FALSE()
{
     	is_alive = false; 

     	if (is_explosed == false)
     	{   
     		Mineral* _mineral;
        	for (int i = 0; i<3; i++)
    		{        		
        		_mineral = createMineral(points.getCenter());
			starsystem->addMineral(_mineral);
    		}
        	is_explosed = true;
     	}
}


void Asteroid :: updateInfo()
{   
	info.clear();

    	info.addTitleStr("ASTEROID");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(id) + " / " + int2str(starsystem->id));
    	info.addNameStr("armor:");       info.addValueStr(int2str(armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
	info.addNameStr("speed x 100:"); info.addValueStr(int2str(int(speed*100)));
}     


void Asteroid :: renderInfo()
{  
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        


Asteroid* createAsteroid()
{
        TextureOb* _texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.asteroid_texOb_pList); 
    
        float _size = 10;
        vec2f _orbit_center = vec2f(0,0);
        int _radius_A = randIntInRange(300, 1200);
        int _radius_B = randIntInRange(300, 1200);
        float _orbit_phi_inD = randIntInRange(0, 360);
        float _speed = 0.1;

        Asteroid* _asteroid = new Asteroid(_texOb,
    				pTo_DEFORMED_SPHERE_MESH,
    				_size, 
    				_orbit_center, 
    				_radius_A, 
    				_radius_B, 
    				_orbit_phi_inD, 
    				_speed);
    	
        _asteroid->update_inSpace_inDynamic_FALSE();
        return _asteroid;        
}


