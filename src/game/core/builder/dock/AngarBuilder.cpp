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
#include <builder/slots/VehicleSlotBuilder.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <slots/VehicleSlot.hpp>

#include <dock/Angar.hpp>


AngarBuilder::AngarBuilder()
{}

AngarBuilder::~AngarBuilder()
{}

Angar* AngarBuilder::createTemplate(id_type id) const
{
    Angar* angar = new Angar(id);
    assert(angar);

    global::get().entityManager().reg(angar);

    return angar;
} 

Angar* AngarBuilder::create() const
{
    Angar* angar = createTemplate();
    createInternals(angar);

    return angar;
} 

void AngarBuilder::createInternals(Angar* angar) const
{ 
    for (unsigned int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM; i++)
    {
        VehicleSlot* vehicle_slot = GetNewVehicleSlot(type::entity::VEHICLE_MILITARY_SLOT_ID);
        angar->AddVehicleSlot(vehicle_slot);
    }

    for (unsigned int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM; i++)
    {
        VehicleSlot* vehicle_slot = GetNewVehicleSlot(type::entity::VEHICLE_VISITORS_SLOT_ID);
        angar->AddVehicleSlot(vehicle_slot);
    }

    for (unsigned int i=0; i<ANGAR_ITEM_SLOTS_NUM; i++)
    {
        ItemSlot* cargo_slot = GetNewItemSlot(type::entity::CARGO_SLOT_ID);
        angar->AddItemSlot(cargo_slot);
    }
    
    //angar->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ANGAR_BACKGROUND_ID));
}


