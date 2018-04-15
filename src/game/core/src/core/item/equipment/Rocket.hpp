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

#include "Weapon.hpp"

namespace descriptor {
class Rocket;
} // namespace descriptor

namespace model {
class Rocket;
} // namespace model

namespace core {
namespace control {

class SpaceObject;

class Rocket : public Weapon
{ 
public:
    Rocket(descriptor::Rocket*, model::Rocket*);
    virtual ~Rocket() = default;

    bool checkAmmo() const override final;
    void fire(control::SpaceObject*, float rate=1.0f) override final;

    virtual void updateProperties();

    descriptor::Rocket* descriptor() const { return m_descriptor_rocket; }
    model::Rocket* model() const { return m_model_rocket; }

private:
    descriptor::Rocket* m_descriptor_rocket = nullptr;
    model::Rocket* m_model_rocket = nullptr;

    int m_ammo_add = 0;

    void virtual addUniqueInfo();

    std::string ammoStr();
};

} // namespace control
} // namespace core
