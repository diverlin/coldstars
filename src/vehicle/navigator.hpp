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
      		Navigator(Ship*);
      		~Navigator();
      
      		void setStaticTargetCoords(vec2f);
      
      		template <typename TARGET_TYPE>
      		void setTarget(TARGET_TYPE*, int);
      		 
      		void forceJump(StarSystem*);
                      
                Planet* getTargetPlanet() const;  
                StarSystem* getTargetStarSystem() const;
                
                int getTargetTypeId() const;
                
               
      		bool checkEchievement();
      		bool getDockingPermission();               
       	
        	void resetTarget();
        	
        	void update_inSpace_inStatic();
        	void update_inSpace_inDynamic();
        	        	
      	private:
      		Ship* ship_owner;
      		TargetObject* targetOb;
      		
		StarSystem* target_starsystem;
		
		vec2f target_pos;
			
		int action_id;
		float target_distance;   
		vec2f target_offset;

        	std::vector<vec2f> path_vec;
        	std::vector<float> angle_inD_vec;

        	bool direction_list_END;
        	int move_it;
   
                void updatePosition();
                       	
                void targetValidation();
		void isJumpNeeded();
	
	        void updateTargetCoord();
		void calcDetaledWay();
		void calcDetaledWay2();
				
		bool targetObValidation_dip1() const;
		bool targetObValidation_dip2() const;
};


#endif
