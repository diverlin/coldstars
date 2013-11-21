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

#include "ScanerEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items/modules/ScanerModule.hpp"

ScanerEquipment::ScanerEquipment(int id)
:
scan_orig(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::EQUIPMENT_ID); 
    SetSubTypeId(TYPE::ENTITY::SCANER_EQUIPMENT_ID); 
}

/* virtual */
ScanerEquipment::~ScanerEquipment() 
{}

/* virtual */
void ScanerEquipment::UpdateProperties()
{
        scan_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
        {
            scan_add += ((ScanerModule*)modules_vec[i])->GetScanAdd();          
        }
        
         scan = scan_orig + scan_add;
}

void ScanerEquipment::CountPrice()
{
         float scan_rate          = (float)scan_orig / EQUIPMENT::SCANER::SCAN_MIN;
         float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::SCANER::MODULES_NUM_MAX;

         float effectiveness_rate = EQUIPMENT::SCANER::SCAN_WEIGHT * scan_rate + 
                        EQUIPMENT::SCANER::MODULES_NUM_WEIGHT * modules_num_rate;

         float mass_rate          = (float)data_item.mass / EQUIPMENT::SCANER::MASS_MIN;
         float condition_rate     = (float)condition / data_item.condition_max;

         price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void ScanerEquipment::AddUniqueInfo()
{
        info.addTitleStr("SCANER");
        info.addNameStr("scan:");     info.addValueStr(GetScanStr());
}

std::string ScanerEquipment::GetScanStr()
{
         if (scan_add == 0)
             return int2str(scan_orig);
         else
             return int2str(scan_orig) + "+" + int2str(scan_add);
}


/*virtual*/
void ScanerEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "scaner_equipment." + int2str(GetId()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    ScanerEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void ScanerEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    ScanerEquipment::LoadData(load_ptree);
}

/*virtual*/
void ScanerEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    ScanerEquipment::ResolveData();
}

void ScanerEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerEquipment::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"scan_orig", scan_orig);
}
                
void ScanerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerEquipment::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    scan_orig = load_ptree.get<int>("scan_orig"); 
}                

void ScanerEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerEquipment::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


