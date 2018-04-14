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

#include "Protector.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Protector::PROTECTION_MIN = 3;
const int Protector::PROTECTION_MAX = 30;
const float Protector::PROTECTION_TECH_RATE = 0.1f;

const int Protector::MODULES_NUM_MIN = 0;
const int Protector::MODULES_NUM_MAX = 2;

const int Protector::CONDITION_MIN = 2000;
const int Protector::CONDITION_MAX = 10000;
const int Protector::MASS_MIN = 20;
const int Protector::MASS_MAX = 80;

const float Protector::PROTECTION_WEIGHT = 0.8f;
const float Protector::MODULES_NUM_WEIGHT = 0.2f;

Protector::Protector()
{
    setType(descriptor::Type::PROTECTOR_EQUIPMENT);
    setObType(entity::Type::PROTECTOR_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::slot::Type::PROTECTOR);
}

Protector::Protector(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Protector::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor

