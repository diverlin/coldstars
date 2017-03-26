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

#include <slots/ItemSlot.hpp>
#include <item/Item.hpp>

#include <client/pilots/Player.hpp>
#include <pilots/Npc.hpp>

#include <spaceobjects/Vehicle.hpp>

#include <common/common.hpp>
    
           
/* virtual override final */
void ButtonItemSlot::OnPressEventMBL(Player* player)
{
    //player->GetCursor().GetItemSlot()->SwapItem(GetItemSlot());
}

         
/* virtual override final */
void ButtonItemSlot::OnPressEventMBR(Player* player)
{    
    //player->GetNpc()->vehicle()->GetComplexWeapon().SetTarget(GetItemSlot()->GetOwnerVehicle(), GetItemSlot());
}

/* virtual override final */
void ButtonItemSlot::UpdateUnique(Player* player)
{
    UpdateAnimationProgram();
}

/* virtual override final */
void ButtonItemSlot::RenderUnique(const jeti::Renderer& render, Player* player) const
{
    //GetItemSlot()->Render(render, GetBox(), glm::vec2(0,0), true);

    assert(false);
//    if (player->cursor().GetItemSlot()->item()) {
//        RenderMarkEmptySlot(render, player->cursor().mouseData().pos_screencoord, getGuiItemSlotType(player->cursor().GetItemSlot()->item()->parentSubtype()));
//    }
    
//    if (player->GetNpc()->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//    {
//        RenderMarkTarget();
//    }
}
  
/* virtual override final */
void ButtonItemSlot::RenderInfo(const jeti::Renderer& render) const
{
    if (GetItemSlot()) {
        if (GetItemSlot()->item()) {
            //GetItemSlot()->item()->RenderInfo(render, GetBox().center());
        } else {
            //GetItemSlot()->RenderInfo();
        }
    }
}
