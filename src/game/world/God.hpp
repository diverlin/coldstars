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

#ifndef GOD_HPP
#define GOD_HPP

#include <common/constants.hpp>
#include <common/Date.hpp>
#include <common/RaceTypes.hpp>

#include <struct/StarSystemsConditionData.hpp>

class Galaxy;
class GalaxyDescription;
class StarSystem;
class StarSystemDescription;
class Planet;

class God
{
	public:
		static God& Instance();
		~God();

		void Init(Galaxy*, const GalaxyDescription&);
		void Update(const Date&);

    private:
		God();
		God(const God&) = delete;
		God& operator=(const God&) = delete;
   	
        Date last_update_date;
        Galaxy* galaxy;
        
        StarSystemsConditionData data_starsystems_condition;
        
        void CreateLife(const GalaxyDescription&) const;
        void CreateInvasion(const GalaxyDescription&) const;
        
        void CreateLifeAtPlanet(Planet*, const StarSystemDescription&) const;
        
        void CreateSpaceStations(StarSystem*, int) const;
        void CreateShipsInSpace(StarSystem*, int, TYPE::RACE, ENTITY::TYPE subtype_id = ENTITY::TYPE::NONE_ID, ENTITY::TYPE subsubtype_id = ENTITY::TYPE::NONE_ID) const;   
        
        void ProceedInvasion() const;
}; 

#endif 
    

        


