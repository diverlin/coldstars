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

#ifndef RADAREQUIPMENTBUILDER_HPP
#define RADAREQUIPMENTBUILDER_HPP

#include <common/constants.hpp>
#include <types/RaceTypes.hpp>

class RadarEquipment;

class RadarEquipmentBuilder
{
	public:
		static RadarEquipmentBuilder& Instance();
		~RadarEquipmentBuilder();

        RadarEquipment* GetNewRadarEquipmentTemplate(INTLONGEST id = NONE_ID) const; 
        RadarEquipment* GetNewRadarEquipment(int tech_level = NONE_ID, TYPE::RACE race_id = TYPE::RACE::NONE_ID, int radius_orig = NONE_ID) const;
        	 		                
    private:
		RadarEquipmentBuilder() {};
		RadarEquipmentBuilder(const RadarEquipmentBuilder&) = delete;
		RadarEquipmentBuilder& operator=(const RadarEquipmentBuilder&) = delete;

        void CreateNewInternals(RadarEquipment*, int, TYPE::RACE, int) const;
}; 

#endif 
    

        


