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

#include "RocketBuilder.hpp"
#include <core/model/item/equipment/Rocket.hpp>
#include <core/item/equipment/Rocket.hpp>
#include <core/descriptor/item/equipment/Rocket.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Rocket*
Rocket::gen()
{
    descriptor::item::Rocket* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::ROCKET_EQUIPMENT)) {
        descr = descriptor::item::genRocket();
    } else {
        descr = core::shortcuts::descriptors()->randRocket();
    }
    assert(descr);
    return gen(descr);
}

control::item::Rocket*
Rocket::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Rocket* descr = core::shortcuts::descriptors()->rocket(descriptor_id);
    control::item::Rocket* rocket = __genTemplate(descr, ob_id);
    __createInternals(rocket, descr);
    return rocket;
}

control::item::Rocket*
Rocket::gen(descriptor::item::Rocket* descr)
{
    control::item::Rocket* rocket = __genTemplate(descr);
    __createInternals(rocket, descr);
    return rocket;
}


control::item::Rocket*
Rocket::__genTemplate(descriptor::item::Rocket* descr, int_t ob_id)
{
    model::item::Rocket* model = new model::item::Rocket(descr->id(), ob_id);
    control::item::Rocket* rocket = new control::item::Rocket(descr, model);
    core::shortcuts::entities()->add(rocket);
    return rocket;
}

void
Rocket::__createInternals(control::item::Rocket* rocket, descriptor::item::Rocket* descr)
{     
    Item::_createInternals(rocket, descr);
    Equipment::_createInternals(rocket, descr);
    rocket->model()->setAmmo(descr->ammo());
    rocket->model()->setDamage(descr->damage());
    rocket->model()->setRadius(descr->radius());

//    if (race_id == race::Type::NONE) {
//        race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(race::KIND::GOOD));
//    }
    
//    if (tech_level == tech::Type::NONE) {
//        tech_level = tech::Type::LEVEL0;
//    }

//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ROCKET_EQUIPMENT);
//    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::ROCKET_EQUIPMENT, revision_id)
    
//    ammo_max_orig = meti::getRandInt(EQUIPMENT::ROCKET::AMMO_MIN, EQUIPMENT::ROCKET::AMMO_MAX)     * (1 + EQUIPMENT::ROCKET::AMMO_TECH_RATE * (int)tech_level);
//    damage_orig   = meti::getRandInt(EQUIPMENT::ROCKET::DAMAGE_MIN, EQUIPMENT::ROCKET::DAMAGE_MAX) * (1 + EQUIPMENT::ROCKET::DAMAGE_TECH_RATE * (int)tech_level);
//    radius_orig   = meti::getRandInt(EQUIPMENT::ROCKET::RADIUS_MIN, EQUIPMENT::ROCKET::RADIUS_MAX) * (1 + EQUIPMENT::ROCKET::RADIUS_TECH_RATE * (int)tech_level);
    
//    ItemCommonData common_data;
//    common_data.tech         = tech_level;
//#ifdef USE_MODULES
//    common_data.modules_num = meti::getRandInt(EQUIPMENT::ROCKET::MODULES_NUM_MIN, EQUIPMENT::ROCKET::MODULES_NUM_MAX);
//#endif
//    common_data.mass            = meti::getRandInt(EQUIPMENT::ROCKET::MASS_MIN, EQUIPMENT::ROCKET::MASS_MAX);
//    common_data.condition_max   = meti::getRandInt(EQUIPMENT::ROCKET::CONDITION_MIN, EQUIPMENT::ROCKET::CONDITION_MAX);
    
//    common_data.deterioration = 1;
    
//    BulletData data_bullet;
//    data_bullet.damage        = damage_orig;
//    data_bullet.armor         = ENTITY::ROCKET::ARMOR;
//    data_bullet.speed_init    = ENTITY::ROCKET::START_SPEED;
//    data_bullet.speed_max     = ENTITY::ROCKET::SPEED_MAX;
//    data_bullet.d_speed       = ENTITY::ROCKET::DELTA_SPEED;
//    data_bullet.live_time     = ENTITY::ROCKET::LIFE_TIME;
//    data_bullet.angular_speed = ENTITY::ROCKET::ANGULAR_SPEED;
    
//    rocket->SetAmmoMaxOrig(ammo_max_orig);
//    rocket->SetDamageOrig(damage_orig);
//    rocket->SetRadiusOrig(radius_orig);
//    rocket->SetBulletData(data_bullet);
//    rocket->SetAmmo(ammo_max_orig*0.6);
//    //alpitodorender rocket->SetRenderData(mesh, texOb_item, texOb_item->size());
//    rocket->setParentSubTypeId(entity::Type::WEAPON_SLOT);
//    rocket->setItemCommonData(common_data);
    
//    rocket->updateProperties();
//    rocket->countPrice();
}

} // namespace item
} // namespace builder
