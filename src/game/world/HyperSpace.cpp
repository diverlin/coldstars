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

#include "HyperSpace.hpp"
#include "starsystem.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../common/constants.hpp"
#include <math/rand.hpp>

HyperSpace::HyperSpace()
{}

HyperSpace::~HyperSpace()
{}      

void HyperSpace::AddVehicle(Vehicle* vehicle)
{
    vehicle->SetPlaceTypeId(TYPE::PLACE::HYPER_SPACE_ID);
    VEHICLE_vec.push_back(vehicle);  
}

bool HyperSpace::IsVehicleHere(int id) const
{
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {               
        if (VEHICLE_vec[i]->GetId() == id)
        {
            return true;
        }
    }
        
    return false;
}    

void HyperSpace::PostHyperJumpEvent(StarSystem* starsystem)
{
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    {             
        VEHICLE_vec[i]->GetComplexDrive().ResetTarget(); 
        
        glm::vec3 center(getRandXYVec3f(500, 900, DEFAULT_ENTITY_ZPOS)); // get correct pos
        glm::vec3 angle(0,0,getRandInt(0, 360));  
        starsystem->AddVehicle(VEHICLE_vec[i], center, angle, VEHICLE_vec[i]->GetParent());  
    }
          
    VEHICLE_vec.clear();  
}
