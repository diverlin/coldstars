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
		 TextureOb* _pTo_atmoshereTexOb, 
		 ObjMeshInstance* _mesh, 
		 PlanetData _planet_data)
{ 
      	type_id = PLANET_ID;
      	subtype_id = _subtype_id;
      
      	CommonForPlanet_init(_texOb, 
    	   		     _mesh, 
			     _planet_data);

      	pTo_atmosphereTexOb = _pTo_atmoshereTexOb;

      	pTo_kosmoport = NULL;
      	pTo_land      = NULL;
      
      	if (subtype_id == INHABITED_ID)
         	createKosmoport();
      	if (subtype_id == UNINHABITED_ID)
         	createLand();
}

    
Planet :: ~Planet()
{}
    
   
       

void Planet :: update_inSpace_inDynamic()
{      
     	updatePosition();  
}
  


void Planet :: update_inSpace_inStatic()
{      
     	if (subtype_id == INHABITED_ID)
        	for (unsigned int ni = 0; ni < pTo_kosmoport->NPC_pList.size(); ni++)
            		pTo_kosmoport->NPC_pList[ni]->thinkCommon_inKosmoport_inStatic();

     	if (subtype_id == UNINHABITED_ID)
        	for (unsigned int ni = 0; ni < pTo_kosmoport->NPC_pList.size(); ni++)
            		pTo_kosmoport->NPC_pList[ni]->thinkCommon_inLand_inStatic();
}
         

void Planet :: updateInfo()
{
	info.clear();

    	info.addTitleStr("PLANET");

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(id) + " / " + int2str(starsystem->id));
}


void Planet :: renderInfo()
{  
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        
void Planet :: createKosmoport()
{   
    	pTo_kosmoport = new Kosmoport(RACE_0_ID);   
}


void Planet :: createLand()
{   
    	pTo_land = new Land();   
}


//// ******* TRANSITION ******* 
bool Planet :: addShip(Ship* _pTo_ship)
{
     	if (subtype_id == INHABITED_ID)
         	return pTo_kosmoport->addShip(_pTo_ship);
     	if (subtype_id == UNINHABITED_ID)
         	return pTo_land->addShip(_pTo_ship);
}

bool Planet :: addNpc(Npc* _pTo_npc)
{
     	if (subtype_id == INHABITED_ID)
         	return pTo_kosmoport->addNpc(_pTo_npc);
     	if (subtype_id == UNINHABITED_ID)
         	return pTo_land->addNpc(_pTo_npc);
}

bool Planet :: removeShipById(int _id)
{
     	if (subtype_id == INHABITED_ID)
         	return pTo_kosmoport->removeShipById(_id);
     	if (subtype_id == UNINHABITED_ID)
         	return pTo_land->removeShipById(_id);
}

bool Planet :: removeNpcById(int _id)
{
     	if (subtype_id == INHABITED_ID)
         	return pTo_kosmoport->removeNpcById(_id);
     	if (subtype_id == UNINHABITED_ID)
         	return pTo_land->removeNpcById(_id);
}
//// ******* TRANSITION ******* 



bool Planet :: getPermissionToLand()
{
     	if (subtype_id == INHABITED_ID)
     	{
        	if (pTo_kosmoport->pTo_angar->returnFreelandingAreaNum() > 0)
            		return true;
        	else
            		return false;       
     	}
     	if (subtype_id == UNINHABITED_ID)
        	return true;
}

        


Planet* createPlanet(int orbit_radius)
{
        int subtype_id   = INHABITED_ID;
        
	PlanetData planet_data;
	
	planet_data.scale         = randIntInRange(PLANET_SIZE_MIN, PLANET_SIZE_MAX);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = orbit_radius;
    	planet_data.radius_B      = orbit_radius; 
    	planet_data.orbit_phi_inD = 0;
    	planet_data.speed         = (float)randIntInRange(PLANET_SPEED_MIN, PLANET_SPEED_MAX) / (float)orbit_radius;


        TextureOb* planetTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.planet_texOb_pList); 
        TextureOb* atmosphereTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.atmosphere_texOb_pList); 
        
        Planet* planet = new Planet(subtype_id, 
        			    planetTexOb, 
        			    atmosphereTexOb, 
        			    pTo_SPHERE_MESH, 
        			    planet_data);
	 
        return planet;        
}
