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
#include <meti/RandUtils.hpp>
#include <stdlib.h>
#include <cmath>

#include <common/constants.hpp>
#include <ceti/type/IdType.hpp>
#include <descriptor/RaceDescriptors.hpp>
#include <common/Global.hpp>

entity::type
getRandNpcSubTypeId(race::type race_id, const std::vector<entity::type>& subtypes)
{
    std::vector<entity::type> allowed_subtypes;
    const std::vector<entity::type>& allowed_race_subtypes = core::global::get().raceDescriptors().getSubTypes(race_id);
    assert(!allowed_race_subtypes.empty());

    for (unsigned int i=0; i<subtypes.size(); i++) {
        for (unsigned int j=0; j<allowed_race_subtypes.size(); j++) {
            if (subtypes[i] == allowed_race_subtypes[j]) {
                allowed_subtypes.push_back(subtypes[i]);
            }
        }
    }
    
    return meti::getRand(allowed_subtypes);
}

entity::type
getRandNpcSubTypeId(race::type race_id)
{
    assert(!core::global::get().raceDescriptors().getSubTypes(race_id).empty());
    return meti::getRand(core::global::get().raceDescriptors().getSubTypes(race_id));
}

entity::type
getRandNpcSubSubTypeId(entity::type subtype_id)
{
//    if (subtype_id == entity::Type::RANGER_ID) {
//        return meti::getRand(core::global::get().raceDescriptors().getSubSubTypes());
//    } else {
        return subtype_id;
//    }
}

