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


#include "protectorslot.h"

ProtectorSlot :: ProtectorSlot()
{}

ProtectorSlot :: ProtectorSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
     CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);
     type_id = PROTECTOR_SLOT_ID;
}

void ProtectorSlot :: insertProtectorItem(ProtectorItem* pTo_item)
{
    pTo_item->pTo_ship = this->pTo_ship;
    // printf("pTo_item->pTo_ship->id  = %i\n", pTo_item->pTo_ship->id);
    // printf("this->pTo_ship->id      = %i\n", this->pTo_ship->id);
    // printf("pTo_item->pTo_shield->pTo_ship->id      = %i\n", pTo_item->pTo_shield->pTo_protectorItem->pTo_ship->id);

    item_subtype_id = pTo_item->subtype_id;    
        
    pTo_protectorItem = pTo_item;

    is_EQUIPED = true;

    pTo_ship->updateProtectionAbility();
}

void ProtectorSlot :: removeProtectorItem()
{
    item_subtype_id = -1;    
        
    pTo_protectorItem = NULL;

    is_EQUIPED = false;

    pTo_ship->updateProtectionAbility();
}


void ProtectorSlot :: renderFrame(GLuint flash_tex)
{
    drawTexturedRect(pTo_texOb->texture, rect, -1.5);

    //if self.flash == True:
       //drawTexturedRect(flash_tex, self.rect, -1.0)
    if (is_EQUIPED == true)
        pTo_protectorItem->render(rect);   
}


void ProtectorSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}


void ProtectorSlot :: renderItemInfo()
{
    if (is_EQUIPED == true)
        pTo_protectorItem->renderInfo(rect);   
}





