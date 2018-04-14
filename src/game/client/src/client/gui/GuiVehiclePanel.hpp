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

namespace core {
namespace control {
class Vehicle;
} // namespace control
} // namespace core

namespace gui {

class ButtonItemSlot2;

class VehiclePanel : public Base
{
public:
    VehiclePanel(const glm::vec2&);
    ~VehiclePanel()=default;

    void unselect(gui::Type, int offset = 0);
    void toggle(gui::Type, int offset = 0);

protected:
    virtual void _updateUnique(client::Player*) override final;

private:
    core::control::Vehicle* m_vehicle = nullptr;
    std::vector<ButtonItemSlot2*> m_slotbuttons;

    ButtonItemSlot2* __button(gui::Type, int offset) const;

    void __clear();
    void __bindVehicle(core::control::Vehicle*);
    void __createFunctionalItemSlotsWithCircleGeometry(core::control::Vehicle*);
};

} // namespace gui
