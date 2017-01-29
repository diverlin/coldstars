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

#include "Scaner.hpp"
//[[deprecated("remove")]]
#include <common/constants.hpp>

#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/ScanerModule.hpp>
#endif

namespace item {
namespace equipment {

Scaner::Scaner(int_t id)
    :
      m_scan_orig(0)
{
    assert(false);
//    setId(id);
//    setTypeId(type::entity::EQUIPMENT_ID);
//    setSubTypeId(type::entity::SCANER_EQUIPMENT_ID);
}

/* virtual */
Scaner::~Scaner()
{}

/* virtual */
void Scaner::updateProperties()
{
    m_scan_add = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        scan_add += ((ScanerModule*)modules_vec[i])->GetScanAdd();
    }
#endif
    m_scan = m_scan_orig + m_scan_add;
}

void Scaner::countPrice()
{
    float scan_rate          = (float)m_scan_orig / EQUIPMENT::SCANER::SCAN_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::SCANER::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::SCANER::SCAN_WEIGHT * scan_rate +
            EQUIPMENT::SCANER::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::SCANER::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void Scaner::addUniqueInfo()
{
    //    info.addTitleStr("SCANER");
    //    info.addNameStr("scan:");     info.addValueStr(GetScanStr());
}

std::string Scaner::str()
{
    if (m_scan_add == 0)
        return std::to_string(m_scan_orig);
    else
        return std::to_string(m_scan_orig) + "+" + std::to_string(m_scan_add);
}


/*virtual*/
void Scaner::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "scaner_equipment." + std::to_string(id()) + ".";
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Scaner::SaveData(save_ptree, root);
}

/*virtual*/
void Scaner::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Scaner::LoadData(load_ptree);
}

/*virtual*/
void Scaner::Resolve()
{
//    Base::ResolveData();
//    Base::ResolveData();
//    Base::ResolveData();
//    Scaner::ResolveData();
}

void Scaner::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
//    LOG(" ScanerEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
//    save_ptree.put(root+"scan_orig", m_scan_orig);
}

void Scaner::LoadData(const boost::property_tree::ptree& load_ptree)
{
//    LOG(" ScanerEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
//    m_scan_orig = load_ptree.get<int>("scan_orig");
}                

void Scaner::ResolveData()
{
//    LOG(" ScanerEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace equipment
} // namespace item

