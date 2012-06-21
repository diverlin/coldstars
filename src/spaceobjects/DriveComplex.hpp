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

      		void SetTarget(BaseGameEntity*, int);       
      		void SetStaticTargetCoords(vec2f);
      		
                void SetDriveSlot(ItemSlot* drive_slot) { this->drive_slot = drive_slot; };
                void SetBakSlot(ItemSlot* bak_slot)     { this->bak_slot = bak_slot; };
                
      		ItemSlot* GetDriveSlot() const { return drive_slot; };
        	ItemSlot* GetBakSlot()   const { return bak_slot; };
                  
                BaseGameEntity* GetTarget() const { return target; };                
             
      		bool CheckTargetEchievement();
      		bool GetDockingPermission();               
       	
        	void ResetTarget();

        	void UpdatePath();
                void UpdatePosition();
                
                void DrawPath();
                void RenderTrail();

      	private:
                ItemSlot* drive_slot;
        	ItemSlot* bak_slot;

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
                       	
                bool ValidateTarget() const;
	
	        bool UpdateTargetCoord();
	        void CalcPath();
			vec2f CalcRoundPath();
			void CalcDirectPath(vec2f);

		void DefineDistance(int);
};


#endif
