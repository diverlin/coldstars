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
      
      		void setTargetPlanet(Planet*); 
      		void setTargetShip(Ship*, int);    
      		void setTargetStarSystem(StarSystem*);
                      
                Planet* getTargetPlanet() const;  // ??
                vec2f getTargetPos() const;
                int getFollowingTypeId() const;
                
    		bool updateDynamicTargetCoords();
      
      		bool checkEchievement();
      		bool getDockingPermission();               
               
        	void updatePosition();
        	
        	void removeTarget();
        	
      	private:
      		Ship* ship_owner;
      		
      		Planet*     target_planet;
		Ship*       target_ship;
		StarSystem* target_starsystem;
		
		vec2f target_pos;
		vec2f* pTo_target_pos;
			
		float echievement_radius;   
		float offset;
                
                int following_type_id;   

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
                
                //template <typename TARGET>
		//void checkHuperJumpNecessary(TARGET _target);
};


#endif
