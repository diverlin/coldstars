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

const int GrappleDescr::STRENGTH_MIN = 6;
const int GrappleDescr::STRENGTH_MAX = 50;
const float GrappleDescr::STRENGTH_TECH_RATE = 0.1f;

const int GrappleDescr::RADIUS_MIN = 100;
const int GrappleDescr::RADIUS_MAX = 200;
const float GrappleDescr::RADIUS_TECH_RATE = 0.1f;

const int GrappleDescr::SPEED_MIN = 100;
const int GrappleDescr::SPEED_MAX = 170;
const float GrappleDescr::SPEED_TECH_RATE = 0.1f;

const int GrappleDescr::MODULES_NUM_MIN = 0;
const int GrappleDescr::MODULES_NUM_MAX = 2;
const int GrappleDescr::MASS_MIN = 10;
const int GrappleDescr::MASS_MAX = 40;
const int GrappleDescr::CONDITION_MIN = 100;
const int GrappleDescr::CONDITION_MAX = 1000;

const float GrappleDescr::STRENGTH_WEIGHT = 0.4f;
const float GrappleDescr::RADIUS_WEIGHT = 0.3f;
const float GrappleDescr::SPEED_WEIGHT = 0.2f;
const float GrappleDescr::MAXNUMITEM_WEIGHT = 0.1f;
const float GrappleDescr::MODULES_NUM_WEIGHT = 0.1f;

GrappleDescr::GrappleDescr()
{
    setType(descriptor::Type::GRAPPLE_EQUIPMENT);
    setObType(entity::Type::GRAPPLE_EQUIPMENT);
    setObGroup(entity::Type::EQUIPMENT);
    setSlotType(core::SlotType::GRAPPLE);
}

GrappleDescr::GrappleDescr(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
GrappleDescr::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor



