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



BaseItem :: BaseItem()
{
        //w = texOb->getFrameWidth();
     	//h = texOb->getFrameHeight();
        
        slot = NULL;
        mass = 0;
}

/* virtual */
BaseItem :: ~BaseItem ()
{}

void BaseItem :: setIdData(IdData data_id)       { this->data_id = data_id; }
void BaseItem :: setTextureOb(TextureOb* texOb)  { this->texOb = texOb; }
void BaseItem :: setFunctionalSlotSubTypeId(int functional_slot_subtype_id) { this->functional_slot_subtype_id = functional_slot_subtype_id; }
void BaseItem :: setItemCommonData(ItemCommonData common_data) { this->common_data = common_data; }
void BaseItem :: bindSlot(ItemSlot* slot)    { this->slot = slot; }


TextureOb* BaseItem :: getTextureOb()     const { return texOb; }
unsigned int BaseItem :: getId()        const { return data_id.id; }
unsigned int BaseItem :: getTypeId()    const { return data_id.type_id; }
unsigned int BaseItem :: getSubTypeId() const { return data_id.subtype_id; }
unsigned int BaseItem :: getMass()    const { return mass; }
unsigned int BaseItem :: getCondition() const { return condition; }
unsigned int BaseItem :: getPrice()     const { return price; } 
int BaseItem :: getFunctionalSlotSubTypeId() const { return functional_slot_subtype_id; }

void BaseItem :: deterioration()
{
    	condition -= common_data.deterioration_rate;
    	if (condition <= 0)
    	{
       		is_DAMAGED = true;
       		if (slot->getOwnerVehicle() != NULL) 
       		{  
           		updateOwnerAbilities();
           	}
    	}
}


void BaseItem :: repair()
{
    	condition = common_data.condition_max;
    	if (is_DAMAGED == true)
    	{
        	is_DAMAGED = false;
        	if (slot->getOwnerVehicle() != NULL)   
        	{
           		updateOwnerAbilities();
           	}
    	}
}


void BaseItem :: updateInfo()
{
	info.clear();

	addUniqueInfo();
    	addCommonInfo();
}

void BaseItem :: addUniqueInfo() { /* virtual */ }
 		
void BaseItem :: addCommonInfo()
{
    	//info.addNameStr("modules:");   info.addValueStr( int2str(common_data.modules_num_max) );
    	//info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	//info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(common_data.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(mass) );
    	//info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

//void BaseItem :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
//{  
	//updateInfo();
        //drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
//}


//void BaseItem :: render(Rect slot_rect)
//{
        //drawTexturedRect(texOb, slot_rect, -1);   
//}


void BaseItem :: renderInfo(Rect slot_rect, float offset_x, float offset_y)
{  
	updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.getCenter().x, slot_rect.getCenter().y, offset_x, offset_y);
}

void BaseItem :: render(Rect slot_rect)
{
    	drawTexturedRect(texOb, slot_rect, -1.0);
    	//if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        	//drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    	//for (unsigned int mi = 0; mi < texOb_modules_pList.size(); mi++)
    	//{
        	//Rect module_rect(slot_rect.getBottomLeft().x + (1.1 * INSERTED_MODULE_SIZE) * (mi), 
        		         //slot_rect.getBottomLeft().y + (1.1 * INSERTED_MODULE_SIZE),
        			 //INSERTED_MODULE_SIZE, 
        			 //INSERTED_MODULE_SIZE);
        	//drawTexturedRect(texOb_modules_pList[mi], module_rect, -1);
    	//}
}

