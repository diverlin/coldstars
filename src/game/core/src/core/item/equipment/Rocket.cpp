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
#include <core/descriptor/item/equipment/Rocket.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/model/item/equipment/Rocket.hpp>

#ifdef USE_MODULES
#include <core/item/modules/RocketModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Rocket::Rocket(model::item::Rocket* model)
    :
      Weapon(model, descriptor::Manager::get().rocket(model->descriptor()))
    , m_model_rocket(model)
    , m_descriptor_rocket(descriptor::Manager::get().rocket(model->descriptor()))
{
//    fire_atOnce = meti::getRandInt(1, 3);
}

/* virtual */
void Rocket::updateProperties()
{
    m_ammo_add = 0;
    
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        ammo_add += ((RocketModule*)modules_vec[i])->GetAmmoMaxAdd();
    }
#endif

    model()->setAmmo(descriptor()->ammo() + m_ammo_add);
}

void Rocket::addUniqueInfo()
{
    //    info.addTitleStr("ROCKET");
    
    //    info.addNameStr("ammo:");      info.addValueStr(GetAmmoStr());
    //    info.addNameStr("damage:");    info.addValueStr(GetDamageStr());
    //    info.addNameStr("radius:");    info.addValueStr(GetRadiusStr());
}

std::string
Rocket::ammoStr()
{
    if (m_ammo_add) {
         return std::to_string(descriptor()->ammo()) + "+" + std::to_string(m_ammo_add) + "/" + std::to_string(model()->ammo());
    } else {
        return std::to_string(descriptor()->ammo()) + "/" + std::to_string(model()->ammo());
    }
}

//void Rocket::FireEvent(float attack_rate_normalized)
//{
//    int num = 0;

//    glm::vec3 start_pos;
//    float angle_inD = 0; // fake

//    if (fire_atOnce>=1)
//    {
//        model::RocketBullet* rocket_bullet = core::global::get().rocketBulletBuilder().gen(data_bullet);
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
