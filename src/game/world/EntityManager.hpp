
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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <cassert>
#include <string>

#include "../common/Base.hpp"
class EntityGarbage;
class Player;


class EntityManager
{
	public:
		static EntityManager& Instance();

		void SaveRequest() { save_request = true; };
		void LoadRequest() { load_request = true; };
		
		void RegisterEntity(Base*);
	
		Base* GetEntityById(unsigned long int) const;
		Player* GetPlayer() const;

		bool UpdateSaveRequest();		
		bool UpdateLoadRequest();
		
	private:
		EntityManager():save_request(false), load_request(false){}
		EntityManager(const EntityManager&);
		EntityManager& operator=(const EntityManager&);

		bool save_request, load_request;
		
		std::map<unsigned long int, Base*> entity_map;

		void RemoveEntity(Base*);

		void Clear();
				
		void SaveEvent(const std::string&);
		void LoadPass0(const std::string&);
		void LoadPass1() const;
						
		friend class EntityGarbage;
};


#endif
