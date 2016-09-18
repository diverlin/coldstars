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

#include "Drive.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include <item/modules/DriveModule.hpp>

namespace item {
namespace equipment {

Drive::Drive(const int_t& id)
{
    setId(id);
    setTypeId(type::entity::EQUIPMENT_ID);
    setSubTypeId(type::entity::DRIVE_EQUIPMENT_ID);
}

/* virtual */
Drive::~Drive()
{}

/* virtual */
void Drive::updateProperties()
{     
    m_speed_add = 0;
    m_hyper_add = 0;
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        m_speed_add += ((DriveModule*)modules_vec[i])->GetSpeedAdd();
        m_hyper_add += ((DriveModule*)modules_vec[i])->GetHyperAdd();
    }
#endif
    m_speed = m_speed_orig + m_speed_add;
    m_hyper = m_hyper_orig + m_hyper_add;
}

void Drive::CountPrice()
{
    float speed_rate         = (float)m_speed_orig / EQUIPMENT::DRIVE::SPEED_MIN;
    float hyper_rate         = (float)m_hyper_orig / EQUIPMENT::DRIVE::HYPER_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::DRIVE::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::DRIVE::SPEED_WEIGHT * speed_rate +
            EQUIPMENT::DRIVE::HYPER_WEIGHT * hyper_rate +
            EQUIPMENT::DRIVE::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::DRIVE::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Drive::addUniqueInfo()
{
    //        info.addTitleStr("DRIVE");
    //        info.addNameStr("speed:");     info.addValueStr(GetSpeedStr());
    //        info.addNameStr("hyper:");     info.addValueStr(GetHyperStr());
}             

std::string Drive::GetSpeedStr()
{
    if (m_speed_add == 0)
        return std::to_string(m_speed_orig);
    else
        return std::to_string(m_speed_orig) + "+" + std::to_string(m_speed_add);
}

std::string Drive::GetHyperStr()
{
    if (m_hyper_add == 0)
        return std::to_string(m_hyper_orig);
    else
        return std::to_string(m_hyper_orig) + "+" + std::to_string(m_hyper_add);
}


/*virtual*/
void Drive::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "drive_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Drive::SaveData(save_ptree, root);
}

/*virtual*/
void Drive::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Drive::LoadData(load_ptree);
}

/*virtual*/    
void Drive::Resolve()
{
    Base::ResolveData();
    Base::ResolveData();
    Base::ResolveData();
    Drive::ResolveData();
}

void Drive::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" DriveEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"speed_orig", m_speed_orig);
    save_ptree.put(root+"hyper_orig", m_hyper_orig);
}

void Drive::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" DriveEquipment::LoadData()  id=" + std::to_string(id()) + " START");

    m_speed_orig = load_ptree.get<int>("speed_orig");
    m_hyper_orig = load_ptree.get<int>("hyper_orig");
}                

void Drive::ResolveData()
{
    LOG(" DriveEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace equipment
} // namespace item



