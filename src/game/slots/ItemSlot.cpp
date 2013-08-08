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

#include "../builder/spaceobjects/ContainerBuilder.hpp"
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

#include "../dock/Store.hpp"
#include "../dock/Angar.hpp"

#include "../common/Logger.hpp"
#include "../common/rand.hpp" // (tmp) move to builder

#include "../garbage/EntityGarbage.hpp"
#include "../world/EntityManager.hpp"


std::string getTargetStatusStr(TARGET_STATUS status)
{
    switch(status)
    {
        case TARGET_STATUS::NOTALIVE:               { return "TARGET_STATUS::NOTALIVE"; break; }
        case TARGET_STATUS::NOTINSPACE:             { return "TARGET_STATUS::NOTINSPACE"; break; }
        case TARGET_STATUS::WRONG_STARSYSTEM:       { return "TARGET_STATUS::WRONG_STARSYSTEM"; break; }
        case TARGET_STATUS::UNREACHABLE_DISTANCE:   { return "TARGET_STATUS::UNREACHABLE_DISTANCE"; break; }
        case TARGET_STATUS::OK:                     { return "TARGET_STATUS::OK"; break; }
        
        default: { return "TARGET_STATUS::UNKNOWN"; break; }
    }
}


ItemSlot::ItemSlot(INTLONGEST id, TYPE::ENTITY subtype_id)
:
m_Turrel(nullptr),	      
m_Item(nullptr),
m_Target(nullptr),
m_Subtarget(nullptr),
m_HitProbability(0)
{
	SetId(id);
	SetTypeId(TYPE::ENTITY::ITEM_SLOT_ID);
	SetSubTypeId(subtype_id);
    
    m_HitProbability = getRandInt(0, 100); // (tmp) move to builder
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
	if (m_Item != nullptr)
	{
		EntityGarbage::Instance().Add(m_Item);
	}
}

void ItemSlot::SetTarget(BaseSpaceEntity* target, ItemSlot* subtarget) 	
{
	m_Target    = target; 
	m_Subtarget = subtarget;

	#if WEAPONSTARGET_LOG_ENABLED == 1 
    Log("SetTarget");
	#endif     
}
        
TARGET_STATUS ItemSlot::ValidateTarget()
{	
	#if WEAPONSTARGET_LOG_ENABLED == 1 
	Log("ValidateTarget");
	#endif   
	
	if (m_Subtarget != nullptr)
	{
		if (CheckSubTarget(m_Subtarget) == false)
		{
			m_Subtarget = nullptr; // reseting only subtarget, firemode for target will be used
		}
	}
	
    return CheckTarget(m_Target);
}

void ItemSlot::ResetTarget()
{ 
    #if WEAPONSTARGET_LOG_ENABLED == 1 
	Log("ResetTarget");
	#endif   
		
	m_Target    = nullptr; 
	m_Subtarget = nullptr;		
}

bool ItemSlot::CheckAmmo() const
{
	switch(GetItem()->GetSubTypeId())
	{
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID: { if (GetRocketEquipment()->GetAmmo() > 0) return true; break; }
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
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:
        {   
            GetLazerEquipment()->FireEvent(GetTarget(), GetSubTarget(), attack_rate, show_effect); 
            break;  
        }

        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:
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
	if (GetSubTypeId() == TYPE::ENTITY::CARGO_SLOT_ID) 
	{
		return true;
	}

	if (GetSubTypeId() == item->GetParentSubTypeId())
	{                                     
        return true;
	}
	
	return false;
}
    		        
bool ItemSlot::InsertItem(BaseItem* item)
{	
	if (GetSubTypeId() == TYPE::ENTITY::GATE_SLOT_ID) 
	{ 
        m_Item = item;
        DropItemToSpace();
        return true;
    }

	if (GetSubTypeId() == TYPE::ENTITY::CARGO_SLOT_ID) 
	{           
		m_Item = item;
		if (item->GetItemSlot() != nullptr)
		{
			item->GetItemSlot()->RemoveItem();
		}
		item->SetItemSlot(this);
	     
		return true;
	}

	if (GetSubTypeId() == item->GetParentSubTypeId())
	{                                     
		m_Item = item;
		if (item->GetItemSlot() != nullptr)
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
    m_Item = nullptr;
    ResetTarget();
    	
    if (GetSubTypeId() != TYPE::ENTITY::CARGO_SLOT_ID) 
	{    
        UpdateVehiclePropetries(); 
	}    	 
}

void ItemSlot::SelectEvent()
{
	selected = true;
        
    if (owner->GetTypeId() == TYPE::ENTITY::VEHICLE_ID)
	{ 	
		switch(GetSubTypeId())
		{
			case TYPE::ENTITY::DRIVE_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesSpeed(); break; }
		}
	}
}
                                
void ItemSlot::DeselectEvent()
{
	selected = false;
	
	if (owner->GetTypeId() == TYPE::ENTITY::VEHICLE_ID)
	{ 	
		switch(GetSubTypeId())
		{
			case TYPE::ENTITY::WEAPON_SLOT_ID: 	{ 	ResetTarget(); break; }
            case TYPE::ENTITY::DRIVE_SLOT_ID: 	
            {
  				GetOwnerVehicle()->UpdatePropertiesSpeed();
				//GetOwnerVehicle()->UpdatePropertiesJump();
                break;
            }
		}
	}
			
}
        	
void ItemSlot::UpdateVehiclePropetries() const
{
	if (GetSubTypeId() != TYPE::ENTITY::CARGO_SLOT_ID)
	{ 	
		switch(GetSubTypeId())
		{
			case TYPE::ENTITY::WEAPON_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesFire(); break; }
			case TYPE::ENTITY::SCANER_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesScan(); break; }
			case TYPE::ENTITY::BAK_SLOT_ID:     	{
						  		GetOwnerVehicle()->UpdatePropertiesSpeed();
   								GetOwnerVehicle()->UpdatePropertiesJump(); 
   	
   						  		break;
  							}
  			
  			case TYPE::ENTITY::DRIVE_SLOT_ID:   	{
  					  			GetOwnerVehicle()->UpdatePropertiesSpeed();
								GetOwnerVehicle()->UpdatePropertiesJump(); 
					  			break;
							}
				
			case TYPE::ENTITY::DROID_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesRepair(); break; }
			case TYPE::ENTITY::ENERGIZER_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesEnergy(); break; }
			case TYPE::ENTITY::FREEZER_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesFreeze(); break; }
			case TYPE::ENTITY::GRAPPLE_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesGrab(); break; }
			case TYPE::ENTITY::PROTECTOR_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesProtection(); break; }
			case TYPE::ENTITY::RADAR_SLOT_ID: 	{ GetOwnerVehicle()->UpdatePropertiesRadar(); break; }
			
			case TYPE::ENTITY::ARTEFACT_SLOT_ID: { GetOwnerVehicle()->UpdateArtefactInfluence(); break; }
		}
	}
}
   
/* virtual */
void ItemSlot::Render(const Box2D& box, const Vec2<float>& gui_offset, bool draw_text) const
{ 
    drawQuad(textureOb, box); 
    RenderItem(box, gui_offset, draw_text);	
}

void ItemSlot::RenderItem(const Box2D& box, const Vec2<float>& gui_offset, bool draw_text) const
{   
    if (m_Item != nullptr)
    {
        m_Item->Render(box, gui_offset, draw_text);	
    }
}

void ItemSlot::RenderMark(const Box2D& box, TextureOb* textureOb_mark) const
{
    drawQuad(textureOb_mark, box); 
}      

void ItemSlot::RenderTargetMark(const Box2D& box, TextureOb* textureOb_mask, TextureOb* textureOb) const
{
    drawQuadMasked(textureOb, box, textureOb_mask, 0.5); 
}     
        
int ItemSlot::GetItemRadius() const
{       
    switch(m_Item->GetTypeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_Item->GetSubTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetRadius();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetRadius(); break; };

                case TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID: { return GetGrappleEquipment()->GetRadius(); break; };
                case TYPE::ENTITY::RADAR_EQUIPMENT_ID:   { return GetRadarEquipment()->GetRadius();   break; };
            }
            
            break;
        }
        
        case TYPE::ENTITY::BOMB_ID:
        {
            return GetBomb()->GetRadius();   break; 
        }
    }
    
    return 0;
}

int ItemSlot::GetItemDamage() const
{       
    switch(m_Item->GetTypeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_Item->GetSubTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetDamage();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetDamage(); break; };
            }
            
            break;
        }
            
        case TYPE::ENTITY::BOMB_ID:
        {
            return GetBomb()->GetDamage();   break; 
        }
    }
    
    return 0;
}

void ItemSlot::DropItemToSpace()
{
    TextureOb* textureOb_ = nullptr;  
           
    switch (m_Item->GetTypeId())
    {
        case TYPE::ENTITY::BOMB_ID: { textureOb_ = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::BOMB_ID); break; }
        default:      				{ textureOb_ = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::CONTAINER_ID); break; }
    }

    Container* container = ContainerBuilder::Instance().GetNewContainer(textureOb_, m_Item);
    float impulse_strength = 0.5;
    Vec3<float> impulse_dir(getRandXYVec3Unit());
    container->ApplyImpulse(impulse_dir, impulse_strength);        
	GetOwnerVehicle()->GetStarSystem()->AddContainer(container, GetOwnerVehicle()->GetCenter());
    RemoveItem();
}
       
bool ItemSlot::SwapItem(ItemSlot* slot)
{
    if ( (m_Item == nullptr) and (slot->GetItem() != nullptr) )
    {      
        if (InsertItem(slot->GetItem()) == true) 
        {  			
            return true; 
        }             
	}
	
	if ( (m_Item != nullptr) and (slot->GetItem() == nullptr) )
    { 
		if (slot->InsertItem(GetItem()) == true)
		{			
			return true; 
		}
	}

	if ( (m_Item != nullptr) and (slot->GetItem() != nullptr) )
    {        
        //if (item->GetTypeId() == slot->GetItem()->GetTypeId())
        {
            BaseItem* tmp_item = slot->GetItem();
            if ( (slot->CheckItemInsertion(m_Item) == true) and (CheckItemInsertion(tmp_item) == true) )
            {  				
                slot->InsertItem(m_Item);
                tmp_item->SetItemSlot(nullptr);
                InsertItem(tmp_item);
            
                return true;
            }
        
        }

        if ( (m_Item->GetTypeId() == TYPE::ENTITY::MODULE_ID) and (slot->GetItem()->GetTypeId() == TYPE::ENTITY::EQUIPMENT_ID) )
        {
            if (((BaseEquipment*)slot->GetItem())->InsertModule((BaseModule*)m_Item) == true)  
            {	
                return true;
            }
        }
	}               
	
	return false;
}

void ItemSlot::UpdateRange(TextureOb* _texOb)
{
	float radius = this->GetItemRadius();
	int size = 6;
	
    m_VisualPath.FillData(_texOb, radius, size);
}

void ItemSlot::DrawRange(const Vec3<float>& offset)
{ 
    m_VisualPath.Draw(offset);
}

bool ItemSlot::CheckSubTarget(ItemSlot* _subtarget) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckSubTarget");
	#endif     
	
	if (_subtarget->GetItem() != nullptr)
	{
		return true;
	}
	
	return false;        
}


TARGET_STATUS ItemSlot::CheckTarget(BaseSpaceEntity* target) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
    Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckTarget");
	#endif     
	
	if (IsTargetAlive(target) == false)
    {
        return TARGET_STATUS::NOTALIVE;
    }
        
    if (IsTargetInSpace(target) == false)
    {
        return TARGET_STATUS::NOTINSPACE;
    }
            
    if (IsTargetInSameStarSystem(target) == false)
    {
        return TARGET_STATUS::WRONG_STARSYSTEM;        
    }

    if (CheckDistanceToTarget(target) == false)
    {
        return TARGET_STATUS::UNREACHABLE_DISTANCE;
    }
        
    return TARGET_STATUS::OK;
}     
   
TARGET_STATUS ItemSlot::CheckTargetPure(BaseSpaceEntity* target) const
{
	#if WEAPONSTARGET_LOG_ENABLED == 1 
    Logger::Instance().Log(" ItemSlot("+int2str(GetId())+")::CheckTarget");
	#endif     
	
	if (IsTargetAlive(target) == false)
    {
        return TARGET_STATUS::NOTALIVE;
    }
        
    if (IsTargetInSpace(target) == false)
    {
        return TARGET_STATUS::NOTINSPACE;
    }
            
    if (IsTargetInSameStarSystem(target) == false)
    {
        return TARGET_STATUS::WRONG_STARSYSTEM;        
    }
        
    return TARGET_STATUS::OK;
} 
       
bool ItemSlot::IsTargetAlive(BaseSpaceEntity* target) const
{
	return target->GetAlive();
}

bool ItemSlot::IsTargetInSpace(BaseSpaceEntity* target) const  
{
	return (target->GetPlaceTypeId() == TYPE::PLACE::SPACE_ID);
}           	

bool ItemSlot::IsTargetInSameStarSystem(BaseSpaceEntity* target) const
{
    return (target->GetStarSystem()->GetId() == GetOwnerVehicle()->GetStarSystem()->GetId());
}                

bool ItemSlot::CheckDistanceToTarget(BaseSpaceEntity* target) const
{
	if (target->GetTypeId() == TYPE::ENTITY::STARSYSTEM_ID)
	{
		return true;
	}
	
    float dist = distanceBetween(GetOwnerVehicle()->GetCenter(), target->GetCenter());                                               
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

    if (m_Target != nullptr)    { save_ptree.put(root+"unresolved_ItemSlot.target_id", m_Target->GetId()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

    if (m_Subtarget != nullptr) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", m_Subtarget->GetId()); }
    else          	            { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
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
		m_Target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.target_id);
	}

	if (unresolved_ItemSlot.subtarget_id != NONE_ID)
	{
		m_Subtarget = (ItemSlot*)EntityManager::Instance().GetEntityById(unresolved_ItemSlot.subtarget_id);
	}

    switch(owner->GetTypeId())
    {
       case TYPE::ENTITY::VEHICLE_ID: 	{	((Vehicle*)owner)->AddItemSlot(this); break; }
       case TYPE::ENTITY::CONTAINER_ID:     	{	((Container*)owner)->BindItemSlot(this); break; }
       case TYPE::ENTITY::STORE_ID:         	{ 	((Store*)owner)->AddItemSlot(this); break; }
       case TYPE::ENTITY::ANGAR_ID:         	{ 	((Angar*)owner)->AddItemSlot(this); break; }
       //case TYPE::ENTITY::NATURELAND_ID:      { 	((NatureLand*)owner)->AddItemSlot(this); break; }
	}
}

void ItemSlot::Log(const std::string& func_name) const
{
	Logger::Instance().Log("ItemSlot("+int2str(GetId())+")::"+func_name+GetDataTypeString());
	
	if (owner != nullptr)
	{
		Logger::Instance().Log(" owner="+owner->GetDataTypeString(), WEAPONSTARGET_LOG_DIP); 
	}
	
	if (m_Item != nullptr)
	{
		Logger::Instance().Log("item="+m_Item->GetDataTypeString(), WEAPONSTARGET_LOG_DIP); 
	}
	
	if (m_Target != nullptr)
	{
		Logger::Instance().Log("target="+m_Target->GetDataTypeString(), WEAPONSTARGET_LOG_DIP); 		
	}
	
	if (m_Subtarget != nullptr)
	{
		Logger::Instance().Log("subtarget="+m_Subtarget->GetDataTypeString(), WEAPONSTARGET_LOG_DIP); 	
	}
}

