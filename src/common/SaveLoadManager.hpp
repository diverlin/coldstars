
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

#ifndef SAVELOADMANAGER_H
#define SAVELOADMANAGER_H

#include "../pilots/Player.hpp"
#include "../common/EntityManager.hpp"
#include "../world/starsystem.hpp"

class SaveLoadManager
{
	public:
		static SaveLoadManager& Instance();
		void SetSave(bool load) { this->save = save; };
		void SetLoad(bool load) { this->load = load; };
		
		void Update(Player*) const;
		
	private:
		SaveLoadManager():save(false), load(false){}
		SaveLoadManager(const SaveLoadManager&);
		SaveLoadManager& operator=(const SaveLoadManager&);
		
		bool save, load;

};


#endif
