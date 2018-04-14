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

#include "Drive.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const float Drive::OVERLOAD_RATE = 1.5f;
const float Drive::OVERLOAD_DETERIORATION_RATE = 4.0f;

const int Drive::SPEED_MIN = 3;
const int Drive::SPEED_MAX = 4;
const float Drive::SPEED_TECH_RATE = 0.1f;

const int Drive::HYPER_MIN = 7;
const int Drive::HYPER_MAX = 20;
const float Drive::HYPER_TECH_RATE = 0.1f;

const int Drive::MODULES_NUM_MIN = 0;
const int Drive::MODULES_NUM_MAX = 2;

const int Drive::MASS_MIN = 20;
const int Drive::MASS_MAX = 70;
const int Drive::CONDITION_MIN = 500;
const int Drive::CONDITION_MAX = 2000;

const float Drive::SPEED_WEIGHT = 0.4f;
const float Drive::HYPER_WEIGHT = 0.4f;
const float Drive::MODULES_NUM_WEIGHT = 0.2f;


Drive::Drive()
{
    setType(descriptor::Type::DRIVE_EQUIPMENT);
    setObType(entity::Type::DRIVE_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::slot::Type::DRIVE);
}

Drive::Drive(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Drive::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor

