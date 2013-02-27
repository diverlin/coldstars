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

#ifndef GALAXYDESCRIPTION_H
#define GALAXYDESCRIPTION_H

#include "../common/constants.hpp"

struct GalaxyDescription
{
	public:
		int starsystem_num;
		
		int planet_num_min;
		int planet_num_max;
		int spacestation_num_min;
		int spacestation_num_max;
		
		GalaxyDescription():
		starsystem_num(ENTITY::GALAXY::STARSYSTEM_NUM),
		planet_num_min(ENTITY::STARSYSTEM::PLANET_NUM_MIN),
		planet_num_max(ENTITY::STARSYSTEM::PLANET_NUM_MAX),		
		spacestation_num_min(ENTITY::STARSYSTEM::SPACESTATION_NUM_MIN),
		spacestation_num_max(ENTITY::STARSYSTEM::SPACESTATION_NUM_MAX)
		{};
		
		~GalaxyDescription() {};
}; 

#endif 
    

        


