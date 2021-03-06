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


#ifndef SPACESTATIONBUILDER_HPP
#define SPACESTATIONBUILDER_HPP

#include <builder/spaceobjects/BaseVehicleBuilder.hpp>
#include <types/MyInt.hpp>

class SpaceStation;

    
namespace ENTITY
{
    namespace SPACESTATION
    {
        const int SCALE_MIN = 200;
        const int SCALE_MAX = 300;
        
        const int MASS_MIN = 1000;
        const int MASS_MAX = 2000;
    }
}

class SpaceStationBuilder : public BaseVehicleBuilder
{
    public:
        static SpaceStationBuilder& Instance();
        ~SpaceStationBuilder();
        
        SpaceStation* GetNewSpaceStationTemplate(INTLONGEST id = NONE_ID) const;                            
        SpaceStation* GetNewSpaceStation() const;         
       
    private:
        SpaceStationBuilder() {};       
        SpaceStationBuilder(const SpaceStationBuilder&) = delete; 
        SpaceStationBuilder& operator=(const SpaceStationBuilder&) = delete;

        void CreateNewInternals(SpaceStation*) const;   
}; 


#endif 
    

        


