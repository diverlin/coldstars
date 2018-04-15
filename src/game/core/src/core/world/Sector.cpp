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

#include "Sector.hpp"
#include <core/world/starsystem.hpp>
#include <core/world/galaxy.hpp>
#include <core/model/world/Sector.hpp>
#include <core/manager/EntityManager.hpp>
#include "../common/constants.hpp"
#include "../common/Global.hpp"
#include <common/common.hpp>
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>
//#include "../pilots/Player.hpp"
#include <core/pilot/Npc.hpp>

#include "../struct/StarSystemsConditionData.hpp"

#include <core/model/world/starsystem.hpp>

#include <ceti/serialization/macro.hpp>


namespace core {
namespace control {

Sector::Sector(SectorDescr* descr, model::Sector* model)
    :
      Base(descr, model)
    , m_descriptor_sector(descr)
    , m_model_sector(model)
{
}

Sector::~Sector()
{}

/* virtual */
void Sector::putChildrenToGarbage() const
{
    assert(false);
//    for (unsigned int i=0; i<m_starsystems.size(); i++) {
//       manager::EntityManager::get().addToGarbage(m_starsystems[i]);
//    }
}

void
Sector::add(control::StarSystem* starsystem, const glm::vec3& center)
{
    starsystem->model()->setSector(model()->id());
    starsystem->model()->setPosition(center);

    m_starsystems.push_back(starsystem);
}

StarSystem*
Sector::randomStarSystem(int condition_id)
{
    StarSystem* result = nullptr;
    if (condition_id == NONE) {
        result = meti::rand::get_element_or_die(m_starsystems);
    } else {
        std::vector<StarSystem*> ss_vec;
        for (StarSystem* starsystem: m_starsystems) {
            if (starsystem->conditionId() == condition_id) {
                ss_vec.push_back(starsystem);
            }
        }
        if (ss_vec.size()) {
            result = meti::rand::get_element_or_die(ss_vec);
        }
    }

    return result;
}



StarSystem*
Sector::closestStarsystemTo(StarSystem* toStarsystem, int condition_id)
{
    float dist_min = INCREDIBLY_MAX_FLOAT;
    StarSystem* result = nullptr;
    assert(false);
    for (auto starsystem: m_starsystems) {
        if (starsystem->id() != toStarsystem->id()) {
            if ( (starsystem->conditionId() == condition_id) || (condition_id == NONE) ) {
                assert(false);
//                float dist = meti::distance(starsystem->position(), toStarsystem->position());
//                if (dist < dist_min) {
//                    dist_min = dist;
//                    result = starsystem;
//                }
            }
        }
    }

    return result;
}

void Sector::update(int time)
{
    for (StarSystem* starsystem: m_starsystems) {
        starsystem->update_server(time);
    }
}

//void Sector::FillStarSystemsCondition(StarSystemsConditionData& data_starsystems_condition) const
//{
//data_starsystems_condition.Reset();

//for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
//{
//switch (STARSYSTEM_vec[i]->GetConditionId())
//{
//case ENTITY::STARSYSTEM::CONDITION::SAFE:         { data_starsystems_condition.safe_num++; break; }
//case ENTITY::STARSYSTEM::CONDITION::WAR:         { data_starsystems_condition.war_num++; break; }
//case ENTITY::STARSYSTEM::CONDITION::CAPTURED:     { data_starsystems_condition.captured_num++; break; }
//}
//}
//}

//void Sector::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    save_ptree.put(root+"galaxy_id", m_galaxy->id());
//}

//void Sector::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    m_data_unresolved_Sector.galaxy_id = load_ptree.get<int>("galaxy_id");
//}

//void Sector::ResolveData()
//{
//    //((Galaxy*)manager::EntityManager::get().get(m_data_unresolved_Sector.galaxy_id))->add(this, data_unresolved_Orientation.center);
//}

//void Sector::Save(boost::property_tree::ptree& save_ptree) const
//{
//    std::string root = "sector." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    Sector::SaveData(save_ptree, root);
//}

//void Sector::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//    Sector::LoadData(load_ptree);
//}

//void Sector::Resolve()
//{
//    Base::ResolveData();
//    Sector::ResolveData();
//}

} // namespace control
} // namespace core

