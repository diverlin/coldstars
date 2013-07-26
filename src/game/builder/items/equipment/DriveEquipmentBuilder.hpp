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

#ifndef DRIVEEQUIPMENTBUILDER_HPP
#define DRIVEEQUIPMENTBUILDER_HPP

#include <common/constants.hpp>
#include <common/RaceTypes.hpp>

class DriveEquipment;

class DriveEquipmentBuilder
{
	public:
		static DriveEquipmentBuilder& Instance();
		~DriveEquipmentBuilder();

        DriveEquipment* GetNewDriveEquipmentTemplate(unsigned long int id = NONE_ID) const; 
        DriveEquipment* GetNewDriveEquipment(int tech_level = NONE_ID, TYPE::RACE race_id = TYPE::RACE::NONE_ID, int speed_orig = NONE_ID, int hyper_orig = NONE_ID) const;
        	 		                
    private:
		DriveEquipmentBuilder() {};
		DriveEquipmentBuilder(const DriveEquipmentBuilder&) = delete;
		DriveEquipmentBuilder& operator=(const DriveEquipmentBuilder&) = delete;

        void CreateNewInternals(DriveEquipment*, int, TYPE::RACE, int, int) const;
}; 

#endif 
    

        


