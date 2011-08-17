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


Asteroid :: Asteroid(TextureOb* _pTo_texOb, StarSystem* _pTo_starsystem, float _size, float _orbit_center_x, float _orbit_center_y, int _radius_A, int _radius_B, float _orbitPhiInDegree, float _speed)
{ 
      id = g_ENTITY_ID_GENERATOR.returnNextId();
      
      is_alive = true;
      is_dying = false;
      is_explosed = false;
      
      dying_time = 50;

      type_id = ASTEROID_ID;

      pTo_starsystem = _pTo_starsystem;
      pTo_texOb      = _pTo_texOb;
            
      texture = (*pTo_texOb).texture;
      w = (*pTo_texOb).w;
      h = (*pTo_texOb).h;
      updateWHRenderConstants();
      size = returnObjectSize(w, h);


      orbit_center_x = _orbit_center_x;
      orbit_center_y = _orbit_center_y;
      radius_A       = _radius_A;
      radius_B       = _radius_B;
      orbitPhiInDegree  = _orbitPhiInDegree;
      speed          = _speed;    
     
      pos_z          = -500.0f;

      angle_x        = 0.0;
      angle_y        = 0.0;
      angle_z        = 0.0;
      d_angle_z      = randIntInRange(10, 100)*0.01;



      
      //lMesh = LoadObjMesh("asteroid.obj");
      //lMesh.createGlList();
      
      //////
      points = Points();

      points.initCenterPoint();
      points.addCenterPoint();
      //////
      
      detailedEllipceOrbitFormation();
     
      armor = 10;
      mass  = randIntInRange(10, 30);
}
    
 
Asteroid :: ~Asteroid()
{}
    
   
void Asteroid :: detailedEllipceOrbitFormation()
{   
     float d_angleInRad = speed / 57.295779;
     float orbitPhiInRad = orbitPhiInDegree * PI/180;
     for(float angleInRad = 0; angleInRad < 2*PI; angleInRad += d_angleInRad) 
     { 
         float new_coord_x = orbit_center_x + radius_A * cos(angleInRad) * cos(orbitPhiInRad) - radius_B * sin(angleInRad) * sin(orbitPhiInRad);
         float new_coord_y = orbit_center_y + radius_A * cos(angleInRad) * sin(orbitPhiInRad) + radius_B * sin(angleInRad) * cos(orbitPhiInRad);
         orbit_vector_x.push_back(new_coord_x);
         orbit_vector_y.push_back(new_coord_y);

         orbit_len = orbit_vector_x.size();
         orbit_it = randIntInRange(1, orbit_len);
     }
}    
        

void Asteroid :: updateWHRenderConstants()
{
     minus_half_w = -w/2;
     minus_half_h = -h/2;
     plus_half_w  =  w/2;
     plus_half_h  =  h/2;
}

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

void Asteroid :: updatePosition()
{   
     if (orbit_it < orbit_len)
     { 
        points.setCenter(orbit_vector_x[orbit_it], orbit_vector_y[orbit_it]);
        orbit_it++;
     }
     else
        orbit_it = 0;
}    
    
    
void Asteroid :: death_TRUE()
{
     is_alive = false; 

     if (is_explosed == false)
     {   
        pTo_starsystem->addExplosion(points.center_x, points.center_y, size);
        pTo_starsystem->addNumMinerals(points.center_x, points.center_y, randIntInRange(1,4));
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
        pTo_starsystem->addNumMinerals(points.center_x, points.center_y, randIntInRange(1,4));
        is_explosed = true;
     }
}


void Asteroid :: render2D()
{ 
     glBindTexture(GL_TEXTURE_2D, texture);
     drawDynamic(points.center_x, points.center_y, angle_z, minus_half_w, minus_half_h, plus_half_w, plus_half_h, pos_z);
     angle_z += d_angle_z;
}



void Asteroid :: updateInfo()
{   
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "ASTEROID";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(pTo_starsystem->id);
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
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y);
}

        



