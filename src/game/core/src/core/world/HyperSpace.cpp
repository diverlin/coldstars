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
//#include "starsystem.hpp"
//#include "../common/constants.hpp"

#include <core/descriptor/world/HyperSpace.hpp>
#include <core/model/world/HyperSpace.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/model/spaceobject/Vehicle.hpp>

//#include <meti/RandUtils.hpp>

namespace core {
namespace control {

HyperSpace::HyperSpace(descriptor::HyperSpace* descr, model::HyperSpace* model)
    :
      Base(descr, model)
    , m_descriptor_hyperspace(descr)
    , m_model_hyperspace(model)
{

}

void
HyperSpace::add(Vehicle* vehicle)
{
    vehicle->resetStarSystem();
    vehicle->setPlace(place::Type::HYPERSPACE);
    m_vehicles.add(vehicle);

    model()->addVehicle(vehicle->id());
}


void
HyperSpace::remove(Vehicle* vehicle)
{
    model()->removeVehicle(vehicle->id());
    m_vehicles.remove(vehicle);
}


//bool HyperSpace::isHere(int id) const
//{
//    for (Vehicle* vehicle: m_vehicles) {
//        if (vehicle->id() == id) {
//            return true;
//        }
//    }
//    return false;
//}

//void HyperSpace::postHyperJumpEvent(Starsystem* starsystem)
//{
////    for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
////    {
////        VEHICLE_vec[i]->driveComplex().ResetTarget();
        
////        glm::vec3 center(meti::getRandXYVec3f(500, 900, DEFAULT_ENTITY_ZPOS)); // get correct pos
////        glm::vec3 angle(0,0,meti::getRandInt(360));
////        starsystem->add(VEHICLE_vec[i], center, angle, VEHICLE_vec[i]->parent());
////    }
          
////    VEHICLE_vec.clear();
//}

} // namespace control
} // namespace core
