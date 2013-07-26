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


#ifndef FREEZEREQUIPMENTBUILDER_HPP
#define FREEZEREQUIPMENTBUILDER_HPP

#include <common/constants.hpp>
#include <common/RaceTypes.hpp>

class FreezerEquipment;

class FreezerEquipmentBuilder
{
	public:
		static FreezerEquipmentBuilder& Instance();
		~FreezerEquipmentBuilder();
		
        FreezerEquipment* GetNewFreezerEquipmentTemplate(unsigned long int id = NONE_ID) const; 
        FreezerEquipment* GetNewFreezerEquipment(int tech_level = NONE_ID, RACE::TYPE race_id = RACE::TYPE::NONE_ID, int freeze_orig = NONE_ID) const;
        	 		                
    private:
		FreezerEquipmentBuilder() {};
		FreezerEquipmentBuilder(const FreezerEquipmentBuilder&) = delete;
		FreezerEquipmentBuilder& operator=(const FreezerEquipmentBuilder&) = delete;

        void CreateNewInternals(FreezerEquipment*, int, RACE::TYPE, int) const;
}; 

#endif 
    

        


