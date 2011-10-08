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


#ifndef NAVIGATOR_H
#define NAVIGATOR_H


class Navigator
{
	public:
      		Navigator(Ship* _ship);
      		~Navigator();
      
      		void setStaticTargetCoords(vec2f _target_pos);
      
      		void setTargetPlanet(Planet* _target_planet); 
      		void setTargetShip(Ship* _target_ship);    
      		void setTargetStarSystem(StarSystem* _target_starsystem);
                void setFollowingTypeID(int);
                      
                Planet* getTargetPlanet() const;
                vec2f getTargetPos() const;
                int getFollowingTypeID() const;
                
      		void removeTargetPlanet();
      		void removeTargetShip(); 
      		void removeTargetStarSystem();  
      
     		bool updateTargetCoords();
      
      		bool checkDocking();
      		bool getDockingPermission();               
               
        	void updatePosition();
      	private:
      		Ship* ship;
      		
      		Planet*     target_planet;
		Ship*       target_ship;
		StarSystem* target_starsystem;
		
		vec2f target_pos;
		vec2f* pTo_target_pos;
			
		int docking_radius;   
                
                int following_TYPE_ID;   
                
                //////// TARGET COORDINATES //////
        	//self.Gl_LIST_direction_ID = None
        	std::vector<float> direction_x_list;
        	std::vector<float> direction_y_list;
        	std::vector<float> angle_inD_list;

        	int len_direction_list;
        	bool direction_list_END;
        	int move_it;
        	//////////////////////////////////
                
                void calculateDetaledWayToPosition();
};


#endif
