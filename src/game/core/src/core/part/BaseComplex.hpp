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

#include <ceti/Pack.hpp>

#include <core/type/StatusType.hpp>

namespace control {
class SpaceObject;
class Vehicle;
} // namespace control

namespace complex {

class Base
{
public:
    Base(control::Vehicle*);
    ~Base() = default;

protected:
    control::Vehicle* _vehicle() const { return m_vehicle; }

    bool _checkDistanceToTarget(control::SpaceObject*, int) const;
    STATUS _checkTarget(control::SpaceObject*) const;

private:
    control::Vehicle* m_vehicle = nullptr;

    bool __isTargetAlive(control::SpaceObject*) const;
    bool __isTargetInSpace(control::SpaceObject*) const;
    bool __isTargetInSameStarSystem(control::SpaceObject*) const;
};

} // namespace complex
