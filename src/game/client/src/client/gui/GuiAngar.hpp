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

class Angar;

namespace control {
class ItemSlot;
class VehicleSlot;
} // namespace control

class GuiAngar : public BaseGuiElement
{
public:
    GuiAngar();
    ~GuiAngar();

    void BindAngar(Angar*);
    void UnbindAngar();

    Angar* GetAngar() const { return angar; };

    bool UpdateMouseInteractionWithVehicleSlots(const MouseData&);

    void CheckButtonsLock();
    void ButtonsAction() const;

    void RenderVehicleAndItemSlots() const;

private:
    Angar* angar = nullptr;

    control::ItemSlot* repair_slot = nullptr;
    control::ItemSlot* charge_slot = nullptr;

    std::vector<GuiPair<ceti::Rect, control::VehicleSlot*>> m_vehicleslot_rects;
    std::vector<GuiPair<ceti::Rect, control::ItemSlot*>> m_itemslot_rects;
};

