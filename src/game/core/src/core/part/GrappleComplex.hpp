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

#include <ceti/Pack.hpp>

namespace core {
namespace slot {
class ItemSlot;
} // namespace slot
namespace control {
class Vehicle;
class SpaceObject;
} // namespace control
} // namespace core



namespace core {
namespace complex {

class Grapple : public Base
{
public:
    Grapple(core::control::Vehicle*);
    ~Grapple() = default;

    void setStrength(int strength) { m_strength = strength; }

    bool isObjectIsTarget(core::control::SpaceObject*) const;
    bool addTarget(core::control::SpaceObject*);
    bool removeTarget(core::control::SpaceObject*);

    void resetTargets();

    void addGrappleSlot(core::slot::ItemSlot* slot) { m_grappleSlots.add(slot); }
    bool canBeManaged(core::control::SpaceObject*) const;

    ceti::pack<core::slot::ItemSlot*> grappleSlots() const { return m_grappleSlots; }

    void UpdateGrabScenarioProgram_inDynamic();

    const ceti::pack<core::control::SpaceObject*>& targets() const { return m_targets; }

private:
    ceti::pack<core::slot::ItemSlot*> m_grappleSlots;
    ceti::pack<core::control::SpaceObject*> m_targets;

    int m_free_strength = 0;
    int m_strength = 0;
    int m_radius;
        //        void RenderGrabTrail(const jeti::Renderer&);
};

} // namespace complex
} // naemspace core
