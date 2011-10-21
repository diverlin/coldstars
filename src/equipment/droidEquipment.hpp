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


#ifndef DROIDEQUIPMENT_H
#define DROIDEQUIPMENT_H


class DroidEquipment : public CommonForEquipment
{
   	public: 
      		DroidEquipment();
     		DroidEquipment(TextureOb* _texOb_item, 
     			       int _repair_orig, 
     			       EquipmentCommonData _common_data);
     			       
      		~DroidEquipment();

		int getRepair() const;
		
      		bool insertModule(DroidModule*);
      		
      	private:
      		int repair_orig;
      		int repair_add;
      		int repair;

      	      	std::vector<DroidModule*> modules_vec;

      		void countPrice();
      		void updatePropetries();
      		void virtual updateOwnerPropetries();
      		
     		void virtual addUniqueInfo();
       		std::string getRepairStr();
};

DroidEquipment* droidEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
