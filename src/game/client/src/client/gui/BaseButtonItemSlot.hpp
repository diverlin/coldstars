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


#pragma once

#include "BaseButton.hpp"

namespace slot {
class Item;
} // namespace slot

namespace jeti {
class Renderer;
} // namespace jeti

class BaseButtonItemSlot : public BaseButton
{
public:
    BaseButtonItemSlot(gui::type type_id, gui::type subtype_id, const std::string& info)
        :
          BaseButton(type_id, subtype_id, info),
          m_slot(nullptr)
    {}

    virtual ~BaseButtonItemSlot() {}

    bool GetEquiped() const;

    void SetItemSlot(slot::Item* item_slot) { m_slot = item_slot; }

protected:
    slot::Item* GetItemSlot() const { return m_slot; }

    void UpdateAnimationProgram();

    void RenderMarkEmptySlot(const jeti::Renderer&, const glm::vec2&, gui::type) const;
    void RenderMarkTarget() const;

private:
    slot::Item* m_slot = nullptr;
};

