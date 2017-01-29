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

namespace control {
class ItemSlot;
} // namespace control

namespace jeti {
class Renderer;
}

class BaseButtonItemSlot : public BaseButton
{
public:
    BaseButtonItemSlot(type::GUI type_id, type::GUI subtype_id, const std::string& info)
        :
          BaseButton(type_id, subtype_id, info),
          m_itemSlot(nullptr)
    {}

    virtual ~BaseButtonItemSlot() {};

    bool GetEquiped() const;

    void SetItemSlot(control::ItemSlot* item_slot) { m_itemSlot = item_slot; }

protected:
    control::ItemSlot* const GetItemSlot() const { return m_itemSlot; }

    void UpdateAnimationProgram();

    void RenderMarkEmptySlot(const jeti::Renderer&, const glm::vec2&, type::GUI) const;
    void RenderMarkTarget() const;

private:
    control::ItemSlot* m_itemSlot = nullptr;
};

