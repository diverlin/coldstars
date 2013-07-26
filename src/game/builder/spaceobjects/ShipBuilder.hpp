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

#ifndef SHIPBUILDER_HPP
#define SHIPBUILDER_HPP

#include <builder/spaceobjects/BaseVehicleBuilder.hpp>

#include <types/MyInt.hpp>
#include <types/RaceTypes.hpp>

#include <common/constants.hpp>


class Ship;

namespace ENTITY
{
	namespace SHIP
	{
		const int SCALE_MIN = 100;
		const int SCALE_MAX = 200;
	}
}

class ShipBuilder : public BaseVehicleBuilder
{
	public:
		static ShipBuilder& Instance();
		~ShipBuilder();
		
		Ship* GetNewShipTemplate(INTLONGEST id = NONE_ID) const;
        Ship* GetNewShip(TYPE::RACE, TYPE::ENTITY, int, int) const;        
        Ship* GetNewShip() const;   
                       
    private:
        ShipBuilder() {};
        ShipBuilder(const ShipBuilder&) = delete; 
        ShipBuilder& operator=(const ShipBuilder&) = delete;
            
        void CreateNewInternals(Ship*, TYPE::RACE, TYPE::ENTITY, int, int) const;  
}; 

#endif 
    

        


