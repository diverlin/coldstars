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

#ifndef BAKEQUIPMENTBUILDER_H
#define BAKEQUIPMENTBUILDER_H

#include "../../../items/equipment/BakEquipment.hpp"
#include "../../../common/constants.hpp"

class BakEquipmentBuilder
{
	public:
		static BakEquipmentBuilder& Instance();
		~BakEquipmentBuilder();

        	void CreateNewBakEquipment(int id = NONE_ID); 
                void CreateNewInternals();
                BakEquipment* GetBakEquipment() const { return bak_equipment; };
        	 		                
        private:
                BakEquipment* bak_equipment;
                
		BakEquipmentBuilder() {};
		BakEquipmentBuilder(const BakEquipmentBuilder&) = delete;
		BakEquipmentBuilder& operator=(const BakEquipmentBuilder&) = delete;
}; 



#endif 
    

        


