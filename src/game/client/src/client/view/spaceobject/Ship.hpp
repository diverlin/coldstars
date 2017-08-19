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

#include <client/view/BaseView.hpp>

#include <map>

namespace jeti {
namespace particlesystem {
class Jet;
} // namespace aprticlesystem
} // namespace jeti

namespace control {
class Ship;
} // namespace control

namespace slot {
class Item;
} // namespace slot


namespace view {

class Dummy;
class Turrel;

class Ship : public Base
{
public:
    Ship(control::Ship*);
    ~Ship() override final;

    //        void RenderAtPlanet(const jeti::Renderer&, const glm::vec3&);
    void draw(const jeti::Render& render) const override final;

    control::Ship* control() const { return m_control; }

private:
    std::map<slot::Item*, view::Turrel*> m_slots_turrels;

    control::Ship* m_control = nullptr;
    std::vector<std::pair<jeti::particlesystem::Jet*, Dummy*>> m_driveJets;
};

} // namespace view
