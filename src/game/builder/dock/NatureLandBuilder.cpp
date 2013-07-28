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


#include <builder/dock/NatureLandBuilder.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/items/artefacts/GravityArtefactBuilder.hpp>
#include <builder/items/artefacts/ProtectorArtefactBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <items/artefacts/GravityArtefact.hpp>
#include <items/artefacts/ProtectorArtefact.hpp>

#include <dock/NatureLand.hpp>

NatureLandBuilder& NatureLandBuilder::Instance()
{
	static NatureLandBuilder instance;
	return instance;
}

NatureLandBuilder::~NatureLandBuilder()
{}

NatureLand* NatureLandBuilder::GetNewNatureLandTemplate(INTLONGEST id) const
{
	NatureLand* natureland = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        natureland = new NatureLand(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(natureland);
    
    return natureland;
} 

NatureLand* NatureLandBuilder::GetNewNatureLand() const
{
	NatureLand* natureland = GetNewNatureLandTemplate();
	CreateNewInternals(natureland);
        
    return natureland;
} 
       	
void NatureLandBuilder::CreateNewInternals(NatureLand* natureland) const
{
	natureland->SetTextureObBackground(TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::NATURELAND_BACKGROUND_ID));
	
	unsigned int item_slot_num = getRandInt(NATURELAND_ITEM_SLOT_MIN, NATURELAND_ITEM_SLOT_MAX);
	for (unsigned int i=0; i<item_slot_num; i++)
	{
		ItemSlot* item_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID);   
		natureland->AddItemSlot(item_slot);
	}
	
	for (unsigned int i=0; i<item_slot_num; i++)
	{
		if (natureland->CanAcceptNewItem() == true)
		{
			//int type_id = getRandInt(ENTITY::GRAVITY_ARTEFACT_ID, ENTITY::PROTECTOR_ARTEFACT_ID);
			//switch (type_id)
			//{
				//case ENTITY::GRAVITY_ARTEFACT_ID:
				//{
					//natureland->AddItem(GravityArtefactBuilder::Instance().GetNewGravityArtefact());
					//break;
				//}
				
				//case ENTITY::PROTECTOR_ARTEFACT_ID:
				//{
					//natureland->AddItem(ProtectorArtefactBuilder::Instance().GetNewProtectorArtefact());
					//break;
				//}
			//}
		}
	}	
}

  	
