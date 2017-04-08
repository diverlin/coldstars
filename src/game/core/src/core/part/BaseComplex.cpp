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

#include "BaseComplex.hpp"

#include <core/world/starsystem.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/SpaceObject.hpp>

namespace complex {

Base::Base(control::Vehicle* vehicle)
    :
      m_vehicle(vehicle)
{}

bool
Base::_checkDistanceToTarget(control::SpaceObject* target, int radius) const
{
    float dist = meti::distance(m_vehicle->position(), target->position());
    if (dist <= radius) {
        return true;
    }
    return false;
}

STATUS
Base::_checkTarget(control::SpaceObject* target) const
{
    if (!__isTargetAlive(target)) {
        return STATUS::TARGET_DEAD;
    }
    if (!__isTargetInSpace(target)) {
        return STATUS::TARGET_NOTIN_SPACE;
    }
    if (!__isTargetInSameStarSystem(target)) {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }
    return STATUS::TARGET_OK;
}

bool
Base::__isTargetAlive(control::SpaceObject* target) const
{
    return target->model()->isAlive();
}

bool
Base::__isTargetInSpace(control::SpaceObject* target) const
{
    return (target->model()->place() == place::Type::SPACE);
}

bool
Base::__isTargetInSameStarSystem(control::SpaceObject* target) const
{
    return (target->starsystem()->id() == m_vehicle->starsystem()->id());
}

} // namespace complex
