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

#include "VehicleSlot.hpp"
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Ship.hpp>

#include <ceti/Logger.hpp>

#include "../dock/Angar.hpp"
#include "../dock/Store.hpp"
#include "../common/Global.hpp"

#include <core/manager/EntityManager.hpp>
#include <core/model/spaceobject/Vehicle.hpp>

namespace slot {

Vehicle::Vehicle(int offset)
    : Base()
{
    setId(offset);
}
   
Vehicle::~Vehicle()
{}
      
/* virtual */
void Vehicle::putChildrenToGarbage() const
{
    assert(false);
//    if (m_vehicle) {
//       EntityManager::get().addToGarbage(m_vehicle);
//    }
}
                      
void Vehicle::insert(control::Vehicle* vehicle)
{
    m_vehicle = vehicle;

    vehicle->model()->setPlace(place::Type::KOSMOPORT);
    vehicle->setParentVehicleSlot(this);
}

void Vehicle::release()
{
    m_vehicle = nullptr;
} 

void Vehicle::swapVehicle(Vehicle* vehicle_slot)
{
    control::Vehicle* tmp_vehicle = vehicle_slot->vehicle();
    vehicle_slot->insert(m_vehicle);
    insert(tmp_vehicle);
}

//void VehicleSlot::Render(const ceti::Rect& rect) const
//{
//    //drawTexturedRect(textureOb, rect, -1);
//    if (m_vehicle != nullptr)
//    {
//        glm::vec3 center(rect.center().x, rect.center().y, -2.0);
//        //((Ship*)vehicle)->RenderAtPlanet(center);
//    }
//}

///*virtual*/
//void VehicleSlot::Save(boost::property_tree::ptree& save_ptree) const
//{
////    const std::string root = "vehicle_slot." + std::to_string(id()) + ".";
////    Base::SaveData(save_ptree, root);
////    BaseSlot::SaveData(save_ptree, root);
////    VehicleSlot::SaveData(save_ptree, root);
//}

///*virtual*/
//void VehicleSlot::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    BaseSlot::LoadData(load_ptree);
////    VehicleSlot::LoadData(load_ptree);
//}
    
///*virtual*/
//void VehicleSlot::Resolve()
//{
////    Base::ResolveData();
////    BaseSlot::ResolveData();
////    VehicleSlot::ResolveData();
//}


//void VehicleSlot::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
////    LOG(" VehicleSlot("+std::to_string(id())+")::SaveData");
//}

//void VehicleSlot::LoadData(const boost::property_tree::ptree& load_ptree)
//{
////    LOG(" VehicleSlot("+std::to_string(id())+")::LoadData");
//}

//void VehicleSlot::ResolveData()
//{
////    LOG(" VehicleSlot("+std::to_string(id())+")::ResolveData");

////    switch(owner()->type())
////    {
////        //case ENTITY::VEHICLE:     { ((Vehicle*)EntityManager::get().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this); break; }
////        //case ENTITY::CONTAINER:     { ((Container*)EntityManager::get().GetEntityById(unresolved_BaseSlot.owner_id))->BindItemSlot(this); break; }
////        case entity::Type::STORE:           { ((Store*)owner())->addVehicleSlot(this); break; }
////        case entity::Type::ANGAR:             { ((Angar*)owner())->AddVehicleSlot(this); break; }
////    }
//}

} // namespace slot
