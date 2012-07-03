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


class Cursor
{
  	public:
        	Cursor(Player*);
        	~Cursor();
		
		void SetLeftMouseButton(bool mouse_left_button) 	{ this->mouse_left_button = mouse_left_button; };
		void SetRightMouseButton(bool mouse_right_button) 	{ this->mouse_right_button = mouse_right_button; };
		
		vec2f GetMousePos() const { return mouse_pos; };
		bool GetMouseLeftButton() const { return mouse_left_button; };
		bool GetMouseRightButton() const { return mouse_right_button; };
			
		ItemSlot* GetItemSlot() const { return slot; };
								
		void UpdateMousePos();		
		void Update(int, int);
        	
        private:
        	ItemSlot* slot;        	
        	Player* player;
        	
        	vec2f mouse_pos;
        	
        	bool mouse_left_button;
        	bool mouse_right_button;
}; 

#endif 
