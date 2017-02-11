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

#include "Rocket.hpp"

#ifdef USE_MODULES
#include <item/modules/RocketModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>


namespace descriptor {
namespace item {

const int Rocket::AMMO_MIN = 20;
const int Rocket::AMMO_MAX = 40;
const float Rocket::AMMO_TECH_RATE = 0.1f;

const int Rocket::RADIUS_MIN = 350;
const int Rocket::RADIUS_MAX = 550;
const float Rocket::RADIUS_TECH_RATE = 0.1f;

const int Rocket::DAMAGE_MIN = 10;
const int Rocket::DAMAGE_MAX = 20;
const float Rocket::DAMAGE_TECH_RATE = 0.1f;

const int Rocket::MODULES_NUM_MIN = 0;
const int Rocket::MODULES_NUM_MAX = 2;

const int Rocket::MASS_MIN = 30;
const int Rocket::MASS_MAX = 60;
const int Rocket::CONDITION_MIN = 100;
const int Rocket::CONDITION_MAX = 900;

const float Rocket::AMMO_WEIGHT = 0.3f;
const float Rocket::DAMAGE_WEIGHT = 0.3f;
const float Rocket::RADIUS_WEIGHT = 0.2f;
const float Rocket::MODULES_NUM_WEIGHT = 0.2f;

Rocket::Rocket()
{
    setDescriptor(descriptor::type::ROCKET_EQUIPMENT);
}

Rocket::Rocket(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Rocket::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor


namespace model {
namespace item {

Rocket::Rocket()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::ROCKET_EQUIPMENT_ID);
}

Rocket::Rocket(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Rocket::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model


namespace control {
namespace item {

Rocket::Rocket(model::item::Rocket* model)
    :
      m_model_rocket(model)
{
    assert(false);
    //    setId(id);
    //    setTypeId(entity::Type::EQUIPMENT_ID);
    //    setSubTypeId(entity::Type::ROCKET_EQUIPMENT_ID);

//    fire_atOnce = meti::getRandInt(1, 3);
}

/* virtual */
void Rocket::updateProperties()
{
    m_ammo_add = 0;
    m_damage_add   = 0;
    m_radius_add   = 0;
    
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        ammo_add += ((RocketModule*)modules_vec[i])->GetAmmoMaxAdd();
        damage_add   += ((RocketModule*)modules_vec[i])->GetDamageAdd();
        radius_add   += ((RocketModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif

    model()->setAmmo(descriptor()->ammo() + m_ammo_add);
    model()->setDamage(descriptor()->damage() + m_damage_add);
    model()->setRadius(descriptor()->radius() + m_radius_add);
}

void Rocket::countPrice()
{
    float ammo_rate     = float(descriptor()->ammo()) / descriptor::item::Rocket::AMMO_MIN;
    float damage_rate   = float(descriptor()->damage()) / descriptor::item::Rocket::DAMAGE_MIN;
    float radius_rate   = float(descriptor()->radius()) / descriptor::item::Rocket::RADIUS_MIN;
    float modules_num_rate   = float(descriptor()->modules()) / descriptor::item::Rocket::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Rocket::AMMO_WEIGHT * ammo_rate +
            descriptor::item::Rocket::DAMAGE_WEIGHT * damage_rate +
            descriptor::item::Rocket::RADIUS_WEIGHT * radius_rate +
            descriptor::item::Rocket::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Rocket::MASS_MIN;
    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Rocket::CONDITION_MIN;

    m_price = int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Rocket::addUniqueInfo()
{
    //    info.addTitleStr("ROCKET");
    
    //    info.addNameStr("ammo:");      info.addValueStr(GetAmmoStr());
    //    info.addNameStr("damage:");    info.addValueStr(GetDamageStr());
    //    info.addNameStr("radius:");    info.addValueStr(GetRadiusStr());
}

std::string Rocket::ammoStr()
{
    if (m_ammo_add) {
         return std::to_string(descriptor()->ammo()) + "+" + std::to_string(m_ammo_add) + "/" + std::to_string(model()->ammo());
    } else {
        return std::to_string(descriptor()->ammo()) + "/" + std::to_string(model()->ammo());
    }
}

std::string Rocket::damageStr()
{
    if (m_damage_add) {
        return std::to_string(descriptor()->damage()) + "+" + std::to_string(m_damage_add);
    } else {
        return std::to_string(descriptor()->damage());
    }
}

std::string Rocket::radiusStr()
{
    if (m_radius_add) {
        return std::to_string(descriptor()->radius()) + "+" + std::to_string(m_radius_add);
    } else {
        return std::to_string(descriptor()->radius());
    }
}

//void Rocket::FireEvent(float attack_rate_normalized)
//{
//    int num = 0;

//    glm::vec3 start_pos;
//    float angle_inD = 0; // fake

//    if (fire_atOnce>=1)
//    {
//        model::RocketBullet* rocket_bullet = core::global::get().rocketBulletBuilder().getNew(data_bullet);
//        rocket_bullet->setDamageRate(attack_rate_normalized);

//        assert(false);
////        if (slot()->vehicleOwner()->vehicleDescriptor().draw_turrels == true)
////        {
////            start_pos = slot()->turrel()->position();
////            //angle_inD = item_slot->GetTurrel()->GetAngle().z;
////        }
////        else
////        {
////            start_pos = slot()->vehicleOwner()->position();
////            //angle_inD = itemSlot()->GetOwnerVehicle()->GetAngle().z;
////        }

////        rocket_bullet->SetOwnerId(slot()->vehicleOwner()->id());
////        rocket_bullet->SetTarget(slot()->target());

////        slot()->vehicleOwner()->starsystem()->add(rocket_bullet, start_pos, glm::vec3(0, 0, angle_inD));
////        num++;
//    }

//    //if (fire_atOnce>=2)
//    //{
//        //offset = +2.0;
//    //RocketBuilder::Instance().CreateNewRocket();
//    //RocketBuilder::Instance().createInternals(data_bullet);
//        //slot->GetOwnerVehicle()->starsystem()->Add(RocketBuilder::Instance().GetRocket(), slot, offset);
//        //num++;
//    //}

//    //if (fire_atOnce>=3)
//    //{
//        //offset = -2.0;
//    //RocketBuilder::Instance().CreateNewRocket();
//    //RocketBuilder::Instance().createInternals(data_bullet);
//        //slot->GetOwnerVehicle()->starsystem()->Add(RocketBuilder::Instance().GetRocket(), slot, offset);
//        //num++;
//    //}

//    //rocketlaunch.play()
//    m_ammo -= num;

//    deteriorationEvent();
//}


} // namespace item
} // namespace control
