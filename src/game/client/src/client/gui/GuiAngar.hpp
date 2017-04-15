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
#include "MouseData.hpp"
#include <ceti/rect.hpp>

namespace control {
class Angar;
} // namespace control

namespace slot {
class Item;
class Vehicle;
} // namespace control

class GuiAngar : public BaseGuiElement
{
public:
    GuiAngar();
    ~GuiAngar();

    void BindAngar(control::Angar*);
    void UnbindAngar();

    control::Angar* GetAngar() const { return m_angar; }

    bool UpdateMouseInteractionWithVehicleSlots(const MouseData&);

    void CheckButtonsLock();
    void ButtonsAction() const;

    void RenderVehicleAndItemSlots() const;

private:
    control::Angar* m_angar = nullptr;

    slot::Item* m_repair_slot = nullptr;
    slot::Item* m_charge_slot = nullptr;

    std::vector<GuiPair<ceti::Rect, slot::Vehicle*>> m_vehicleslot_rects;
    std::vector<GuiPair<ceti::Rect, slot::Item*>> m_itemslot_rects;
};

