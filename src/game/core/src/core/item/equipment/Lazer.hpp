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
namespace item {
class Lazer;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Lazer;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Lazer : public Weapon
{
public:
    Lazer(descriptor::item::Lazer*, model::item::Lazer*);
    virtual ~Lazer() = default;

    bool checkAmmo() const override final;
    void fire(float rate=1.0f) override final;

    descriptor::item::Lazer* descriptor() const { m_descriptor_lazer; }
    model::item::Lazer* model() const { return m_model_lazer; }

private:
    descriptor::item::Lazer* m_descriptor_lazer = nullptr;
    model::item::Lazer* m_model_lazer = nullptr;

    //              jeti::control::TextureOb* texOb_turrel;
    //              jeti::control::TextureOb* texOb_lazerEffect;

    void virtual addUniqueInfo();
};

} // namespace item
} // namespace control
