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

#ifndef STARSYSTEMDESCRIPTION_H
#define STARSYSTEMDESCRIPTION_H

#include "../common/constants.hpp"

struct StarSystemDescription
{
	public:
		int race_id;
		
		int planet_num;
		int spacestation_num_min;
		int spacestation_num_max;

		bool allow_ships;		
		bool allow_satellites;
		bool allow_spacestations;

		bool allow_ship_ranger;
		bool allow_ship_warrior;
		bool allow_ship_trader;
		bool allow_ship_pirat;
		bool allow_ship_diplomat;
														
		StarSystemDescription():
		race_id(RACE::R0_ID),
		planet_num(ENTITY::STARSYSTEM::PLANET_NUM_MIN),
		spacestation_num_min(ENTITY::STARSYSTEM::SPACESTATION_NUM_MIN),
		spacestation_num_max(ENTITY::STARSYSTEM::SPACESTATION_NUM_MAX),
		allow_ships(true),
		allow_satellites(true),
		allow_spacestations(true),			
		allow_ship_ranger(true),
		allow_ship_warrior(true),
		allow_ship_trader(true),
		allow_ship_pirat(true),
		allow_ship_diplomat(true)
		{};
		
		~StarSystemDescription() {};
}; 

#endif 
    

        


