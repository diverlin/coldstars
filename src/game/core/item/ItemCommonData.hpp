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

#pragma once

#include <types/IdType.hpp>
#include <types/TechLevelTypes.hpp>
#include <types/RaceTypes.hpp>

namespace descriptor {
class Base;
}

struct ItemCommonData 
{
    ItemCommonData()
    {}

    id_type id = NONE_ID; // changable

    TYPE::RACE race = TYPE::RACE::R0_ID;
    TYPE::TECH tech = TYPE::TECH::NONE_ID;
    int modules_num = 0;
    int condition_max = 0;
    int deterioration = 0;
    float deterioration_overload_rate = 0.0f;
    int mass = 0;
    int price = 0;
    int descriptor_type = 0;
};

ItemCommonData extractCommonData(const descriptor::Base& descriptor);
