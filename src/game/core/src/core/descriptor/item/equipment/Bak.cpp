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

#include "Bak.hpp"

#include <core/types/EntityTypes.hpp>

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Bak::FUEL_MIN = 10;
const int Bak::FUEL_MAX = 30;
const float Bak::FUEL_TECH_RATE = 0.1f;

const int Bak::MODULES_NUM_MIN = 0;
const int Bak::MODULES_NUM_MAX = 2;

const int Bak::MASS_MIN = 10;
const int Bak::MASS_MAX = 40;
const int Bak::CONDITION_MIN = 30;
const int Bak::CONDITION_MAX = 100;

const float Bak::FUEL_WEIGHT = 0.7f;
const float Bak::MODULES_NUM_WEIGHT = 0.3f;

Bak::Bak()
{
    setType(descriptor::Type::BAK_EQUIPMENT);
    setObType(entity::Type::EQUIPMENT);
    setObSubType(entity::Type::BAK_EQUIPMENT);
    setSlotType(entity::Type::BAK_SLOT);
}

Bak::Bak(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Bak::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor
