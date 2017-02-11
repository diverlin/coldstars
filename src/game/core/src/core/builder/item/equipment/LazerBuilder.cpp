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

#include "LazerBuilder.hpp"
#include <core/model/item/equipment/Lazer.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/common/Global.hpp>

namespace builder {
namespace item {

model::item::Lazer*
Lazer::getNew()
{
    const descriptor::item::Lazer& descr = core::global::get().descriptors().lazer().random();
    return getNew(descr);
}

model::item::Lazer*
Lazer::getNew(const std::string& data)
{
    descriptor::item::Lazer descr(data);
    assert(descr.descriptor() != descriptor::type::LAZER_EQUIPMENT);
    return getNew(descr);
}

model::item::Lazer*
Lazer::getNew(const descriptor::item::Lazer& descr)
{
    model::item::Lazer* lazer = createTemplate();
    createInternals(lazer, descr);

    return lazer;
}

model::item::Lazer*
Lazer::createTemplate()
{ 
    model::item::Lazer* lazer = new model::item::Lazer;
    assert(lazer);

    assert(false);
    //core::global::get().entityManager().reg(lazer);
    
    return lazer;
} 

void
Lazer::createInternals(model::item::Lazer* lazer, const descriptor::item::Lazer& descr)
{     
    assert(false);
//    if (race_id == race::type::NONE_ID) {
//        race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(race::KIND::GOOD));
//    }
    
//    if (tech_level == tech::type::NONE) {
//        tech_level = tech::type::LEVEL0;
//    }

//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE_ID);
//    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::LAZER_EQUIPMENT_ID, revision_id)
//    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EQUIPMENT_ID);

//    damage_orig     = meti::getRandInt(EQUIPMENT::LAZER::DAMAGE_MIN, EQUIPMENT::LAZER::DAMAGE_MAX) * (1 + EQUIPMENT::LAZER::DAMAGE_TECH_RATE * (int)tech_level);
//    radius_orig     = meti::getRandInt(EQUIPMENT::LAZER::RADIUS_MIN, EQUIPMENT::LAZER::RADIUS_MAX) * (1 + EQUIPMENT::LAZER::RADIUS_TECH_RATE * (int)tech_level);
    
//    ItemCommonData common_data;
//    common_data.tech         = tech_level;
//#ifdef USE_MODULES
//    common_data.modules_num = meti::getRandInt(EQUIPMENT::LAZER::MODULES_NUM_MIN, EQUIPMENT::LAZER::MODULES_NUM_MAX);
//#endif
//    common_data.mass            = meti::getRandInt(EQUIPMENT::LAZER::MASS_MIN, EQUIPMENT::LAZER::MASS_MAX);
//    common_data.condition_max   = meti::getRandInt(EQUIPMENT::LAZER::CONDITION_MIN, EQUIPMENT::LAZER::CONDITION_MAX);
//    common_data.deterioration = 1;

//    lazer->SetDamageOrig(damage_orig);
//    lazer->SetRadiusOrig(radius_orig);
//    //alpitodorender lazer->SetRenderData(mesh, texOb_item, texOb_item->size());
//    lazer->setParentSubTypeId(entity::type::WEAPON_SLOT_ID);
//    lazer->setItemCommonData(common_data);

//    lazer->updateProperties();
//    lazer->countPrice();
}

} // namespace item
} // namespace builder