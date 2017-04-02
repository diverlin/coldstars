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
#include <core/item/equipment/Lazer.hpp>
#include <core/descriptor/item/equipment/Lazer.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Lazer*
Lazer::gen()
{
    descriptor::item::Lazer* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::LAZER_EQUIPMENT)) {
        descr = descriptor::item::genLazer();
    } else {
        descr = descriptor::Manager::get().randLazer();
    }
    assert(descr);
    return gen(descr);
}

control::item::Lazer*
Lazer::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Lazer* descr = descriptor::Manager::get().lazer(descriptor_id);
    control::item::Lazer* lazer = __genTemplate(descr, ob_id);
    __createInternals(lazer, descr);
    return lazer;
}

control::item::Lazer*
Lazer::gen(descriptor::item::Lazer* descr)
{
    control::item::Lazer* lazer = __genTemplate(descr);
    __createInternals(lazer, descr);
    return lazer;
}

control::item::Lazer*
Lazer::__genTemplate(descriptor::item::Lazer* descr, int_t ob_id)
{ 
    model::item::Lazer* model = new model::item::Lazer(descr->id(), ob_id);
    control::item::Lazer* lazer = new control::item::Lazer(descr, model);
    EntityManager::get().reg(lazer);
    return lazer;
} 

void
Lazer::__createInternals(control::item::Lazer* lazer, descriptor::item::Lazer* descr)
{     
    Item::_createInternals(lazer, descr);
    Equipment::_createInternals(lazer, descr);
    lazer->model()->setDamage(descr->damage());
    lazer->model()->setRadius(descr->radius());

//    if (race_id == race::type::NONE) {
//        race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(race::KIND::GOOD));
//    }
    
//    if (tech_level == tech::type::NONE) {
//        tech_level = tech::type::LEVEL0;
//    }

//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::LAZER_EQUIPMENT, revision_id)
//    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EQUIPMENT);

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
//    lazer->setParentSubTypeId(entity::type::WEAPON_SLOT);
//    lazer->setItemCommonData(common_data);

//    lazer->updateProperties();
//    lazer->countPrice();
}

} // namespace item
} // namespace builder
