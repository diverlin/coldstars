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

namespace core {

class ItemSlot;

namespace control {
class Vehicle;
class SpaceObject;

namespace item {
class Weapon;
} // namespace item

} // namespace control

namespace complex {

class Weapon : public Base
{
public:
    Weapon(control::Vehicle*);
    ~Weapon() = default;

    int radiusMin() const { return m_radiusMin; }
    int radiusMax() const { return m_radiusMax; }
    int damage() const { return m_damage; }

    std::vector<ItemSlot*> weaponSlots() const { return m_slots; }

    bool addSlot(ItemSlot*);
    ItemSlot* freeSlot() const;
    ItemSlot* equipedWeakestSlot() const;
    
    void prepare();

    bool setTarget(control::SpaceObject*, ItemSlot* item_slot = nullptr);

    void updateFire(int, float);

    void activate();
    void deactivate();
    void activate(const entity::Type&);
    void deactivate(const entity::Type&);

    bool isAnyWeaponSelected() const;
//    int itemsNum() const;

    void updateFireAbility();

    int guessDamage(int dist = 0);

//    void RenderWeaponIcons() const;
//    void RenderWeaponsRange();

//    void RenderTurrels() const;

    std::vector<control::item::Weapon*> rockets() const;

    std::vector<int> radiusesOfSelectedWeapons() const;

private:
    int m_damage = 0;
    int m_radiusMax = 0;
    int m_radiusMin = 0;

//    Vehicle* owner_vehicle = nullptr;

//    int fire_delay = 0, d_fire_delay = 0;
    ceti::pack<ItemSlot*> m_slots;
    ceti::pack<ItemSlot*> m_slots_reloaded;

    void __reload();
    void __validateTargets();

    ItemSlot* __nextSlotReadyToFire() const;
    std::vector<control::item::Weapon*> __functionalWeapons(entity::Type type = entity::Type::ANY) const;
};

} // namespace complex
} // namespace core
