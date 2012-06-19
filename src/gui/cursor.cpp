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


Cursor::Cursor(Player* player):
mouse_left_button(false), 
mouse_right_button(false)
{
	this->player = player;
	
     	slot = GetNewItemSlot(ITEMSLOT::CARGO_ID);
     	slot->SetRect(0, 0, GUI::ITEMSLOT::WIDTH_FOR_CURSOR, GUI::ITEMSLOT::HEIGHT_FOR_CURSOR);
}

Cursor::~Cursor()
{}

void Cursor::UpdateMousePos()
{
        const sf::Input& Input = Gui::GetWindow().GetInput();
        mouse_pos.Set(Input.GetMouseX(), Input.GetMouseY());
}

void Cursor::Update()
{
     	slot->GetRect().SetCenter(mouse_pos.x, player->GetScreen()->GetHeight()  - mouse_pos.y);
}


