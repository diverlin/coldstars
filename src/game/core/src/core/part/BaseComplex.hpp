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

namespace core {
namespace control {
class SpaceObject;
class Vehicle;
} // namespace control
} // namespace core

namespace core {
namespace complex {

class Base
{
public:
    Base(core::control::Vehicle*);
    ~Base() = default;

protected:
    core::control::Vehicle* _vehicle() const { return m_vehicle; }

    bool _checkDistanceToTarget(core::control::SpaceObject*, int) const;
    STATUS _checkTarget(core::control::SpaceObject*) const;

private:
    core::control::Vehicle* m_vehicle = nullptr;

    bool __isTargetAlive(core::control::SpaceObject*) const;
    bool __isTargetInSpace(core::control::SpaceObject*) const;
    bool __isTargetInSameStarSystem(core::control::SpaceObject*) const;
};

} // namespace complex
} // naemspace core
