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




Cursor :: Cursor(Player* player)
{
	this->player = player;
	
     	slot = new ItemSlot();
     	slot->SetSubTypeId(SLOT::CARGO_ID);
     	slot->SetRect(0, 0, GUI::SLOT::WIDTH_FOR_CURSOR, GUI::SLOT::HEIGHT_FOR_CURSOR);
     	
     	mouse_left_button  = false;
     	mouse_right_button = false;
}


Cursor :: ~Cursor()
{}

void Cursor :: setLeftMouseButton(bool mouse_left_button) { this->mouse_left_button = mouse_left_button; }
void Cursor :: setRightMouseButton(bool mouse_right_button) { this->mouse_right_button = mouse_right_button; }
		
vec2f Cursor :: getMousePos() const { return mouse_pos; }
	
bool Cursor :: getMouseLeftButton() const { return mouse_left_button; }
bool Cursor :: getMouseRightButton() const { return mouse_right_button; }
			
ItemSlot* Cursor :: getSlot() { return slot; }

		
void Cursor :: updateMousePos()
{
        const sf::Input& Input = Gui::GetWindow().GetInput();
        mouse_pos.set(Input.GetMouseX(), Input.GetMouseY());
}


void Cursor :: update()
{
     	slot->GetRect().setCenter(mouse_pos.x, player->GetScreen()->getHeight()  - mouse_pos.y);
}


