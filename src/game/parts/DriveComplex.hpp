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

class Vehicle;
class DriveEffect;
class ItemSlot; 
#include "../render/PathVisual.hpp" 
#include "../math/myVector.hpp" 
class BaseSpaceEntity;

class DriveComplex
{
	public:
      		DriveComplex();
      		~DriveComplex();
      		
      		void SetOwnerVehicle(Vehicle* owner_vehicle) { this->owner_vehicle = owner_vehicle; };
      		void SetDriveEffect(DriveEffect* drive_effect) { this->drive_effect = drive_effect; };
      		      		
                void SetDriveSlot(ItemSlot* drive_slot) { this->drive_slot = drive_slot; };
                void SetBakSlot(ItemSlot* bak_slot)     { this->bak_slot = bak_slot; };

      		void SetTarget(BaseSpaceEntity*, int);       
      		void SetStaticTargetCoords(const Vec3<float>&);

		int GetActionId() const { return action_id; };
      		DriveEffect* GetDriveEffect() const { return drive_effect; };
      		      		                
      		ItemSlot* GetDriveSlot() const { return drive_slot; };
        	ItemSlot* GetBakSlot()   const { return bak_slot; };
                  
                BaseSpaceEntity* GetTarget() const { return target; };                
    			        
    		bool PathExists() const;
    		
      		bool CheckTargetEchievement();
      		bool GetDockingPermission();               
       	
        	void ResetTarget();

    		//void CalcAcceleratedPath(); // used for hyper jump effect
        	void UpdatePath();
                void UpdatePosition();

                void UpdatePathVisualisation();                
                void DrawPath();
    		
      	private:
                ItemSlot* drive_slot;
        	ItemSlot* bak_slot;

      		Vehicle* owner_vehicle;
      		BaseSpaceEntity* target;

		DriveEffect* drive_effect; 

		Vec3<float> target_pos;
		
		int action_id;
		float target_distance;   
		Vec3<float> target_offset;

		//std::vector<Vec2<float>> debug_midLeft_vec;
        	std::vector<Vec3<float>> path_center_vec;
        	std::vector<float> angle_inD_vec;

                bool has_target;
        	bool direction_list_END;
        	int move_it;
   
                PathVisual visual_center_path;
                PathVisual visual_center_turn;
                //PathVisual visual_debug_midLeft_path;

		void ClearPath();
   		void CalcPath();      
                bool ValidateTarget() const;
	
	        void UpdateDynamicTargetCoord();

		void DefineDistance();
};


#endif
