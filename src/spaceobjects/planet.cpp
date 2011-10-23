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


#include "planet.hpp"

Planet :: Planet(int _subtype_id, 
		 TextureOb* _texOb, 
		 TextureOb* _texOb_atmoshere, 
		 ObjMeshInstance* _mesh, 
		 PlanetData _planet_data,
		 unsigned long int _population)
{ 
      	type_id = PLANET_TYPE_ID;
      	subtype_id = _subtype_id;
      
      	CommonForPlanet_init(_texOb, 
    	   		     _mesh, 
			     _planet_data);

      	texOb_atmosphere = _texOb_atmoshere;



      	
      	population = _population;
      
      	if (subtype_id == KOSMOPORT_TYPE_ID)
      	{
      	      	createKosmoport();
      	      	land      = NULL;
        }
        
      	if (subtype_id == LAND_ID)
      	{
         	createLand();
         	kosmoport = NULL;
        }
}

    
Planet :: ~Planet()
{}
    

int Planet :: getDockingRadius() const { return data.scale; }
Kosmoport* Planet :: getKosmoport()    { return kosmoport; }
Land* Planet :: getLand()              { return land; }
                

void Planet :: update_inSpace_inDynamic()
{      
     	updatePosition();  
}
  


void Planet :: update_inSpace_inStatic()
{      
     	if (subtype_id == KOSMOPORT_TYPE_ID)
     	{
                kosmoport->ai();
        }
                
     	if (subtype_id == LAND_ID)
     	{
                land->ai();    
        }    	
}
         

void Planet :: updateInfo()
{
	info.clear();

    	info.addTitleStr("PLANET");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(id) + " / " + int2str(starsystem->getId()));
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
         	NPC_launching_vec[i]->launchingEvent();
         }
              
         NPC_launching_vec.clear();  
}

void Planet :: addToLaunchingQueue(Npc* _npc)
{
         NPC_launching_vec.push_back(_npc);
}
		
                
bool Planet :: addShip(Ship* _ship)
{
     	if (subtype_id == KOSMOPORT_TYPE_ID)
        {
                return kosmoport->addShip(_ship);
        }
     	if (subtype_id == LAND_ID)
        {
                return land->addShip(_ship);
        }
}

bool Planet :: addNpc(Npc* _npc)
{
     	if (subtype_id == KOSMOPORT_TYPE_ID)
        {       
                return kosmoport->addNpc(_npc);
        }
     	if (subtype_id == LAND_ID)
        {
                return land->addNpc(_npc);
        }
}

bool Planet :: removeShipById(int _id)
{
     	if (subtype_id == KOSMOPORT_TYPE_ID)
     	{
         	return kosmoport->removeShip(_id);
        }
        
     	if (subtype_id == LAND_ID)
     	{
         	return land->removeShip(_id);
        }
}

bool Planet :: removeNpcById(int _id)
{
     	if (subtype_id == KOSMOPORT_TYPE_ID)
     	{
         	return kosmoport->removeNpc(_id);
        }
        
     	if (subtype_id == LAND_ID)
     	{
         	return land->removeNpc(_id);
        }
}
//// ******* TRANSITION ******* 



bool Planet :: getPermissionToLand() const
{
     	if (subtype_id == KOSMOPORT_TYPE_ID)
     	{
        	if (kosmoport->getAngar()->getNumFreelandingArea() > 0)
            		return true;
        	else
            		return false;       
     	}
     	if (subtype_id == LAND_ID)
        	return true;
}

        


Planet* createPlanet(int orbit_radius)
{
        int subtype_id   = KOSMOPORT_TYPE_ID;
        
	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(PLANET_SIZE_MIN, PLANET_SIZE_MAX);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = orbit_radius;
    	planet_data.radius_B      = orbit_radius; 
    	planet_data.orbit_phi_inD = 0;
    	planet_data.speed         = (float)getRandInt(PLANET_SPEED_MIN, PLANET_SPEED_MAX) / (float)orbit_radius;


        TextureOb* texOb 	    = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.planet_texOb_pList); 
        TextureOb* texOb_atmosphere = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.atmosphere_texOb_pList); 
        
        unsigned long int population = getRandInt(1000, 4000);
        
        Planet* planet = new Planet(subtype_id, 
        			    texOb, 
        			    texOb_atmosphere, 
        			    pTo_SPHERE_MESH, 
        			    planet_data,
        			    population);
	 
        return planet;        
}
