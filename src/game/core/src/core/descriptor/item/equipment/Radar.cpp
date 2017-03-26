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

#include "Radar.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>


namespace descriptor {
namespace item {

const int Radar::RADIUS_MIN = 700;
const int Radar::RADIUS_MAX = 1500;
const float Radar::RADIUS_TECH_RATE = 0.1f;

const int Radar::MODULES_NUM_MIN = 0;
const int Radar::MODULES_NUM_MAX = 2;

const int Radar::MASS_MIN = 10;
const int Radar::MASS_MAX = 50;
const int Radar::CONDITION_MIN = 2000;
const int Radar::CONDITION_MAX = 10000;

const float Radar::RADIUS_WEIGHT = 0.6;
const float Radar::MODULES_NUM_WEIGHT = 0.4;

Radar::Radar()
{
    setType(descriptor::Type::RADAR_EQUIPMENT);
    setObType(entity::Type::EQUIPMENT);
    setObSubType(entity::Type::RADAR_EQUIPMENT);
    setSlotType(entity::Type::RADAR_SLOT);
}

Radar::Radar(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Radar::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor

