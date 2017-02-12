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

#include <ceti/IdGenerator.hpp>
#include <ceti/Logger.hpp>

//#include <client/resources/MeshCollector.hpp>
//#include <client/resources/TextureCollector.hpp>
//#include <jeti/Material.hpp>

#include <common/Global.hpp>

#include <parts/Turrel.hpp>
#include <slots/ItemSlot.hpp>


control::ItemSlot*
getNewItemSlot(entity::type subtype_id, int_t id)
{  
    assert(false);
    control::ItemSlot* item_slot = new control::ItemSlot(id, subtype_id);
    assert(item_slot);
    
    //jeti::control::TextureOb* texOb_slot = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ITEM_SLOT);
//    item_slot->SetTextureOb(texOb_slot);
    
    if (subtype_id == entity::type::WEAPON_SLOT) {
        assert(false);
//        Turrel* turrel = new Turrel(item_slot);
//        assert(turrel);
////        jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
////        jeti::control::TextureOb* texOb_turrel = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL);
//        // alpitodorender turrel->SetRenderData(mesh, texOb_turrel, texOb_turrel->size());
//        item_slot->setTurrel(turrel);
    }
    
    return item_slot;
}

