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

#pragma once


#include <builder/spaceobjects/BaseVehicleBuilder.hpp>

#include <types/IdType.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

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
        ShipBuilder();
        ~ShipBuilder();
        
        Ship* createTemplate(IDTYPE id = NONE_ID) const;
        Ship* create(TYPE::RACE, TYPE::ENTITY, int, int) const;
        Ship* create() const;
                       
    private:
        void createInternals(Ship*, TYPE::RACE, TYPE::ENTITY, int, int) const;
}; 

        


