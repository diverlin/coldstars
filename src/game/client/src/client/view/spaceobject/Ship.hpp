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

#include <client/view/Base.hpp>

#include <map>

namespace core {

namespace control {
class Ship;
} // namespace control

namespace slot {
class Item;
} // namespace slot

} // namespace core

namespace view {

class Turrel;

namespace effect {
class Jet;
} // namespace effect

class Ship : public Base
{
public:
    Ship(core::control::Ship*);
    ~Ship() override final;

    //        void RenderAtPlanet(const jeti::Renderer&, const glm::vec3&);
    void draw(const jeti::Render& render) const override final;

    core::control::Ship* control() const { return m_control; }

private:
    std::map<core::slot::Item*, view::Turrel*> m_slots_turrels;

    core::control::Ship* m_control = nullptr;
    std::vector<view::effect::Jet*> m_driveJets;

protected:
    void _drawSelectedWeaponsRadius(const jeti::Render& render) const;
};

} // namespace view
