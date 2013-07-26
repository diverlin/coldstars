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

#ifndef DROIDEQUIPMENTBUILDER_HPP
#define DROIDEQUIPMENTBUILDER_HPP

#include <common/constants.hpp>
#include <common/RaceTypes.hpp>

class DroidEquipment;

class DroidEquipmentBuilder
{
	public:
		static DroidEquipmentBuilder& Instance();
		~DroidEquipmentBuilder();

        DroidEquipment* GetNewDroidEquipmentTemplate(unsigned long int id = NONE_ID) const; 
        DroidEquipment* GetNewDroidEquipment(int tech_level = NONE_ID, RACE::TYPE race_id = RACE::TYPE::NONE_ID, int repair_orig = NONE_ID) const;
        	 		                
    private:
		DroidEquipmentBuilder() {};
		DroidEquipmentBuilder(const DroidEquipmentBuilder&) = delete;
		DroidEquipmentBuilder& operator=(const DroidEquipmentBuilder&) = delete;

        void CreateNewInternals(DroidEquipment*, int, RACE::TYPE, int) const;
}; 

#endif 
    

        


