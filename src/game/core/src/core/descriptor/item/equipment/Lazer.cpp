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

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Lazer::RADIUS_MIN = 200;
const int Lazer::RADIUS_MAX = 400;
const float Lazer::RADIUS_TECH_RATE = 0.1f;

const int Lazer::DAMAGE_MIN = 40;
const int Lazer::DAMAGE_MAX = 200;
const float Lazer::DAMAGE_TECH_RATE = 0.1f;

const int Lazer::MODULES_NUM_MIN = 0;
const int Lazer::MODULES_NUM_MAX = 2;

const int Lazer::MASS_MIN = 10;
const int Lazer::MASS_MAX = 40;
const int Lazer::CONDITION_MIN = 100;
const int Lazer::CONDITION_MAX = 1000;

const float Lazer::DAMAGE_WEIGHT = 0.4f;
const float Lazer::RADIUS_WEIGHT = 0.4f;
const float Lazer::MODULES_NUM_WEIGHT = 0.2f;

Lazer::Lazer()
{
    setDescriptor(descriptor::type::LAZER_EQUIPMENT);
    setSlotType(entity::type::WEAPON_SLOT);
}

Lazer::Lazer(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Lazer::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor

