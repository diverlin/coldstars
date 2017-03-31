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


#include <builder/dock/AngarBuilder.hpp>
#include <core/builder/slot/VehicleSlotBuilder.hpp>
#include <core/builder/slot/ItemSlotBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/slot/VehicleSlot.hpp>

#include <dock/Angar.hpp>

namespace builder {

control::Angar*
Angar::gen()
{
    control::Angar* angar = __createTemplate();
    __createInternals(angar);

    return angar;
} 

control::Angar*
Angar::__createTemplate(int_t id)
{
    control::Angar* angar = new control::Angar(id);
    assert(angar);

    EntityManager::get().reg(angar);

    return angar;
}

void
Angar::__createInternals(control::Angar* angar)
{ 
    for (unsigned int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM; i++)
    {
        control::VehicleSlot* vehicle_slot = getNewVehicleSlot(entity::Type::VEHICLE_MILITARY_SLOT);
        angar->AddVehicleSlot(vehicle_slot);
    }

    for (unsigned int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM; i++)
    {
        control::VehicleSlot* vehicle_slot = getNewVehicleSlot(entity::Type::VEHICLE_VISITORS_SLOT);
        angar->AddVehicleSlot(vehicle_slot);
    }

    for (unsigned int i=0; i<ANGAR_ITEM_SLOTS_NUM; i++)
    {
        control::ItemSlot* cargo_slot = genItemSlot(entity::Type::CARGO_SLOT);
        angar->AddItemSlot(cargo_slot);
    }
    
    //angar->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ANGAR_BACKGROUND));
}

} // namespace builder
