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

//#include "EntityManager.hpp"
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>


EntityManager& EntityManager::Instance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::RegisterEntity(BaseGameEntity* new_entity)
{
	entity_map.insert(std::make_pair(new_entity->GetId(), new_entity));
}

BaseGameEntity* EntityManager::GetEntityById(int id) const
{
	std::map<int, BaseGameEntity*>::const_iterator slice = entity_map.find(id);

	//assert((slice !=  entity_map.end()) && "<EntityManager::getEntityById>: invalid Id");

	return slice->second;
}

void EntityManager::RemoveEntity(BaseGameEntity* entity)
{    
	entity_map.erase(entity_map.find(entity->GetId()));
} 

void EntityManager::Clear()
{
	for (std::map<int, BaseGameEntity*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		delete iterator->second;
	}
	entity_map.clear();
}
		
void EntityManager::SaveEvent()
{
	boost::property_tree::ptree save_ptree;
	
	for (std::map<int, BaseGameEntity*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		switch(iterator->second->GetTypeId())
		{	
			case ENTITY::GALAXY_ID:     { ((Galaxy*)iterator->second)->SaveData(save_ptree); break; } 
			case ENTITY::STARSYSTEM_ID: { ((StarSystem*)iterator->second)->SaveData(save_ptree); break; }
			case ENTITY::STAR_ID:       { ((Star*)iterator->second)->SaveData(save_ptree);   break; }
			case ENTITY::PLANET_ID:     { ((Planet*)iterator->second)->SaveData(save_ptree); break; }  
		}
	}
	
	SaveManager::Instance().SaveFile("save.info", save_ptree);
}
		
void EntityManager::LoadPass0()
{
	this->Clear();

	boost::property_tree::ptree load_ptree;
	SaveManager::Instance().LoadFile("save.info", load_ptree);
			
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("galaxy"))
	{
		GalaxyBuilder::Instance().CreateNewGalaxy(v.second.get<int>("data_id.id"));
		GalaxyBuilder::Instance().LoadPass0(v.second);
	}
		
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
	{
		StarSystemBuilder::Instance().CreateNewStarSystem(v.second.get<int>("data_id.id"));
		StarSystemBuilder::Instance().Load(v.second);
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
	{
		StarBuilder::Instance().CreateNewStar(v.second.get<int>("data_id.id"));
		StarBuilder::Instance().Load(v.second);
	}
	
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
	{
		PlanetBuilder::Instance().CreateNewPlanet(v.second.get<int>("data_id.id"));
		PlanetBuilder::Instance().LoadPass0(v.second);
	}
}

void EntityManager::LoadPass1()
{
	for (std::map<int, BaseGameEntity*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		switch(iterator->second->GetTypeId())
		{	
			case ENTITY::GALAXY_ID: 
			{ 
				Galaxy* galaxy = (Galaxy*)iterator->second;
				galaxy->ResolveData();  
				
				break; 
			}
			
			case ENTITY::STARSYSTEM_ID: 
			{ 
				StarSystem* starsystem = ((StarSystem*)iterator->second);
				starsystem->ResolveData();									
				starsystem->GetGalaxy()->Add(starsystem);

				break; 
			}
			
			case ENTITY::STAR_ID:       
			{ 
				Star* star = ((Star*)iterator->second);
				star->ResolveData();

				star->GetStarSystem()->Add(star);
								
				break; 
			}
			//case ENTITY::PLANET_ID:     { ((Planet*)iterator->second)->ResolveDataUniquePlanet();         break; }
		}
	}
}
