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

#include "Lazer.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>

namespace core {

const int LazerDescr::RADIUS_MIN = 200;
const int LazerDescr::RADIUS_MAX = 400;
const float LazerDescr::RADIUS_TECH_RATE = 0.1f;

const int LazerDescr::DAMAGE_MIN = 40;
const int LazerDescr::DAMAGE_MAX = 200;
const float LazerDescr::DAMAGE_TECH_RATE = 0.1f;

const int LazerDescr::MODULES_NUM_MIN = 0;
const int LazerDescr::MODULES_NUM_MAX = 2;

const int LazerDescr::MASS_MIN = 10;
const int LazerDescr::MASS_MAX = 40;
const int LazerDescr::CONDITION_MIN = 100;
const int LazerDescr::CONDITION_MAX = 1000;

const float LazerDescr::DAMAGE_WEIGHT = 0.4f;
const float LazerDescr::RADIUS_WEIGHT = 0.4f;
const float LazerDescr::MODULES_NUM_WEIGHT = 0.2f;

LazerDescr::LazerDescr()
{
    setType(core::Type::LAZER_EQUIPMENT);
    setObType(entity::Type::LAZER_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::WEAPON);
}

LazerDescr::LazerDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
LazerDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor

