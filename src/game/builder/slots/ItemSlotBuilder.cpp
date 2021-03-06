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


#include <builder/slots/ItemSlotBuilder.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>

#include <resources/MeshCollector.hpp>
#include <resources/TextureManager.hpp>
#include <resources/textureOb.hpp>

#include <world/EntityManager.hpp>

#include <parts/Turrel.hpp>
#include <slots/ItemSlot.hpp>


ItemSlot* GetNewItemSlot(TYPE::ENTITY subtype_id, INTLONGEST id)
{
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    } 
    
    ItemSlot* item_slot = nullptr;
    try 
    { 
        item_slot = new ItemSlot(id, subtype_id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(item_slot);
    
    TextureOb* texOb_slot = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::ITEM_SLOT_ID);
    item_slot->SetTextureOb(texOb_slot);
    
    if (subtype_id == TYPE::ENTITY::WEAPON_SLOT_ID)
    {
        Turrel* turrel = nullptr;
        Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);  
        TextureOb* texOb_turrel = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::TURREL_ID); 
        try 
        { 
            turrel = new Turrel(item_slot); 
        }
        catch(std::bad_alloc)
        {
            Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
    
        turrel->SetRenderData(mesh, texOb_turrel, texOb_turrel->GetSize());       
        item_slot->SetTurrel(turrel);
    }
    
    return item_slot;
}

ItemSlot* GetNewItemSlotWithoutSaveAbility(TYPE::ENTITY subtype_id)
{
    ItemSlot* item_slot = nullptr;
    try 
    { 
        item_slot = new ItemSlot(NONE_ID, subtype_id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation");
    }
    
    TextureOb* texOb_slot = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::ITEM_SLOT_ID);
    item_slot->SetTextureOb(texOb_slot);
    
    return item_slot;
}
