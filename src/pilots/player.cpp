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


#include "player.hpp"


void WeaponSelector :: reset()
{
	slot_1 = false;
     	slot_2 = false;
     	slot_3 = false;
     	slot_4 = false;
     	slot_5 = false;
}
     		
//void WeaponSlotSelector :: set(bool _slot_1 = true, 
			       //bool _slot_2 = true, 
			       //bool _slot_3 = true, 
			       //bool _slot_4 = true, 
			       //bool _slot_5 = true)
//{
	//slot_1 = _slot_1;
     	//slot_2 = _slot_2;
     	//slot_3 = _slot_3;
     	//slot_4 = _slot_4;
     	//slot_5 = _slot_5;
//}




PlayerInstance :: PlayerInstance()
{ 
    	type_id = PLAYER_ID;
    	id = g_ENTITY_ID_GENERATOR.returnNextId(); 

    	ship       = NULL;


	
    	//weapon_slot_1_SELECTED = false;
    	//weapon_slot_2_SELECTED = false;
    	//weapon_slot_3_SELECTED = false;
    	//weapon_slot_4_SELECTED = false;
    	//weapon_slot_5_SELECTED = false;

    	garpun_slot_SELECTED = false; 
    
    	ships_info_SHOW = false;
    	planets_info_SHOW = false;
    	planets_orbit_SHOW = false;

    	radar_range_SHOW = false;
     
    	is_SCANNING = false;
    	show_WORLDMAP = false;
    	
    	cursor = new Cursor();
}
    
PlayerInstance :: ~PlayerInstance()
{}  
    
    
void PlayerInstance :: setActiveStarSystem(StarSystem* _ss_active) 
{ 
	// The starsystem were at least one player exist is living with true simulation
	ss_active->setDetailedSimulation(false);
	ss_active = _ss_active; 
	ss_active->setDetailedSimulation(true);	
}	


Ship* PlayerInstance :: getShip() 		    { return ship; }
Npc* PlayerInstance :: getPilot() 		    { return npc; }
StarSystem* PlayerInstance :: getActiveStarSystem() { return ss_active; }	
Cursor* PlayerInstance :: getCursor()               { return cursor; }

void PlayerInstance :: bindShip(Ship* _ship)
{
    	ship = _ship;

    	//ship->pTo_playerOwner = this;
    	npc = ship->getNpc();
    	ship->getNpc()->extractTheMind();

}

    
void PlayerInstance :: update_inSpace_inDynamic()
{
     if (ship->in_SPACE == false)       // FUUUUUUUUUUUUUUUUUUUUUU must be imprroved
        npc->setPlaceTypeId(PLANET_TYPE_ID);

     //if (pTo_ship->pTo_npc_owner->pTo_scanShip != NULL)
        //is_SCANNING = true;
}




        
