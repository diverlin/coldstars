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

#include "Protector.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/ProtectorModule.hpp>
#endif

namespace item {
namespace equipment {

Protector::Protector(const id_type& id)
    :
      protection_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    setSubTypeId(TYPE::ENTITY::PROTECTOR_EQUIPMENT_ID);
}

/* virtual */
Protector::~Protector()
{}

/* virtual */
void Protector::updateProperties()
{   
    protection_add  = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        protection_add += ((ProtectorModule*)modules_vec[i])->GetProtectionAdd();
    }
#endif

    protection = protection_orig + protection_add;
}

void Protector::CountPrice()
{
    float protection_rate    = (float)protection_orig / EQUIPMENT::PROTECTOR::PROTECTION_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::PROTECTOR::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::PROTECTOR::PROTECTION_WEIGHT * protection_rate +
            EQUIPMENT::PROTECTOR::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::PROTECTOR::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Protector::addUniqueInfo()
{
    //        info.addTitleStr("PROTECTOR");
    //        info.addNameStr("protection:");     info.addValueStr(GetProtectionStr());
}

std::string Protector::GetProtectionStr()
{
    if (protection_add == 0)
        return std::to_string(protection_orig);
    else
        return std::to_string(protection_orig) + "+" + std::to_string(protection_add);
}

/*virtual*/
void Protector::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "protector_equipment." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Protector::SaveData(save_ptree, root);
}

/*virtual*/
void Protector::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Protector::LoadData(load_ptree);
}

/*virtual*/
void Protector::Resolve()
{
    Base::ResolveData();
    Base::ResolveData();
    Base::ResolveData();
    Protector::ResolveData();
}

void Protector::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" ProtectorEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"protection_orig", protection_orig);
}

void Protector::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" ProtectorEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
    protection_orig = load_ptree.get<int>("protection_orig");
}                

void Protector::ResolveData()
{
    LOG(" ProtectorEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace equipment
} // namespace item
