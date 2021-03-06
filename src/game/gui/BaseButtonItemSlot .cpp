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

#include <resources/GuiTextureObCollector.hpp>

#include <render/AnimationEffect2D.hpp> 
#include <render/Render.hpp> 

#include <common/common.hpp>
#include <common/myStr.hpp>

    
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
        if (m_ItemSlot->GetSubTypeId() != TYPE::ENTITY::CARGO_SLOT_ID)
        {
            if (m_ItemSlot->GetItem() != nullptr)
            {
                if (m_ItemSlot->GetItem()->GetFunctioning() == false) 
                {
                    if (GetAnimationProgramActive() == false)
                    {
                        SetAnimationProgram(new AnimationEffect2D(glm::vec3(0.7, 0.7, 1.0), glm::vec3(1.3, 1.3, 1.0), glm::vec3(0.02, 0.02, 0.0), 0, 0, 0));
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

void BaseButtonItemSlot::RenderMarkEmptySlot(const Renderer& render, const glm::vec2& mouse_screen_coord_pos, TYPE::GUI mark_slot_subtype_id) const
{
    if (m_ItemSlot != nullptr)
    {
        if (GetEquiped() == false) 
        {
            TYPE::GUI buton_subtype_id = GetSubTypeId();
            for (TYPE::ENTITY type : SLOT_WEAPON_TYPES)
            {
                if (buton_subtype_id == getGuiItemSlotType(type))
                {
                   buton_subtype_id = TYPE::GUI::WEAPON_SLOT_ID;
                   break;
                }
            }
            for (TYPE::ENTITY type : SLOT_CARGO_TYPES)
            {
                if (buton_subtype_id == getGuiItemSlotType(type))
                {
                   buton_subtype_id = TYPE::GUI::CARGO_SLOT_ID;
                   break;
                }
            }
            for (TYPE::ENTITY type : SLOT_ARTEFACT_TYPES)
            {
                if (buton_subtype_id == getGuiItemSlotType(type))
                {
                   buton_subtype_id = TYPE::GUI::ARTEFACT_SLOT_ID;
                   break;
                }
            }
                                
            if (buton_subtype_id != TYPE::GUI::GATE_SLOT_ID)
            {            
                if ((mark_slot_subtype_id == buton_subtype_id) or (buton_subtype_id == TYPE::GUI::CARGO_SLOT_ID))  
                {
                   m_ItemSlot->RenderMark(render, GetBox(), GuiTextureObCollector::Instance().slot_mark_accept);
                }
                else
                {
                    if (GetBox().CheckInteraction(mouse_screen_coord_pos) == true)
                    {
                        m_ItemSlot->RenderMark(render, GetBox(), GuiTextureObCollector::Instance().slot_mark_reject);
                    }
                }
            }
        }
    }
}

void BaseButtonItemSlot::RenderMarkTarget() const
{
    if (m_ItemSlot != nullptr)
    {
        if (m_ItemSlot->GetItem() != nullptr)
        {              
            //box.SetScale(1.5, 1.5);
            //drawQuadMasked(GuiTextureObCollector::Instance().slot_mark_accept, box, GuiTextureObCollector::Instance().mask_round, 1.0-0.5);
            //drawQuad(GuiTextureObCollector::Instance().mark_target_slot, box);
            drawColoredTextWithBackground(int2str(m_ItemSlot->GetHitProbability()), /*font_size=*/12, GetBox().GetMiddleTop(), glm::ivec4(255));
        }
    }
}
