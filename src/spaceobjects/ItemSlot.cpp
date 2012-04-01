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


ItemSlot::ItemSlot()
{
	/* 
        The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
        Depending on slot subtype there is the rule what items can be used with slot (for example 
        Lazer weapon item cannot be inserted to drive slot and so on).
	*/

        type_id    = SLOT::SLOT_ID;
	subtype_id = -1;
     
        rect = Rect();         

        is_EQUIPED       = false;
        is_FLASHING      = false;

        owner_vehicle  = NULL; 
        
        turrel = NULL;                
        item   = NULL;
        texOb = NULL;
}

ItemSlot::~ItemSlot()
{
        delete item;
}
                
void ItemSlot::SetRect(int _pos_x, int _pos_y, int w, int h) 
{
	rect.set(_pos_x, _pos_y, w, h);
}

bool ItemSlot::InsertItem(BaseItem* item)
{
	if (item != NULL)
	{
		if (subtype_id == SLOT::CARGO_ID) 
		{
                	this->item = item;
                	is_EQUIPED = true; 
                
			return true;
   		}
   	
		if (subtype_id == item->GetFunctionalSlotSubTypeId())
		{
		        this->item = item;
                	is_EQUIPED = true; 
                
			item->BindSlot(this);
			item->UpdateOwnerAbilities();
		
			return true;
		}
	}

	return false;
}

bool ItemSlot::ExtractItemFromContainer(Container* container)
{
	return this->SwapItemWith(container->getItemSlot());
}

void ItemSlot::RemoveItem()
{
        BaseItem* tmp_item = item;
        
        item = NULL;
    	is_EQUIPED = false;  
        
    	if (subtype_id != SLOT::CARGO_ID) 
    	{ 
    		tmp_item->UpdateOwnerAbilities(); 
    	}                     
}

void ItemSlot::Render(GLuint flash_tex)
{
       	drawTexturedRect(texOb, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
                
        RenderEquipedItem();     
}
              
int ItemSlot::GetItemRadius() const
{       
        switch(item->GetTypeId())
        {
                case EQUIPMENT::EQUIPMENT_ID:
                {
                        switch (item->GetSubTypeId())
                        {
                                case EQUIPMENT::LAZER_ID:   { return ((LazerEquipment*)item)->getRadius();  break; };
                                case EQUIPMENT::ROCKET_ID:  { return ((RocketEquipment*)item)->getRadius(); break; };
		
                                case EQUIPMENT::GRAPPLE_ID: { return ((GrappleEquipment*)item)->getRadius(); break; };
                                case EQUIPMENT::RADAR_ID:   { return ((RadarEquipment*)item)->getRadius();   break; };
                        }
                        
                        break;
                }
                
                case ENTITY::BOMB_ID:
                {
                        return ((Bomb*)item)->getRadius();   break; 
                }
        }
        
        return 0;
}


void ItemSlot::RenderEquipedItem()
{
        if (is_EQUIPED == true)
        {
                item->Render(rect);
        }
}

void ItemSlot::RenderItemInfo(float offset_x, float offset_y)
{
        if (is_EQUIPED == true)
        {
                item->RenderInfo(rect, offset_x, offset_y);
        }
}

bool ItemSlot::CheckInteraction(int _x, int _y)
{        
        float dist = distBetweenPoints(rect.getCenter().x, rect.getCenter().y, _x, _y);
        if (dist < rect.getWidth()/2)
                return true;
        else
                return false;    
}

void ItemSlot::DropItemToSpace()
{
	Container* _container = getNewContainer();
	_container->getItemSlot()->SwapItemWith(this);
	
	// update mass

	owner_vehicle->GetStarSystem()->AddToSpace(_container, owner_vehicle->GetPoints().getCenter());	

	//printf("container was created in ss_id = %i, pos = %f, %f\n", _starsystem->GetId(), _container->getPoints()->getCenter().x, _container->getPoints()->getCenter().y );
}
        
bool ItemSlot::SwapItemWith(ItemSlot* _slot)
{
       	if ( (is_EQUIPED == false) and (_slot->GetEquipedStatus() == true) )
       	{      
       		if (InsertItem(_slot->GetItem()) == true) 
       		{
       			_slot->RemoveItem(); 
       			
       			return true; 
       		}             
	}
	
	if ( (is_EQUIPED == true) and (_slot->GetEquipedStatus() == false) )
       	{ 
		if (_slot->InsertItem(GetItem())     == true)
		{ 
			RemoveItem(); 
			
			return true; 			
		}                     				
	}

	if ( (is_EQUIPED == true) and (_slot->GetEquipedStatus() == true) )
       	{          
       		if ( (item->GetTypeId() == MODULE::MODULE_ID) and (_slot->GetItem()->GetTypeId() == EQUIPMENT::EQUIPMENT_ID) )
       		{
			if (((EquipmentBase*)_slot->GetItem())->insertModule((ModuleBase*)item) == true)  
			{ 
				RemoveItem(); 
				
				return true;       		
        		}
       		}
       		
       		if ( (item->GetTypeId() == EQUIPMENT::EQUIPMENT_ID) and (_slot->GetItem()->GetTypeId() == MODULE::MODULE_ID) )
       		{
			 if (((EquipmentBase*)item)->insertModule((ModuleBase*)_slot->GetItem()) == true)  
			 { 
			 	_slot->RemoveItem(); 
			 	
			 	return true; 
			 }       		        		
       		}
	}               
	
	return false;
}

void ItemSlot::UpdateRange(TextureOb* _texOb)
{
	float radius = this->GetItemRadius();
	float da = 4.0f/RADIAN_TO_DEGREE_RATE;// - radius/1000.0f;
	
    	range_vec.clear();
      	for (float a = 0.0f; a <= 2*PI; a+=da)
      	{
      		range_vec.push_back( vec2f(radius * cos(a), radius * sin(a)) );
      	}
      	
	int step = 1;
	int size = 6;
        range_visual.fillData(_texOb->texture, &range_vec, step, size);
}

void ItemSlot::DrawRange()
{ 
    	range_visual.draw();
}

bool ItemSlot::CheckTarget(BaseGameEntity* _target) const
{
        if (_target->GetAlive() == true)
        {
                if (CheckStarSystem(_target) == true)
                {
                        if (CheckDistance(_target) == true)
                        {
                                return true;
                        }
                }
        }
        
        return false;
}

bool ItemSlot::CheckStarSystem(BaseGameEntity* _target) const
{
        if (_target->GetStarSystem() == owner_vehicle->GetStarSystem())
        {
                return true;
        }
        
        return false;
}                

bool ItemSlot::CheckDistance(BaseGameEntity* _target) const
{
	if (_target->GetTypeId() == ENTITY::STARSYSTEM_ID)
	{
		return true;
	}
	
        float dist = distBetweenPoints(GetOwnerVehicle()->GetPoints().getCenter(), _target->GetPoints().getCenter());                                               
        if (dist < GetItemRadius())
        {
                return true;
        }

       	return false;
}

