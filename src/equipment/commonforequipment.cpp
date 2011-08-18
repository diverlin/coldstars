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


#include "commonforequipment.h"


CommonForEquipment :: CommonForEquipment()
{}

void CommonForEquipment :: CommonForEquipment_init(TextureOb* _pTo_itemTexOb, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
    pTo_itemTexOb = _pTo_itemTexOb;

    if (pTo_itemTexOb->is_animated == false)
       pToFunc_render = &CommonForEquipment::_renderFrame;
    else
       pToFunc_render = &CommonForEquipment::_renderFrames;

    w = pTo_itemTexOb->w;
    h = pTo_itemTexOb->h;
    race_id = pTo_itemTexOb->race_id;
          
    in_SPACE   = false;                 // this flag is needed for grap function to check if the item was already collected or not
    is_DAMAGED = false;

    id = g_ENTITY_ID_GENERATOR.returnNextId();



    mass            = _mass;

    modules_num_max = _modules_num_max;

    condition_max   = _condition_max;
    condition       = _condition_max;

    deterioration_rate = _deterioration_rate;

    //turns_LOCKED = 0;

    price = 0;
    pTo_ship = NULL;
}

void CommonForEquipment :: deterioration()
{
    condition -= deterioration_rate;
    if (condition <= 0)
    {
       is_DAMAGED = true;
       //if self.owner != None:   //# not sure if's it really needed
       //updateOwnerPropetries();
    }
}

void CommonForEquipment :: repair()
{
    condition = condition_max;
    if (is_DAMAGED == true)
       is_DAMAGED = false;
}

void CommonForEquipment :: render(Rect slot_rect)
{
     (this->*pToFunc_render)(slot_rect);
}


void CommonForEquipment :: _renderFrame(Rect slot_rect)
{
    drawTexturedRect(pTo_itemTexOb->texture, slot_rect, -1.0);
    //if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        //drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    for (unsigned int mi = 0; mi < texOb_modules_pList.size(); mi++)
    {
        Rect module_rect(slot_rect.bottomLeft_x + (1.1 * INSERTED_MODULE_SIZE) * (mi), slot_rect.bottomLeft_y + (1.1 * INSERTED_MODULE_SIZE), INSERTED_MODULE_SIZE, INSERTED_MODULE_SIZE);
        drawTexturedRect(texOb_modules_pList[mi]->texture, module_rect, -1);
    }
}           


void CommonForEquipment :: _renderFrames(Rect slot_rect)
{
    int i = pTo_itemTexOb->updateAnimationFrame(); 
    glBindTexture(GL_TEXTURE_2D, pTo_itemTexOb->texture);
    drawRect(slot_rect, -1.0, pTo_itemTexOb->texCoord_bottomLeft_x_list[i], pTo_itemTexOb->texCoord_bottomLeft_y_list[i], pTo_itemTexOb->texCoord_bottomRight_x_list[i], pTo_itemTexOb->texCoord_bottomRight_y_list[i], pTo_itemTexOb->texCoord_topLeft_x_list[i], pTo_itemTexOb->texCoord_topLeft_y_list[i], pTo_itemTexOb->texCoord_topRight_x_list[i], pTo_itemTexOb->texCoord_topRight_y_list[i]);
    //if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        //drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    for (unsigned int mi = 0; mi < texOb_modules_pList.size(); mi++)
    {
        Rect module_rect(slot_rect.bottomLeft_x + (1.1 * INSERTED_MODULE_SIZE) * (mi), slot_rect.bottomLeft_y + (1.1 * INSERTED_MODULE_SIZE), INSERTED_MODULE_SIZE, INSERTED_MODULE_SIZE);
        drawTexturedRect(texOb_modules_pList[mi]->texture, module_rect, -1);
    }
}      



void CommonForEquipment :: renderInfo(Rect slot_rect)
{  
     drawInfoIn2Column(&info_title_pList, &info_value_pList, slot_rect.center_x, slot_rect.center_y, 0, 0);
}
