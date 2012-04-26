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

void EntityManager::RegisterEntity(Base* new_entity)
{
	entity_map.insert(std::make_pair(new_entity->GetId(), new_entity));
}

Base* EntityManager::GetEntityById(int id) const
{
	std::map<int, Base*>::const_iterator slice = entity_map.find(id);

	//assert((slice !=  entity_map.end()) && "<EntityManager::getEntityById>: invalid Id");

	return slice->second;
}


void EntityManager::RemoveEntity(Base* entity)
{    
	entity_map.erase(entity_map.find(entity->GetId()));
} 

void EntityManager::Clear()
{
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		delete iterator->second;
	}
	entity_map.clear();
}
		
void EntityManager::SaveEvent()
{
	boost::property_tree::ptree save_ptree;
	
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		iterator->second->SaveData(save_ptree);
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
		GalaxyBuilder::Instance().GetGalaxy()->LoadData(v.second);
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("player"))
	{
		PlayerBuilder::Instance().CreateNewPlayer(v.second.get<int>("data_id.id"));
		PlayerBuilder::Instance().GetPlayer()->LoadData(v.second);
	}
			
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("starsystem"))
	{
		StarSystemBuilder::Instance().CreateNewStarSystem(v.second.get<int>("data_id.id"));
		StarSystemBuilder::Instance().GetStarSystem()->LoadData(v.second);
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("star"))
	{
		StarBuilder::Instance().CreateNewStar(v.second.get<int>("data_id.id"));
		StarBuilder::Instance().GetStar()->LoadData(v.second);
	}
	
	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("planet"))
	//{
		//PlanetBuilder::Instance().CreateNewPlanet(v.second.get<int>("data_id.id"));
		//PlanetBuilder::Instance().GetPlanet()->LoadData(v.second);
	//}
	
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("npc"))
	{
		NpcBuilder::Instance().CreateNewNpc(v.second.get<int>("data_id.id"));
		NpcBuilder::Instance().GetNpc()->LoadData(v.second);
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("ship"))
	{
		ShipBuilder::Instance().CreateNewShip(v.second.get<int>("data_id.id"));
		ShipBuilder::Instance().GetShip()->LoadData(v.second);
	}
	
	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("kosmoport"))
	//{
		//KosmoportBuilder::Instance().CreateNewKosmoport(v.second.get<int>("data_id.id"));
		//KosmoportBuilder::Instance().GetKosmoport()->LoadData(v.second);
	//}

	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("angar"))
	//{
		//AngarBuilder::Instance().CreateNewAngar(v.second.get<int>("data_id.id"));
		//AngarBuilder::Instance().GetAngar()->LoadData(v.second);
	//}

	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("store"))
	//{
		//StoreBuilder::Instance().CreateNewStore(v.second.get<int>("data_id.id"));
		//StoreBuilder::Instance().GetStore()->LoadData(v.second);
	//}

	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("shop"))
	//{
		//ShopBuilder::Instance().CreateNewShop(v.second.get<int>("data_id.id"));
		//ShopBuilder::Instance().GetShop()->LoadData(v.second);
	//}

	//BOOST_FOREACH(boost::property_tree::ptree::value_type &v, load_ptree.get_child("goverment"))
	//{
		//GovermentBuilder::Instance().CreateNewGoverment(v.second.get<int>("data_id.id"));
		//GovermentBuilder::Instance().GetGoverment()->LoadData(v.second);
	//}
}

void EntityManager::LoadPass1()
{
	for (std::map<int, Base*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		iterator->second->ResolveData();  			
	}
}
