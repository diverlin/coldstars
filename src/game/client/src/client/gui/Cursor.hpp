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

namespace slot {
class Item;
} // namespace slot

namespace model {
class SpaceObject;
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

class Cursor
{
public:
    Cursor();
    ~Cursor();

    void setFocusedView(view::Base* focusedView) { m_focusedView = focusedView; }
    void setFocusedView(Base* gui_element) { m_focusedGuiElement = gui_element; }

    view::Base* focusedView() const { return m_focusedView; }

    const MouseData& mouseData() const { return m_dataMouse; }
    MouseData& mouseData() { return m_dataMouse; }
    slot::Item* itemSlot() const { return m_itemSlot; }

    void update(client::Player*, const jeti::Render& render);

    void renderFocusedObjectStuff(const jeti::Render&) const;
    void renderFocusedObjectInfo(const jeti::Render&) const;

    void renderItem(const jeti::Render&) const;
    void updateMouseInput(const jeti::Render& render);

    void reset();

private:
    //glm::vec3 m_screenCoord;
    view::Base* m_focusedView = nullptr;

    slot::Item* m_itemSlot = nullptr;

    MouseData m_dataMouse;

    jeti::control::Material* m_markTargetMaterial = nullptr;
    Base* m_focusedGuiElement = nullptr;

    ceti::Box2D m_box;
}; 

} // namespace gui
