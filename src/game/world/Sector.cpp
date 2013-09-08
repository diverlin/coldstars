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
#include "../common/constants.hpp"
#include "../world/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../struct/StarSystemsConditionData.hpp"

Sector::Sector(int id)
:
galaxy(nullptr)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::SECTOR_ID);  
}

Sector::~Sector()
{}

/* virtual */
void Sector::PutChildsToGarbage() const
{
    for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
    {    
        EntityGarbage::Instance().Add(STARSYSTEM_vec[i]);
    }
}

void Sector::Add(StarSystem* starsystem, const glm::vec3& center) 
{ 
    starsystem->SetSector(this);
        starsystem->SetCenter(center);
        
    STARSYSTEM_vec.push_back(starsystem); 
}
             
StarSystem* Sector::GetRandomStarSystem(int condition_id)
{
    if (condition_id == NONE_ID)
    {
        return STARSYSTEM_vec[getRandInt(0, STARSYSTEM_vec.size()-1)];
    }
    else
    {
        std::vector<StarSystem*> ss_vec;    
        for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
        {
            if (STARSYSTEM_vec[i]->GetConditionId() == condition_id)
            {
                ss_vec.push_back(STARSYSTEM_vec[i]);
            }
        }
    
        if (ss_vec.size() > 0)
        {
            return ss_vec[getRandInt(0, ss_vec.size()-1)];
        }
    }

    return nullptr;
}

 
            
StarSystem* Sector::GetClosestStarSystemTo(StarSystem* starsystem, int condition_id)
{
        float dist_min = INCREDIBLY_MAX_FLOAT;
        int index_min = -1;
        
        for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
        {
                if (STARSYSTEM_vec[i]->GetId() != starsystem->GetId())
                {                        
                        if ( (STARSYSTEM_vec[i]->GetConditionId() == condition_id) or (condition_id == NONE_ID) )
                        {                                
                                float dist = distanceBetween(starsystem->GetCenter(), STARSYSTEM_vec[i]->GetCenter());
                                
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
                return STARSYSTEM_vec[index_min];
        }
        
        return nullptr;
}
             
void Sector::Update(int time)
{
    for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
         {         
             STARSYSTEM_vec[i]->Update(time);
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
        
void Sector::SaveDataUniqueSector(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"galaxy_id", galaxy->GetId());
}

void Sector::LoadDataUniqueSector(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_Sector.galaxy_id = load_ptree.get<int>("galaxy_id");
}

void Sector::ResolveDataUniqueSector()
{
    ((Galaxy*)EntityManager::Instance().GetEntityById(data_unresolved_Sector.galaxy_id))->Add(this, data_unresolved_Orientation.center);
}

void Sector::SaveData(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "sector." + int2str(GetId())+".";
    SaveDataUniqueBase(save_ptree, root); 
    SaveDataUniqueSector(save_ptree, root); 
}

void Sector::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBase(load_ptree); 
    LoadDataUniqueSector(load_ptree); 
}

void Sector::ResolveData()
{
    ResolveDataUniqueBase();  
    ResolveDataUniqueSector();  
}
            
            
  

