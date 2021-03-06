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

#include "DroidEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items/modules/DroidModule.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../slots/ItemSlot.hpp"

DroidEquipment::DroidEquipment(int id)
:
repair_orig(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::EQUIPMENT_ID); 
    SetSubTypeId(TYPE::ENTITY::DROID_EQUIPMENT_ID); 
}

/* virtual */
DroidEquipment::~DroidEquipment() 
{}

/* virtual */
void DroidEquipment::UpdateProperties()
{
        repair_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
        {
            repair_add += ((DroidModule*)modules_vec[i])->GetRepairAdd();        
        }
        
         repair = repair_orig + repair_add;
}

/* virtual */
void DroidEquipment::UpdateInStatic()
{
    if (GetFunctioning() == true)    
    {
        if (item_slot->GetOwnerVehicle()->IsArmorFull() == false)
        {
            item_slot->GetOwnerVehicle()->IncreaseArmor(repair);
            DeteriorationEvent();
        }
    }
    
    UpdateLock();
}
              
void DroidEquipment::CountPrice()
{
         float repair_rate        = (float)repair_orig / EQUIPMENT::DROID::REPAIR_MIN;
         float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::DROID::MODULES_NUM_MAX;

         float effectiveness_rate = EQUIPMENT::DROID::REPAIR_WEIGHT * repair_rate + 
                        EQUIPMENT::DROID::MODULES_NUM_WEIGHT * modules_num_rate;

         float mass_rate          = (float)data_item.mass / EQUIPMENT::DROID::MASS_MIN;
         float condition_rate     = (float)condition / data_item.condition_max;

         price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void DroidEquipment::AddUniqueInfo()
{
        info.addTitleStr("DROID");
       info.addNameStr("repair:");     info.addValueStr(GetRepairStr());
}
             
             
std::string DroidEquipment::GetRepairStr()
{
        if (repair_add == 0)
            return int2str(repair_orig);
        else
            return int2str(repair_orig) + "+" + int2str(repair_add);
}

/*virtual*/
void DroidEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "droid_equipment." + int2str(GetId()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    DroidEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void DroidEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    DroidEquipment::LoadData(load_ptree);
}

/*virtual*/
void DroidEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    DroidEquipment::ResolveData();
}

void DroidEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidEquipment::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        save_ptree.put(root+"repair_orig", repair_orig);
}
                
void DroidEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidEquipment::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    repair_orig = load_ptree.get<int>("repair_orig");
}                

void DroidEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidEquipment::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


