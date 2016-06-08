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
#include "starsystem.hpp"
#include "galaxy.hpp"
#include <managers/EntityManager.hpp>
#include "../common/constants.hpp"
#include "../common/Global.hpp"
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>
//#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../struct/StarSystemsConditionData.hpp"

Sector::Sector(int id)
    :
      m_galaxy(nullptr)
{
    setId(id);
    setTypeId(TYPE::ENTITY::SECTOR_ID);
}

Sector::~Sector()
{}

/* virtual */
void Sector::putChildrenToGarbage() const
{
    for (unsigned int i=0; i<m_starsystems.size(); i++) {
        global::get().entityManager().addToGarbage(m_starsystems[i]);
    }
}

void Sector::add(Starsystem* starsystem, const glm::vec3& center)
{ 
    starsystem->setSector(this);
    starsystem->setCenter(center);

    m_starsystems.push_back(starsystem);
}

Starsystem* Sector::randomStarSystem(int condition_id)
{
    if (condition_id == NONE_ID) {
        return m_starsystems[meti::getRandInt(0, m_starsystems.size()-1)];
    } else {
        std::vector<Starsystem*> ss_vec;
        for (unsigned int i=0; i<m_starsystems.size(); i++) {
            if (m_starsystems[i]->conditionId() == condition_id) {
                ss_vec.push_back(m_starsystems[i]);
            }
        }

        if (ss_vec.size() > 0) {
            return ss_vec[meti::getRandInt(0, ss_vec.size()-1)];
        }
    }

    return nullptr;
}



Starsystem* Sector::closestStarSystemTo(Starsystem* starsystem, int condition_id)
{
    float dist_min = INCREDIBLY_MAX_FLOAT;
    int index_min = -1;

    for (unsigned int i=0; i<m_starsystems.size(); i++)
    {
        if (m_starsystems[i]->id() != starsystem->id())
        {
            if ( (m_starsystems[i]->conditionId() == condition_id) or (condition_id == NONE_ID) )
            {
                float dist = meti::distance(starsystem->center(), m_starsystems[i]->center());

                if (dist < dist_min)
                {
                    dist_min = dist;
                    index_min = i;
                }
            }
        }
    }

    if (index_min != -1)
    {
        return m_starsystems[index_min];
    }

    return nullptr;
}

void Sector::update(int time)
{
    for (unsigned int i=0; i<m_starsystems.size(); i++)
    {
        m_starsystems[i]->update(time);
    }
}

//void Sector::FillStarSystemsCondition(StarSystemsConditionData& data_starsystems_condition) const
//{
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
//}

void Sector::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"galaxy_id", m_galaxy->id());
}

void Sector::LoadData(const boost::property_tree::ptree& load_ptree)
{
    m_data_unresolved_Sector.galaxy_id = load_ptree.get<int>("galaxy_id");
}

void Sector::ResolveData()
{
    ((Galaxy*)global::get().entityManager().get(m_data_unresolved_Sector.galaxy_id))->Add(this, data_unresolved_Orientation.center);
}

void Sector::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "sector." + std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    Sector::SaveData(save_ptree, root);
}

void Sector::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Sector::LoadData(load_ptree);
}

void Sector::Resolve()
{
    Base::ResolveData();
    Sector::ResolveData();
}




