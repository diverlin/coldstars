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
class Renderer;
}

class Cursor
{
public:
    Cursor();
    ~Cursor();

    void setLeftMouseButtonClick(bool left_click)         { m_dataMouse.left_click = left_click; }
    void setRightMouseButtonClick(bool right_click)     { m_dataMouse.right_click = right_click; }
    void focusOn(model::SpaceObject* space_object)   { m_focusedSpaceObject = space_object; }
    void focusOn(BaseGuiElement* gui_element)      { m_focusedGuiElement = gui_element; }

    const MouseData& mouseData() const { return m_dataMouse; }
    ItemSlot* itemSlot() const { return m_itemSlot; }

    void reset();
    void update(Player*);

    void renderFocusedObjectStuff(const jeti::Renderer&) const;
    void renderFocusedObjectInfo(const jeti::Renderer&) const;

    void renderItem(const jeti::Renderer&) const;

private:
    ItemSlot* m_itemSlot = nullptr;

    MouseData m_dataMouse;

    model::SpaceObject* m_focusedSpaceObject = nullptr;
    BaseGuiElement* m_focusedGuiElement;

    ceti::Box2D m_box;

    void updateMouseStuff();
}; 

