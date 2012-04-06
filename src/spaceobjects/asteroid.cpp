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



Asteroid :: Asteroid(int id)
{   
	data_id.id = id;
	data_id.type_id = ENTITY::ASTEROID_ID;
	
      	mass  = getRandInt(10, 30);
}
    
 
Asteroid :: ~Asteroid()
{}
    

int Asteroid :: getDamage() const { return mass*10; }
		


void Asteroid :: update_inSpace(int time, bool show_effect)
{    
	CheckDeath(show_effect);
	UpdateRotation();
	if (time > 0)
	{	
     		orbit->UpdatePosition();  
     		points.setCenter(orbit->GetPosition());
     	}     	
}

void Asteroid :: collisionEvent(bool show_effect)
{
	data_life.is_alive = false;
	data_life.dying_time = -1;
}

    
void Asteroid :: PostDeathUniqueEvent(bool show_effect)
{
       	for (int i = 0; i<3; i++)
	{
		Mineral* _mineral = getNewMineral();
		starsystem->AddToSpace(_mineral, points.getCenter());			
   	}
   	
   	if (show_effect == true)
     	{
        	createExplosion(starsystem, points.getCenter(), data_planet.scale/2);        		
        }
        			
}    





void Asteroid :: UpdateInfo()
{   
	info.clear();

    	info.addTitleStr("ASTEROID");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
	info.addNameStr("speed x 100:"); info.addValueStr(int2str(int(data_planet.speed*100)));
}     


void Asteroid :: renderInfo_inSpace(vec2f scroll_coords) 
{  
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);
}

        


Asteroid* getNewAsteroid()
{
	int id      = g_ID_GENERATOR.getNextId();
        	
	LifeData data_life;   
	data_life.armor      = 10;
      	data_life.dying_time = 50;
      	
    	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(ENTITY::ASTEROID::SIZE_MIN_, ENTITY::ASTEROID::SIZE_MAX_);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = getRandInt(300, 1200);
    	planet_data.radius_B      = getRandInt(300, 1200); 
    	planet_data.orbit_phi_inD = getRandInt(0, 360);
    	planet_data.speed         = 0.1;

        TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::ASTEROID_ID); 
    
        Asteroid* asteroid = new Asteroid(id); 
        
        asteroid->SetPlanetData(planet_data);
	asteroid->SetTextureOb(texOb);
	asteroid->SetLifeData(data_life);
	asteroid->SetMesh(g_DEFORMED_SPHERE_MESH);	
       	
        asteroid->PostCreateInit();
        
        return asteroid;        
}


