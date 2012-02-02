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


Planet :: Planet(unsigned long int _population)
{    
      	//texOb_atmosphere = _texOb_atmoshere;
      	population  = _population;
}

    
Planet :: ~Planet()
{}
    
void Planet :: createInternals()
{
      	if (data_id.subtype_id == KOSMOPORT_ID)
      	{
      	      	createKosmoport();
      	      	land      = NULL;
        }
        
      	if (data_id.subtype_id == LAND_ID)
      	{
         	createLand();
         	kosmoport = NULL;
        }
}

//void Planet :: setPlanetData(PlanetData data_planet) { data = data_planet; }
		
int Planet :: getDockingRadius() const { return data_planet.scale; }
Kosmoport* Planet :: getKosmoport()    { return kosmoport; }
Land* Planet :: getLand()              { return land; }
                

void Planet :: update_inSpace_inDynamic()
{      
     	updatePosition();  
}
  


void Planet :: update_inSpace_inStatic()
{      
     	if (data_id.subtype_id == KOSMOPORT_ID)
     	{
                kosmoport->ai();
        }
                
     	if (data_id.subtype_id == LAND_ID)
     	{
                land->ai();    
        }    	
}
         

void Planet :: updateInfo()
{
	info.clear();

    	info.addTitleStr("PLANET");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("population:");  info.addValueStr(int2str(population));
}


void Planet :: renderInfo()
{  
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        
void Planet :: createKosmoport()
{   
    	kosmoport = new Kosmoport(RACE_0_ID);   
}


void Planet :: createLand()
{   
    	land = new Land();   
}


//// ******* TRANSITION ******* 
void Planet :: launchingProcedure()
{
         for (unsigned int i = 0; i<NPC_launching_vec.size(); i++)
         {
         	NPC_launching_vec[i]->getVehicle()->launchingEvent();
         }
              
         NPC_launching_vec.clear();  
}

void Planet :: addToLaunchingQueue(Npc* _npc)
{
         NPC_launching_vec.push_back(_npc);
}
		
                
bool Planet :: add(Ship* _ship)
{
     	if (data_id.subtype_id == KOSMOPORT_ID)
        {
                return kosmoport->addShip(_ship);
        }
     	if (data_id.subtype_id == LAND_ID)
        {
                return land->addShip(_ship);
        }
        
        return false;
}

bool Planet :: add(Npc* _npc)
{
     	if (data_id.subtype_id == KOSMOPORT_ID)
        {       
                return kosmoport->addNpc(_npc);
        }
     	if (data_id.subtype_id == LAND_ID)
        {
                return land->addNpc(_npc);
        }
        
        return false;
}

bool Planet :: removeShipById(int _id)
{
     	if (data_id.subtype_id == KOSMOPORT_ID)
     	{
         	return kosmoport->removeShip(_id);
        }
        
     	if (data_id.subtype_id == LAND_ID)
     	{
         	return land->removeShip(_id);
        }
        
        return false;
}

bool Planet :: removeNpcById(int _id)
{
     	if (data_id.subtype_id == KOSMOPORT_ID)
     	{
         	return kosmoport->removeNpc(_id);
        }
        
     	if (data_id.subtype_id == LAND_ID)
     	{
         	return land->removeNpc(_id);
        }
        
        return false;
}
//// ******* TRANSITION ******* 



bool Planet :: getPermissionToLand() const
{
     	if (data_id.subtype_id == KOSMOPORT_ID)
     	{
        	if (kosmoport->getAngar()->getNumFreelandingArea() > 0)
            		return true;
        	else
            		return false;       
     	}
     	if (data_id.subtype_id == LAND_ID)
        	return true;
                
        return false;
}

        


Planet* createPlanet(int orbit_radius)
{
	IdData data_id;
	data_id.id         = g_PLANET_ID_GENERATOR.getNextId();
      	data_id.type_id    = PLANET_ID;
      	data_id.subtype_id = KOSMOPORT_ID;
        
        LifeData data_life;
        
	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(PLANET_SIZE_MIN, PLANET_SIZE_MAX);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = orbit_radius;
    	planet_data.radius_B      = orbit_radius; 
    	planet_data.orbit_phi_inD = 0;
    	planet_data.speed         = (float)getRandInt(PLANET_SPEED_MIN, PLANET_SPEED_MAX) / (float)orbit_radius;


        TextureOb* texOb 	    = g_TEXTURE_MANAGER.getRandomTexOb(PLANET_TEXTURE_ID); 
        TextureOb* texOb_atmosphere = g_TEXTURE_MANAGER.getRandomTexOb(ATMOSPHERE_TEXTURE_ID); 
        
        unsigned long int population = getRandInt(1000, 4000);
        
        Planet* planet = new Planet(population);
        planet->setPlanetData(planet_data);
	planet->setTextureOb(texOb);
	planet->setIdData(data_id);
	planet->setLifeData(data_life);
	planet->setMesh(g_SPHERE_MESH);	
      	
      	planet->postCreateInit();
        planet->createInternals();
    			     
        return planet;        
}
