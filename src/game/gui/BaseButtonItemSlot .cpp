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
          
             
#include "BaseButtonItemSlot.hpp"
#include <slots/ItemSlot.hpp>
#include <items/BaseItem.hpp>

#include <render/AnimationEffect2D.hpp> 
    
bool BaseButtonItemSlot::GetEquiped() const
{
    if (m_ItemSlot != nullptr)
    {
        if (m_ItemSlot->GetItem() != nullptr)
        {
            return true;
        }
    } 
    
    return false;
}   

void BaseButtonItemSlot::UpdateAnimationProgram()
{
    if (m_ItemSlot != nullptr)
    {
        if (m_ItemSlot->GetSubTypeId() != ENTITY::TYPE::CARGO_SLOT_ID)
        {
            if (m_ItemSlot->GetItem() != nullptr)
            {
                if (m_ItemSlot->GetItem()->GetFunctioning() == false) 
                {
                    if (GetAnimationProgramActive() == false)
                    {
                        SetAnimationProgram(new AnimationEffect2D(Vec3<float>(0.7, 0.7, 1.0), Vec3<float>(1.3, 1.3, 1.0), Vec3<float>(0.02, 0.02, 0.0), 0, 0, 0));
                        return;
                    }                    
                } 
                else
                {
                    if (GetAnimationProgramActive() == true)
                    {
                        DeleteAnimationProgram();
                        return;
                    }
                }
            }
            else
            {
                if (GetAnimationProgramActive() == true)
                {
                    DeleteAnimationProgram();
                    return;
                }
            }
        }
    }
}

void BaseButtonItemSlot::RenderMark(const Box2D& box, TextureOb* textureOb) const
{
    if (m_ItemSlot != nullptr)
    {
        m_ItemSlot->RenderMark(box, textureOb);
    }
}
