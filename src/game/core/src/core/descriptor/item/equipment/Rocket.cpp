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

#include <core/type/EntityType.hpp>

#include <ceti/serialization/macro.hpp>

namespace core {

const int RocketDescr::AMMO_MIN = 20;
const int RocketDescr::AMMO_MAX = 40;
const float RocketDescr::AMMO_TECH_RATE = 0.1f;

const int RocketDescr::RADIUS_MIN = 350;
const int RocketDescr::RADIUS_MAX = 550;
const float RocketDescr::RADIUS_TECH_RATE = 0.1f;

const int RocketDescr::DAMAGE_MIN = 10;
const int RocketDescr::DAMAGE_MAX = 20;
const float RocketDescr::DAMAGE_TECH_RATE = 0.1f;

const int RocketDescr::MODULES_NUM_MIN = 0;
const int RocketDescr::MODULES_NUM_MAX = 2;

const int RocketDescr::MASS_MIN = 30;
const int RocketDescr::MASS_MAX = 60;
const int RocketDescr::CONDITION_MIN = 100;
const int RocketDescr::CONDITION_MAX = 900;

const float RocketDescr::AMMO_WEIGHT = 0.3f;
const float RocketDescr::DAMAGE_WEIGHT = 0.3f;
const float RocketDescr::RADIUS_WEIGHT = 0.2f;
const float RocketDescr::MODULES_NUM_WEIGHT = 0.2f;

RocketDescr::RocketDescr()
{
    setType(core::Type::ROCKET_EQUIPMENT);
    setObType(entity::Type::ROCKET_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::WEAPON);
}

RocketDescr::RocketDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
RocketDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor

