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


namespace control {
class SpaceObject;
} // namespace control

namespace slot {

class Item;

class Weapon
{ 
public:
    Weapon();
    ~Weapon() = default;

    void setTarget(control::SpaceObject* target, slot::Item* subtarget = nullptr);

    control::SpaceObject* target() const { return m_target; }
    slot::Item* subtarget() const { return m_subtarget; }

    bool validateSubTarget() const;

    void reset();
    void resetTarget();
    void resetSubTarget();

private:
    control::SpaceObject* m_target = nullptr;
    slot::Item* m_subtarget = nullptr;
};

} // namespace slot
