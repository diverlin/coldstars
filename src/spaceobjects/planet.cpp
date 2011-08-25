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


#include "planet.h"

Planet :: Planet(int _subtype_id, 
		 TextureOb* _texOb, 
		 TextureOb* _pTo_atmoshereTexOb, 
		 ObjMeshInstance* _mesh, 
		 float _size, 
		 float _orbit_center_x, 
		 float _orbit_center_y, 
		 int _radius_A, 
		 int _radius_B, 
		 int _orbit_phi_inD,
		 float _speed)
{ 
      id = g_ENTITY_ID_GENERATOR.returnNextId();
      type_id = PLANET_ID;
      subtype_id = _subtype_id;
      
       CommonForPlanet_init(_texOb, 
    	   		    _mesh, 
    	   	            _size, 
    	   		    _orbit_center_x, 
    	   		    _orbit_center_y, 
    	   		    _radius_A,
    	   		    _radius_B, 
    	   		    _orbit_phi_inD,
    	   		    _speed);

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
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "PLANET";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(starsystem->id);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
}


void Planet :: renderInfo()
{  
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y ); 
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

        


