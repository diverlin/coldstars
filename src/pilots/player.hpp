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

class WeaponSelector
{
	public:
    		bool slot_1;
     		bool slot_2;
     		bool slot_3;
     		bool slot_4;
     		bool slot_5;
     	
     		void reset();
     		//void set(bool, bool, bool, bool, bool);
};


class PlayerInstance 
{
   	public:
    		bool is_SCANNING;
     		bool show_WORLDMAP;

    		
     	     	bool garpun_slot_SELECTED;
     
     		bool ships_info_SHOW;
     		bool planets_info_SHOW;
     		bool planets_orbit_SHOW;

     		bool radar_range_SHOW;
     		
    		PlayerInstance();
     		~PlayerInstance();
     
          	void setActiveStarSystem(StarSystem*);
          		
        	Ship* getShip();
   		Npc* getPilot();
     		StarSystem* getActiveStarSystem();
     		Cursor* getCursor();
     		     
     		void bindShip(Ship*);
     		void update_inSpace_inDynamic();
     	
     	private:
     	     	int type_id, id;
     	     		
     	     	Ship* ship;
     	     	Npc* npc;
     	     	
     	     	StarSystem* ss_active;
     	     	Cursor* cursor;
};

#endif 



        
