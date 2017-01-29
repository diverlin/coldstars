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
#include "../../common/constants.hpp"
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/RocketModule.hpp>
#endif
#include <common/Global.hpp>
#include "../../builder/spaceobjects/RocketBulletBuilder.hpp"
#include "../../world/starsystem.hpp"
#include "../../parts/Turrel.hpp"
#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../spaceobjects/RocketBullet.hpp"

void BulletData::Save(boost::property_tree::ptree& save_ptree, const std::string& root) const
{           
    std::string sroot = root+"data_bullet.";
    save_ptree.put(sroot+"damage", damage);        
    save_ptree.put(sroot+"armor", armor); 
    save_ptree.put(sroot+"live_time", live_time); 

    save_ptree.put(sroot+"speed_init", speed_init); 
    save_ptree.put(sroot+"speed_max", speed_max); 
    save_ptree.put(sroot+"d_speed", d_speed); 
    save_ptree.put(sroot+"angular_speed", angular_speed); 
}    

void BulletData::Load(const boost::property_tree::ptree& load_ptree)
{
    damage = load_ptree.get<int>("damage"); 
    armor = load_ptree.get<int>("armor"); 
    live_time = load_ptree.get<int>("live_time"); 

    speed_init = load_ptree.get<float>("speed_init"); 
    speed_max = load_ptree.get<float>("speed_max"); 
    d_speed = load_ptree.get<float>("d_speed"); 
    angular_speed = load_ptree.get<float>("angular_speed"); 
}

void BulletData::Resolve()
{}

namespace item {
namespace equipment {

Rocket::Rocket(int_t id)
:
m_ammo_max_orig(0),
m_ammo(0),
m_damage_orig(0),
m_radius_orig(0)
{
    assert(false);
//    setId(id);
//    setTypeId(type::entity::EQUIPMENT_ID);
//    setSubTypeId(type::entity::ROCKET_EQUIPMENT_ID);

    fire_atOnce = meti::getRandInt(1, 3);
}

/* virtual */
Rocket::~Rocket()
{}

/* virtual */
void Rocket::updateProperties()
{
    m_ammo_max_add = 0;
    m_damage_add   = 0;
    m_radius_add   = 0;
    
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        ammo_max_add += ((RocketModule*)modules_vec[i])->GetAmmoMaxAdd();
        damage_add   += ((RocketModule*)modules_vec[i])->GetDamageAdd();
        radius_add   += ((RocketModule*)modules_vec[i])->GetRadiusAdd();            
    }
#endif

    m_ammo_max = m_ammo_max_orig + m_ammo_max_add;
    m_damage   = m_damage_orig + m_damage_add;
    m_radius   = m_radius_orig + m_radius_add;
}

void Rocket::CountPrice()
{
    float ammo_rate     = (float)m_ammo_max_orig / EQUIPMENT::ROCKET::AMMO_MIN;
    float damage_rate   = (float)m_damage_orig / EQUIPMENT::ROCKET::DAMAGE_MIN;
    float radius_rate   = (float)m_radius_orig / EQUIPMENT::ROCKET::RADIUS_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::ROCKET::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::ROCKET::AMMO_WEIGHT * ammo_rate + 
                   EQUIPMENT::ROCKET::DAMAGE_WEIGHT * damage_rate + 
                   EQUIPMENT::ROCKET::RADIUS_WEIGHT * radius_rate + 
                   EQUIPMENT::ROCKET::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::ROCKET::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Rocket::addUniqueInfo()
{
//    info.addTitleStr("ROCKET");
    
//    info.addNameStr("ammo:");      info.addValueStr(GetAmmoStr());
//    info.addNameStr("damage:");    info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");    info.addValueStr(GetRadiusStr());
}

std::string Rocket::GetAmmoStr()
{
    if (m_ammo_max_add == 0)
        return std::to_string(m_ammo_max_orig) + "/" + std::to_string(m_ammo);
    else
        return std::to_string(m_ammo_max_orig) + "+" + std::to_string(m_ammo_max_add) + "/" + std::to_string(m_ammo);
}

std::string Rocket::GetDamageStr()
{
    if (m_damage_add == 0)
        return std::to_string(m_damage_orig);
    else
        return std::to_string(m_damage_orig) + "+" + std::to_string(m_damage_add);
}

std::string Rocket::GetRadiusStr()
{
    if (m_radius_add == 0)
        return std::to_string(m_radius_orig);
    else
        return std::to_string(m_radius_orig) + "+" + std::to_string(m_radius_add);
}

void Rocket::FireEvent(float attack_rate_normalized)
{
    int num = 0;

    glm::vec3 start_pos;
    float angle_inD = 0; // fake
            
    if (fire_atOnce>=1)
    {
        model::RocketBullet* rocket_bullet = core::global::get().rocketBulletBuilder().getNew(data_bullet);
        rocket_bullet->setDamageRate(attack_rate_normalized);

        assert(false);
//        if (slot()->vehicleOwner()->vehicleDescriptor().draw_turrels == true)
//        {
//            start_pos = slot()->turrel()->position();
//            //angle_inD = item_slot->GetTurrel()->GetAngle().z;
//        }
//        else
//        {
//            start_pos = slot()->vehicleOwner()->position();
//            //angle_inD = itemSlot()->GetOwnerVehicle()->GetAngle().z;
//        }
        
//        rocket_bullet->SetOwnerId(slot()->vehicleOwner()->id());
//        rocket_bullet->SetTarget(slot()->target());
    
//        slot()->vehicleOwner()->starsystem()->add(rocket_bullet, start_pos, glm::vec3(0, 0, angle_inD));
//        num++;
    }
        
    //if (fire_atOnce>=2)
    //{
        //offset = +2.0;
    //RocketBuilder::Instance().CreateNewRocket();
    //RocketBuilder::Instance().createInternals(data_bullet);
        //slot->GetOwnerVehicle()->starsystem()->Add(RocketBuilder::Instance().GetRocket(), slot, offset);
        //num++;
    //}

    //if (fire_atOnce>=3)
    //{
        //offset = -2.0;
    //RocketBuilder::Instance().CreateNewRocket();
    //RocketBuilder::Instance().createInternals(data_bullet);
        //slot->GetOwnerVehicle()->starsystem()->Add(RocketBuilder::Instance().GetRocket(), slot, offset);
        //num++;
    //}        
    
    //rocketlaunch.play()
    m_ammo -= num;

    deteriorationEvent();
}

/*virtual*/
void Rocket::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "rocket_equipment." + std::to_string(id()) + ".";

//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Rocket::SaveData(save_ptree, root);
}

/*virtual*/
void Rocket::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Rocket::LoadData(load_ptree);
}

/*virtual*/
void Rocket::Resolve()
{
//    Base::ResolveData();
//    Base::ResolveData();
//    Base::ResolveData();
//    Rocket::ResolveData();
}

void Rocket::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
//    LOG(" RocketEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
//    save_ptree.put(root+"ammo_max_orig", m_ammo_max_orig);
//    save_ptree.put(root+"ammo", m_ammo);
//    save_ptree.put(root+"damage_orig", m_damage_orig);
//    save_ptree.put(root+"radius_orig", m_radius_orig);
//    save_ptree.put(root+"fire_atOnce", fire_atOnce);
    
//    data_bullet.Save(save_ptree, root);
}
                
void Rocket::LoadData(const boost::property_tree::ptree& load_ptree)
{
//    LOG(" RocketEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
//    m_ammo_max_orig = load_ptree.get<int>("ammo_max_orig");
//    m_ammo = load_ptree.get<int>("ammo");
//    m_damage_orig = load_ptree.get<int>("damage_orig");
//    m_radius_orig = load_ptree.get<int>("radius_orig");
//    fire_atOnce = load_ptree.get<int>("fire_atOnce");

//    data_bullet.Load(load_ptree.get_child("data_bullet"));
}                

void Rocket::ResolveData()
{
//    LOG(" RocketEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
    
//    data_bullet.Resolve();
}

} // namespace equipment
} // namespace item

