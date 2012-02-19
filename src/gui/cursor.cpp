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
     
     	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);
     	slot = new ItemSlot(CARGO_SLOT_ID, NULL, texOb_slot);
     	slot->setRect(0, 0, CURSOR_SLOT_WIDTH, CURSOR_SLOT_HEIGHT);
     
}


Cursor :: ~Cursor()
{}


ItemSlot* Cursor :: getSlot() { return slot; }
ItemSlot* Cursor :: getInfoSlot() { return slot_info; }
void Cursor :: setInfoSlot(ItemSlot* slot_info) { this->slot_info = slot_info; }


void Cursor :: updatePos()
{
     	slot->getRect().setCenter(g_MOUSE_POS_X, g_VIEW_HEIGHT - g_MOUSE_POS_Y);
}

void  Cursor :: resetInfoSlot()
{
	slot_info = NULL;
}

void Cursor :: update()
{
	updatePos();
}

void Cursor :: render()
{
	enable_BLEND();
                slot->renderEquipedItem();
	disable_BLEND();
}

void Cursor :: renderInfoSlot()
{
	if (slot_info != NULL)
	{
		enable_BLEND();
			slot_info->renderItemInfo();
		disable_BLEND();
	}
}
