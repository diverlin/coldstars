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

#include "commonforequipment.hpp"


CommonForEquipment :: CommonForEquipment()
{}


CommonForEquipment :: ~CommonForEquipment()
{}


void CommonForEquipment :: CommonForEquipment_init(int _subtype_id, 
						   TextureOb* _itemTexOb, 
						   EquipmentCommonData _common_data)
{
    	id         = g_ENTITY_ID_GENERATOR.returnNextId();
    	type_id    = EQUIPMENT_ID;
    	subtype_id = _subtype_id;
    
    	common_data = _common_data;

   
    	itemTexOb = _itemTexOb;

    	if (itemTexOb->is_animated == false)
      		pToFunc_render = &CommonForEquipment::_renderFrame;
    	else
       		pToFunc_render = &CommonForEquipment::_renderFrames;

    	w = itemTexOb->w;
    	h = itemTexOb->h;
    	race_id = itemTexOb->race_id;
          
    	in_SPACE   = false;                 // this flag is needed for grap function to check if the item was already collected or not
    	is_DAMAGED = false;

    	condition       = common_data.condition_max;
    	price = 0;

    	slot = NULL;
}


int CommonForEquipment :: getType()    const { return type_id; }
int CommonForEquipment :: getSubType() const { return subtype_id; }
unsigned int CommonForEquipment :: getMass()    const { return common_data.mass; }
unsigned int CommonForEquipment :: getCondition() const { return condition; }
int CommonForEquipment :: getPrice() const {return price; } 
        	    	
        	
void CommonForEquipment :: bindSlot(ItemSlot* _slot)
{
	slot = _slot;
}     

void CommonForEquipment :: deterioration()
{
    	condition -= common_data.deterioration_rate;
    	if (condition <= 0)
    	{
       		is_DAMAGED = true;
       		if (slot->getShip() != NULL)   
           		updateOwnerPropetries();
    	}
}

void CommonForEquipment :: updateOwnerPropetries()  { /* virtual */ }

void CommonForEquipment :: repair()
{
    	condition = common_data.condition_max;
    	if (is_DAMAGED == true)
    	{
        	is_DAMAGED = false;
        	if (slot->getShip() != NULL)   
           		updateOwnerPropetries();
    	}
}



void CommonForEquipment :: updateInfo()
{
	info.clear();

	addUniqueInfo();
    	addCommonInfo();
}

void CommonForEquipment :: addUniqueInfo() { /* virtual */ }
 		
void CommonForEquipment :: addCommonInfo()
{
    	info.addNameStr("modules:");   info.addValueStr( int2str(common_data.modules_num_max) );
    	info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(common_data.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(common_data.mass) );
    	info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

void CommonForEquipment :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
{  
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}



void CommonForEquipment :: render(Rect slot_rect)
{
     	(this->*pToFunc_render)(slot_rect);
}


void CommonForEquipment :: _renderFrame(Rect slot_rect)
{
    	drawTexturedRect(itemTexOb->texture, slot_rect, -1.0);
    	//if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        	//drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    	for (unsigned int mi = 0; mi < texOb_modules_pList.size(); mi++)
    	{
        	Rect module_rect(slot_rect.getBottomLeft().x + (1.1 * INSERTED_MODULE_SIZE) * (mi), 
        		         slot_rect.getBottomLeft().y + (1.1 * INSERTED_MODULE_SIZE),
        			 INSERTED_MODULE_SIZE, 
        			 INSERTED_MODULE_SIZE);
        	drawTexturedRect(texOb_modules_pList[mi]->texture, module_rect, -1);
    	}
}           


void CommonForEquipment :: _renderFrames(Rect slot_rect)
{
    	int i = itemTexOb->updateAnimationFrame(); 
    	glBindTexture(GL_TEXTURE_2D, itemTexOb->texture);
    	drawRect(slot_rect, 
    	    	 -1.0, 
    	    	 itemTexOb->texCoord_bottomLeft_x_list[i], 
    	    	 itemTexOb->texCoord_bottomLeft_y_list[i], 
    	    	 itemTexOb->texCoord_bottomRight_x_list[i], 
    	    	 itemTexOb->texCoord_bottomRight_y_list[i], 
    	    	 itemTexOb->texCoord_topLeft_x_list[i], 
    	    	 itemTexOb->texCoord_topLeft_y_list[i], 
    	    	 itemTexOb->texCoord_topRight_x_list[i], 
    	    	 itemTexOb->texCoord_topRight_y_list[i]);
    	    
    	//if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        	//drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    	for (unsigned int mi = 0; mi < texOb_modules_pList.size(); mi++)
    	{
        	Rect module_rect(slot_rect.getBottomLeft().x + (1.1 * INSERTED_MODULE_SIZE) * (mi), 
        			 slot_rect.getBottomLeft().y + (1.1 * INSERTED_MODULE_SIZE),
        		         INSERTED_MODULE_SIZE, 
        		         INSERTED_MODULE_SIZE);
        		         
        	drawTexturedRect(texOb_modules_pList[mi]->texture, module_rect, -1);
    	}
}      
