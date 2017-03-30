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
#include <core/spaceobject/Vehicle.hpp>
#include "../common/constants.hpp"

#include <core/model/spaceobject/Vehicle.hpp>

#include <meti/RandUtils.hpp>

namespace control {

void HyperSpace::add(Vehicle* vehicle)
{
    vehicle->model()->setPlace(place::Type::HYPER);
    m_vehicles.push_back(vehicle);
}

bool HyperSpace::isHere(int id) const
{
    for (Vehicle* vehicle: m_vehicles) {
        if (vehicle->id() == id) {
            return true;
        }
    }        
    return false;
}    

void HyperSpace::postHyperJumpEvent(Starsystem* starsystem)
{
//    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
//    {
//        VEHICLE_vec[i]->driveComplex().ResetTarget();
        
//        glm::vec3 center(meti::getRandXYVec3f(500, 900, DEFAULT_ENTITY_ZPOS)); // get correct pos
//        glm::vec3 angle(0,0,meti::getRandInt(360));
//        starsystem->add(VEHICLE_vec[i], center, angle, VEHICLE_vec[i]->parent());
//    }
          
//    VEHICLE_vec.clear();
}

} // namespace control
