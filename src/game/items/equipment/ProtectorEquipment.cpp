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

#include "ProtectorEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items/modules/ProtectorModule.hpp"

ProtectorEquipment::ProtectorEquipment(int id)
:
protection_orig(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    SetSubTypeId(TYPE::ENTITY::PROTECTOR_EQUIPMENT_ID);
}

/* virtual */
ProtectorEquipment::~ProtectorEquipment() 
{}

/* virtual */
void ProtectorEquipment::UpdateProperties()
{   
        protection_add  = 0;
        
           for (unsigned int i = 0; i < modules_vec.size(); i++)
        {
            protection_add += ((ProtectorModule*)modules_vec[i])->GetProtectionAdd();         
        }
        
          protection = protection_orig + protection_add;
}

void ProtectorEquipment::CountPrice()
{
          float protection_rate    = (float)protection_orig / EQUIPMENT::PROTECTOR::PROTECTION_MIN;
          float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::PROTECTOR::MODULES_NUM_MAX;

          float effectiveness_rate = EQUIPMENT::PROTECTOR::PROTECTION_WEIGHT * protection_rate + 
                         EQUIPMENT::PROTECTOR::MODULES_NUM_WEIGHT * modules_num_rate;

          float mass_rate          = (float)data_item.mass / EQUIPMENT::PROTECTOR::MASS_MIN;
          float condition_rate     = (float)condition / data_item.condition_max;

          price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void ProtectorEquipment::AddUniqueInfo()
{
        info.addTitleStr("PROTECTOR");
        info.addNameStr("protection:");     info.addValueStr(GetProtectionStr());
}

std::string ProtectorEquipment::GetProtectionStr()
{
         if (protection_add == 0)
             return int2str(protection_orig);
         else
             return int2str(protection_orig) + "+" + int2str(protection_add);
}

/*virtual*/
void ProtectorEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "protector_equipment." + int2str(GetId()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    ProtectorEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void ProtectorEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    ProtectorEquipment::LoadData(load_ptree);
}

/*virtual*/
void ProtectorEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    ProtectorEquipment::ResolveData();
}

void ProtectorEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ProtectorEquipment::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        save_ptree.put(root+"protection_orig", protection_orig);
}
                
void ProtectorEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ProtectorEquipment::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        protection_orig = load_ptree.get<int>("protection_orig");     
}                

void ProtectorEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ProtectorEquipment::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


