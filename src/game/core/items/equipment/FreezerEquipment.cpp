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

#include "FreezerEquipment.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../../items/modules/FreezerModule.hpp"

FreezerEquipment::FreezerEquipment(int id)
:
freeze_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);  
    setSubTypeId(TYPE::ENTITY::FREEZER_EQUIPMENT_ID); 
}

/* virtual */
FreezerEquipment::~FreezerEquipment() 
{}

/* virtual */
void FreezerEquipment::UpdateProperties()
{
    freeze_add  = 0;
    
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        freeze_add += ((FreezerModule*)modules_vec[i])->GetFreezeAdd();       
    }
    
    freeze = freeze_orig + freeze_add;
}

void FreezerEquipment::CountPrice()
{
     float freeze_rate          = (float)freeze_orig / EQUIPMENT::FREEZER::FREEZE_MIN;
     float modules_num_rate     = (float)data_item.modules_num_max / EQUIPMENT::FREEZER::MODULES_NUM_MAX;

     float effectiveness_rate = EQUIPMENT::FREEZER::FREEZE_WEIGHT * freeze_rate + EQUIPMENT::FREEZER::MODULES_NUM_WEIGHT * modules_num_rate;

     float mass_rate          = (float)data_item.mass / EQUIPMENT::FREEZER::MASS_MIN;
     float condition_rate     = (float)condition / data_item.condition_max;

     price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void FreezerEquipment::AddUniqueInfo()
{
//    info.addTitleStr("FREEZER");
//    info.addNameStr("freeze:");     info.addValueStr(GetFreezeStr());
}

std::string FreezerEquipment::GetFreezeStr()
{
     if (freeze_add == 0)
         return std::to_string(freeze_orig);
     else
         return std::to_string(freeze_orig) + "+" + std::to_string(freeze_add);
}


/*virtual*/
void FreezerEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "freezer_equipment." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    FreezerEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void FreezerEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    FreezerEquipment::LoadData(load_ptree);
}

/*virtual*/
void FreezerEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    FreezerEquipment::ResolveData();
}

void FreezerEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerEquipment::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"freeze_orig", freeze_orig);
}
                
void FreezerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerEquipment::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    freeze_orig = load_ptree.get<int>("freeze_orig");     
}                

void FreezerEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerEquipment::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}

