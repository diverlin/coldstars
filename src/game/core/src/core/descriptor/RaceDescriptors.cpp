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

#include <core/descriptor/RaceDescriptors.hpp>
#include <assert.h>

RaceDescriptors::RaceDescriptors()
{
    std::vector<race::type> races_good = {
        race::type::R0,
        race::type::R1,
        race::type::R2,
        race::type::R3,
        race::type::R4
    };

    std::vector<race::type> races_evil = {
        race::type::R6,
        race::type::R7
    };

    std::vector<race::type> races_all;
    for (auto race_id: races_good) {
        races_all.push_back(race_id);
    }
    for (auto race_id: races_evil) {
        races_all.push_back(race_id);
    }

    m_races[race::KIND::GOOD] = races_good;
    m_races[race::KIND::EVIL] = races_evil;
    m_races[race::KIND::ALL] = races_all;

    for (auto race_id: races_good) {
        m_subtypes[race_id] = {
            entity::Type::RANGER,
            entity::Type::WARRIOR,
            entity::Type::TRADER,
            entity::Type::RANGER,
            entity::Type::DIPLOMAT
        };
    }

    for (auto race_id: races_evil) {
        m_subtypes[race_id] = {
            entity::Type::WARRIOR
        };
    }
//    std::map<race::type, std::vector<entity::Type>> m_subtypes;
}

RaceDescriptors::~RaceDescriptors()
{

}

const std::vector<race::type>&
RaceDescriptors::getRaces(race::KIND kind_id) const
{
    const auto& el = m_races.find(kind_id);
    assert(el != m_races.end());
    return el->second;
}

const std::vector<entity::Type>&
RaceDescriptors::getSubTypes(race::type race_id) const
{
    const auto& el = m_subtypes.find(race_id);
    assert( el != m_subtypes.end());
    return el->second;
}

bool
RaceDescriptors::isGood(race::type race_id) const
{
    const auto& el = m_races.find(race::KIND::GOOD);
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
//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R0)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R0)].size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R0)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R0)].size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R0)].size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R1)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R1)].size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R1)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R1)].size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R1)].size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R2)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R2)].size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R2)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R2)].size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R2)].size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R3)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R3)].size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R3)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R3)].size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R3)].size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R4)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R4)].size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R4)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R4)].size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R4)].size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R6)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R6)].size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R6)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R6)].size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R6)].size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

//    if (ship_ranger_texOb_vec[static_cast<int>(race::type::R7)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(entity::Type::RANGER);
//    if (ship_warrior_texOb_vec[static_cast<int>(race::type::R7)].size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    if (ship_trader_texOb_vec[static_cast<int>(race::type::R7)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(entity::Type::TRADER);
//    if (ship_pirat_texOb_vec[static_cast<int>(race::type::R7)].size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(entity::Type::PIRAT);
//    if (ship_diplomat_texOb_vec[static_cast<int>(race::type::R7)].size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(entity::Type::DIPLOMAT);
//}
