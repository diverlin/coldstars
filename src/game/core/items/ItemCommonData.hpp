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

#include <types/TechLevelTypes.hpp>
#include <types/RaceTypes.hpp>

class Descriptor;

struct ItemCommonData 
{
    ItemCommonData()
    {}

    TYPE::RACE race = TYPE::RACE::R0_ID;
    TYPE::TECH tech = TYPE::TECH::NONE_ID;
    unsigned int modules_num = 0;
    unsigned int condition = 0;
    unsigned int deterioration = 0;
    float deterioration_overload_rate = 0.0f;
    unsigned int mass = 0;
};

ItemCommonData extractCommonData(const Descriptor& descriptor);
