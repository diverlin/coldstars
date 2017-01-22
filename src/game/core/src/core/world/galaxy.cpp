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

#include "galaxy.hpp"
#include "Sector.hpp"
#include <common/constants.hpp>
#include <common/Global.hpp>
#include <common/common.hpp>
#include <managers/EntityManager.hpp>

#include <meti/RandUtils.hpp>

#include "../struct/StarSystemsConditionData.hpp"

#include <ceti/serialization/macro.hpp>

namespace model {

Galaxy::Galaxy()
{
    setType(type::entity::GALAXY_ID);
}

Galaxy::Galaxy(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Galaxy::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

bool Galaxy::operator==(const Galaxy& rhs) const {
    return isEqual(m_sectors, rhs.m_sectors);
}

bool Galaxy::operator!=(const Galaxy& rhs) const {
    return *this == rhs;
}

} // namespace model


namespace control {

Galaxy::Galaxy(model::Galaxy* model)
    :
      m_model_galaxy(model)
{
}

Galaxy::~Galaxy()
{}

model::Starsystem*
Galaxy::activeStarsystem() const
{
    assert(m_sectors.size() != 0);
    assert(false);
    //    return m_sectors[0]->activeStarsystem();
}



/* virtual */
void Galaxy::putChildrenToGarbage() const
{
    assert(false);
//    for (unsigned int i=0; i<m_sectors.size(); i++) {
//       core::global::get().entityManager().addToGarbage(m_sectors[i]);
//    }
}

void Galaxy::add(model::Sector* model, const glm::vec3& center)
{ 
    model->setGalaxy(id());
    model->setPosition(center);

    control::Sector* sector = new control::Sector(model);
    m_sectors.push_back(sector);
}

model::Sector*
Galaxy::randomSector()
{
    return meti::getRand(m_sectors)->model();
}

model::Sector*
Galaxy::closestSectorTo(model::Sector* toSector)
{
    float dist_min = INCREDIBLY_MAX_FLOAT;

    model::Sector* result = nullptr;
    for (auto sector : m_sectors) {
        float dist = meti::distance(toSector->position(), sector->position());
        if (dist < dist_min) {
            dist_min = dist;
            result = sector->model();
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
    //case ENTITY::STARSYSTEM::CONDITION::SAFE_ID:         { data_starsystems_condition.safe_num++; break; }
    //case ENTITY::STARSYSTEM::CONDITION::WAR_ID:         { data_starsystems_condition.war_num++; break; }
    //case ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID:     { data_starsystems_condition.captured_num++; break; }
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



