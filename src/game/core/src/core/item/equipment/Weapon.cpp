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

#include "Weapon.hpp"
#include <core/descriptor/item/equipment/Weapon.hpp>
#include <core/model/item/equipment/Weapon.hpp>

#include <core/slot/ItemSlot.hpp>

//#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Weapon::Weapon(descriptor::item::Weapon* descr, model::item::Weapon* model)
    : Equipment(descr, model)
    , m_descriptor_weapon(descr)
    , m_model_weapon(model)
{
//    fire_atOnce = meti::getRandInt(1, 3);
}

int Weapon::radius() const { return model()->radius(); }
int Weapon::damage() const { return model()->damage(); }

void Weapon::updateProperties()
{
    m_damage_add   = 0;
    m_radius_add   = 0;
    
#ifdef USE_MODULES
    // todo implement weapon module class
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        damage_add   += ((RocketModule*)modules_vec[i])->GetDamageAdd();
        radius_add   += ((RocketModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif

    model()->setDamage(descriptor()->damage() + m_damage_add);
    model()->setRadius(descriptor()->radius() + m_radius_add);
}

void Weapon::addUniqueInfo()
{
    //    info.addTitleStr("ROCKET");
    
    //    info.addNameStr("ammo:");      info.addValueStr(GetAmmoStr());
    //    info.addNameStr("damage:");    info.addValueStr(GetDamageStr());
    //    info.addNameStr("radius:");    info.addValueStr(GetRadiusStr());
}

std::string Weapon::damageStr()
{
    if (m_damage_add) {
        return std::to_string(descriptor()->damage()) + "+" + std::to_string(m_damage_add);
    } else {
        return std::to_string(descriptor()->damage());
    }
}

std::string Weapon::radiusStr()
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
//        model::Bullet* rocket_bullet = core::global::get().BulletBuilder().gen(data_bullet);
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
