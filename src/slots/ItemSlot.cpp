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

#include "ItemSlot.hpp"

#include "../builder/ContainerBuilder.hpp"
#include "../common/myStr.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../render/Render.hpp"
#include "../world/starsystem.hpp"
#include "../resources/TextureManager.hpp"
#include "../parts/Turrel.hpp"

#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../items/equipment/RadarEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"

#include "../items/others/Bomb.hpp"

#include "../docking/Store.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"

ItemSlot::ItemSlot(int id)
{
	/* 
                The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
                Depending on slot subtype there is the rule what items can be used with slot (for example 
                Lazer weapon item cannot be inserted to drive slot and so on).
	*/

	data_id.id         = id;
        data_id.type_id    = ENTITY::ITEM_SLOT_ID;
                        
        turrel     = NULL;                
        item   	   = NULL;
}

/* virtual */
ItemSlot::~ItemSlot()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~ItemSlot(), id="+int2str(GetId()));
	#endif
		
	if (equiped == true)
	{
		delete item;
		item = NULL;
	}
}  
        		        
bool ItemSlot::InsertItem(BaseItem* item)
{
	if (owner != NULL) // slot in cursor has owner = NULL
	{
		if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
		{
			GetOwnerVehicle()->ChangeMass(item->GetMass());
		}
	}
	
	if (data_id.subtype_id == ENTITY::CARGO_SLOT_ID) 
	{           
		this->item = item;
		equiped = true; 
		item->SetItemSlot(this);
	     
		return true;
	}

	if (data_id.subtype_id == item->GetFunctionalSlotSubTypeId())
	{                                     
		this->item = item;
		equiped = true; 
		item->SetItemSlot(this);
                UpdateVehiclePropetries(); 

                return true;
	}
	
	return false;
}

void ItemSlot::RemoveItem()
{        
	if (owner != NULL) // slot in cursor has owner = NULL
	{
		if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
		{
			GetOwnerVehicle()->ChangeMass(-item->GetMass());
		}
	}
	
        item = NULL;
    	equiped = false;
    	
    	if (data_id.subtype_id != ENTITY::CARGO_SLOT_ID) 
	{    
                UpdateVehiclePropetries(); 
	}    	 
}

void ItemSlot::SelectEvent1()
{
	selected = true;
        
        if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
	{ 	
		switch(data_id.subtype_id)
		{
			case ENTITY::DRIVE_SLOT_ID: 	{
  					  			GetOwnerVehicle()->UpdatePropertiesSpeed();
								//GetOwnerVehicle()->UpdatePropertiesJump();                                                                                                                                
					  			break;
							}
		}
	}
}
                                
void ItemSlot::DeselectEvent()
{
	selected = false;
	
	if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
	{ 	
		switch(data_id.subtype_id)
		{
			case ENTITY::WEAPON_SLOT_ID: 	{ turrel->ResetTarget(); break; }
                        case ENTITY::DRIVE_SLOT_ID: 	{
  					  			GetOwnerVehicle()->UpdatePropertiesSpeed();
								//GetOwnerVehicle()->UpdatePropertiesJump();
                                                                break;
							}
		}
	}
			
}
        	
void ItemSlot::UpdateVehiclePropetries() const
{
	if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
	{ 	
		switch(data_id.subtype_id)
		{
			case ENTITY::WEAPON_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesFire(); break; }
			case ENTITY::SCANER_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesScan(); break; }
			case ENTITY::BAK_SLOT_ID:     	{
						  		GetOwnerVehicle()->UpdatePropertiesSpeed();
   								GetOwnerVehicle()->UpdatePropertiesJump(); 
   	
   						  		break;
  							}
  			
  			case ENTITY::DRIVE_SLOT_ID:   	{
  					  			GetOwnerVehicle()->UpdatePropertiesSpeed();
								GetOwnerVehicle()->UpdatePropertiesJump(); 
					  			break;
							}
				
			case ENTITY::DROID_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesRepair(); break; }
			//case ENTITY::ENERGIZER_SLOT_ID: 	{ GetOwnerVehicle()->UpdateEnergyAbility(); break; }
			//case ENTITY::FREEZER_SLOT_ID: 	{ GetOwnerVehicle()->UpdateFreezeAbility(); break; }
			case ENTITY::GRAPPLE_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesGrab(); break; }
			case ENTITY::PROTECTOR_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesProtection(); break; }
			case ENTITY::RADAR_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesRadar(); break; }
			
			case ENTITY::ARTEFACT_SLOT_ID: { GetOwnerVehicle()->UpdateArtefactInfluence(); break; }
		}
	}
}
   
/* virtual */
void ItemSlot::Render(const Rect& rect, const vec2f& gui_offset, bool draw_text) const
{
       	drawTexturedRect(textureOb, rect, -1.5);    
       	if (equiped == true)
       	{
       		item->Render(rect, gui_offset, draw_text);	
        }
}

void ItemSlot::RenderMark(const Rect& rect, TextureOb* textureOb_mark) const
{
	drawTexturedRect(textureOb_mark, rect, -1.0);
}      
        
int ItemSlot::GetItemRadius() const
{       
        switch(item->GetTypeId())
        {
                case ENTITY::EQUIPMENT_ID:
                {
                        switch (item->GetSubTypeId())
                        {
                                case ENTITY::LAZER_EQUIPMENT_ID:   { return ((LazerEquipment*)item)->GetRadius();  break; };
                                case ENTITY::ROCKET_EQUIPMENT_ID:  { return ((RocketEquipment*)item)->GetRadius(); break; };
		
                                case ENTITY::GRAPPLE_EQUIPMENT_ID: { return ((GrappleEquipment*)item)->GetRadius(); break; };
                                case ENTITY::RADAR_EQUIPMENT_ID:   { return ((RadarEquipment*)item)->GetRadius();   break; };
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

void ItemSlot::RenderItemInfo(const vec2f& pos, const vec2f& offset) const
{
	RenderItemInfo(pos, offset.x, offset.y);
}

void ItemSlot::RenderItemInfo(const vec2f& pos, float offset_x, float offset_y) const
{
        if (equiped == true)
        {
                item->RenderInfo(pos, offset_x, offset_y);
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
       	if ( (equiped == false) and (_slot->GetEquiped() == true) )
       	{      
       		if (InsertItem(_slot->GetItem()) == true) 
       		{
       			_slot->RemoveItem(); 
       			
       			return true; 
       		}             
	}
	
	if ( (equiped == true) and (_slot->GetEquiped() == false) )
       	{ 
		if (_slot->InsertItem(GetItem())     == true)
		{ 
			RemoveItem(); 
			
			return true; 
		}
	}

	if ( (equiped == true) and (_slot->GetEquiped() == true) )
       	{          
       		if ( (item->GetTypeId() == ENTITY::MODULE_ID) and (_slot->GetItem()->GetTypeId() == ENTITY::EQUIPMENT_ID) )
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
        range_visual.FillData(_texOb, range_vec, step, size);
}

void ItemSlot::DrawRange()
{ 
    	range_visual.Draw();
}

bool ItemSlot::CheckTarget(BaseSpaceEntity* _target) const
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

bool ItemSlot::CheckAlive(BaseSpaceEntity* _target) const
{
	return _target->GetAlive();
}

bool ItemSlot::CheckPlaceTypeId(BaseSpaceEntity* _target) const  
{
	return (_target->GetPlaceTypeId() == ENTITY::SPACE_ID);
}           	

bool ItemSlot::CheckStarSystem(BaseSpaceEntity* _target) const
{
        return (_target->GetStarSystem() == ((Vehicle*)owner)->GetStarSystem());
}                

bool ItemSlot::CheckDistance(BaseSpaceEntity* _target) const
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

void ItemSlot::RemoveChildFromEntityManager()
{
	if (equiped == true)
	{
		EntityManager::Instance().RemoveEntity(item);
		if (item->GetTypeId() == ENTITY::EQUIPMENT_ID)
		{
			((BaseEquipment*)item)->RemoveChildFromEntityManager();
		}
	}
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
        switch(unresolved_BaseSlot.owner_type_id)
        {
	       case ENTITY::VEHICLE_ID: 	{	((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this); break; }
	       case ENTITY::CONTAINER_ID:     	{	((Container*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->BindItemSlot(this); break; }
	       case ENTITY::STORE_ID:         	{ 	((Store*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this); break; }
	       case ENTITY::ANGAR_ID:         	{ 	}//((Angar*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddItemSlot(this, tmp_rect); break; }
	}
}
