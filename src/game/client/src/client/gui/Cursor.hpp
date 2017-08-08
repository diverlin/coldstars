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
#include <ceti/Box2D.hpp>

class ItemSlot;

namespace model {
class SpaceObject;
} // namespace model

class BaseGuiElement;
class Player;

namespace jeti {
class Render;
}

namespace view {
class Base;
}

namespace gui {

class Cursor
{
public:
    Cursor();
    ~Cursor();

    void leftMouseButtonClick() { m_dataMouse.event = MouseData::LeftButtonClick; }
    void rightMouseButtonClick() { m_dataMouse.event = MouseData::RightButtonClick; }

    void setFocusedView(view::Base* focusedView) { m_focusedView = focusedView; }
    void setFocusedView(BaseGuiElement* gui_element) { m_focusedGuiElement = gui_element; }

    view::Base* focusedView() const { return m_focusedView; }

    const MouseData& mouseData() const { return m_dataMouse; }
    ItemSlot* itemSlot() const { return m_itemSlot; }

    void update(Player*, const jeti::Render& render);

    void renderFocusedObjectStuff(const jeti::Render&) const;
    void renderFocusedObjectInfo(const jeti::Render&) const;

    void renderItem(const jeti::Render&) const;
    void updateMouseInput(const jeti::Render& render);

private:
    glm::vec3 m_screenCoord;
    view::Base* m_focusedView = nullptr;

    ItemSlot* m_itemSlot = nullptr;

    MouseData m_dataMouse;

    BaseGuiElement* m_focusedGuiElement = nullptr;

    ceti::Box2D m_box;

    void __reset();
}; 

} // namespace gui
