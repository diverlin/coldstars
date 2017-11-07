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
#include <core/session/Shortcuts.hpp>
#include <core/model/item/Item.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <client/resources/GuiTextureObCollector.hpp>
#include <client/resources/Utils.hpp>
#include <client/view/item/Item.hpp>

#include <jeti/AnimationEffect2D.hpp>
#include <jeti/Material.hpp>
#include <jeti/Render.hpp>

#include <common/common.hpp>


namespace gui {

BaseButtonItemSlot::BaseButtonItemSlot(slot::Item* slot)
    :
      BaseButton(Type::NONE, Type::NONE, slot::to_string(slot->type()))
    , m_slot(slot)
{
    m_material_mark_accept = new jeti::control::Material(gui::MaterialCollector::get().slot_mark_accept);
    m_material_mark_reject = new jeti::control::Material(gui::MaterialCollector::get().slot_mark_reject);
    m_material_slot = new jeti::control::Material(gui::MaterialCollector::get().slot);
}
    
BaseButtonItemSlot::~BaseButtonItemSlot()
{
    delete m_material_mark_accept;
    delete m_material_mark_reject;
    delete m_material_slot;
    delete m_itemView;
}

void BaseButtonItemSlot::__reset()
{
    delete m_itemView;
    m_itemView = nullptr;
}

void BaseButtonItemSlot::__createItemView(control::Item* item)
{
    if (m_itemView) {
        __reset();
    }

    m_itemView = new view::Item(m_slot->item());
    ceti::Box2D _box = box();
    _box.setScale(0.8f);
    m_itemView->setBox(_box);
}

void BaseButtonItemSlot::_invalidateItemView()
{
    // item is inserted
    if (!m_itemView && m_slot->item()) {
        __createItemView(m_slot->item());
    }

    // item moved out
    if (m_itemView && !m_slot->item()) {
        __reset();
    }

    // item changed
    if (m_itemView && m_slot->item()) {
        if (m_itemView->item() != m_slot->item()) {
            __createItemView(m_slot->item());
        }
    }
}

void BaseButtonItemSlot::_updateAnimation()
{
    if (!m_slot) {
        return;
    }
    if (m_slot->type() == slot::Type::CARGO) {
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

void BaseButtonItemSlot::_drawSlot(const jeti::Render& render) const
{
    render.drawQuad_HUD(box(), *m_material_slot);
}

void BaseButtonItemSlot::_drawItem(const jeti::Render& render) const
{
    if (m_itemView) {
        m_itemView->render(render);
    }
}

void BaseButtonItemSlot::_drawMarkEmptySlot(const jeti::Render& render,
                                            const glm::vec2& screen_coord,
                                            slot::Type type_to_mark) const
{
    if (m_slot->item()) {
        return;
    }
    if (m_slot->type() == slot::Type::GATE)  {
        return;
    }
    if ((type_to_mark == m_slot->type()) || (m_slot->type() == slot::Type::CARGO)) {
        render.drawQuad_HUD(box(), *m_material_mark_accept);
    } else {
        if (box().checkInteraction(screen_coord)) {
            render.drawQuad_HUD(box(), *m_material_mark_reject);
        }
    }
}

void BaseButtonItemSlot::_drawMarkTarget() const
{
    if (!m_slot->item()) {
        return;
    }

    //box.SetScale(1.5, 1.5);
    //drawQuadMasked(GuiTextureObCollector::Instance().slot_mark_accept, box, GuiTextureObCollector::Instance().mask_round, 1.0-0.5);
    //drawQuad(GuiTextureObCollector::Instance().mark_target_slot, box);
    jeti::drawColoredTextWithBackground(std::to_string(m_slot->hitProbability()), /*font_size=*/12, box().middleTop(), glm::ivec4(255));
}

} // namespace gui
