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
    
/*virtual override final*/
void ButtonItemSlot2::PressEvent(Player* player)
{
    if (m_ItemSlot)
    {
        
        if (GetPressed() == true)
        {
            if (m_ItemSlot->GetSelected() == false)
            {
                m_ItemSlot->SelectEvent();
            }
        }
        else
        {
            if (m_ItemSlot->GetSelected() == true)
            {
                m_ItemSlot->DeselectEvent();
            }
        }    
            
        if (m_Lock == false)
        {
            if (m_Pressed == false)
            {
                m_Pressed = true;
                ShadeOn();
            }
            else
            {
                m_Pressed = false;
                ShadeOff();
            }
        }
    }
}

/*virtual override final*/	
void ButtonItemSlot2::UpdateUnique(Player* player)
{
    if (m_ItemSlot)
    {
        if ( (m_Lock == false) and (m_Pressed == false) )
        {
            m_Alpha < 1.0f ? m_Alpha += 0.01f : m_Alpha = 1.0f;
        }
    }
}

/*virtual override final*/
void ButtonItemSlot2::RenderUnique(Player*) const 
{
    if (m_ItemSlot)
    {
        m_ItemSlot->Render(m_Box, Vec3<float>(0,0,0), false);
    }
}        
