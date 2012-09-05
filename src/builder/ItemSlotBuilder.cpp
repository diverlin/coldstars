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

#include "ItemSlotBuilder.hpp"

ItemSlot* GetNewItemSlot(int subtype_id, int id)
{
       	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	} 

	ItemSlot* item_slot = NULL;
        try 
        { 
        	item_slot = new ItemSlot(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(item_slot);
      
        TextureOb* texOb_slot = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ITEM_SLOT_ID);
	item_slot->SetSubTypeId(subtype_id);
    	item_slot->SetTextureOb(texOb_slot);
        
        if (subtype_id == ENTITY::WEAPON_SLOT_ID)
        {
        	Turrel* turrel = NULL;
                TextureOb* texOb_turrel = TextureManager::Instance().GetRandomTextureOb(TEXTURE::TURREL_ID); 
                try 
        	{ 
                	turrel = new Turrel(item_slot); 
        	}
        	catch(std::bad_alloc)
        	{
        		Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        	}
        
                turrel->SetTextureOb(texOb_turrel);       
                turrel->GetPoints().addMainQuadPoints();
                turrel->GetPoints().initMainQuadPoints(texOb_turrel->GetFrameWidth(), texOb_turrel->GetFrameHeight());
                item_slot->SetTurrel(turrel);
        }
        
        return item_slot;
}

