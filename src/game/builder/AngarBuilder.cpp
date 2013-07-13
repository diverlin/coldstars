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

#include "AngarBuilder.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../docking/Angar.hpp"
#include "../common/IdGenerator.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"

#include "../builder/VehicleSlotBuilder.hpp"
#include "../builder/ItemSlotBuilder.hpp"

AngarBuilder& AngarBuilder::Instance()
{
	static AngarBuilder instance;
	return instance;
}

AngarBuilder::~AngarBuilder()
{}

Angar* AngarBuilder::GetNewAngarTemplate(unsigned long int id) const
{
	Angar* angar = nullptr;
	
	if (id == NONE_ID) 
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}
        
    try 
    { 
        angar = new Angar(id); 
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(angar);
    
    return angar;
} 

Angar* AngarBuilder::GetNewAngar() const
{
	Angar* angar = GetNewAngarTemplate();
	CreateNewInternals(angar);
        
    return angar;
} 
        	
void AngarBuilder::CreateNewInternals(Angar* angar) const
{ 
 	for (int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM; i++)
 	{
 		VehicleSlot* vehicle_slot = GetNewVehicleSlot(ENTITY::eTYPE::VEHICLE_MILITARY_SLOT_ID); 
 		angar->AddVehicleSlot(vehicle_slot);
	}

 	for (int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM; i++)
 	{
 		VehicleSlot* vehicle_slot = GetNewVehicleSlot(ENTITY::eTYPE::VEHICLE_VISITORS_SLOT_ID); 
 		angar->AddVehicleSlot(vehicle_slot);
	}
        
    for (int i=0; i<ANGAR_ITEM_SLOTS_NUM; i++)
 	{
 		ItemSlot* cargo_slot = GetNewItemSlot(ENTITY::eTYPE::CARGO_SLOT_ID); 
        angar->AddItemSlot(cargo_slot);
	}
	
	angar->SetTextureObBackground(TextureManager::Instance().GetRandomTextureOb(TEXTURE::ANGAR_BACKGROUND_ID));
}

  	
