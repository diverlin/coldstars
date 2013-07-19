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

#ifndef CURSOR_HPP
#define CURSOR_HPP

class ItemSlot;
#include "../common/rect.hpp"
#include "MouseData.hpp"
class Base;
#include "BaseGuiElement.hpp"

class Cursor : public BaseGuiElement
{
  	public:
		Cursor();
		~Cursor();		
		
		void SetLeftMouseButtonClick(bool left_click) 		{ data_mouse.left_click = left_click; };
		void SetRightMouseButtonClick(bool right_click) 	{ data_mouse.right_click = right_click; };
		void SetFocusedObject(Base* focused_ob) { this->focused_ob = focused_ob; };
		
		const MouseData& GetMouseData() { return data_mouse; };
		ItemSlot* GetItemSlot() const { return item_slot; };
		const Rect& GetRect() const { return rect; };
		
		void UpdateMouseStuff();		
		void Update();
		bool UpdateInSpace();
		
		void RenderFocusedObjectStuff() const;
		void RenderFocusedObjectInfo();
        
        virtual void RenderUnique() const final;
				
	private:       	
		ItemSlot* item_slot;  
		Rect rect;      	
		
		MouseData data_mouse;
		
		Base* focused_ob;
}; 

#endif 
