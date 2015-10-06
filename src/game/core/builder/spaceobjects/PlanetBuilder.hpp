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

#include <types/IdType.hpp>


class Planet;

namespace ENTITY
{
    namespace PLANET
    {
        const int DISTANCE_MIN = 400;
        const int DISTANCE_MAX = 500;
        const int SCALE_MIN = 100;
        const int SCALE_MAX = 190;
        const int SPEED_MIN = 40;
        const int SPEED_MAX = 50;
        const int POPULATION_MIN = 6000;
        const int POPULATION_MAX = 20000;
    }
}    
    

class PlanetBuilder
{
    public:
        PlanetBuilder();
        ~PlanetBuilder();

        Planet* createTemplate(ID id = NONE_ID) const;
        Planet* create(float) const;
                                     
    private:
        void createInternals(Planet*, float) const;
}; 
