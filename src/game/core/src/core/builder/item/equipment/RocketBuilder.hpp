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

class Rocket;

class RocketBuilder
{
public:
    RocketBuilder();
    ~RocketBuilder();

    Rocket* createTemplate(int_t id = NONE) const;
    Rocket* getNew(tech::type tech_level = tech::type::NONE, race::type race_id = race::type::NONE_ID, int ammo_max_orig = NONE, int damage_orig = NONE, int radius_orig = NONE) const;

private:
    void createInternals(Rocket*, tech::type, race::type, int, int, int) const;
}; 

} // namespace item
