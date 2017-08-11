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

#include "Grapple.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Grapple::STRENGTH_MIN = 6;
const int Grapple::STRENGTH_MAX = 50;
const float Grapple::STRENGTH_TECH_RATE = 0.1f;

const int Grapple::RADIUS_MIN = 100;
const int Grapple::RADIUS_MAX = 200;
const float Grapple::RADIUS_TECH_RATE = 0.1f;

const int Grapple::SPEED_MIN = 100;
const int Grapple::SPEED_MAX = 170;
const float Grapple::SPEED_TECH_RATE = 0.1f;

const int Grapple::MODULES_NUM_MIN = 0;
const int Grapple::MODULES_NUM_MAX = 2;
const int Grapple::MASS_MIN = 10;
const int Grapple::MASS_MAX = 40;
const int Grapple::CONDITION_MIN = 100;
const int Grapple::CONDITION_MAX = 1000;

const float Grapple::STRENGTH_WEIGHT = 0.4f;
const float Grapple::RADIUS_WEIGHT = 0.3f;
const float Grapple::SPEED_WEIGHT = 0.2f;
const float Grapple::MAXNUMITEM_WEIGHT = 0.1f;
const float Grapple::MODULES_NUM_WEIGHT = 0.1f;

Grapple::Grapple()
{
    setType(descriptor::Type::GRAPPLE_EQUIPMENT);
    setObType(entity::Type::EQUIPMENT);
    setObGroup(entity::Type::GRAPPLE_EQUIPMENT);
    setSlotType(entity::Type::GRAPPLE_SLOT);
}

Grapple::Grapple(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Grapple::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor



