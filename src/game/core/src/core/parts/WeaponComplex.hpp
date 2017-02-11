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

#include <core/types/EntityTypes.hpp>

#include <vector>

class Vehicle;

namespace item {
class Item;
} // namespace item

namespace model {
class SpaceObject;
} // namespace model

namespace control {
class ItemSlot;
} // namespace control

class WeaponComplex
{
public:
    WeaponComplex();
    WeaponComplex(Vehicle* owner_vehicle);
    ~WeaponComplex();

    int radiusMin() const { return m_radiusMin; }
    int radiusMax() const { return m_radiusMax; }
    int damage() const { return m_damage; }

    bool addSlot(control::ItemSlot*);
    control::ItemSlot* freeSlot() const;
    control::ItemSlot* equipedWeakestSlot() const;
    
    void prepareWeapons();

    void setTarget(model::SpaceObject*, control::ItemSlot* item_slot = nullptr);

    void fire(int, float, bool);

    void activateWeapons();
    void deactivateWeapons();
    void activateWeapons(const entity::type&);
    void deactivateWeapons(const entity::type&);

    bool isAnyWeaponSelected() const;
//    int itemsNum() const;

    void updateFireAbility();

    int guessDamage(int dist);

//    void RenderWeaponIcons() const;
//    void RenderWeaponsRange();

//    void RenderTurrels() const;

private:
    int m_damage = 0;
    int m_radiusMax = 0;
    int m_radiusMin = 0;

    Vehicle* owner_vehicle = nullptr;

//    int fire_delay = 0, d_fire_delay = 0;
    std::vector<control::ItemSlot*> m_slots;
    std::vector<control::ItemSlot*> m_slots_reloaded;

    void __reloadAllWeapons();
    void __validateAllWeaponsTarget();
};


