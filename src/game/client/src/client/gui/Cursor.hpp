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

#include <client/gui/MouseData.hpp>

namespace core {
class ItemSlot;
} // namespace core

namespace model {
class SpaceObjectModel;
} // namespace model

namespace client {
class Player;
} // namespace client

namespace jeti {
namespace control {
class Material;
} //namespace control
class Render;
} // namespace jeti

namespace view {
class Base;
} // namespace view

namespace gui {

class Base;
class ButtonItemSlot;

class Cursor
{
public:
    Cursor();
    ~Cursor();

    void setFocusedView(view::Base* view) { m_focusedView = view; }
    void setFocusedItemSlot(core::ItemSlot* slot) { m_focusedItemSlot = slot; }
    void setFocusedGuiElement(Base* gui_element) { m_focusedGuiElement = gui_element; }

    view::Base* focusedView() const { return m_focusedView; }

    const MouseData& mouseData() const { return m_dataMouse; }
    MouseData& mouseData() { return m_dataMouse; }
    core::ItemSlot* itemSlot() const { return m_itemSlot; }

    void update(client::Player*, const jeti::Render& render);

    void renderFocusedObjectStuff(const jeti::Render&) const;
    void renderFocusedObjectInfo(const jeti::Render&) const;

    void updateMouseInput(const jeti::Render& render);

    void reset();

    void updateTakenItem();
    void renderTakenItem(const jeti::Render&) const;

private:
    view::Base* m_focusedView = nullptr;

    core::ItemSlot* m_focusedItemSlot = nullptr;
    core::ItemSlot* m_itemSlot = nullptr;
    gui::ButtonItemSlot* m_itemSlotGui = nullptr;

    MouseData m_dataMouse;

    jeti::control::Material* m_markTargetMaterial = nullptr;
    Base* m_focusedGuiElement = nullptr;
}; 

} // namespace gui
