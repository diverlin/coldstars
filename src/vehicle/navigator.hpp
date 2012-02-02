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
      		Navigator(Vehicle*);
      		~Navigator();
      
      		void setStaticTargetCoords(vec2f);
      
      		template <typename TARGET_TYPE>
      		void setTarget(TARGET_TYPE*, int);      
                     
                TargetObject* getTargetOb() const;     
                Planet* getTargetPlanet() const;  
                
                int getTargetTypeId() const;
                
               
      		bool checkEchievement();
      		bool getDockingPermission();               
       	
        	void resetTarget();
        	
        	void update_inSpace_inStatic();
        	void update_inSpace_inDynamic();
                
                void drawPath();

      	private:
      		Vehicle* owner_vehicle;
      		TargetObject* targetOb;

		vec2f target_pos;
		
		int action_id;
		float target_distance;   
		vec2f target_offset;

        	std::vector<vec2f> path_vec;
        	std::vector<float> angle_inD_vec;

                                        std::vector<vec2f> c1c2_vec;   // debug
                                        std::vector<vec2f> rc_vec;     // debug
                                        std::vector<vec2f> k1k2_vec;   // debug
                                        std::vector<vec2f> k_vec;      // debug
                                        std::vector<vec2f> target_vec; // debug
                                
        	bool direction_list_END;
        	int move_it;
   
                PathVisual visual_path;
                                        PathVisual visual_c1c2;      // debug
                                        PathVisual visual_rc;        // debug
                                        PathVisual visual_k1k2;      // debug
                                        PathVisual visual_k;         // debug
                                        PathVisual visual_target;    // debug
                void updatePosition();
                       	
                bool targetValidation();
	
	        bool updateTargetCoord();
	        void calcPath();
			vec2f calcRoundPath();
			void calcDirectPath(vec2f);
		                				
		bool targetObValidation_dip1() const;
		bool targetObValidation_dip2() const;
		
		void defineDistance(int);
};


#endif
