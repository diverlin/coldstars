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


#include "player.h"

PlayerInstance :: PlayerInstance()
{ 
    type_id = PLAYER_ID;
    id = g_ENTITY_ID_GENERATOR.returnNextId(); 

    pTo_ship       = NULL;

    weapon_slot_1_SELECTED = false;
    weapon_slot_2_SELECTED = false;
    weapon_slot_3_SELECTED = false;
    weapon_slot_4_SELECTED = false;
    weapon_slot_5_SELECTED = false;

    garpun_slot_SELECTED = false; 
    
    ships_info_SHOW = false;
    planets_info_SHOW = false;
    planets_orbit_SHOW = false;

    radar_range_SHOW = false;
     
    in_SPACE    = true;
    is_SCANNING = false;
    in_WORLDMAP = false;
}
    
PlayerInstance :: ~PlayerInstance()
{}  
    


void PlayerInstance :: setShip(Ship* _pTo_ship)
{
    pTo_ship = _pTo_ship;

    pTo_ship->pTo_playerOwner = this;
    pTo_npc = pTo_ship->getNpc();
    pTo_ship->getNpc()->extractTheMind();

}

    
void PlayerInstance :: update_inSpace_inDynamic()
{
     if (pTo_ship->in_SPACE == false)
        in_SPACE = false;

     //if (pTo_ship->pTo_npc_owner->pTo_scanShip != NULL)
        //is_SCANNING = true;
}




        
