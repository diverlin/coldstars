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


#include "weaponslot.h"

WeaponSlot :: WeaponSlot()
{}

WeaponSlot :: WeaponSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{    
     CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);

     type_id = WEAPON_SLOT_ID;







     is_SELECTED      = false;

     //self.GL_LIST_slot_ID = None
}







void WeaponSlot :: insertLazerEquipment(LazerEquipment* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;   
 
    pTo_lazerEquipment = pTo_item;
    pTo_lazerEquipment->pTo_ship = pTo_ship;
    pTo_lazerEquipment->pTo_wslot = this;

    is_EQUIPED = true;

    pTo_ship->updateFireAbility();
}

void WeaponSlot :: removeLazerEquipment()
{
    item_subtype_id = -1;
        
    pTo_lazerEquipment->pTo_ship = NULL;      
    pTo_lazerEquipment->pTo_wslot = NULL;
    pTo_lazerEquipment = NULL;

    is_EQUIPED = false;

    pTo_ship->updateFireAbility();
}



void WeaponSlot :: insertRocketEquipment(RocketEquipment* pTo_item)
{
    item_subtype_id = pTo_item->subtype_id;    
 
    pTo_rocketEquipment = pTo_item;
    
    pTo_rocketEquipment->pTo_ship = pTo_ship;
    pTo_rocketEquipment->pTo_wslot = this;
    
    is_EQUIPED = true;

    pTo_ship->updateFireAbility();
}

void WeaponSlot :: removeRocketEquipment()
{
    item_subtype_id = -1;
        
    pTo_rocketEquipment->pTo_ship = NULL;      
    pTo_rocketEquipment->pTo_wslot = NULL;
    pTo_rocketEquipment = NULL;
    
    is_EQUIPED = false;

    pTo_ship->updateFireAbility();
}




int WeaponSlot :: returnEquipedItemCondition()
{
    if (item_subtype_id == LAZER_ID)
       return pTo_lazerEquipment->condition;
    if (item_subtype_id == ROCKET_ID)
       return pTo_rocketEquipment->condition;
}

int WeaponSlot :: returnEquipedItemMass()
{
    if (item_subtype_id == LAZER_ID)
       return pTo_lazerEquipment->mass;
    if (item_subtype_id == ROCKET_ID)
       return pTo_rocketEquipment->mass;
}




















void WeaponSlot :: renderFrame(GLuint flash_tex)
{
    drawTexturedRect(pTo_texOb->texture, rect, -1.5);

    //if self.flash == True:
       //drawTexturedRect(flash_tex, self.rect, -1.0)
    if (is_EQUIPED == true)
    {
       if (item_subtype_id == LAZER_ID)
          pTo_lazerEquipment->render(rect);
        
       if (item_subtype_id == ROCKET_ID)
          pTo_rocketEquipment->render(rect);
    }
        
}


void WeaponSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void WeaponSlot :: renderItemInfo()
{
    if (is_EQUIPED == true)
    {
       if (item_subtype_id == LAZER_ID)
          pTo_lazerEquipment->renderInfo(rect);
        
       if (item_subtype_id == ROCKET_ID)
          pTo_rocketEquipment->renderInfo(rect);
    }      
}

