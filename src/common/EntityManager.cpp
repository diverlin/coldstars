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

void EntityManager::SaveEvent()
{
	for (std::map<int, BaseGameEntity*>::iterator iterator = entity_map.begin(); iterator != entity_map.end(); iterator++)
	{
		switch(iterator->second->GetTypeId())
		{	
			//case ENTITY::STARSYSTEM_ID: { StarSystemBuilder::Instance().Save((StarSystem*)iterator->second); break; }
			case ENTITY::STAR_ID:       { StarBuilder::Instance().Save((Star*)iterator->second);             break; }
			//case ENTITY::PLANET_ID:     { PlanetBuilder::Instance().Save((Planet*)iterator->second);         break; }
		}
	}
}
		


