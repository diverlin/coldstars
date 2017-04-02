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


#include <core/builder/slot/VehicleSlotBuilder.hpp>
#include <core/manager/EntityManager.hpp>

#include <core/slot/VehicleSlot.hpp>

#include <common/Global.hpp>

#include <ceti/IdGenerator.hpp>

#include <ceti/Logger.hpp>
#include <math/rand.hpp>

//#include <client/resources/TextureCollector.hpp>

slot::VehicleSlot*
getNewVehicleSlot(entity::Type subtype_id, int_t id)
{
    slot::VehicleSlot* slot = new slot::VehicleSlot(id, subtype_id);
    assert(slot);

//    jeti::control::TextureOb* texOb_slot = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::VEHICLE_SLOT);
//    vehicle_slot->SetTextureOb(texOb_slot);
          
    return slot;
}

