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
        data_id.type_id    = SLOT::SLOT_ID;
	data_id.subtype_id = NONE_ID;

        is_EQUIPED = false;

        owner_vehicle = NULL; 
        owner_angar   = NULL; 
        owner_store   = NULL; 
                        
        turrel     = NULL;                
        item   	   = NULL;
        textureOb  = NULL;
}

ItemSlot::~ItemSlot()
{}
                
void ItemSlot::SetRect(float pos_x, float pos_y, int w, int h) 
{
	rect.Set(pos_x, pos_y, w, h);
	if (turrel != NULL)
	{
		turrel->GetPoints().SetParentCenter(vec2f(pos_x/owner_vehicle->data_korpus.gui_scale, pos_y/owner_vehicle->data_korpus.gui_scale));
	}
}

bool ItemSlot::InsertItem(BaseItem* item)
{
	if (item != NULL)
	{
		if (data_id.subtype_id == SLOT::CARGO_ID) 
		{           
                        this->item = item;
                        is_EQUIPED = true; 
                        item->SetSlot(this);
                     
			return true;
   		}
   	
		if (data_id.subtype_id == item->GetFunctionalSlotSubTypeId())
		{              
                        this->item = item;
                        is_EQUIPED = true; 
                        item->SetSlot(this);
                
			UpdateOwnerAbilities();
			return true;
		}
	}

	return false;
}

void ItemSlot::RemoveItem()
{
        item = NULL;
    	is_EQUIPED = false;  
        
       	UpdateOwnerAbilities();
}

void ItemSlot::UpdateOwnerAbilities()
{
	if (owner_vehicle)
        {
		switch(data_id.subtype_id)
		{
			case SLOT::WEAPON_ID: 	{ owner_vehicle->UpdateFireAbility(); break; }
			case SLOT::SCANER_ID: 	{ owner_vehicle->UpdateScanAbility(); break; }
			case SLOT::BAK_ID:     	{
						  owner_vehicle->UpdateDriveAbility();
    						  owner_vehicle->UpdateJumpAbility(); 
						  break;
						}

			case SLOT::DRIVE_ID:   {
						  owner_vehicle->UpdateDriveAbility();
    						  owner_vehicle->UpdateJumpAbility(); 
						  break;
						}
					
			case SLOT::DROID_ID: 	{ owner_vehicle->UpdateRepairAbility(); break; }
			case SLOT::ENERGIZER_ID: { owner_vehicle->UpdateEnergyAbility(); break; }
			case SLOT::FREEZER_ID: { owner_vehicle->UpdateFreezeAbility(); break; }
			case SLOT::GRAPPLE_ID: { owner_vehicle->UpdateGrabAbility(); break; }
			case SLOT::PROTECTOR_ID: { owner_vehicle->UpdateProtectionAbility(); break; }
			case SLOT::RADAR_ID: 	{ owner_vehicle->UpdateRadarAbility(); break; }
										
			case SLOT::CARGO_ID: 	{ break; }
		

		}
	}
}

void ItemSlot::Render(GLuint flash_tex)
{
       	drawTexturedRect(textureOb, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
                
        RenderEquipedItem();     
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
        float dist = distBetweenPoints(rect.GetCenter().x, rect.GetCenter().y, _x, _y);
        if (dist < rect.GetWidth()/2)
                return true;
        else
                return false;    
}

void ItemSlot::DropItemToSpace()
{
        TextureOb* textureOb_ = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::CONTAINER_ID);    
        Container* container = GetNewContainer(textureOb_, item);
        RemoveItem();
        
	owner_vehicle->GetStarSystem()->Add(container, owner_vehicle->GetPoints().GetCenter());	
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
       		if ( (item->GetTypeId() == TYPE::MODULE_ID) and (_slot->GetItem()->GetTypeId() == TYPE::EQUIPMENT_ID) )
       		{
			if (((BaseEquipment*)_slot->GetItem())->InsertModule((BaseModule*)item) == true)  
			{ 
                                std::cout<<"__1"<<item->GetTypeId()<<_slot->GetItem()->GetTypeId()<<std::endl;
				RemoveItem(); 
				
				return true;
        		}
       		}
       		
       		if ( (item->GetTypeId() == TYPE::EQUIPMENT_ID) and (_slot->GetItem()->GetTypeId() == TYPE::MODULE_ID) )
       		{
			 if (((BaseEquipment*)item)->InsertModule((BaseModule*)_slot->GetItem()) == true)  
			 { 
                                std::cout<<"__2"<<item->GetTypeId()<<_slot->GetItem()->GetTypeId()<<std::endl;
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
	const std::string root = "item_slot." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueItemSlot(save_ptree, root);
}

/*virtual*/		
void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueItemSlot(load_ptree);
}
	
/*virtual*/	
void ItemSlot::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueItemSlot();
}

void ItemSlot::SaveDataUniqueItemSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"unresolved.rect.BottomLeft.x", rect.GetBottomLeft().x);
        save_ptree.put(root+"unresolved.rect.BottomLeft.y", rect.GetBottomLeft().y); 
        save_ptree.put(root+"unresolved.rect.width", rect.GetWidth());
        save_ptree.put(root+"unresolved.rect.height", rect.GetHeight()); 
        
        if (owner_vehicle) save_ptree.put(root+"unresolved.owner_vehicle_id", owner_vehicle->GetId());
        else               save_ptree.put(root+"unresolved.owner_vehicle_id", NONE_ID);

        if (owner_angar) save_ptree.put(root+"unresolved.owner_angar_id", owner_angar->GetId());
        else             save_ptree.put(root+"unresolved.owner_angar_id", NONE_ID);
        
        if (owner_store) save_ptree.put(root+"unresolved.owner_store_id", owner_store->GetId());
        else             save_ptree.put(root+"unresolved.owner_store_id", NONE_ID);
}

void ItemSlot::LoadDataUniqueItemSlot(const boost::property_tree::ptree& load_ptree)
{
        unresolved_ItemSlot.rect_blx = load_ptree.get<float>("unresolved.rect.BottomLeft.x");
        unresolved_ItemSlot.rect_bly = load_ptree.get<float>("unresolved.rect.BottomLeft.y");
        unresolved_ItemSlot.rect_w   = load_ptree.get<int>("unresolved.rect.width"); 
        unresolved_ItemSlot.rect_h   = load_ptree.get<int>("unresolved.rect.height"); 
     
        unresolved_ItemSlot.owner_vehicle_id = load_ptree.get<int>("unresolved.owner_vehicle_id"); 
        unresolved_ItemSlot.owner_angar_id   = load_ptree.get<int>("unresolved.owner_angar_id"); 
        unresolved_ItemSlot.owner_store_id   = load_ptree.get<int>("unresolved.owner_store_id"); 
}

void ItemSlot::ResolveDataUniqueItemSlot()
{
        Rect tmp_rect(unresolved_ItemSlot.rect_blx, unresolved_ItemSlot.rect_bly, unresolved_ItemSlot.rect_w, unresolved_ItemSlot.rect_h);
        if (unresolved_ItemSlot.owner_vehicle_id != NONE_ID)
        {	std::cout<<"slot id ="<<data_id.id<<" added to vehicle!!!!"<<std::endl;
                ((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.owner_vehicle_id))->AddSlot(this, tmp_rect);
	}

        if (unresolved_ItemSlot.owner_angar_id != NONE_ID)
        {
                //((Angar*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.owner_angar_id))->AddSlot(this, tmp_rect);
	}
	
	if (unresolved_ItemSlot.owner_store_id != NONE_ID)
        {     	std::cout<<"slot id ="<<data_id.id<<" added to store!!!!"<<std::endl;
                ((Store*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.owner_store_id))->AddSlot(this, tmp_rect);
	}
}
