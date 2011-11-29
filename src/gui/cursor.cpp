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




Cursor :: Cursor()
{
     	type_id = CURSOR_ID;
     
     	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);
     	slot = new ItemSlot(CARGO_SLOT_ID, NULL, texOb_slot, 0, 0);
     
}


Cursor :: ~Cursor()
{}


ItemSlot* Cursor :: getSlot() { return slot; }
		


void Cursor :: updatePos()
{
     	slot->getRect().setNewCenter(g_MOUSE_POS_X, g_VIEW_HEIGHT - g_MOUSE_POS_Y);
}

void Cursor :: renderFrame()
{
    	slot->renderEquipedItem(); 
}


void Cursor :: update()
{
	updatePos();
}

void Cursor :: render()
{
	enable_BLEND();
		renderFrame();
	disable_BLEND();
}
