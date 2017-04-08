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

#include "Equipment.hpp"

namespace descriptor {
namespace item {
class Weapon;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Weapon;
} // namespace item
} // namespace model

namespace control {

class SpaceObject;

namespace item {

class Weapon : public Equipment
{ 
public:
    Weapon(descriptor::item::Weapon*, model::item::Weapon*);
    virtual ~Weapon() = default;

    void setTarget(control::SpaceObject* target, slot::Item* subtarget = nullptr);
    //void setTurrel(Turrel* turrel) { m_turrel = turrel; }

    //Turrel* turrel() const { return m_turrel; }
    control::SpaceObject* target() const { return m_target; }
    slot::Item* subtarget() const { return m_subtarget; }

//    void SetBulletData(BulletData data_bullet) { data_bullet = data_bullet; }

    virtual void updateProperties();

    virtual bool checkAmmo() const = 0;
    virtual void fire(float rate=1.0f) = 0;

    int radius() const;
    int damage() const;

    bool validateSubTarget() const;

    void reset();
    void resetTarget();
    void resetSubTarget();

public:
    descriptor::item::Weapon* descriptor() const { return m_descriptor_weapon; }
    model::item::Weapon* model() const { return m_model_weapon; }

private:
    descriptor::item::Weapon* m_descriptor_weapon = nullptr;
    model::item::Weapon* m_model_weapon = nullptr;

    int m_damage_add = 0;
    int m_radius_add = 0;

    control::SpaceObject* m_target = nullptr;
    slot::Item* m_subtarget = nullptr;

//    Turrel* m_turrel = nullptr;          // only for weapons slot

//    int fire_atOnce;

//    BulletData data_bullet;

    void virtual addUniqueInfo();

    std::string damageStr();
    std::string radiusStr();
};

} // namespace item
} // namespace control
