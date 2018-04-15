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

namespace core {


namespace control {
class SpaceObject;
} // namespace control

namespace slot {

class ItemSlot;

class WeaponSlot
{ 
public:
    WeaponSlot();
    ~WeaponSlot() = default;

    void setTarget(core::control::SpaceObject* target, slot::ItemSlot* subtarget = nullptr);

    core::control::SpaceObject* target() const { return m_target; }
    slot::ItemSlot* subtarget() const { return m_subtarget; }

    bool validateSubTarget() const;

    void reset();
    void resetTarget();
    void resetSubTarget();

private:
    core::control::SpaceObject* m_target = nullptr;
    core::slot::ItemSlot* m_subtarget = nullptr;
};

} // namespace slot
} // naemspace core
