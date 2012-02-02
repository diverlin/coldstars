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




class Player 
{
   	public:
     		WeaponSelector weapon_selector;
     		
    		Player();
     		~Player();
     
          	void setStarSystem(StarSystem*);
          	void setScanFlag(bool);
          	void setWorldMapShowFlag(bool);
          	
          	void setShowAllOrbit(bool);
          	void setShowAllPath(bool);
          	void setShowRadarRange(bool);
          	void setShowGrappleRange(bool);
          	          	
          	bool getAlive() const;
          	bool getWorldMapShowFlag() const;
          	bool getScanFlag() const;
          	bool getShowAllOrbit() const;
          	bool getShowAllPath() const;
          	bool getShowRadarRange() const;
          	bool getShowGrappleRange() const;
          	          	
          	Vehicle* getVehicle(); 	     
		Npc* getPilot(); 	     
		StarSystem* getStarSystem(); 	
		Cursor* getCursor();         
          	int getPlaceTypeId() const;
          		
     		void update_global();     
     		void bindNpc(Npc*);
     		     	
     	private:
     	   	bool is_alive;
     	   		
     	     	int type_id, id;
     	     	int place_type_id;
     	     		
     	     	Vehicle* vehicle;
     	     	Npc*     npc;
     	     	
     	     	StarSystem* starsystem;
     	     	Cursor* cursor;
     	     	
     	     	ControlWord control;  
     	     	
     	     	bool show_all_orbit;
     	     	bool show_all_path;
     	     	bool show_radar_range;
     	     	bool show_grapple_range;
};

#endif 



        
