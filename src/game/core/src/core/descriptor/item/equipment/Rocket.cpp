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

#include "Rocket.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace item {

const int Rocket::AMMO_MIN = 20;
const int Rocket::AMMO_MAX = 40;
const float Rocket::AMMO_TECH_RATE = 0.1f;

const int Rocket::RADIUS_MIN = 350;
const int Rocket::RADIUS_MAX = 550;
const float Rocket::RADIUS_TECH_RATE = 0.1f;

const int Rocket::DAMAGE_MIN = 10;
const int Rocket::DAMAGE_MAX = 20;
const float Rocket::DAMAGE_TECH_RATE = 0.1f;

const int Rocket::MODULES_NUM_MIN = 0;
const int Rocket::MODULES_NUM_MAX = 2;

const int Rocket::MASS_MIN = 30;
const int Rocket::MASS_MAX = 60;
const int Rocket::CONDITION_MIN = 100;
const int Rocket::CONDITION_MAX = 900;

const float Rocket::AMMO_WEIGHT = 0.3f;
const float Rocket::DAMAGE_WEIGHT = 0.3f;
const float Rocket::RADIUS_WEIGHT = 0.2f;
const float Rocket::MODULES_NUM_WEIGHT = 0.2f;

Rocket::Rocket()
{
    setDescriptor(descriptor::type::ROCKET_EQUIPMENT);
    setSlotType(entity::type::WEAPON_SLOT);
}

Rocket::Rocket(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Rocket::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor

