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

#include "BaseComplex.hpp"

#include <core/type/EntityType.hpp>

#include <ceti/Pack.hpp>

namespace control {
class Vehicle;
class SpaceObject;
} // namespace control

namespace slot {
class Item;
} // namespace slot

namespace complex {

class Weapon : public Base
{
public:
    Weapon(control::Vehicle*);
    ~Weapon() = default;

    int radiusMin() const { return m_radiusMin; }
    int radiusMax() const { return m_radiusMax; }
    int damage() const { return m_damage; }

    std::vector<slot::Item*> weaponSlots() const { return m_slots; }

    bool addSlot(slot::Item*);
    slot::Item* freeSlot() const;
    slot::Item* equipedWeakestSlot() const;
    
    void prepare();

    void setTarget(control::SpaceObject*, slot::Item* item_slot = nullptr);

    void fire(int, float);

    void select();
    void deactivateWeapons();
    void select(const entity::Type&);
    void deactivateWeapons(const entity::Type&);

    bool isAnyWeaponSelected() const;
//    int itemsNum() const;

    void updateFireAbility();

    int guessDamage(int dist = 0);

//    void RenderWeaponIcons() const;
//    void RenderWeaponsRange();

//    void RenderTurrels() const;

private:
    int m_damage = 0;
    int m_radiusMax = 0;
    int m_radiusMin = 0;

//    Vehicle* owner_vehicle = nullptr;

//    int fire_delay = 0, d_fire_delay = 0;
    ceti::pack<slot::Item*> m_slots;
    ceti::pack<slot::Item*> m_slots_reloaded;

    void __reload();
    void __validateTargets();
};

} // namespace complex

