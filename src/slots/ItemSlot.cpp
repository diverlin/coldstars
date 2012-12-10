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
#include "../spaceobjects/Container.hpp"
#include "../pilots/Npc.hpp"
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
#include "../docking/Angar.hpp"

#include "../common/Logger.hpp"

#include "../garbage/EntityGarbage.hpp"
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
                      
        target    = NULL;
        subtarget = NULL;
                     
        item   	   = NULL;
}

/* virtual */
ItemSlot::~ItemSlot()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~ItemSlot(), id="+int2str(GetId()));
	#endif
}  
    
void ItemSlot::PutChildsToGarbage() const
{
	if (item != NULL)
	{
		if (item->GetTypeId() == ENTITY::EQUIPMENT_ID)
		{
			((BaseEquipment*)item)->PutChildsToGarbage();
		}
		
		EntityGarbage::Instance().Add(item);
	}
}

void ItemSlot::SetTarget(BaseSpaceEntity* target, ItemSlot* subtarget) 	
{
	this->target    = target; 
	this->subtarget = subtarget;

	#if WEAPONSTARGET_LOG_ENABLED == 1 
        std::string func_name = " ItemSlot::SetTarget";
        if (GetSubTarget() == NULL)
        LogSimpleTarget(func_name);
        else
	LogComplexTarget(func_name); 
	#endif     
}
        
bool ItemSlot::ValidateTarget()
{	
        if (target != NULL)
        {
                #if WEAPONSTARGET_LOG_ENABLED == 1 
	        std::string func_name = " ItemSlot::ValidateTarget";
	        if (GetSubTarget() == NULL)
	        LogSimpleTarget(func_name);
	        else
		LogComplexTarget(func_name); 
		#endif   
	
                return CheckTarget(target);
        }
        
        return false;
}

void ItemSlot::ResetTarget()
{ 
        if (target != NULL)
        {
        	#if WEAPONSTARGET_LOG_ENABLED == 1 
	        std::string func_name = " ItemSlot::ResetTarget";
	        if (GetSubTarget() == NULL)
	        LogSimpleTarget(func_name);
	        else
		LogComplexTarget(func_name); 
		#endif   
	
		target    = NULL; 
		subtarget = NULL; 
	}
}

bool ItemSlot::CheckAmmo() const
{
	switch(GetItem()->GetSubTypeId())
	{
    		case ENTITY::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
    		case ENTITY::ROCKET_EQUIPMENT_ID: { if (GetRocketEquipment()->GetAmmo() > 0) return true; break; }
	}
	
    	return false;           
}

bool ItemSlot::FireEvent(int attack_skill, bool show_effect)
{    
        #if WEAPONSTARGET_LOG_ENABLED == 1 
        std::string func_name = " ItemSlot::FireEvent";
        if (GetSubTarget() == NULL)
        LogSimpleTarget(func_name);
        else
	LogComplexTarget(func_name); 
	#endif   
	   			
	switch(GetItem()->GetSubTypeId())
	{
    		case ENTITY::LAZER_EQUIPMENT_ID:
    		{   
			int damage = GetLazerEquipment()->GetDamage() * attack_skill * SKILL::ATTACK_NORMALIZED_RATE;						
			if (GetSubTarget() != NULL) // precise fire
			{
				if (GetTarget()->GetTypeId() == ENTITY::VEHICLE_ID)
				{			       		
					//if (getRandInt(1, 2) == 1)
					{
						((Vehicle*)target)->LockItemInItemSlot(GetSubTarget(), 1);
					}
					damage /= 3; // lower damage is used for precise fire
				}	
			}
       			GetLazerEquipment()->FireEvent(show_effect); 
			GetTarget()->Hit(damage, show_effect);
									       			
       			if (GetTarget()->GetAlive() == false)
       			{
       				GetOwnerVehicle()->GetOwnerNpc()->AddExpirience(GetTarget()->GetGivenExpirience(), show_effect);
       			}
       			
       			return true; break;  
    		}

    		case ENTITY::ROCKET_EQUIPMENT_ID:
    		{       
                	GetRocketEquipment()->FireEvent(attack_skill * SKILL::ATTACK_NORMALIZED_RATE);
                	return true; break;              
    		}

	}
	
    	return false;
}

bool ItemSlot::CheckItemInsertion(BaseItem* item) const
{
	if (data_id.subtype_id == ENTITY::CARGO_SLOT_ID) 
	{
		return true;
	}

	if (data_id.subtype_id == item->GetParentSubTypeId())
	{                                     
                return true;
	}
	
	return false;
}
    		        
bool ItemSlot::InsertItem(BaseItem* item)
{	
	if (data_id.subtype_id == ENTITY::CARGO_SLOT_ID) 
	{           
		this->item = item;
		if (item->GetItemSlot() != NULL)
		{
			item->GetItemSlot()->RemoveItem();
		}
		item->SetItemSlot(this);
	     
		return true;
	}

	if (data_id.subtype_id == item->GetParentSubTypeId())
	{                                     
		this->item = item;
		if (item->GetItemSlot() != NULL)
		{
			item->GetItemSlot()->RemoveItem();
		}
		item->SetItemSlot(this);
                UpdateVehiclePropetries(); 

                return true;
	}
	
	return false;
}

void ItemSlot::RemoveItem()
{	
        item = NULL;
    	
    	if (data_id.subtype_id != ENTITY::CARGO_SLOT_ID) 
	{    
                UpdateVehiclePropetries(); 
	}    	 
}

void ItemSlot::SelectEvent()
{
	selected = true;
        
        if (owner->GetTypeId() == ENTITY::VEHICLE_ID)
	{ 	
		switch(data_id.subtype_id)
		{
			case ENTITY::DRIVE_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesSpeed(); break; }
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
			case ENTITY::WEAPON_SLOT_ID: 	{ ResetTarget(); break; }
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
	if (data_id.subtype_id != ENTITY::CARGO_SLOT_ID)
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
       	if (item != NULL)
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

void ItemSlot::DropItemToSpace(Vehicle* vehicle)
{
        TextureOb* textureOb_ = TextureManager::Instance().GetRandomTextureOb(TEXTURE::CONTAINER_ID);   
        
        Container* container = ContainerBuilder::Instance().GetNewContainer(textureOb_, item);
        
	vehicle->GetStarSystem()->AddContainer(container, vehicle->GetPoints().GetCenter());	
}
        
bool ItemSlot::SwapItem(ItemSlot* slot)
{
       	if ( (item == NULL) and (slot->GetItem() != NULL) )
       	{      
       		if (InsertItem(slot->GetItem()) == true) 
       		{  			
       			return true; 
       		}             
	}
	
	if ( (item != NULL) and (slot->GetItem() == NULL) )
       	{ 
		if (slot->InsertItem(GetItem()) == true)
		{			
			return true; 
		}
	}

	if ( (item != NULL) and (slot->GetItem() != NULL) )
       	{        
       		if (item->GetTypeId() == slot->GetItem()->GetTypeId())
       		{
       			BaseItem* tmp_item = slot->GetItem();
       			if ( (slot->CheckItemInsertion(item) == true) and (CheckItemInsertion(tmp_item) == true) )
       			{       				
       				slot->InsertItem(item);
       				tmp_item->SetItemSlot(NULL);
       				InsertItem(tmp_item);
       			
       				return true;
       			}
       		
       		}

       		if ( (item->GetTypeId() == ENTITY::MODULE_ID) and (slot->GetItem()->GetTypeId() == ENTITY::EQUIPMENT_ID) )
       		{
			if (((BaseEquipment*)slot->GetItem())->InsertModule((BaseModule*)item) == true)  
			{	
				return true;
        		}
       		}

       		//if ( (item->GetTypeId() == ENTITY::EQUIPMENT_ID) and (slot->GetItem()->GetTypeId() == ENTITY::MODULE_ID) )
       		//{
			//if (((BaseEquipment*)item)->InsertModule((BaseModule*)slot->GetItem()) == true)  
			//{				
				//return true;
        		//}
       		//}
	}               
	
	return false;
}

void ItemSlot::UpdateRange(TextureOb* _texOb)
{
	float radius = this->GetItemRadius();
	int size = 6;
	
        range_visual.FillData(_texOb, radius, size);
}

void ItemSlot::DrawRange(const vec2f& offset)
{ 
    	range_visual.Draw(offset);
}

bool ItemSlot::CheckTarget(BaseSpaceEntity* _target, ItemSlot* _subtarget) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log(" ItemSlot::CheckTarget");
	#endif     
	
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
        return (_target->GetStarSystem()->GetId() == ((Vehicle*)owner)->GetStarSystem()->GetId());
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
{
        if (target) { save_ptree.put(root+"unresolved_ItemSlot.target_id", target->GetId()); }
        else        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

        if (subtarget) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", subtarget->GetId()); }
        else           { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
}

void ItemSlot::LoadDataUniqueItemSlot(const boost::property_tree::ptree& load_ptree)
{
        unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id"); 
        unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id"); 
}

void ItemSlot::ResolveDataUniqueItemSlot()
{
	if (unresolved_ItemSlot.target_id != NONE_ID)
	{
		target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.target_id);
	}

	if (unresolved_ItemSlot.subtarget_id != NONE_ID)
	{
		subtarget = (ItemSlot*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.subtarget_id);
	}

        switch(owner->GetTypeId())
        {
	       case ENTITY::VEHICLE_ID: 	{	((Vehicle*)owner)->AddItemSlot(this); break; }
	       case ENTITY::CONTAINER_ID:     	{	((Container*)owner)->BindItemSlot(this); break; }
	       case ENTITY::STORE_ID:         	{ 	((Store*)owner)->AddItemSlot(this); break; }
	       case ENTITY::ANGAR_ID:         	{ 	((Angar*)owner)->AddItemSlot(this); break; }
	       //case ENTITY::NATURELAND_ID:      { 	((NatureLand*)owner)->AddItemSlot(this); break; }
	}
}

void ItemSlot::LogSimpleTarget(const std::string& func_name) const
{
	Logger::Instance().Log("owner_type_id/id="+getTypeStr(owner->GetTypeId())+"/"+int2str(owner->GetId())+" itemslot_subtype_id/itemslot_subsubtype_id/Item subtype_id="+getTypeStr(GetSubTypeId())+"/"+getTypeStr(GetSubSubTypeId())+"/"+getTypeStr(item->GetSubTypeId())+func_name + " target_type_id= " + getTypeStr(GetTarget()->GetTypeId()) + " id=" + int2str(GetTarget()->GetId()), WEAPONSTARGET_LOG_DIP); 
}

void ItemSlot::LogComplexTarget(const std::string& func_name) const
{
	Logger::Instance().Log("owner_type_id/id="+getTypeStr(owner->GetTypeId())+"/"+int2str(owner->GetId())+" itemslot_subtype_id/itemslot_subsubtype_id/Item subtype_id="+getTypeStr(GetSubTypeId())+"/"+getTypeStr(GetSubSubTypeId())+"/"+getTypeStr(item->GetSubTypeId())+func_name+"target_type_id= " + getTypeStr(GetTarget()->GetTypeId()) + " id=" + int2str(GetTarget()->GetId()) + " item_subtype_id=" + getTypeStr(subtarget->GetItem()->GetSubTypeId()) + " id=" + int2str(subtarget->GetItem()->GetId()), WEAPONSTARGET_LOG_DIP); 
}
