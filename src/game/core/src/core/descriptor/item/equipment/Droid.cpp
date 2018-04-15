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

namespace core {

const int DroidDescr::REPAIR_MIN = 1;
const int DroidDescr::REPAIR_MAX = 15;
const float DroidDescr::REPAIR_TECH_RATE = 0.1f;

const int DroidDescr::MODULES_NUM_MIN = 0;
const int DroidDescr::MODULES_NUM_MAX = 2;

const int DroidDescr::MASS_MIN = 10;
const int DroidDescr::MASS_MAX = 50;
const int DroidDescr::CONDITION_MIN = 300;
const int DroidDescr::CONDITION_MAX = 2000;

const float DroidDescr::REPAIR_WEIGHT = 0.8f;
const float DroidDescr::MODULES_NUM_WEIGHT = 0.2f;

DroidDescr::DroidDescr()
{
    setType(core::Type::DROID_EQUIPMENT);
    setObType(entity::Type::DROID_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::DROID);
}

DroidDescr::DroidDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
DroidDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace core

