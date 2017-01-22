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

#include <descriptors/RaceDescriptors.hpp>
#include <assert.h>

RaceDescriptors::RaceDescriptors()
{
    std::vector<type::race> races_good = {
        type::race::R0_ID,
        type::race::R1_ID,
        type::race::R2_ID,
        type::race::R3_ID,
        type::race::R4_ID
    };

    std::vector<type::race> races_evil = {
        type::race::R6_ID,
        type::race::R7_ID
    };

    std::vector<type::race> races_all;
    for (auto race_id: races_good) {
        races_all.push_back(race_id);
    }
    for (auto race_id: races_evil) {
        races_all.push_back(race_id);
    }

    m_races[type::KIND::GOOD] = races_good;
    m_races[type::KIND::EVIL] = races_evil;
    m_races[type::KIND::ALL] = races_all;

    for (auto race_id: races_good) {
        m_subtypes[race_id] = {
            type::entity::RANGER_ID,
            type::entity::WARRIOR_ID,
            type::entity::TRADER_ID,
            type::entity::RANGER_ID,
            type::entity::DIPLOMAT_ID
        };
    }

    for (auto race_id: races_evil) {
        m_subtypes[race_id] = {
            type::entity::WARRIOR_ID
        };
    }
//    std::map<TYPE::RACE, std::vector<type::entity>> m_subtypes;
}

RaceDescriptors::~RaceDescriptors()
{

}

const std::vector<type::race>&
RaceDescriptors::getRaces(type::KIND kind_id) const
{
    const auto& el = m_races.find(kind_id);
    assert(el != m_races.end());
    return el->second;
}

const std::vector<type::entity>&
RaceDescriptors::getSubTypes(type::race race_id) const
{
    const auto& el = m_subtypes.find(race_id);
    assert( el != m_subtypes.end());
    return el->second;
}

bool
RaceDescriptors::isGood(type::race race_id) const
{
    const auto& el = m_races.find(type::KIND::GOOD);
    assert(el != m_races.end());

    for (const auto& id: el->second) {
        if (race_id == id) {
            return true;
        }
    }    
    return false;
}        
    
//void TextureCollector::FillShipSubTypeList()
//{
//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(type::entity::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(type::entity::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(type::entity::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(type::entity::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(type::entity::DIPLOMAT_ID);
//}
