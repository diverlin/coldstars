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

#include "VehicleSlotBuilder.hpp"

#include "../slots/VehicleSlot.hpp"

#include "../common/IdGenerator.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"

VehicleSlot* GetNewVehicleSlot(ENTITY::TYPE subtype_id, unsigned long int id)
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
    
    EntityManager::Instance().RegisterEntity(vehicle_slot);
      
	TextureOb* texOb_slot = TextureManager::Instance().GetRandomTextureOb(TEXTURE::VEHICLE_SLOT_ID);
    vehicle_slot->SetTextureOb(texOb_slot);
          
    return vehicle_slot;
}

