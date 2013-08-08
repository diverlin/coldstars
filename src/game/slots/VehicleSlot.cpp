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
#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Ship.hpp"
#include "../render/Render.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"

#include "../dock/Angar.hpp"
#include "../dock/Store.hpp"
#include "../world/EntityManager.hpp"

#include "../garbage/EntityGarbage.hpp"

VehicleSlot::VehicleSlot(int id, TYPE::ENTITY subtype_id)
:
vehicle(nullptr)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::VEHICLE_SLOT_ID);  
    SetSubTypeId(subtype_id);  
}
   
VehicleSlot::~VehicleSlot()
{}
      
/* virtual */
void VehicleSlot::PutChildsToGarbage() const
{
    if (vehicle)
    {
        EntityGarbage::Instance().Add(vehicle);
    } 
}
                      
void VehicleSlot::InsertVehicle(Vehicle* vehicle)
{
        this->vehicle = vehicle;

        //vehicle->SetPlaceTypeId(data_id.type_id);
        vehicle->SetParentVehicleSlot(this);
}

void VehicleSlot::Release()
{
        vehicle = nullptr;
} 

void VehicleSlot::SwapVehicle(VehicleSlot* vehicle_slot)
{
    Vehicle* tmp_vehicle = vehicle_slot->GetVehicle();
    vehicle_slot->InsertVehicle(GetVehicle());
    InsertVehicle(tmp_vehicle);
}

void VehicleSlot::Render(const Rect& rect) const
{
         drawTexturedRect(textureOb, rect, -1);
         if (vehicle != nullptr)
         {
             Vec3<float> center(rect.GetCenter().x, rect.GetCenter().y, -2.0);
                    ((Ship*)vehicle)->RenderAtPlanet(center);
    }
}

/*virtual*/
void VehicleSlot::SaveData(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "vehicle_slot." + int2str(GetId()) + ".";
    SaveDataUniqueBase(save_ptree, root);
    SaveDataUniqueBaseSlot(save_ptree, root);
    SaveDataUniqueVehicleSlot(save_ptree, root);
}

/*virtual*/        
void VehicleSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBase(load_ptree);
    LoadDataUniqueBaseSlot(load_ptree);
    LoadDataUniqueVehicleSlot(load_ptree);
}
    
/*virtual*/    
void VehicleSlot::ResolveData()
{
    ResolveDataUniqueBase();
    ResolveDataUniqueBaseSlot();
    ResolveDataUniqueVehicleSlot();
}


void VehicleSlot::SaveDataUniqueVehicleSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" VehicleSlot("+int2str(GetId())+")::SaveDataUniqueVehicleSlot", SAVELOAD_LOG_DIP);
    #endif
}

void VehicleSlot::LoadDataUniqueVehicleSlot(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" VehicleSlot("+int2str(GetId())+")::LoadDataUniqueVehicleSlot", SAVELOAD_LOG_DIP);
    #endif
}

void VehicleSlot::ResolveDataUniqueVehicleSlot()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" VehicleSlot("+int2str(GetId())+")::ResolveDataUniqueVehicleSlot", SAVELOAD_LOG_DIP);
    #endif

        switch(owner->GetTypeId())
        {
           //case ENTITY::VEHICLE_ID:     { ((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this); break; }
           //case ENTITY::CONTAINER_ID:     { ((Container*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->BindItemSlot(this); break; }
           case TYPE::ENTITY::STORE_ID:           { ((Store*)owner)->AddVehicleSlot(this); break; }
           case TYPE::ENTITY::ANGAR_ID:             { ((Angar*)owner)->AddVehicleSlot(this); break; }
    }
}
