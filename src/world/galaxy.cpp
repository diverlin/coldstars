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
#include "starsystem.hpp"
#include "../common/constants.hpp"
#include "../managers/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"

Galaxy::Galaxy(int id)
{
	data_id.id = id;
	data_id.type_id =  ENTITY::GALAXY_ID;
	data_id.subtype_id = NONE_ID;
}

Galaxy::~Galaxy()
{}

/* virtual */
void Galaxy::PutChildsToGarbage() const
{
	for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
	{	
		EntityGarbage::Instance().Add(STARSYSTEM_vec[i]);
	}
}

void Galaxy::Add(StarSystem* starsystem, const vec2f& center) 
{ 
	starsystem->SetGalaxy(this);
        starsystem->GetPoints().SetCenter(center);
        
	STARSYSTEM_vec.push_back(starsystem); 
}
     		
StarSystem* Galaxy::GetRandomStarSystem(int condition_id)
{
	if (condition_id == NONE_ID)
	{
		return STARSYSTEM_vec[getRandInt(0, STARSYSTEM_vec.size()-1)];
	}
	else
	{
		std::vector<StarSystem*> ss_vec;
	
		for (unsigned int i = 0; i<STARSYSTEM_vec.size(); i++)
		{
			if (STARSYSTEM_vec[i]->GetConditionId() == condition_id)
			{
				ss_vec.push_back(STARSYSTEM_vec[i]);
			}
		}
	
		return ss_vec[getRandInt(0, ss_vec.size()-1)];
	}
}
     		
void Galaxy::Update(Player* player, int time)
{
	for (unsigned int i=0; i<STARSYSTEM_vec.size(); i++)
     	{
     		bool simulation_detalied = false;
     		if (player->GetNpc()->GetVehicle()->GetStarSystem()->GetId() == STARSYSTEM_vec[i]->GetId())
		{
			simulation_detalied = true;
		}
		 
     		STARSYSTEM_vec[i]->Update(time, simulation_detalied);
     	}
}

void Galaxy::SaveDataUniqueGalaxy(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Galaxy::LoadDataUniqueGalaxy(const boost::property_tree::ptree& load_ptree)
{}

void Galaxy::ResolveDataUniqueGalaxy()
{}

void Galaxy::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "galaxy." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root); 
	SaveDataUniqueGalaxy(save_ptree, root); 
}

void Galaxy::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree); 
	LoadDataUniqueGalaxy(load_ptree); 
}

void Galaxy::ResolveData()
{
	ResolveDataUniqueBase();  
	ResolveDataUniqueGalaxy();  
}
    		
    		
  

