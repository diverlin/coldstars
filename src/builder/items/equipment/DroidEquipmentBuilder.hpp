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

#ifndef DROIDEQUIPMENTBUILDER_H
#define DROIDEQUIPMENTBUILDER_H

#include "../../../items/equipment/DroidEquipment.hpp"
#include "../../../common/constants.hpp"

class DroidEquipmentBuilder
{
	public:
		static DroidEquipmentBuilder& Instance();
		~DroidEquipmentBuilder();

        	void CreateNewDroidEquipment(int id = NONE_ID); 
                void CreateNewInternals(int race_id, int revision_id = -1);
                DroidEquipment* GetDroidEquipment() const { return droid_equipment; };
        	 		                
        private:
                DroidEquipment* droid_equipment;
                
		DroidEquipmentBuilder() {};
		DroidEquipmentBuilder(const DroidEquipmentBuilder&) = delete;
		DroidEquipmentBuilder& operator=(const DroidEquipmentBuilder&) = delete;
}; 

#endif 
    

        


