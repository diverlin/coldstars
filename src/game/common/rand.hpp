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
#include <common/constants.hpp>

int getRandIntFromVec(const std::vector<int>&);
ENTITY::TYPE getRandIntFromVec(const std::vector<ENTITY::TYPE>&);

float getRandFloat(float, float);
int getRandInt(int, int);
int getRandSign();
bool getRandBool();

ENTITY::TYPE getRandNpcSubTypeId(int, const std::vector<ENTITY::TYPE>&);
const std::vector<ENTITY::TYPE>& getAllowedSubTypesByRaceId(int);

ENTITY::TYPE getRandNpcSubTypeId(int);
ENTITY::TYPE getRandNpcSubSubTypeId(ENTITY::TYPE);

ENTITY::TYPE getRand(const std::vector<ENTITY::TYPE>&);



#endif
