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


#ifndef RAND_HPP
#define RAND_HPP

#include <vector>

#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>


int getRandIntFromVec(const std::vector<int>&);
TYPE::ENTITY getRandIntFromVec(const std::vector<TYPE::ENTITY>&);
TYPE::RACE getRandIntFromVec(const std::vector<TYPE::RACE>&);

float getRandFloat(float, float);
int getRandInt(int, int);
int getRandSign();
bool getRandBool();

TYPE::ENTITY getRandNpcSubTypeId(TYPE::RACE, const std::vector<TYPE::ENTITY>&);
const std::vector<TYPE::ENTITY>& getAllowedSubTypesByRaceId(TYPE::RACE);

TYPE::ENTITY getRandNpcSubTypeId(TYPE::RACE);
TYPE::ENTITY getRandNpcSubSubTypeId(TYPE::ENTITY);

TYPE::ENTITY getRand(const std::vector<TYPE::ENTITY>&); 

#endif
