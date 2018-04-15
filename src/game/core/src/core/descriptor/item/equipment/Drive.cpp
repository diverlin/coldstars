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

namespace core {

const float DriveDescr::OVERLOAD_RATE = 1.5f;
const float DriveDescr::OVERLOAD_DETERIORATION_RATE = 4.0f;

const int DriveDescr::SPEED_MIN = 3;
const int DriveDescr::SPEED_MAX = 4;
const float DriveDescr::SPEED_TECH_RATE = 0.1f;

const int DriveDescr::HYPER_MIN = 7;
const int DriveDescr::HYPER_MAX = 20;
const float DriveDescr::HYPER_TECH_RATE = 0.1f;

const int DriveDescr::MODULES_NUM_MIN = 0;
const int DriveDescr::MODULES_NUM_MAX = 2;

const int DriveDescr::MASS_MIN = 20;
const int DriveDescr::MASS_MAX = 70;
const int DriveDescr::CONDITION_MIN = 500;
const int DriveDescr::CONDITION_MAX = 2000;

const float DriveDescr::SPEED_WEIGHT = 0.4f;
const float DriveDescr::HYPER_WEIGHT = 0.4f;
const float DriveDescr::MODULES_NUM_WEIGHT = 0.2f;


DriveDescr::DriveDescr()
{
    setType(core::Type::DRIVE_EQUIPMENT);
    setObType(entity::Type::DRIVE_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::DRIVE);
}

DriveDescr::DriveDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
DriveDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace core

