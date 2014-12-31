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

#include <common/constants.hpp>
#include <types/MyInt.hpp>
#include <struct/RaceInformationCollector.hpp>

TYPE::ENTITY getRandNpcSubTypeId(TYPE::RACE race_id, const std::vector<TYPE::ENTITY>& subtypes)
{
    std::vector<TYPE::ENTITY> allowed_subtypes;
    const std::vector<TYPE::ENTITY>& allowed_race_subtypes =  getAllowedSubTypesByRaceId(race_id);
    
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
    
    return getRand(allowed_subtypes);  
}

TYPE::ENTITY getRandNpcSubTypeId(TYPE::RACE race_id)
{
    const std::vector<TYPE::ENTITY>& allowed_race_subtypes =  getAllowedSubTypesByRaceId(race_id);
    return getRand(allowed_race_subtypes);
}

const std::vector<TYPE::ENTITY>& getAllowedSubTypesByRaceId(TYPE::RACE race_id)
{
    switch(race_id)
    {
        case TYPE::RACE::R0_ID: { return RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R1_ID: { return RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R2_ID: { return RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R3_ID: { return RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R4_ID: { return RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R6_ID: { return RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec;  break; }
        case TYPE::RACE::R7_ID: { return RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec;  break; }
    }
    
    return RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec; // normally this should never happend
}

TYPE::ENTITY getRandNpcSubSubTypeId(TYPE::ENTITY subtype_id)
{
    if (subtype_id == TYPE::ENTITY::RANGER_ID) {
        return getRand(RaceInformationCollector::Instance().SUBSUBTYPE_vec);
    }
    else {
        return subtype_id;
    }
}

