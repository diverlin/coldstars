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

#include "RocketEquipment.hpp"
#include "../../common/constants.hpp"
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../../items/modules/RocketModule.hpp"
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



RocketEquipment::RocketEquipment(const ID& id)
:
ammo_max_orig(0),
ammo(0),
damage_orig(0),
radius_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID); 
    setSubTypeId(TYPE::ENTITY::ROCKET_EQUIPMENT_ID);     

    fire_atOnce = meti::getRandInt(1, 3);
}

/* virtual */
RocketEquipment::~RocketEquipment() 
{}

/* virtual */
void RocketEquipment::updateProperties()
{
    ammo_max_add = 0;
    damage_add   = 0;
    radius_add   = 0;
    
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        ammo_max_add += ((RocketModule*)modules_vec[i])->GetAmmoMaxAdd();
        damage_add   += ((RocketModule*)modules_vec[i])->GetDamageAdd();
        radius_add   += ((RocketModule*)modules_vec[i])->GetRadiusAdd();            
    }
        
    ammo_max = ammo_max_orig + ammo_max_add;
    damage   = damage_orig + damage_add;
    radius   = radius_orig + radius_add;
}

void RocketEquipment::CountPrice()
{
    float ammo_rate     = (float)ammo_max_orig / EQUIPMENT::ROCKET::AMMO_MIN;
    float damage_rate   = (float)damage_orig / EQUIPMENT::ROCKET::DAMAGE_MIN;
    float radius_rate   = (float)radius_orig / EQUIPMENT::ROCKET::RADIUS_MIN;
    float modules_num_rate   = (float)m_data_item.modules_num_max / EQUIPMENT::ROCKET::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::ROCKET::AMMO_WEIGHT * ammo_rate + 
                   EQUIPMENT::ROCKET::DAMAGE_WEIGHT * damage_rate + 
                   EQUIPMENT::ROCKET::RADIUS_WEIGHT * radius_rate + 
                   EQUIPMENT::ROCKET::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::ROCKET::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void RocketEquipment::AddUniqueInfo()
{
//    info.addTitleStr("ROCKET");
    
//    info.addNameStr("ammo:");      info.addValueStr(GetAmmoStr());
//    info.addNameStr("damage:");    info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");    info.addValueStr(GetRadiusStr());
}

std::string RocketEquipment::GetAmmoStr()
{
    if (ammo_max_add == 0)
        return std::to_string(ammo_max_orig) + "/" + std::to_string(ammo);
    else
        return std::to_string(ammo_max_orig) + "+" + std::to_string(ammo_max_add) + "/" + std::to_string(ammo);
}

std::string RocketEquipment::GetDamageStr()
{
    if (damage_add == 0)
        return std::to_string(damage_orig);
    else
        return std::to_string(damage_orig) + "+" + std::to_string(damage_add);
}

std::string RocketEquipment::GetRadiusStr()
{
    if (radius_add == 0)
        return std::to_string(radius_orig);
    else
        return std::to_string(radius_orig) + "+" + std::to_string(radius_add);
}

void RocketEquipment::FireEvent(float attack_rate_normalized)
{
    int num = 0;

    glm::vec3 start_pos;
    float angle_inD = 0; // fake
            
    if (fire_atOnce>=1)
    {
        RocketBullet* rocket_bullet = global::get().rocketBulletBuilder().create(data_bullet);
        rocket_bullet->SetDamageRate(attack_rate_normalized);

        if (itemSlot()->GetOwnerVehicle()->GetVehicleDescriptor().draw_turrels == true)
        {
            start_pos = itemSlot()->turrel()->center();
            //angle_inD = item_slot->GetTurrel()->GetAngle().z;
        }
        else
        {
            start_pos = itemSlot()->GetOwnerVehicle()->center();
            //angle_inD = itemSlot()->GetOwnerVehicle()->GetAngle().z;
        }  
        
        rocket_bullet->SetOwnerId(itemSlot()->GetOwnerVehicle()->id());
        rocket_bullet->SetTarget(itemSlot()->target());
    
        itemSlot()->GetOwnerVehicle()->starsystem()->add(rocket_bullet, start_pos, glm::vec3(0, 0, angle_inD));
        num++;
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
    ammo -= num;

    deteriorationEvent();
}

/*virtual*/
void RocketEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "rocket_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    RocketEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void RocketEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    RocketEquipment::LoadData(load_ptree);
}

/*virtual*/
void RocketEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    RocketEquipment::ResolveData();
}

void RocketEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" RocketEquipment::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"ammo_max_orig", ammo_max_orig);
    save_ptree.put(root+"ammo", ammo);
    save_ptree.put(root+"damage_orig", damage_orig);
    save_ptree.put(root+"radius_orig", radius_orig);
    save_ptree.put(root+"fire_atOnce", fire_atOnce);
    
    data_bullet.Save(save_ptree, root);
}
                
void RocketEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" RocketEquipment::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    ammo_max_orig = load_ptree.get<int>("ammo_max_orig"); 
    ammo = load_ptree.get<int>("ammo"); 
    damage_orig = load_ptree.get<int>("damage_orig");  
    radius_orig = load_ptree.get<int>("radius_orig");   
    fire_atOnce = load_ptree.get<int>("fire_atOnce");  

    data_bullet.Load(load_ptree.get_child("data_bullet"));
}                

void RocketEquipment::ResolveData()
{
    Logger::Instance().Log(" RocketEquipment::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    data_bullet.Resolve();
}


