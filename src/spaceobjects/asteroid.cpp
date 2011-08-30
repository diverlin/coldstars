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
		     float _orbit_center_x, 
		     float _orbit_center_y, 
		     int _radius_A, 
		     int _radius_B, 
		     float _orbit_phi_inD, 
		     float _speed)
{ 
       CommonForPlanet_init(_texOb, 
    	   		    _mesh, 
    	   	            _size, 
    	   		    _orbit_center_x, 
    	   		    _orbit_center_y, 
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
        starsystem->addExplosion(points.getCenter().x, points.getCenter().y, scale/2);
        starsystem->addNumMinerals(points.getCenter().x, points.getCenter().y, randIntInRange(1,4));
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
        starsystem->addNumMinerals(points.getCenter().x, points.getCenter().y, randIntInRange(1,4));
        is_explosed = true;
     }
}


void Asteroid :: updateInfo()
{   
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "ASTEROID";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(starsystem->id);
    info_title_2 = "armor:";
    info_value_2 = int2str(armor);
    info_title_3 = "mass:";
    info_value_3 = int2str(mass);
    info_title_4 = "speed x 100:";
    info_value_4 = int2str(int(speed*100));

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
}     


void Asteroid :: renderInfo()
{  
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.getCenter().x, points.getCenter().y);
}

        


Asteroid* asteroidGenerator()
{
        TextureOb* _texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.asteroid_texOb_pList); 
    
        float _size = 10;
        float _orbit_center_x = 0;
        float _orbit_center_y = 0;
        int _radius_A = randIntInRange(300, 1200);
        int _radius_B = randIntInRange(300, 1200);
        float _orbit_phi_inD = randIntInRange(0, 360);
        float _speed = 0.1;

        Asteroid* _asteroid = new Asteroid(_texOb,
    				pTo_DEFORMED_SPHERE_MESH,
    				_size, 
    				_orbit_center_x, 
    				_orbit_center_y, 
    				_radius_A, 
    				_radius_B, 
    				_orbit_phi_inD, 
    				_speed);
    	
        _asteroid->update_inSpace_inDynamic_FALSE();
        return _asteroid;        
}


