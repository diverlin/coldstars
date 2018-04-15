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

namespace core {
class LazerDescr;
} // namespace core

namespace model {
class LazerModel;
} // namespace model

namespace core {
namespace control {

class Lazer : public Weapon
{
public:
    Lazer(LazerDescr*, model::LazerModel*);
    virtual ~Lazer() = default;

    bool checkAmmo() const override final;
    void fire(control::SpaceObject*, float rate=1.0f) override final;

    LazerDescr* descriptor() const { m_descriptor_lazer; }
    model::LazerModel* model() const { return m_model_lazer; }

private:
    LazerDescr* m_descriptor_lazer = nullptr;
    model::LazerModel* m_model_lazer = nullptr;

    //              jeti::control::TextureOb* texOb_turrel;
    //              jeti::control::TextureOb* texOb_lazerEffect;

    void virtual addUniqueInfo();
};

} // namespace control
} // namespace core
