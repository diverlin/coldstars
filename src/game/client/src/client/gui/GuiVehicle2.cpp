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

namespace gui {

VehicleSimple::VehicleSimple()
    :
      Base(gui::Type::PLAYER_VEHICLE, gui::Type::PLAYER_VEHICLE)
{

}        

void VehicleSimple::__reset()
{
    for (auto* child: _children()) {
        delete child;
    }
    _children().clear();
    
    m_vehicle = nullptr;
}

void VehicleSimple::__bindVehicle(control::Vehicle* vehicle, float scale)
{
    __createFunctionalItemSlotsWithCircleGeometry(vehicle, scale);
    
    m_vehicle = vehicle;
}    
    
void VehicleSimple::__createFunctionalItemSlotsWithCircleGeometry(control::Vehicle* vehicle, float scale)
{   
    __reset();
    int angle = 0;
    for (slot::Item* slot: vehicle->slots()) {
        if (slot->group() == entity::Type::WEAPON_SLOT || slot->group() == entity::Type::ITEM_SLOT) {

            ButtonItemSlot2* button = new ButtonItemSlot2(getGuiItemSlotSelectorType(slot->type()),
                                                          entity::to_string(slot->type()), slot);

            glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
            button->setSize(size*scale);

            glm::vec2 offset = meti::genVec2f(160, angle);
            add(button, offset*scale);

            angle += 20;
        }
    }
}    

/* virtual override final */
void VehicleSimple::_updateUnique(client::Player* player)
{
    bool need_update = false;
    if (m_vehicle) {
        if (m_vehicle != player->npc()->vehicle()) {
            need_update = true;
        }
    } else {
        need_update = true;
    }
    
    if (need_update) {
        __bindVehicle(player->npc()->vehicle(), 0.6);
    }
}

} // namespace gui
