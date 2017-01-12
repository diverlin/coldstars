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
class SpaceObject;
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
        
        void SetLeftMouseButtonClick(bool left_click)         { m_DataMouse.left_click = left_click; }
        void SetRightMouseButtonClick(bool right_click)     { m_DataMouse.right_click = right_click; }
        void SetFocusedSpaceObject(SpaceObject* space_object)   { m_FocusedSpaceObject = space_object; }
        void SetFocusedGuiElement(BaseGuiElement* gui_element)      { m_FocusedGuiElement = gui_element; }
                
        const MouseData& mouseData() const { return m_DataMouse; }
        ItemSlot* GetItemSlot() const { return m_ItemSlot; }

        void Reset();    
        void Update(Player*);
        
        void RenderFocusedObjectStuff(const jeti::Renderer&) const;
        void RenderFocusedObjectInfo(const jeti::Renderer&) const;
        
        void RenderItem(const jeti::Renderer&) const;
                
    private:           
        ItemSlot* m_ItemSlot;  
        
        MouseData m_DataMouse;
        
        SpaceObject* m_FocusedSpaceObject;
        BaseGuiElement* m_FocusedGuiElement;
        
        ceti::Box2D m_Box;

        void UpdateMouseStuff(); 
}; 

