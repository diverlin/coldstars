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
          
             
#include "ButtonItemSlot.hpp"

#include <core/descriptor/item/Item.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/item/Item.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <client/pilot/Player.hpp>

#include <common/common.hpp>


namespace gui {
           
void ButtonItemSlot::onPressEventMBL(client::Player* player)
{
    //player->GetCursor().GetItemSlot()->SwapItem(GetItemSlot());
}

         
void ButtonItemSlot::onPressEventMBR(client::Player* player)
{    
    //player->GetNpc()->vehicle()->GetComplexWeapon().SetTarget(GetItemSlot()->GetOwnerVehicle(), GetItemSlot());
}

void ButtonItemSlot::_updateUnique(client::Player* player)
{
    _invalidateItemView();
    _updateAnimation();
}

void ButtonItemSlot::_renderUnique(const jeti::Render& render, client::Player* player) const
{
    if (m_cursorMode) {
        _drawItem(render);
    } else {
        _drawSlot(render);
        _drawItem(render);
        control::Item* taken_item = player->cursor().itemSlot()->item();
        if (taken_item) {
            _drawMarkEmptySlot(render,
                               player->cursor().mouseData().screenCoordGui(),
                               taken_item->descriptor()->slotType());
        }
        //    if (player->GetNpc()->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
        //        RenderMarkTarget();
        //    }
    }
}

void ButtonItemSlot::renderInfo(const jeti::Render& render) const
{
    if (itemSlot()) {
        if (itemSlot()->item()) {
            //GetItemSlot()->item()->RenderInfo(render, GetBox().center());
        } else {
            //GetItemSlot()->RenderInfo();
        }
    }
}

} // namespace gui
