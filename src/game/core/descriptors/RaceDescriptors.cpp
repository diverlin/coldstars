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
    std::vector<TYPE::RACE> races_good = {
        TYPE::RACE::R0_ID,
        TYPE::RACE::R1_ID,
        TYPE::RACE::R2_ID,
        TYPE::RACE::R3_ID,
        TYPE::RACE::R4_ID
    };

    std::vector<TYPE::RACE> races_evil = {
        TYPE::RACE::R6_ID,
        TYPE::RACE::R7_ID
    };

    std::vector<TYPE::RACE> races_all;
    for (auto race_id: races_good) {
        races_all.push_back(race_id);
    }
    for (auto race_id: races_evil) {
        races_all.push_back(race_id);
    }

    m_races[TYPE::KIND::GOOD] = races_good;
    m_races[TYPE::KIND::EVIL] = races_evil;
    m_races[TYPE::KIND::ALL] = races_all;

    for (auto race_id: races_good) {
        m_subtypes[race_id] = {
            TYPE::ENTITY::RANGER_ID,
            TYPE::ENTITY::WARRIOR_ID,
            TYPE::ENTITY::TRADER_ID,
            TYPE::ENTITY::RANGER_ID,
            TYPE::ENTITY::DIPLOMAT_ID
        };
    }

    for (auto race_id: races_evil) {
        m_subtypes[race_id] = {
            TYPE::ENTITY::WARRIOR_ID
        };
    }
//    std::map<TYPE::RACE, std::vector<TYPE::ENTITY>> m_subtypes;
}

RaceDescriptors::~RaceDescriptors()
{

}

const std::vector<TYPE::RACE>&
RaceDescriptors::getRaces(TYPE::KIND kind_id) const
{
    const auto& el = m_races.find(kind_id);
    assert(el != m_races.end());
    return el->second;
}

const std::vector<TYPE::ENTITY>&
RaceDescriptors::getSubTypes(TYPE::RACE race_id) const
{
    const auto& el = m_subtypes.find(race_id);
    assert( el != m_subtypes.end());
    return el->second;
}

bool
RaceDescriptors::isGood(TYPE::RACE race_id) const
{
    const auto& el = m_races.find(TYPE::KIND::GOOD);
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
//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);
//}
