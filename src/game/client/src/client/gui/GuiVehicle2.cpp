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

GuiVehicle2::GuiVehicle2()
:
Base(gui::type::PLAYER_VEHICLE, gui::type::PLAYER_VEHICLE),
m_vehicle(nullptr)
{

}        

void GuiVehicle2::Reset()
{
    for (auto* child: _children()) {
        delete child;
    }
    _children().clear();
    
    m_vehicle = nullptr;
}

void GuiVehicle2::BindVehicle(control::Vehicle* vehicle, float scale)
{
    CreateFunctionalItemSlotsWithCircleGeometry(vehicle, scale);
    
    m_vehicle = vehicle;
}    
    
void GuiVehicle2::CreateFunctionalItemSlotsWithCircleGeometry(control::Vehicle* vehicle, float scale)
{   
    Reset();     
    int angle = 0;
    for (slot::Item* slot: vehicle->slots())
    {
        entity::Type slot_group = slot->group();
        if ( (slot_group != entity::Type::CARGO_SLOT) && (slot_group != entity::Type::ARTEFACT_SLOT) )
        {
            entity::Type entity_type_id = slot_group;
            if (slot_group == entity::Type::WEAPON_SLOT) {
                entity_type_id = slot->type();
            }
                          
            //TextureOb* textureOb = GuiTextureObCollector::Instance().dot_purple;
            ButtonItemSlot2* button = new ButtonItemSlot2(getGuiItemSlotSelectorType(entity_type_id), entity::to_string(entity_type_id), slot);

            glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
            button->setSize(size*scale);

            glm::vec2 offset = meti::genVec2f(160, angle);
            add(button, offset*scale);

            angle += 20;
        }
    }
}    

/* virtual override final */
void GuiVehicle2::_updateUnique(client::Player* player)
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
        BindVehicle(player->npc()->vehicle(), 0.6);
    }
}

} // namespace gui
