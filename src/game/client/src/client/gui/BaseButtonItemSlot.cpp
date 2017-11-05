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
#include <core/slot/ItemSlot.hpp>
#include <core/item/Item.hpp>

#include <client/resources/GuiTextureObCollector.hpp>

#include <jeti/AnimationEffect2D.hpp>
#include <jeti/Render.hpp>

#include <common/common.hpp>
//#include <ceti/StringUtils.hpp>

namespace gui {
    
bool BaseButtonItemSlot::isEquiped() const
{
    if (m_slot) {
        if (m_slot->item()) {
            return true;
        }
    } 
    
    return false;
}   

void BaseButtonItemSlot::updateAnimation()
{
    if (m_slot == nullptr) {
        return;
    }
    if (m_slot->group() == entity::Group::CARGO_SLOT) {
        return;
    }
    if (!m_slot->item()) {
        if (hasAnimation()) {
            _deleteAnimationProgram();
        }
        return;
    }

    if (!m_slot->item()->isFunctioning()) {
        if (!hasAnimation()) {
            //setAnimation(new jeti::AnimationEffect2D(glm::vec3(0.7, 0.7, 1.0), glm::vec3(1.3, 1.3, 1.0), glm::vec3(0.02, 0.02, 0.0), 0, 0, 0));
        }
    } else {
        if (hasAnimation()) {
            _deleteAnimationProgram();
        }
    }
}

void BaseButtonItemSlot::RenderMarkEmptySlot(const jeti::Render& render, const glm::vec2& mouse_screen_coord_pos, Type mark_slot_group) const
{
    if (m_slot == nullptr) {
        return;
    }

    if (!isEquiped()) {
        return;
    }

    Type buton_group = group();
    for (entity::Type type: SLOT_WEAPON_TYPES) {
        if (buton_group == getGuiItemSlotType(type)) {
            buton_group = Type::WEAPON_SLOT;
            break;
        }
    }
    for (entity::Type type: SLOT_CARGO_TYPES) {
        if (buton_group == getGuiItemSlotType(type)) {
            buton_group = Type::CARGO_SLOT;
            break;
        }
    }
    for (entity::Type type: SLOT_ARTEFACT_TYPES) {
        if (buton_group == getGuiItemSlotType(type)) {
            buton_group = Type::ARTEFACT_SLOT;
            break;
        }
    }

    if (buton_group == Type::GATE_SLOT)  {
        return;
    }
    if ((mark_slot_group == buton_group) || (buton_group == Type::CARGO_SLOT)) {
        //m_ItemSlot->RenderMark(render, box(), GuiTextureObCollector::Instance().slot_mark_accept);
    } else {
        if (box().checkInteraction(mouse_screen_coord_pos)) {
            //m_ItemSlot->RenderMark(render, box(), GuiTextureObCollector::Instance().slot_mark_reject);
        }
    }
}

void BaseButtonItemSlot::RenderMarkTarget() const
{
    if (!m_slot) {
        return;
    }
    if (!m_slot->item()) {
        return;
    }

    //box.SetScale(1.5, 1.5);
    //drawQuadMasked(GuiTextureObCollector::Instance().slot_mark_accept, box, GuiTextureObCollector::Instance().mask_round, 1.0-0.5);
    //drawQuad(GuiTextureObCollector::Instance().mark_target_slot, box);
    jeti::drawColoredTextWithBackground(std::to_string(m_slot->hitProbability()), /*font_size=*/12, box().middleTop(), glm::ivec4(255));
}

} // namespace gui
