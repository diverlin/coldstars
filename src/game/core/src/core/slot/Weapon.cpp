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

#include "Weapon.hpp"

#include <core/slot/ItemSlot.hpp>


namespace slot {

Weapon::Weapon()
{
}

void Weapon::setTarget(control::SpaceObject* target, slot::Item* subtarget)
{
    m_target = target;
    m_subtarget = subtarget;
}

void Weapon::reset()
{
    resetTarget();
    resetSubTarget();
}

void Weapon::resetTarget()
{
    m_target = nullptr;
    resetSubTarget();
}

void Weapon::resetSubTarget()
{
    m_subtarget = nullptr;
}

bool Weapon::validateSubTarget() const
{
    if (!m_subtarget) {
        return false;
    }
    if (m_subtarget->item()) {
        return true;
    }
    return false;
}

} // namespace slot
