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

#include <core/world/galaxy.hpp>
#include <core/model/world/galaxy.hpp>
#include <core/world/Sector.hpp>
#include <core/model/world/Sector.hpp>
#include <common/constants.hpp>
#include <common/Global.hpp>
#include <common/common.hpp>
#include <core/manager/EntityManager.hpp>

#include <meti/RandUtils.hpp>

#include "../struct/StarSystemsConditionData.hpp"

#include <core/descriptor/world/GalaxyDescriptor.hpp>

#include <ceti/serialization/macro.hpp>

namespace core {
namespace control {

Galaxy::Galaxy(GalaxyDescr* descr, model::Galaxy* model)
    :
    Base(descr, model)
  , m_descriptor_galaxy(descr)
  , m_model_galaxy(model)

{
}

Galaxy::~Galaxy()
{}

/* virtual */
void Galaxy::putChildrenToGarbage() const
{
    assert(false);
//    for (unsigned int i=0; i<m_sectors.size(); i++) {
//       manager::EntityManager::get().addToGarbage(m_sectors[i]);
//    }
}

void Galaxy::add(Sector* sector, const meti::vec3& center)
{ 
    sector->model()->setGalaxy(id());
    sector->model()->setPosition(center);
    m_sectors.push_back(sector);
}

Sector*
Galaxy::randomSector()
{
    return meti::rand::get_element_or_die(m_sectors);
}

Sector*
Galaxy::closestSectorTo(Sector* toSector)
{
    Sector* result = nullptr;

    float dist_min = INCREDIBLY_MAX_FLOAT;
    for (auto sector : m_sectors) {
        float dist = meti::distance(toSector->model()->position(), sector->model()->position());
        if (dist < dist_min) {
            dist_min = dist;
            result = sector;
        }
    }

    return result;
}

void Galaxy::update(int time)
{
    for (Sector* sector: m_sectors) {
        sector->update(time);
    }
}

void Galaxy::analizeStarSystemsCondition(StarSystemsConditionData& data_starsystems_condition) const
{
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
}

//void Galaxy::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{}

//void Galaxy::LoadData(const boost::property_tree::ptree& load_ptree)
//{}

//void Galaxy::ResolveData()
//{}

//void Galaxy::Save(boost::property_tree::ptree& save_ptree) const
//{
//    std::string root = "galaxy." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    Galaxy::SaveData(save_ptree, root);
//}

//void Galaxy::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//    Galaxy::LoadData(load_ptree);
//}

//void Galaxy::Resolve()
//{
//    Base::ResolveData();
//    Galaxy::ResolveData();
//}

} // namespace control
} // namespace core


