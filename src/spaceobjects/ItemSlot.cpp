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


ItemSlot::ItemSlot(int id)
{
	/* 
                The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
                Depending on slot subtype there is the rule what items can be used with slot (for example 
                Lazer weapon item cannot be inserted to drive slot and so on).
	*/

	data_id.id         = id;
        data_id.type_id    = ENTITY::ITEMSLOT_ID;
	data_id.subtype_id = NONE_ID;
                        
        turrel     = NULL;                
        item   	   = NULL;
}

ItemSlot::~ItemSlot()
{
	EntityManager::Instance().RemoveEntity(this);
		
	if (is_EQUIPED == true)
	{
		delete item;
		item = NULL;
	}
}
                
void ItemSlot::SetRect(float pos_x, float pos_y, int w, int h) 
{
	rect.Set(pos_x, pos_y, w, h);
}

bool ItemSlot::InsertItem(BaseItem* item)
{
	if (data_id.subtype_id == ITEMSLOT::CARGO_ID) 
	{           
		this->item = item;
		is_EQUIPED = true; 
		item->SetItemSlot(this);
	     
		return true;
	}

	if (data_id.subtype_id == item->GetFunctionalSlotSubTypeId())
	{       
                //this means slot is functional, and this means it's defenately is part of vehicle
                                 
		this->item = item;
		is_EQUIPED = true; 
		item->SetItemSlot(this);
	
                if (item->GetFunctioning() == true)
                {
                        item->UpdateVehiclePropetries(GetOwnerVehicle());
		}
                return true;
	}

	return false;
}

void ItemSlot::RemoveItem()
{
        if (data_id.subtype_id != ITEMSLOT::CARGO_ID) 
	{    
                //this means slot is functional, and this means it's defenately is part of vehicle
                if (item->GetFunctioning() == true)
                {
                        item->UpdateVehiclePropetries(GetOwnerVehicle());
                }
	}
        
        item = NULL;
    	is_EQUIPED = false;  
}


void ItemSlot::Render() const
{
       	drawTexturedRect(textureOb, rect, -1.5);    
       	if (is_EQUIPED == true)
       	{
       		item->Render(rect);	
        }
}

void ItemSlot::RenderMark(TextureOb* textureOb_mark) const
{
	drawTexturedRect(textureOb_mark, rect, -1.0);
}      
        
int ItemSlot::GetItemRadius() const
{       
        switch(item->GetTypeId())
        {
                case TYPE::EQUIPMENT_ID:
                {
                        switch (item->GetSubTypeId())
                        {
                                case SUBTYPE::LAZER_ID:   { return ((LazerEquipment*)item)->GetRadius();  break; };
                                case SUBTYPE::ROCKET_ID:  { return ((RocketEquipment*)item)->GetRadius(); break; };
		
                                case SUBTYPE::GRAPPLE_ID: { return ((GrappleEquipment*)item)->GetRadius(); break; };
                                case SUBTYPE::RADAR_ID:   { return ((RadarEquipment*)item)->GetRadius();   break; };
                        }
                        
                        break;
                }
                
                case ENTITY::BOMB_ID:
                {
                        return ((Bomb*)item)->GetRadius();   break; 
                }
        }
        
        return 0;
}

void ItemSlot::RenderItemInfo(const vec2f& offset) const
{
	RenderItemInfo(offset.x, offset.y);
}

void ItemSlot::RenderItemInfo(float offset_x, float offset_y) const
{
        if (is_EQUIPED == true)
        {
                item->RenderInfo(rect, offset_x, offset_y);
        }
}

void ItemSlot::DropItemToSpace(Vehicle* vehicle)
{
        TextureOb* textureOb_ = TextureManager::Instance().GetRandomTextureOb(TEXTURE::CONTAINER_ID);   
        
        ContainerBuilder::Instance().CreateNewContainer();
        ContainerBuilder::Instance().CreateNewInternals(textureOb_, item);

        RemoveItem();
        
	vehicle->GetStarSystem()->Add(ContainerBuilder::Instance().GetContainer(), vehicle->GetPoints().GetCenter());	
}
        
bool ItemSlot::SwapItemWith(ItemSlot* _slot)
{
       	if ( (is_EQUIPED == false) and (_slot->GetEquiped() == true) )
       	{      
       		if (InsertItem(_slot->GetItem()) == true) 
       		{
       			_slot->RemoveItem(); 
       			
       			return true; 
       		}             
	}
	
	if ( (is_EQUIPED == true) and (_slot->GetEquiped() == false) )
       	{ 
		if (_slot->InsertItem(GetItem())     == true)
		{ 
			RemoveItem(); 
			
			return true; 
		}
	}

	if ( (is_EQUIPED == true) and (_slot->GetEquiped() == true) )
       	{          
       		if ( (item->GetTypeId() == TYPE::MODULE_ID) and (_slot->GetItem()->GetTypeId() == TYPE::EQUIPMENT_ID) )
       		{
			if (((BaseEquipment*)_slot->GetItem())->InsertModule((BaseModule*)item) == true)  
			{ 
				RemoveItem(); 
				
				return true;
        		}
       		}
       		
       		//if ( (item->GetTypeId() == TYPE::EQUIPMENT_ID) and (_slot->GetItem()->GetTypeId() == TYPE::MODULE_ID) )
       		//{
			 //if (((BaseEquipment*)item)->InsertModule((BaseModule*)_slot->GetItem()) == true)  
			 //{ 
			 	//_slot->RemoveItem(); 
			 	
			 	//return true; 
			 //}       		        		
       		//}
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
        range_visual.FillData(_texOb->texture, &range_vec, step, size);
}

void ItemSlot::DrawRange()
{ 
    	range_visual.Draw();
}

bool ItemSlot::CheckTarget(BaseGameEntity* _target) const
{
        if (CheckAlive(_target) == true)
        {
        	if (CheckPlaceTypeId(_target) == true)
        	{
                	if (CheckStarSystem(_target) == true)
                	{
                        	if (CheckDistance(_target) == true)
                        	{
                                	return true;
                        	}
                        }
                }
        }
        
        return false;
}

bool ItemSlot::CheckAlive(BaseGameEntity* _target) const
{
	return _target->GetAlive();
}

bool ItemSlot::CheckPlaceTypeId(BaseGameEntity* _target) const  
{
	return (_target->GetPlaceTypeId() == ENTITY::SPACE_ID);
}           	

bool ItemSlot::CheckStarSystem(BaseGameEntity* _target) const
{
        return (_target->GetStarSystem() == ((Vehicle*)owner)->GetStarSystem());
}                

bool ItemSlot::CheckDistance(BaseGameEntity* _target) const
{
	if (_target->GetTypeId() == ENTITY::STARSYSTEM_ID)
	{
		return true;
	}
	
        float dist = distBetweenPoints(GetOwnerVehicle()->GetPoints().GetCenter(), _target->GetPoints().GetCenter());                                               
        if (dist < GetItemRadius())
        {
                return true;
        }

       	return false;
}

/*virtual*/
void ItemSlot::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "item_slot." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSlot(save_ptree, root);
	SaveDataUniqueItemSlot(save_ptree, root);
}

/*virtual*/		
void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSlot(load_ptree);
	LoadDataUniqueItemSlot(load_ptree);
}
	
/*virtual*/	
void ItemSlot::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseSlot();
	ResolveDataUniqueItemSlot();
}

void ItemSlot::SaveDataUniqueItemSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void ItemSlot::LoadDataUniqueItemSlot(const boost::property_tree::ptree& load_ptree)
{}

void ItemSlot::ResolveDataUniqueItemSlot()
{
        Rect tmp_rect(unresolved_BaseSlot.rect_blx, unresolved_BaseSlot.rect_bly, unresolved_BaseSlot.rect_w, unresolved_BaseSlot.rect_h);
        switch(unresolved_BaseSlot.owner_type_id)
        {
	       case ENTITY::VEHICLE_ID: 	{	((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this, tmp_rect); break; }
	       case ENTITY::CONTAINER_ID:     	{	((Container*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->BindItemSlot(this); break; }
	       case ENTITY::STORE_ID:         	{ 	((Store*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this, tmp_rect); break; }
	       case ENTITY::ANGAR_ID:         	{ 	}//((Angar*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this, tmp_rect); break; }
	}
}
