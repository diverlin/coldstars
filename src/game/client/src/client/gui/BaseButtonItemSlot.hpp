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
class Item;
} // namespace control

namespace view {
class Item;
} // namespace view

namespace slot {
class Item;
} // namespace slot

namespace jeti {

namespace control {
class Material;
} // namespace control

class Render;
} // namespace jeti


namespace gui {

class BaseButtonItemSlot : public BaseButton
{
public:
    BaseButtonItemSlot(slot::Item*);
    ~BaseButtonItemSlot();

    slot::Item* itemSlot() const { return m_slot; }

protected:
    void _createItemView();
    void _updateAnimation();
    void _drawSlot(const jeti::Render&) const;
    void _drawItem(const jeti::Render&) const;
    void _drawMarkEmptySlot(const jeti::Render&, const glm::vec2&, slot::Type) const;
    void _drawMarkTarget() const;

private:
    slot::Item* m_slot = nullptr;
    view::Item* m_itemView = nullptr;

    jeti::control::Material* m_material_mark_accept = nullptr;
    jeti::control::Material* m_material_mark_reject = nullptr;
    jeti::control::Material* m_material_slot = nullptr;

    void __reset();
    void __createItemView(control::Item*);
};

} // namespace gui
