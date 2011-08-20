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


#include "cursor.h"


Cursor :: Cursor()
{
     type = CURSOR_ID;
     
     TextureOb* pTo_slotTexOb   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);
     pTo_otsec_slot = new ItemSlot(UNIVERSAL_SLOT_ID, NULL, pTo_slotTexOb, 0, 0);
     
}



void Cursor :: updatePos()
{
     pTo_otsec_slot->getRect().setNewCenter(g_MOUSE_POS_X, g_VIEW_HEIGHT - g_MOUSE_POS_Y);
}

void Cursor:: renderFrame()
{
    pTo_otsec_slot->renderEquipedItem(); 
}
