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

#include "rand.hpp"
#include <stdlib.h>
#include <cmath>

#include "constants.hpp"
#include "../struct/gameStruct.hpp"

int getRandIntFromVec(const std::vector<int>& vec)
{
	if (vec.size()>0) { return vec[getRandInt(0, vec.size()-1)]; }
	else 		  { return NONE_ID; }
}

ENTITY::TYPE getRandIntFromVec(const std::vector<ENTITY::TYPE>& vec)
{
	if (vec.size()>0)   { return vec[getRandInt(0, vec.size()-1)]; }
	else 		        { return ENTITY::TYPE::NONE_ID; }
}
        
        
float getRandFloat(float low, float high)
{
	float precision = 100000.0;
	return (float)getRandInt((int)precision*low, (int)precision*high)/precision;
}

int getRandInt(int low, int high)
{
	return (low != high) ? rand()%(high+1-low) + low : low;
}

int getRandSign()
{
	if (getRandInt(0,10) > 5)
		return 1;
	else
		return -1; 
}

bool getRandBool()
{
	if (getRandInt(0,10) > 5)
		return true;
	else
		return false; 
}

ENTITY::TYPE getRandNpcSubTypeId(int race_id, const std::vector<ENTITY::TYPE>& subtypes)
{
	std::vector<ENTITY::TYPE> allowed_subtypes;
	const std::vector<ENTITY::TYPE>& allowed_race_subtypes =  getAllowedSubTypesByRaceId(race_id);
	
	for (unsigned int i=0; i<subtypes.size(); i++)
	{
		for (unsigned int j=0; j<allowed_race_subtypes.size(); j++)
		{
			if (subtypes[i] == allowed_race_subtypes[j])
			{
				allowed_subtypes.push_back(subtypes[i]);
			}
		}
	}
	
    return getRandIntFromVec(allowed_subtypes);  
}

ENTITY::TYPE getRandNpcSubTypeId(int race_id)
{
	const std::vector<ENTITY::TYPE>& allowed_race_subtypes =  getAllowedSubTypesByRaceId(race_id);
	return getRandIntFromVec(allowed_race_subtypes);
}

const std::vector<ENTITY::TYPE>& getAllowedSubTypesByRaceId(int race_id)
{
	switch(race_id)
    {
        case RACE::R0_ID: { return RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R1_ID: { return RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R2_ID: { return RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R3_ID: { return RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R4_ID: { return RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R6_ID: { return RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec;  break; }
        case RACE::R7_ID: { return RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec;  break; }
	}
}

ENTITY::TYPE getRandNpcSubSubTypeId(ENTITY::TYPE subtype_id)
{
        if (subtype_id == ENTITY::TYPE::RANGER_ID)
        {
                return getRandIntFromVec(RaceInformationCollector::Instance().SUBSUBTYPE_vec);
        }
        else
        {
                return subtype_id;
        }
}

ENTITY::TYPE getRand(const std::vector<ENTITY::TYPE>& types)
{
    int rindex = getRandInt(0, types.size()-1);
    return types[rindex];
}
