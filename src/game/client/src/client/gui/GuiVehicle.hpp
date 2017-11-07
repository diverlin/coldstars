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

#include <client/gui/BaseGuiElement.hpp>

namespace slot {
class Item;
} // namespace slot

namespace control {
class Vehicle;
} // namespace control

class Store;
class MouseData; // to be removed

namespace gui {

class ButtonItemSlot;

class Vehicle : public Base
{
public:
    Vehicle();
    ~Vehicle();

    bool isActive() const { return m_vehicle != nullptr; }
    bool blockManualExit() const { return m_blockManualExit; }
    bool allowFullControl() const { return m_allowFullControl; }

    void bindVehicle(control::Vehicle*,
                     const glm::vec2& offset,
                     bool full_control_on,
                     bool block_manual_closing = false,
                     float scale = 1.0f);

    void unbindVehicle();
    
    void update(client::Player*) override final;
    void render(const jeti::Render&, client::Player*) const override final;

    bool updateMouseInteraction(client::Player*);

private:
    bool m_blockManualExit;
    bool m_allowFullControl;

    slot::Item* m_slot_gate = nullptr;
    control::Vehicle* m_vehicle = nullptr;
    std::vector<ButtonItemSlot*> m_buttonslots;

    bool __updateMouseInteractionWithSlot(ButtonItemSlot*, client::Player*, const MouseData&);

    void __renderKorpus(const jeti::Render&, client::Player*) const;

    void __createKorpusGui(control::Vehicle*, float);
    void __createItemSlotsGeometry(control::Vehicle*);
    void __createFunctionalItemSlotsCircleGeometry(control::Vehicle*, float);
};

} // namespace gui

