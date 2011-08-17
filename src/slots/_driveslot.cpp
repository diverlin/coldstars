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



#include "driveslot.h"


DriveSlot :: DriveSlot()
{}

DriveSlot :: DriveSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
     CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);
     type_id = DRIVE_SLOT_ID;
}

void DriveSlot :: insertDriveItem(DriveItem* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;    

    pTo_driveItem = pTo_item;

    is_EQUIPED = true;

    pTo_ship->updateDriveAbility();
}

void DriveSlot :: removeDriveItem()
{
    item_subtype_id = -1;    
            
    pTo_driveItem = NULL;

    is_EQUIPED = false;

    pTo_ship->updateDriveAbility();
}


void DriveSlot :: renderFrame(GLuint flash_tex)
{
    drawTexturedRect(pTo_texOb->texture, rect, -1.5);

    //if self.flash == True:
       //drawTexturedRect(flash_tex, self.rect, -1.0)
    if (is_EQUIPED == true)
        pTo_driveItem->render(rect);
}


void DriveSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}


void DriveSlot :: renderItemInfo()
{
    if (is_EQUIPED == true)
        pTo_driveItem->renderInfo(rect);
}


