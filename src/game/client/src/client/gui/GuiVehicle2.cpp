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

#include "GuiVehicle2.hpp"
#include "ButtonItemSlot2.hpp"
//#include <ceti/StringUtils.hpp>
#include <common/common.hpp>
#include <client/resources/GuiTextureObCollector.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/pilot/Npc.hpp>

#include <client/pilot/Player.hpp>
#include <client/gui/constants.hpp>

namespace gui {

VehicleSimple::VehicleSimple(const glm::vec2& size)
    :
      Base(gui::Type::PLAYER_VEHICLE, gui::Type::PLAYER_VEHICLE)
{
    setSize(size);
}

void VehicleSimple::__clear()
{
    for (auto* child: _children()) {
        delete child;
    }
    _children().clear();
    
    m_vehicle = nullptr;
}

void VehicleSimple::__bindVehicle(control::Vehicle* vehicle)
{
    __clear();
    __createFunctionalItemSlotsWithCircleGeometry(vehicle);
    m_vehicle = vehicle;
}    
    
void VehicleSimple::__createFunctionalItemSlotsWithCircleGeometry(control::Vehicle* vehicle)
{   
    int angle = 0;
    for (slot::Item* slot: vehicle->slots()) {
        if (slot->type() != slot::Type::CARGO && slot->type() != slot::Type::ARTEFACT) {
            ButtonItemSlot2* button = new ButtonItemSlot2(slot);

            glm::vec2 size(gui::itemslot::WIDTH_FOR_RADAR, gui::itemslot::HEIGHT_FOR_RADAR);
            button->setSize(size);

            glm::vec2 offset = meti::genVec2f(box().size().x - 1.8f*gui::itemslot::WIDTH_FOR_RADAR, angle);
            add(button, offset);

            angle += 20;
        }
    }
}    

void VehicleSimple::_updateUnique(client::Player* player)
{
    if (m_vehicle) {
        if (m_vehicle == player->npc()->vehicle()) {
            return;
        }
    }
    __bindVehicle(player->npc()->vehicle());
}

} // namespace gui
