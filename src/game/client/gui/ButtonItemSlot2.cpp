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
             
#include "ButtonItemSlot2.hpp"
#include <slots/ItemSlot.hpp>
    
/* virtual override final */
void ButtonItemSlot2::OnPressEventMBL(Player* player)
{
    if (GetLocked() == false)
    {
        SetPressed(!GetPressed());
    }
    else
    {
        SetPressed(false);
    }
        
    if (GetItemSlot() != nullptr) // !!!
    {        
//        if (GetPressed() == true)
//        {
//            if (GetItemSlot()->GetSelected() == false)
//            {
//                GetItemSlot()->SelectEvent();
//            }
//        }
//        else
//        {
//            if (GetItemSlot()->GetSelected() == true)
//            {
//                GetItemSlot()->DeselectEvent();
//            }
//        }
    }
}

/* virtual override final */
void ButtonItemSlot2::ResetState()
{
    SetPressed(false);
    if (GetItemSlot() != nullptr)
    {  
//        if (GetItemSlot()->GetSelected() == true)
//        {
//            GetItemSlot()->DeselectEvent();
//        }
    }
}
        
/* virtual override final */    
void ButtonItemSlot2::UpdateUnique(Player* player)
{
    UpdateAnimationProgram();
            
    if (IsAnimationProgramActive() == false)
    {
        if (GetItemSlot() != nullptr)
        {
            if (GetPressed() == true)
            {
                GetBox().SetScale(1.5, 1.5);
            }
            else
            {
                GetBox().SetScale(1.0, 1.0);        
            }
        }
    }
    else
    {        
        if (GetPressed() == true)
        {
            ResetState();
        }
    }
}

/*virtual override final*/
void ButtonItemSlot2::RenderUnique(const jeti::Renderer& render, Player*) const
{
    if (GetItemSlot()) {
        //GetItemSlot()->Render(render, GetBox(), glm::vec2(0), false);
    }
}        
