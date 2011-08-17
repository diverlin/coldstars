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


#ifndef PLAYER_H
#define PLAYER_H


class PlayerInstance 
{
   public:
     int type_id, id;
  
     Ship* pTo_ship;
     Npc* pTo_npc;

     bool in_SPACE;
     bool is_SCANNING;
     bool in_WORLDMAP;

     bool weapon_slot_1_SELECTED;
     bool weapon_slot_2_SELECTED;
     bool weapon_slot_3_SELECTED;
     bool weapon_slot_4_SELECTED;
     bool weapon_slot_5_SELECTED;

     bool garpun_slot_SELECTED;
     
     bool ships_info_SHOW;
     bool planets_info_SHOW;
     bool planets_orbit_SHOW;

     bool radar_range_SHOW;
        
     PlayerInstance();
     ~PlayerInstance();
     
     void setShip(Ship* _pTo_ship);

     void update_inSpace_inDynamic();
};

#endif 



        
