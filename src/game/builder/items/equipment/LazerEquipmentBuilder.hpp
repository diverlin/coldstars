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

#ifndef LAZEREQUIPMENTBUILDER_HPP
#define LAZEREQUIPMENTBUILDER_HPP

#include <types/MyInt.hpp>
#include <types/RaceTypes.hpp>
#include <common/constants.hpp>

class LazerEquipment;

class LazerEquipmentBuilder
{
	public:
		static LazerEquipmentBuilder& Instance();
		~LazerEquipmentBuilder();

        LazerEquipment* GetNewLazerEquipmentTemplate(INTLONGEST id = NONE_ID) const; 
        LazerEquipment* GetNewLazerEquipment(int tech_level = NONE_ID, TYPE::RACE race_id = TYPE::RACE::NONE_ID, int damage_orig = NONE_ID, int radius_orig = NONE_ID) const;
        	 		                
    private:
		LazerEquipmentBuilder() {};
		LazerEquipmentBuilder(const LazerEquipmentBuilder&) = delete;
		LazerEquipmentBuilder& operator=(const LazerEquipmentBuilder&) = delete;

        void CreateNewInternals(LazerEquipment*, int, TYPE::RACE, int, int) const;
}; 

#endif 
    

        


