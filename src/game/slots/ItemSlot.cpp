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
#include "../world/EntityManager.hpp"

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
	Logger::Instance().Log("___::~ItemSlot("+int2str(GetId())+")");
	#endif
}  
  
/* virtual */  
void ItemSlot::PutChildsToGarbage() const
{
	if (item != NULL)
	{
		EntityGarbage::Instance().Add(item);
	}
}

void ItemSlot::SetTarget(BaseSpaceEntity* target, ItemSlot* subtarget) 	
{
	this->target    = target; 
	this->subtarget = subtarget;

	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Log("SetTarget");
	#endif     
}
        
bool ItemSlot::ValidateTarget()
{	
	#if WEAPONSTARGET_LOG_ENABLED == 1 
	Log("ValidateTarget");
	#endif   
	
	if (subtarget != NULL)
	{
		if (CheckSubTarget(subtarget) == false)
		{
			subtarget = NULL; // reseting only subtarget, firemode for target will be used
		}
	}
	
        return CheckTarget(target);
}

void ItemSlot::ResetTarget()
{ 
       	#if WEAPONSTARGET_LOG_ENABLED == 1 
	Log("ResetTarget");
	#endif   
		
	target    = NULL; 
	subtarget = NULL;		
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

void ItemSlot::FireEvent(float attack_rate, bool show_effect)
{    
        #if WEAPONSTARGET_LOG_ENABLED == 1 
	Log("FireEvent");
	#endif   

	switch(GetItem()->GetSubTypeId())
	{
    		case ENTITY::LAZER_EQUIPMENT_ID:
    		{   
       			GetLazerEquipment()->FireEvent(GetTarget(), GetSubTarget(), attack_rate, show_effect); 
       			break;  
    		}

    		case ENTITY::ROCKET_EQUIPMENT_ID:
    		{       
                	GetRocketEquipment()->FireEvent(attack_rate);
                	break;              
    		}

	}

	if (GetTarget()->GetAlive() == false)
	{
		GetOwnerVehicle()->GetOwnerNpc()->AddExpirience(GetTarget()->GetGivenExpirience(), show_effect);
	}
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
    	ResetTarget();
    	
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
			case ENTITY::WEAPON_SLOT_ID: 	{ 	ResetTarget(); break; }
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
			case ENTITY::ENERGIZER_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesEnergy(); break; }
			case ENTITY::FREEZER_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesFreeze(); break; }
			case ENTITY::GRAPPLE_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesGrab(); break; }
			case ENTITY::PROTECTOR_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesProtection(); break; }
			case ENTITY::RADAR_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesRadar(); break; }
			
			case ENTITY::ARTEFACT_SLOT_ID: { GetOwnerVehicle()->UpdateArtefactInfluence(); break; }
		}
	}
}
   
/* virtual */
void ItemSlot::Render(const Box& box, const Vec2<float>& gui_offset, bool draw_text) const
{ 
       	drawQuad_inXYPlane(textureOb, box); 
       	if (item != NULL)
       	{
       		item->Render(box, gui_offset, draw_text);	
        }
}

void ItemSlot::RenderMark(const Box& box, TextureOb* textureOb_mark) const
{
       	drawQuad_inXYPlane(textureOb_mark, box); 
}      
        
int ItemSlot::GetItemRadius() const
{       
        switch(item->GetTypeId())
        {
                case ENTITY::EQUIPMENT_ID:
                {
                        switch (item->GetSubTypeId())
                        {
                                case ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetRadius();  break; };
                                case ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetRadius(); break; };
		
                                case ENTITY::GRAPPLE_EQUIPMENT_ID: { return GetGrappleEquipment()->GetRadius(); break; };
                                case ENTITY::RADAR_EQUIPMENT_ID:   { return GetRadarEquipment()->GetRadius();   break; };
                        }
                        
                        break;
                }
                
                case ENTITY::BOMB_ID:
                {
                        return GetBomb()->GetRadius();   break; 
                }
        }
        
        return 0;
}

int ItemSlot::GetItemDamage() const
{       
        switch(item->GetTypeId())
        {
                case ENTITY::EQUIPMENT_ID:
                {
                        switch (item->GetSubTypeId())
                        {
                                case ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetDamage();  break; };
                                case ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetDamage(); break; };
                        }
                        
                        break;
                }
                
                case ENTITY::BOMB_ID:
                {
                        return GetBomb()->GetDamage();   break; 
                }
        }
        
        return 0;
}

void ItemSlot::DropItemToSpace(Vehicle* vehicle)
{
        TextureOb* textureOb_ = NULL;  
                
        switch (item->GetTypeId())
        {
                case ENTITY::BOMB_ID: { textureOb_ = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BOMB_ID); break; }
                default:      { textureOb_ = TextureManager::Instance().GetRandomTextureOb(TEXTURE::CONTAINER_ID); break; }
        }
         
        Container* container = ContainerBuilder::Instance().GetNewContainer(textureOb_, item);
        
	vehicle->GetStarSystem()->AddContainer(container, vehicle->GetCenter());
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

void ItemSlot::DrawRange(const Vec3<float>& offset)
{ 
    	range_visual.Draw(offset);
}

bool ItemSlot::CheckSubTarget(ItemSlot* _subtarget) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckSubTarget");
	#endif     
	
	if (_subtarget->GetItem() != NULL)
	{
		return true;
	}
	
	return false;        
}


bool ItemSlot::CheckTarget(BaseSpaceEntity* _target) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckTarget");
	#endif     
	
	if (CheckTargetPure(_target) == true)
        {
                if (CheckDistanceToTarget(_target) == true)
                {
                        return true;
                }
        }
        
        return false;
}
      
      
      
bool ItemSlot::CheckTargetPure(BaseSpaceEntity* _target) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckTargetPure");
	#endif     
	
	if (IsTargetAlive(_target) == true)
        {
        	if (IsTargetInSpace(_target) == true)
        	{
                	if (IsTargetInSameStarSystem(_target) == true)
                        {
                                return true;
                        }
                }
        }
        
        return false;
}
          
bool ItemSlot::IsTargetAlive(BaseSpaceEntity* _target) const
{
	return _target->GetAlive();
}

bool ItemSlot::IsTargetInSpace(BaseSpaceEntity* _target) const  
{
	return (_target->GetPlaceTypeId() == ENTITY::SPACE_ID);
}           	

bool ItemSlot::IsTargetInSameStarSystem(BaseSpaceEntity* _target) const
{
        return (_target->GetStarSystem()->GetId() == ((Vehicle*)owner)->GetStarSystem()->GetId());
}                

bool ItemSlot::CheckDistanceToTarget(BaseSpaceEntity* _target) const
{
	if (_target->GetTypeId() == ENTITY::STARSYSTEM_ID)
	{
		return true;
	}
	
        float dist = distanceBetween(GetOwnerVehicle()->GetCenter(), _target->GetCenter());                                               
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
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::SaveDataUniqueItemSlot", SAVELOAD_LOG_DIP);
	#endif
	
        if (target != NULL) { save_ptree.put(root+"unresolved_ItemSlot.target_id", target->GetId()); }
        else                { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

        if (subtarget != NULL) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", subtarget->GetId()); }
        else          	       { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
}

void ItemSlot::LoadDataUniqueItemSlot(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::LoadDataUniqueItemSlot", SAVELOAD_LOG_DIP);
	#endif
	
        unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id"); 
        unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id"); 
}

void ItemSlot::ResolveDataUniqueItemSlot()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::ResolveDataUniqueItemSlot", SAVELOAD_LOG_DIP);
	#endif
	
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

void ItemSlot::Log(const std::string& func_name) const
{
	Logger::Instance().Log("ItemSlot("+int2str(GetId())+")::"+func_name+getBaseInfoStr(this));
	
	if (owner != NULL)
	{
		Logger::Instance().Log(" owner="+getBaseInfoStr(owner), WEAPONSTARGET_LOG_DIP); 
	}
	
	if (item != NULL)
	{
		Logger::Instance().Log("item="+getBaseInfoStr(item), WEAPONSTARGET_LOG_DIP); 
	}
	
	if (target != NULL)
	{
		Logger::Instance().Log("target="+getBaseInfoStr(target), WEAPONSTARGET_LOG_DIP); 		
	}
	
	if (subtarget != NULL)
	{
		Logger::Instance().Log("subtarget="+getBaseInfoStr(subtarget), WEAPONSTARGET_LOG_DIP); 	
	}
}

