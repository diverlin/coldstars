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


namespace core {

const int ScanerDescr::SCAN_MIN = 2;
const int ScanerDescr::SCAN_MAX = 40;
const float ScanerDescr::SCAN_TECH_RATE = 0.1f;

const int ScanerDescr::MODULES_NUM_MIN = 0;
const int ScanerDescr::MODULES_NUM_MAX = 2;

const int ScanerDescr::MASS_MIN = 7;
const int ScanerDescr::MASS_MAX = 38;
const int ScanerDescr::CONDITION_MIN = 30;
const int ScanerDescr::CONDITION_MAX = 100;

const float ScanerDescr::SCAN_WEIGHT = 0.7f;
const float ScanerDescr::MODULES_NUM_WEIGHT = 0.3f;


ScanerDescr::ScanerDescr()
{
    setType(core::Type::SCANER_EQUIPMENT);
    setObType(entity::Type::SCANER_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::SCANER);
}

ScanerDescr::ScanerDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
ScanerDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor

