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


#include "scanerslot.h"


ScanerSlot :: ScanerSlot()
{}

ScanerSlot :: ScanerSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
     CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);
     type_id = SCANER_SLOT_ID;
}

void ScanerSlot :: insertScanerItem(ScanerItem* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;  
        
    pTo_scanerItem = pTo_item;

    is_EQUIPED = true;

    pTo_ship->updateScanAbility();
}

void ScanerSlot :: removeScanerItem()
{
    item_subtype_id = -1;
        
    pTo_scanerItem = NULL;

    is_EQUIPED = false;

    pTo_ship->updateScanAbility();
}


void ScanerSlot :: renderFrame(GLuint flash_tex)
{
    drawTexturedRect(pTo_texOb->texture, rect, -1.5);

    //if self.flash == True:
       //drawTexturedRect(flash_tex, self.rect, -1.0)
    if (is_EQUIPED == true)
        pTo_scanerItem->render(rect);               
}


void ScanerSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void ScanerSlot :: renderItemInfo()
{
    if (is_EQUIPED == true)
        pTo_scanerItem->renderInfo(rect);
}



