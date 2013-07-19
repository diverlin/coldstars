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
#include <pilots/Player.hpp>
    
/*virtual final*/
void ButtonItemSlot::PressEvent(Player* player)
{
    if (m_ItemSlot)
    {    
        if ((player->GetCursor().GetItemSlot()->GetItem() == nullptr) and (m_ItemSlot->GetItem() != nullptr))
        {
            player->GetCursor().GetItemSlot()->SwapItem(m_ItemSlot);
            return;
        }
    
        if ((player->GetCursor().GetItemSlot()->GetItem() != nullptr) and (m_ItemSlot->GetItem() == nullptr))
        {
            player->GetCursor().GetItemSlot()->SwapItem(m_ItemSlot);
            return;
        }
    }
        
}

/*virtual final*/
void ButtonItemSlot::RenderUnique() const 
{
    if (m_ItemSlot)
    {
       m_ItemSlot->Render(m_Box, Vec3<float>(0,0,0), false);
    }
}
        
