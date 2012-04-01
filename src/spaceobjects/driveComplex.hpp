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


#ifndef DRIVECOMPLEX_H
#define DRIVECOMPLEX_H


class DriveComplex
{
	public:
      		DriveComplex(Vehicle*);
      		~DriveComplex();

      		void setTarget(BaseGameEntity*, int);       
      		void setStaticTargetCoords(vec2f);
      		
      		ItemSlot& GetDriveSlot();
        	ItemSlot& GetBakSlot();
                  
                BaseGameEntity* getTarget() const;                
             
      		bool checkEchievement();
      		bool getDockingPermission();               
       	
        	void resetTarget();
        	
        	void Update_inSpace_inStatic();
        	void update_inSpace_inDynamic();
                
                void drawPath();
                void renderTrail();

      	private:
                ItemSlot drive_slot;
        	ItemSlot bak_slot;
        	
      		Vehicle* owner_vehicle;
      		BaseGameEntity* target;

		TrailEffect* drive_trail; 
		
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
                       	
                bool validateTarget() const;
	
	        bool updateTargetCoord();
	        void calcPath();
			vec2f calcRoundPath();
			void calcDirectPath(vec2f);
		                				
		void defineDistance(int);
};


#endif
