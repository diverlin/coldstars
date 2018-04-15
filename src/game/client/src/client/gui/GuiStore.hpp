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

#include "BaseGuiElement.hpp"
#include "GuiPair.hpp"

#include <ceti/rect.hpp>
#include "MouseData.hpp"

namespace core {

namespace control {
class Store;
} // namespace control

class ItemSlot;

namespace slot {
class VehicleSlot;
} // namespace slot

} // namespace core

namespace gui {

class GuiStore : public Base
{
public:
    GuiStore();
    ~GuiStore();

    void bindStore(core::control::Store*);
    void UnbindStore();

    core::control::Store* store() const { return m_store; }

    bool updateMouseInteraction(const MouseData&);

    void renderSlots(int) const;

private:
    core::control::Store* m_store = nullptr;

    std::vector<GuiPair<ceti::Rect, core::ItemSlot*>> m_itemslot_rects;
    std::vector<GuiPair<ceti::Rect, core::slot::VehicleSlot*>> m_vehicleslot_rects;
};

} // namepsace gui


