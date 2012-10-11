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

#ifndef CURSOR_H
#define CURSOR_H

class ItemSlot;
#include "../common/rect.hpp"
#include "MouseData.hpp"
class Player;
class BaseSpaceEntity;
#include "BaseGui.hpp"

class Cursor : public BaseGui
{
  	public:
        	Cursor();
        	~Cursor();
		
		void SetPlayer(Player* player) {this->player = player; };
		
		void SetLeftMouseButtonClick(bool left_click) 		{ data_mouse.left_click = left_click; };
		void SetRightMouseButtonClick(bool right_click) 	{ data_mouse.right_click = right_click; };
		void SetFocusedSpaceObject(BaseSpaceEntity* focused_space_ob) { this->focused_space_ob = focused_space_ob; };
		
		const MouseData& GetMouseData() { return data_mouse; };
		ItemSlot* GetItemSlot() const { return item_slot; };
		const Rect& GetRect() const { return rect; };
								
		void UpdateMouseStuff();		
		void Update();
		bool UpdateInSpace();
		
		void RenderFocusedSpaceObjectStuff();
		
        private:
        	ItemSlot* item_slot;  
        	Rect rect;      	
        	
        	MouseData data_mouse;
        	
        	BaseSpaceEntity* focused_space_ob;
}; 

#endif 
