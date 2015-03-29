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


#include <builder/slots/VehicleSlotBuilder.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>

#include <common/Logger.hpp>
#include <math/rand.hpp>

//#include <resources/TextureCollector.hpp>

#include <slots/VehicleSlot.hpp>

#include <common/Global.hpp>


VehicleSlot* GetNewVehicleSlot(TYPE::ENTITY subtype_id, INTLONGEST id)
{
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    } 

    VehicleSlot* vehicle_slot = nullptr;
    try 
    { 
        vehicle_slot = new VehicleSlot(id, subtype_id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    global::get().entitiesManager().RegisterEntity(vehicle_slot);
      
//    jeti::TextureOb* texOb_slot = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::VEHICLE_SLOT_ID);
//    vehicle_slot->SetTextureOb(texOb_slot);
          
    return vehicle_slot;
}
