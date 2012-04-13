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

#include "../common/constants.hpp"

Galaxy::Galaxy(int id)
{
	data_id.id = id;
	data_id.type_id =  ENTITY::GALAXY_ID;
}

Galaxy::~Galaxy()
{}

void Galaxy::Add(StarSystem* starsystem) 
{ 
	starsystem->SetGalaxy(this);
	STARSYSTEM_vec.push_back(starsystem); 
}
     		
////ugly
StarSystem* Galaxy::GetRandomStarSystem()
{
	return STARSYSTEM_vec[getRandInt(0, STARSYSTEM_vec.size())];
}

StarSystem* Galaxy::GetRandomCapturedStarSystem()
{
	std::vector<StarSystem*> ss_vec;
	
	for (unsigned int i = 0; i<STARSYSTEM_vec.size(); i++)
	{
		if (STARSYSTEM_vec[i]->GetCaptured() == true)
		{
			ss_vec.push_back(STARSYSTEM_vec[i]);
		}
	}
	
	return ss_vec[getRandInt(0, ss_vec.size())];
}
//ugly
     		
void Galaxy::Update(int time)
{
	for (unsigned int i = 0; i < STARSYSTEM_vec.size(); i++)
     	{
		STARSYSTEM_vec[i]->Update(time, true); 
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

void Galaxy::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree); 
	LoadDataUniqueGalaxy(load_ptree); 
}

void Galaxy::ResolveData()
{
	ResolveDataUniqueBase();  
	ResolveDataUniqueGalaxy();  
}
    		
    		
  

