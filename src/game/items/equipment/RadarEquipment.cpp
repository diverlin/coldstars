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

#include "RadarEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items//modules/RadarModule.hpp"

RadarEquipment::RadarEquipment(int id)
:
radius_orig(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    SetSubTypeId(TYPE::ENTITY::RADAR_EQUIPMENT_ID);
}

/* virtual */
RadarEquipment::~RadarEquipment() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~RadarEquipment("+int2str(GetId())+")");
    #endif    
}

/* virtual */
void RadarEquipment::UpdateProperties()
{
    radius_add  = 0;
    
    for (unsigned int i=0; i<modules_vec.size(); i++)
    {
        radius_add += ((RadarModule*)modules_vec[i])->GetRadiusAdd();            
    }
    
    radius = radius_orig + radius_add;
}
   
void RadarEquipment::CountPrice()
{
    float radius_rate         = (float)radius_orig / EQUIPMENT::RADAR::RADIUS_MIN;

    float modules_num_rate    = (float)data_item.modules_num_max / EQUIPMENT::RADAR::MODULES_NUM_MAX;

    float effectiveness_rate  = EQUIPMENT::RADAR::RADIUS_WEIGHT * radius_rate + EQUIPMENT::RADAR::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate           = (float)data_item.mass / EQUIPMENT::RADAR::MASS_MIN;
    float condition_rate      = (float)condition / data_item.condition_max;

    price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}
 
void RadarEquipment::AddUniqueInfo()
{
    info.addTitleStr("RADAR");
    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string RadarEquipment::GetRadiusStr()
{
    if (radius_add == 0)
        return int2str(radius_orig);
    else
        return int2str(radius_orig) + "+" + int2str(radius_add);
}

/*virtual*/
void RadarEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "radar_equipment." + int2str(GetId()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    RadarEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void RadarEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    RadarEquipment::LoadData(load_ptree);
}

/*virtual*/
void RadarEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    RadarEquipment::ResolveData();
}

void RadarEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RadarEquipment::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"radius_orig", radius_orig);
}
                
void RadarEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RadarEquipment::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    radius_orig = load_ptree.get<int>("radius_orig");   
}                

void RadarEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RadarEquipment::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
   

