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

namespace control {
class Vehicle;
} // namespace control

namespace gui {

class GuiVehicle2 : public Base
{
public:
    GuiVehicle2();
    ~GuiVehicle2() {}

    virtual void _updateUnique(client::Player*) override final;

private:
    control::Vehicle* m_vehicle = nullptr;

    void Reset();
    void BindVehicle(control::Vehicle*, float scale = 1.0f);
    void CreateFunctionalItemSlotsWithCircleGeometry(control::Vehicle*, float);
};

} // namespace gui
