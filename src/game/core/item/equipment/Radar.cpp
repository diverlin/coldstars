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

#include "Radar.hpp"
#ifdef USE_MODULES
#include <item/modules/RadarModule.hpp>
#endif
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>


namespace item {
namespace equipment {

Radar::Radar(const id_type& id)
    :
      m_radius_orig(0)
{
    setId(id);
    setTypeId(type::entity::EQUIPMENT_ID);
    setSubTypeId(type::entity::RADAR_EQUIPMENT_ID);
}

/* virtual */
Radar::~Radar()
{
    LOG("___::~RadarEquipment("+std::to_string(id())+")");
}

/* virtual */
void Radar::updateProperties()
{
    m_radius_add  = 0;
    
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        radius_add += ((RadarModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif
    m_radius = m_radius_orig + m_radius_add;
}

void Radar::CountPrice()
{
    float radius_rate         = (float)m_radius_orig / EQUIPMENT::RADAR::RADIUS_MIN;

    float modules_num_rate    = (float)modulesNum() / EQUIPMENT::RADAR::MODULES_NUM_MAX;

    float effectiveness_rate  = EQUIPMENT::RADAR::RADIUS_WEIGHT * radius_rate + EQUIPMENT::RADAR::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate           = (float)m_data_item.mass / EQUIPMENT::RADAR::MASS_MIN;
    float condition_rate      = (float)m_condition / m_data_item.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Radar::addUniqueInfo()
{
    //    info.addTitleStr("RADAR");
    //    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string Radar::GetRadiusStr()
{
    if (m_radius_add == 0)
        return std::to_string(m_radius_orig);
    else
        return std::to_string(m_radius_orig) + "+" + std::to_string(m_radius_add);
}

/*virtual*/
void Radar::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "radar_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Radar::SaveData(save_ptree, root);
}

/*virtual*/
void Radar::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Radar::LoadData(load_ptree);
}

/*virtual*/
void Radar::Resolve()
{
    Base::ResolveData();
    Base::ResolveData();
    Base::ResolveData();
    Radar::ResolveData();
}

void Radar::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" RadarEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"radius_orig", m_radius_orig);
}

void Radar::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" RadarEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
    m_radius_orig = load_ptree.get<int>("radius_orig");
}                

void Radar::ResolveData()
{
    LOG(" RadarEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace equipment
} // namespace item

