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

#include <core/types/RaceTypes.hpp>
#include <core/types/TechLevelTypes.hpp>

#include <ceti/type/IdType.hpp>

namespace descriptor {
class BaseOLD;
} // namespace descriptor

namespace item {
namespace equipment {

class Lazer;

class LazerBuilder
{
public:
    LazerBuilder();
    ~LazerBuilder();

    Lazer* createTemplate(int_t id = NONE) const;
    Lazer* getNew(type::tech tech_level = type::tech::NONE, type::race race_id = type::race::NONE_ID, int damage_orig = NONE, int radius_orig = NONE) const;

private:
    void createInternals(Lazer*, type::tech, type::race, int, int) const;
}; 

} // namespace equipment
} // namespace item

