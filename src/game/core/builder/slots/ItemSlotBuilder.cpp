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
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>

//#include <resources/MeshCollector.hpp>
//#include <resources/TextureCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <common/Global.hpp>

#include <parts/Turrel.hpp>
#include <slots/ItemSlot.hpp>


ItemSlot* GetNewItemSlot(TYPE::ENTITY subtype_id, const id_type& id)
{  
    ItemSlot* item_slot = new ItemSlot(id, subtype_id);
    assert(item_slot);
    
    //jeti::TextureOb* texOb_slot = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ITEM_SLOT_ID);
//    item_slot->SetTextureOb(texOb_slot);
    
    if (subtype_id == TYPE::ENTITY::WEAPON_SLOT_ID) {
        Turrel* turrel = new Turrel(item_slot);
        assert(turrel);
//        jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//        jeti::TextureOb* texOb_turrel = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL_ID);
        // alpitodorender turrel->SetRenderData(mesh, texOb_turrel, texOb_turrel->size());
        item_slot->setTurrel(turrel);
    }
    
    return item_slot;
}

ItemSlot* GetNewItemSlotWithoutSaveAbility(TYPE::ENTITY subtype_id)
{
    ItemSlot* item_slot = new ItemSlot(NONE_ID, subtype_id);
    assert(item_slot);
    
//    jeti::TextureOb* texOb_slot = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ITEM_SLOT_ID);
//    item_slot->SetTextureOb(texOb_slot);
    
    return item_slot;
}
