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

#include "Scaner.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>


namespace descriptor {
namespace item {

const int Scaner::SCAN_MIN = 2;
const int Scaner::SCAN_MAX = 40;
const float Scaner::SCAN_TECH_RATE = 0.1f;

const int Scaner::MODULES_NUM_MIN = 0;
const int Scaner::MODULES_NUM_MAX = 2;

const int Scaner::MASS_MIN = 7;
const int Scaner::MASS_MAX = 38;
const int Scaner::CONDITION_MIN = 30;
const int Scaner::CONDITION_MAX = 100;

const float Scaner::SCAN_WEIGHT = 0.7f;
const float Scaner::MODULES_NUM_WEIGHT = 0.3f;


Scaner::Scaner()
{
    setType(descriptor::Type::SCANER_EQUIPMENT);
    setObType(entity::Type::EQUIPMENT);
    setObGroup(entity::Type::SCANER_EQUIPMENT);
    setSlotType(entity::Type::SCANER_SLOT);
}

Scaner::Scaner(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Scaner::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor

