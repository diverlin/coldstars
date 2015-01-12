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
#include "../common/constants.hpp"
#include "../world/EntityManager.hpp"
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>

#include "../garbage/EntityGarbage.hpp"
#include "../struct/StarSystemsConditionData.hpp"

Galaxy::Galaxy(int id)
{
    setId(id);
    setTypeId(TYPE::ENTITY::GALAXY_ID);
}

Galaxy::~Galaxy()
{}

/* virtual */
void Galaxy::putChildrenToGarbage() const
{
    for (unsigned int i=0; i<SECTOR_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(SECTOR_vec[i]);
    }
}

void Galaxy::Add(Sector* sector, const glm::vec3& center) 
{ 
    sector->SetGalaxy(this);
    sector->SetCenter(center);

    SECTOR_vec.push_back(sector);
}

Sector* Galaxy::GetRandomSector()
{
    return SECTOR_vec[meti::getRandInt(0, SECTOR_vec.size()-1)];
}



Sector* Galaxy::GetClosestSectorTo(Sector* sector)
{
    float dist_min = INCREDIBLY_MAX_FLOAT;
    int index_min = -1;

    for (unsigned int i=0; i<SECTOR_vec.size(); i++)
    {
        float dist = meti::distance(sector->GetCenter(), SECTOR_vec[i]->GetCenter());
        if (dist < dist_min)
        {
            dist_min = dist;
            index_min = i;
        }
    }

    if (index_min != -1)
    {
        return SECTOR_vec[index_min];
    }

    return nullptr;
}

void Galaxy::Update(int time)
{
    for (unsigned int i=0; i<SECTOR_vec.size(); i++)
    {
        SECTOR_vec[i]->Update(time);
    }
}

void Galaxy::FillStarSystemsCondition(StarSystemsConditionData& data_starsystems_condition) const
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

void Galaxy::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Galaxy::LoadData(const boost::property_tree::ptree& load_ptree)
{}

void Galaxy::ResolveData()
{}

void Galaxy::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "galaxy." + std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    Galaxy::SaveData(save_ptree, root);
}

void Galaxy::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Galaxy::LoadData(load_ptree);
}

void Galaxy::Resolve()
{
    Base::ResolveData();
    Galaxy::ResolveData();
}




