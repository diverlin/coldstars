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

VehicleSlot* GetNewVehicleSlot(int id)
{
       	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	} 
        VehicleSlot* vehicle_slot = new VehicleSlot(id);
        EntityManager::Instance().RegisterEntity(vehicle_slot);
      
	TextureOb* texOb_slot = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::VEHICLESLOT_ID);
    	vehicle_slot->SetTextureOb(texOb_slot);
              
        return vehicle_slot;
}

