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


Planet :: Planet(int race_id, unsigned long int _population)
{    
      	//texOb_atmosphere = _texOb_atmoshere;
      	population  = _population;      	
      	land = NULL;
}

    
Planet :: ~Planet()
{
	delete land;
}
    
		
int Planet :: getDockingRadius() const              { return data_planet.scale; }
LandBase* Planet :: getLand() const { return land; }

void Planet :: createLand()
{
      	if (population > 0) 
      	{ 
      		land = new Kosmoport(RACE::R0_ID); 
      	}
        else
        { 
        	land = new Land();
        }
}              

void Planet :: update_inSpace(int time, bool show_effect)
{      
	updateRotation();
	if (time > 0)
	{
     		orbit->updatePosition();  
     		if (parent == NULL)
     		{
     			points.setCenter(orbit->getPosition());
     		}
     		else
     		{
     			points.setCenter(parent->GetPoints().getCenter() + orbit->getPosition());
     		}
     	}
}
  
void Planet :: update_inSpace_inStatic()
{}

                       

void Planet :: updateInfo()
{
	info.clear();

    	info.addTitleStr("PLANET");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("population:");  info.addValueStr(int2str(population));
}


void Planet :: renderInfo_inSpace(vec2f scroll_coords)
{  
	updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);
}
        
void Planet :: postDeathUniqueEvent(bool)
{}


Planet* getNewPlanet(int orbit_radius)
{
	IdData data_id;
	data_id.id         = g_ID_GENERATOR.getNextId();
      	data_id.type_id    = ENTITY::PLANET_ID;
      	data_id.subtype_id = ENTITY::KOSMOPORT_ID;
        
        LifeData data_life;
        
	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(PLANET_SIZE_MIN, PLANET_SIZE_MAX);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = orbit_radius;
    	planet_data.radius_B      = orbit_radius; 
    	planet_data.orbit_phi_inD = 0;
    	planet_data.speed         = (float)getRandInt(PLANET_SPEED_MIN, PLANET_SPEED_MAX) / (float)orbit_radius;


        TextureOb* texOb 	    = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::PLANET_ID); 
        TextureOb* texOb_atmosphere = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::ATMOSPHERE_ID); 
        
        unsigned long int population = getRandInt(1000, 4000);
        
        Planet* planet = new Planet(RACE::R0_ID, population);
        planet->setPlanetData(planet_data);
	planet->setTextureOb(texOb);
	planet->setIdData(data_id);
	planet->setLifeData(data_life);
	planet->setMesh(g_SPHERE_MESH);	
      	
      	planet->postCreateInit();
      	planet->createLand();
    			     
        return planet;        
}
