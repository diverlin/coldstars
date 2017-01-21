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
#include <core/types/EntityTypes.hpp>
#include <core/common/GameDate.hpp>
#include <core/struct/StarSystemsConditionData.hpp>


class Starsystem;
class Planet;

namespace model {
class Galaxy;
} // namespace model

namespace control {
class Galaxy;
} // namespace control

namespace descriptor {
class Galaxy;
} // namespace descriptor

class StarSystemDescriptor;

class God
{
public:
    God();
    ~God();

    void createWorld(const descriptor::Galaxy&);
    void update();

    control::Galaxy* galaxy() const { return m_galaxy; }

private:
    GameDate m_DateLastUpdate;

    StarSystemsConditionData data_starsystems_condition;

    void __createLifeAtPlanet(Planet*, const StarSystemDescriptor&) const;

    void __createSpaceStations(Starsystem*, int) const;
    void __createShips(Starsystem*, int, type::race race_id = type::race::NONE_ID, type::entity subtype_id = type::entity::NONE_ID, type::entity subsubtype_id = type::entity::NONE_ID) const;

    void __proceedInvasion(control::Galaxy*) const;

    void __createLife(control::Galaxy*, const descriptor::Galaxy&) const;
    void __createInvasion(control::Galaxy*, const descriptor::Galaxy&) const;

    control::Galaxy* m_galaxy = nullptr;
}; 







