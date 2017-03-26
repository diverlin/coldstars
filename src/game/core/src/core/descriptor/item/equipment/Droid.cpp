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

#include "Droid.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Droid::REPAIR_MIN = 1;
const int Droid::REPAIR_MAX = 15;
const float Droid::REPAIR_TECH_RATE = 0.1f;

const int Droid::MODULES_NUM_MIN = 0;
const int Droid::MODULES_NUM_MAX = 2;

const int Droid::MASS_MIN = 10;
const int Droid::MASS_MAX = 50;
const int Droid::CONDITION_MIN = 300;
const int Droid::CONDITION_MAX = 2000;

const float Droid::REPAIR_WEIGHT = 0.8f;
const float Droid::MODULES_NUM_WEIGHT = 0.2f;

Droid::Droid()
{
    setType(descriptor::Type::DROID_EQUIPMENT);
    setObType(entity::Type::EQUIPMENT);
    setObSubType(entity::Type::DROID_EQUIPMENT);
    setSlotType(entity::Type::DROID_SLOT);
}

Droid::Droid(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Droid::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor

