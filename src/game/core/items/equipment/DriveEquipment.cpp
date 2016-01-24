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

#include "DriveEquipment.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../../items//modules/DriveModule.hpp"

DriveEquipment::DriveEquipment(const id_type& id)
:
speed_orig(0),
hyper_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);  
    setSubTypeId(TYPE::ENTITY::DRIVE_EQUIPMENT_ID);
}

/* virtual */
DriveEquipment::~DriveEquipment() 
{}

/* virtual */
void DriveEquipment::updateProperties()
{     
         speed_add        = 0;
         hyper_add        = 0;
     
        for (unsigned int i = 0; i < modules_vec.size(); i++)
        {
            speed_add += ((DriveModule*)modules_vec[i])->GetSpeedAdd();
            hyper_add += ((DriveModule*)modules_vec[i])->GetHyperAdd();      
        }
        
         speed = speed_orig + speed_add;
         hyper = hyper_orig + hyper_add;
}
             
void DriveEquipment::CountPrice()
{
         float speed_rate         = (float)speed_orig / EQUIPMENT::DRIVE::SPEED_MIN;
         float hyper_rate         = (float)hyper_orig / EQUIPMENT::DRIVE::HYPER_MIN;
         float modules_num_rate   = (float)m_data_item.modules_num_max / EQUIPMENT::DRIVE::MODULES_NUM_MAX;

         float effectiveness_rate = EQUIPMENT::DRIVE::SPEED_WEIGHT * speed_rate + 
                        EQUIPMENT::DRIVE::HYPER_WEIGHT * hyper_rate + 
                        EQUIPMENT::DRIVE::MODULES_NUM_WEIGHT * modules_num_rate;

         float mass_rate          = (float)m_data_item.mass / EQUIPMENT::DRIVE::MASS_MIN;
         float condition_rate     = (float)m_condition / m_data_item.condition_max;

         m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void DriveEquipment::addUniqueInfo()
{
//        info.addTitleStr("DRIVE");
//        info.addNameStr("speed:");     info.addValueStr(GetSpeedStr());
//        info.addNameStr("hyper:");     info.addValueStr(GetHyperStr());
}             

std::string DriveEquipment::GetSpeedStr()
{
         if (speed_add == 0)
            return std::to_string(speed_orig);
         else
            return std::to_string(speed_orig) + "+" + std::to_string(speed_add);
}

std::string DriveEquipment::GetHyperStr()
{
         if (hyper_add == 0)
            return std::to_string(hyper_orig);
         else
            return std::to_string(hyper_orig) + "+" + std::to_string(hyper_add);
}


/*virtual*/
void DriveEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "drive_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    DriveEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void DriveEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    DriveEquipment::LoadData(load_ptree);
}

/*virtual*/    
void DriveEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    DriveEquipment::ResolveData();
}

void DriveEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" DriveEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"speed_orig", speed_orig);
    save_ptree.put(root+"hyper_orig", hyper_orig);
}
                
void DriveEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" DriveEquipment::LoadData()  id=" + std::to_string(id()) + " START");

    speed_orig = load_ptree.get<int>("speed_orig");
    hyper_orig = load_ptree.get<int>("hyper_orig");
}                

void DriveEquipment::ResolveData()
{
    LOG(" DriveEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}




