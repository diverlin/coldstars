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


#ifndef DRIVEEQUIPMENT_H
#define DRIVEEQUIPMENT_H


class DriveEquipment :  public CommonForEquipment
{
	public:
      		DriveEquipment();
      		DriveEquipment(TextureOb* pTo_itemTexOb, 
      			       int speed_orig, 
      			       int hyper_orig, 
      			       EquipmentCommonData _common_data);
      			       
      		~DriveEquipment();

		int getSpeed() const;
		int getHyper() const;

      		bool insertModule(DriveModule* pTo_driveModule);
      		
      	private:
      	      	int speed_orig;
      		int speed_add;
      		int speed;

      		int hyper_orig;
      		int hyper_add;
      		int hyper;
      		
      		std::vector<DriveModule*> modules_pList;
      		
     		// particle system settings // MAKE AS STRUCTURE!
      	      	TextureOb* pTo_particleTexOb;
      	      	int particle_num;
      		float particle_size;
      		float particle_velocity;
      		float particle_alpha_start;
      		float particle_alpha_end;
      		float particle_d_alpha;

      		void countPrice();
      		void updatePropetries();
 		void virtual updateOwnerPropetries();
      		
     		void virtual addUniqueInfo();
           	std::string getSpeedStr();
           	std::string getHyperStr();      	
};

DriveEquipment* driveEquipmentGenerator(int race_id, int revision_id = -1);

#endif 




