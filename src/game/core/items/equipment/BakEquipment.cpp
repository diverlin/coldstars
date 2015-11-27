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

#include "BakEquipment.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../../items//modules/BakModule.hpp"

BakEquipment::BakEquipment(const id_type& id)
:
fuel_max_orig(0),  
fuel(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    setSubTypeId(TYPE::ENTITY::BAK_EQUIPMENT_ID);
}
   
/* virtual */
BakEquipment::~BakEquipment() 
{}
        
void BakEquipment::IncreaseFuel(int fuel)        
{
    this->fuel += fuel; 
    if (this->fuel > fuel_max)
    { 
        this->fuel = fuel_max; // not sure if it's needed
    }                           
}    
                                    
/* virtual */            
void BakEquipment::updateProperties()
{
    fuel_max_add = 0;
    
    for (unsigned int i = 0; i<modules_vec.size(); i++)
    {
        fuel_max_add += ((BakModule*)modules_vec[i])->GetFuelMaxAdd();
    }
    
    fuel_max = fuel_max_orig + fuel_max_add;        
}

void BakEquipment::CountPrice()
{
    float fuel_rate          = (float)fuel_max_orig / EQUIPMENT::BAK::FUEL_MIN;
    float modules_num_rate   = (float)m_data_item.modules_num_max / EQUIPMENT::BAK::MODULES_NUM_MAX;
    
    float effectiveness_rate = EQUIPMENT::BAK::FUEL_WEIGHT * fuel_rate + 
                               EQUIPMENT::BAK::MODULES_NUM_WEIGHT * modules_num_rate;
    
    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::BAK::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition_max;
    
    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void BakEquipment::AddUniqueInfo()
{
//    info.addTitleStr("BAK");
//    info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}


std::string BakEquipment::GetFuelStr()
{
     if (fuel_max_add == 0)
        return std::to_string(fuel_max_orig) + "/" + std::to_string(fuel);
     else
        return std::to_string(fuel_max_orig) + "+" + std::to_string(fuel_max_add) + "/" + std::to_string(fuel);
}

/*virtual*/
void BakEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "bak_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    BakEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void BakEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    BakEquipment::LoadData(load_ptree);
}

/*virtual*/
void BakEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    BakEquipment::ResolveData();
}

void BakEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" BakEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"fuel_max_orig", fuel_max_orig);
    save_ptree.put(root+"fuel", fuel);
}
                
void BakEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" BakEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
    fuel_max_orig = load_ptree.get<int>("fuel_max_orig");
    fuel = load_ptree.get<int>("fuel");
}                

void BakEquipment::ResolveData()
{
    LOG(" BakEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

