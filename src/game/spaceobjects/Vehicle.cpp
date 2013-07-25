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

#include "Vehicle.hpp"
#include "../world/starsystem.hpp"
#include "../world/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../docking/Kosmoport.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../effects/particlesystem/ExplosionEffect.hpp"

#include "../resources/TextureManager.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../builder/spaceobjects/BaseVehicleBuilder.hpp"

#include "../common/Logger.hpp"

#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/EnergizerEquipment.hpp"
#include "../items/equipment/FreezerEquipment.hpp"
#include "../items/equipment/RadarEquipment.hpp"
#include "../items/equipment/BakEquipment.hpp"
#include "../items/equipment/ProtectorEquipment.hpp"
#include "../items/equipment/DroidEquipment.hpp"
#include "../items/equipment/DriveEquipment.hpp"
#include "../items/equipment/ScanerEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"

#include "../items/others/GoodsPack.hpp"

#include "../items/artefacts/GravityArtefact.hpp"
#include "../items/artefacts/ProtectorArtefact.hpp"

#include "../parts/Turrel.hpp"
#include "../effects/Shield.hpp"
#include "../effects/particlesystem/DriveEffect.hpp"

#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/Container.hpp"
#include "../parts/WeaponComplex.hpp"

#include "../text/VerticalFlowText.hpp" 
#include "../slots/VehicleSlot.hpp" 

#include "../docking/Angar.hpp"
#include "../pilots/Npc.hpp"

#include "../builder/ItemSlotBuilder.hpp"

#include "../docking/Shop.hpp"
#include "../docking/Store.hpp"
#include "../docking/NatureLand.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../effects/ShockWaveEffect.hpp"

Vehicle::Vehicle()
{
	god_mode = false;
	
	special_action_id = NONE_ID;
	
	owner_npc  = nullptr;
	
	weapon_complex.SetOwnerVehicle(this);
	drive_complex.SetOwnerVehicle(this);
	protection_complex.SetOwnerVehicle(this);
	
	radar_slot     = nullptr;
	scaner_slot    = nullptr;
	energizer_slot = nullptr;
	grapple_slot   = nullptr;
	droid_slot     = nullptr;
	freezer_slot   = nullptr;
	
	parent_vehicleslot = nullptr;
	land  = nullptr;
}

/*virtual*/
Vehicle::~Vehicle()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Vehicle("+int2str(GetId())+")");
	#endif
} 

/* virtual */
void Vehicle::PutChildsToGarbage() const
{
	owner_npc->SetAlive(false);
	EntityGarbage::Instance().Add(owner_npc);
	
	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		EntityGarbage::Instance().Add(slot_total_vec[i]);	
	}
}

void Vehicle::CreateDriveComplexTextureDependedStuff()
{
	GetPoints().addMidLeftPoint();
	GetPoints().addMidFarLeftPoint();
    	
	DriveEffect* drive_effect = GetNewDriveEffect(GetTextureOb()->size_id, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
 	GetDriveComplex().SetDriveEffect(drive_effect);
}    

void Vehicle::CreateProtectionComplexTextureDependedStuff()
{
	protection_complex.GetShieldEffect()->SetParent(this);
}

void Vehicle::SetKorpusData(const VehicleKorpusData& data_korpus) 
{ 
	this->data_korpus = data_korpus; 
	properties.protection = data_korpus.protection;
}
                
GoodsPack* Vehicle::GetGoodsPack() const
{
	for(unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetItem() != nullptr)
		{
			if (slot_cargo_vec[i]->GetItem()->GetTypeId() == ENTITY::TYPE::GOODS_ID)
			{
				return slot_cargo_vec[i]->GetGoodsPack();
			}
		}
	}	
	
	return nullptr;
}
        
/* virtual */
int Vehicle::GetGivenExpirience() const
{
	return owner_npc->GetSkills().GetExpirience() * GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE;
}
    
bool Vehicle::CheckItemSlotPresenceBySubTypeId(ENTITY::TYPE slot_subtype_id) const
{
	for (unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->GetSubTypeId() == slot_subtype_id)
		{
			return true;
		}
	}
	
	return false;
}
                    
void Vehicle::AddItemSlot(ItemSlot* slot) 
{ 
	slot->SetOwner(this); 
                
	switch(slot->GetSubTypeId())
	{
		case ENTITY::TYPE::WEAPON_SLOT_ID:    
		{
			float border_start = 0.2;
			float border_end   = 0.8;
			
			float pos_x = getRandFloat(border_start, border_end) - 0.5;
			float pos_y = getRandFloat(border_start, border_end) - 0.5;
							
			slot->GetTurrel()->SetParentCenter(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
			GetPoints().Add(slot->GetTurrel()->GetpCenter(), slot->GetTurrel()->GetpParentCenter()); 
			weapon_complex.AddSlot(slot); 
			
			break; 
		}
		case ENTITY::TYPE::DRIVE_SLOT_ID:     { drive_complex.SetDriveSlot(slot); break; }
		case ENTITY::TYPE::BAK_SLOT_ID:       { drive_complex.SetBakSlot(slot); break; }
		case ENTITY::TYPE::PROTECTOR_SLOT_ID: { protection_complex.SetProtectorSlot(slot); break; }
		case ENTITY::TYPE::RADAR_SLOT_ID:     { radar_slot  = slot; break; }
		case ENTITY::TYPE::SCANER_SLOT_ID:    { scaner_slot = slot; break; }
		
		case ENTITY::TYPE::ENERGIZER_SLOT_ID: { energizer_slot = slot; break; }
		case ENTITY::TYPE::GRAPPLE_SLOT_ID:   { grapple_slot   = slot; break; }
		case ENTITY::TYPE::DROID_SLOT_ID:     { droid_slot     = slot; break; }
		case ENTITY::TYPE::FREEZER_SLOT_ID:   { freezer_slot   = slot; break; }
	}
        
	slot_total_vec.push_back(slot); 

	if ( (slot->GetSubTypeId() != ENTITY::TYPE::ARTEFACT_SLOT_ID) and (slot->GetSubTypeId() != ENTITY::TYPE::CARGO_SLOT_ID) )
	{
		slot_funct_vec.push_back(slot);
	}
	
	if (slot->GetSubTypeId() == ENTITY::TYPE::ARTEFACT_SLOT_ID)
	{
		slot_artef_vec.push_back(slot);
	}
	
	if (slot->GetSubTypeId() == ENTITY::TYPE::CARGO_SLOT_ID)
	{
		slot_cargo_vec.push_back(slot); 
	}
		
}

bool Vehicle::GetAllItemsFromVehicle(Vehicle* vehicle)
{
	bool result = true;
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->GetItem() != nullptr)
		{
			if (vehicle->slot_total_vec[i]->GetSubTypeId() == ENTITY::TYPE::CARGO_SLOT_ID)
			{
				result = AddItemToCargoSlot(vehicle->slot_total_vec[i]->GetItem());
			}
			else
			{
				result = AddAndManageItem(vehicle->slot_total_vec[i]->GetItem());
			}
		}
	}
	
	return result;
}
                
bool Vehicle::ManageItem(BaseItem* item)
{
	switch(item->GetTypeId())
	{
		case ENTITY::TYPE::EQUIPMENT_ID: 	{ return ManageFunctionEquipment(item); break; }
		case ENTITY::TYPE::MODULE_ID: 	{ return ManageFunctionModule(item); break; }
		case ENTITY::TYPE::ARTEFACT_ID: 	{ return ManageFunctionArtefact(item); break; }	
		case ENTITY::TYPE::GOODS_ID: 		{ return ManageFunctionGoodsPack(item); break; }
	}
	
	return false;
} 
            	
bool Vehicle::ManageFunctionGoodsPack(BaseItem* item)
{
	return MergeIdenticalGoods(item);
}	

bool Vehicle::ManageFunctionEquipment(BaseItem* item)
{
	if (item->GetParentSubTypeId() == ENTITY::TYPE::WEAPON_SLOT_ID)
	{
		ItemSlot* item_slot = weapon_complex.GetEmptyWeaponSlot();
		if (item_slot != nullptr)
		{
			return item_slot->SwapItem(item->GetItemSlot());
		}
		else
		{
			ItemSlot* item_slot = weapon_complex.GetEquipedWeakestWeaponSlot();
			if (item_slot != nullptr)
			{
				if (item->GetPrice() > item_slot->GetItem()->GetPrice())
				{
					return item_slot->SwapItem(item->GetItemSlot());
				}
			}
		}
	}
	else
	{
		ItemSlot* item_slot = GetFuctionalSlot(item->GetParentSubTypeId());
		if (item_slot->GetItem() == nullptr)
		{
			return item_slot->SwapItem(item->GetItemSlot());
		}
		else
		{
			if (item->GetPrice() > item_slot->GetItem()->GetPrice())
			{
				return item_slot->SwapItem(item->GetItemSlot());
			}
		}		
	}
	
	return false;        
} 	

bool Vehicle::ManageFunctionModule(BaseItem* item)
{
	for (unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetItem() != nullptr)
		{
			if (slot_funct_vec[i]->GetItem()->GetSubTypeId() == item->GetParentSubTypeId())
			{
				return ((BaseEquipment*)slot_funct_vec[i]->GetItem())->InsertModule((BaseModule*)item);				
			}
		}
	}
	
	return false;
}

bool Vehicle::ManageFunctionArtefact(BaseItem* item)
{
	ItemSlot* artef_slot = GetEmptyArtefactSlot();
	if (artef_slot != nullptr)
	{
		return artef_slot->SwapItem(item->GetItemSlot());
	}

	return false;
}

ItemSlot* Vehicle::GetFuctionalSlot(ENTITY::TYPE functional_slot_subtype_id) const
{
	for(unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetSubTypeId() == functional_slot_subtype_id)
		{
			return slot_funct_vec[i];
		}
	}
}

ItemSlot* Vehicle::GetEmptyArtefactSlot() const
{
	for(unsigned int i=0; i<slot_artef_vec.size(); i++)
	{
		if (slot_artef_vec[i]->GetItem() == nullptr)
		{
			return slot_artef_vec[i];
		}
	}
	
	return nullptr;
}
                	
ItemSlot* Vehicle::GetEmptyCargoSlot()
{
	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{      			
		if (slot_cargo_vec[i]->GetItem() == nullptr)
		{
			return slot_cargo_vec[i];
		}
	}
	
	return nullptr;
}

ItemSlot* Vehicle::GetCargoSlotWithGoods(ENTITY::TYPE requested_goods_subtype_id)
{
	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetItem() != nullptr)
		{
			if (slot_cargo_vec[i]->GetItem()->GetTypeId() == ENTITY::TYPE::GOODS_ID)
			{
				if (slot_cargo_vec[i]->GetItem()->GetSubTypeId() == requested_goods_subtype_id)
				{
					return slot_cargo_vec[i];
				}
			}
		}             		
	}
	
	return nullptr;
}

bool Vehicle::UnpackContainerItemToCargoSlot(Container* container)
{	
 	if (AddItemToCargoSlot(container->GetItemSlot()->GetItem()) == true)
	{      
		container->SilentKill();
								
		return true;
	}
	
	return false;
} 

bool Vehicle::AddItemToCargoSlot(BaseItem* item)
{
	IncreaseMass(item->GetMass());
	if (item->GetTypeId() == ENTITY::TYPE::GOODS_ID)
	{
		if (ManageFunctionGoodsPack(item) == true)
		{
			return true;
		}
	}
	
	ItemSlot* cargo_slot = GetEmptyCargoSlot();
	if (cargo_slot != nullptr)
	{
		return cargo_slot->InsertItem(item);
	}
	
	return false;
} 

bool Vehicle::AddAndManageItem(BaseItem* item)
{
	bool result = AddItemToCargoSlot(item);
	                        
	if (result == true)
	{
		ManageItem(item);
	}

	return result;
}
     
void Vehicle::ManageItemsInCargo()
{
	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetItem() != nullptr)
		{
			ManageItem(slot_cargo_vec[i]->GetItem());
		}
	}
}
    
void Vehicle::SellItemsInCargo()
{
	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetItem() != nullptr)
		{
			SellItem(slot_cargo_vec[i]->GetItem());
		}
	}
}

bool Vehicle::SellItem(BaseItem* item)
{
	//float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
	//npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
	int earn_money = 0;
	int item_mass = item->GetMass();
	switch(item->GetTypeId())
	{
		case ENTITY::TYPE::GOODS_ID: 	   
		{ 
			earn_money = ((Kosmoport*)land)->GetShop()->BuyGoods((GoodsPack*)item);	
			break; 
		}
		
		case ENTITY::TYPE::EQUIPMENT_ID: 
		{ 
			earn_money = ((Kosmoport*)land)->GetStore()->BuyItem(item);
			break; 
		}		
	}
	
	if (earn_money > 0)
	{
		DecreaseMass(item_mass);
		owner_npc->IncreaseCredits(earn_money);
		
		return true;
	}
	else
	{
		return false;
	}
}
 
bool Vehicle::BuyItem(BaseItem* item)
{
        if (AddItemToCargoSlot(item) == true)
        {
        	owner_npc->IncreaseCredits(-item->GetPrice());
        	
        	return true; 
        }
        
        return false;
}
                
bool Vehicle::MergeIdenticalGoods(BaseItem* item)
{
	ItemSlot* item_slot = GetCargoSlotWithGoods(item->GetSubTypeId());
	if (item_slot != nullptr)
	{
		item_slot->GetGoodsPack()->Increase(item->GetMass());
		// delete item; dangerrr
		return true;
	}
	
	return false;                
} 

void Vehicle::BindOwnerNpc(Npc* owner_npc) 	           
{ 
	this->owner_npc = owner_npc; 
	owner_npc->SetVehicle(this); 
} 

bool Vehicle::IsObjectWithinRadarRange(BaseSpaceEntity* object) const
{
    float dist = distanceBetween(GetCenter(), object->GetCenter());
    if (dist < properties.radar)
    {
            return true;
    }
    
    return false;
}	

void Vehicle::UpdateSpecialAction()
{
	if (special_action_id != NONE_ID)
	{
		switch(special_action_id)
		{
			case SPECIAL_ACTION::INITIATE_DOCKING_ID:
			{
				if (UpdateFadeInEffect() == true)
				{
					DockingEvent();
					special_action_id = NONE_ID;
				}
				
				break;			
			}
						
			case SPECIAL_ACTION::INITIATE_LAUNCHING_ID:
			{
				if (UpdateFadeOutEffect() == true)
				{
					special_action_id = NONE_ID;
				}
				
				break;
			}

			case SPECIAL_ACTION::INITIATE_JUMPIN_ID:
			{
				if (UpdateFadeInEffect() == true)
				{
			                HyperJumpEvent(drive_complex.GetTarget()->GetStarSystem());
			        }
			
				break;
			}
			
			case SPECIAL_ACTION::INITIATE_JUMPOUT_ID:
			{
				if (UpdateFadeOutEffect() == true)
				{
			                special_action_id = NONE_ID;
			        }
			
				break;
			}
		}
	}
}
              
bool Vehicle::UpdateFadeInEffect()
{
	if (color.a > 0.01)
	{
		color.a -= 0.02;
		return false;
	}
	else
	{
		color.a = 0.0;
		return true;
	}
}

bool Vehicle::UpdateFadeOutEffect()
{
	if (color.a < 1.0)
	{
		color.a += 0.02;
		return false;
	}
	else
	{
		color.a = 1.0;
		return true;
	}
}

//// ******** DOCKING/LAUNCHING ******** 
void Vehicle::HyperJumpEvent(StarSystem* starsystem)
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
    Logger::Instance().Log("Vehicle("+int2str(GetId())+")::HyperJumpEvent", ENTITY_TRANSACTION_LOG_DIP); 
    #endif   
    
    weapon_complex.DeactivateAllWeapons();
    
    special_action_id = SPECIAL_ACTION::INITIATE_JUMPOUT_ID;
    starsystem->GetHyperSpace().AddVehicle(this);
}
                
                
void Vehicle::DockingEvent()
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::DockingEvent", ENTITY_TRANSACTION_LOG_DIP); 
	#endif
	          
	weapon_complex.DeactivateAllWeapons();
	          	 
        switch(drive_complex.GetTarget()->GetTypeId())         	     	     	
     	{
     		case ENTITY::TYPE::PLANET_ID:
     		{
                	Planet* planet = ((Planet*)drive_complex.GetTarget());                
     			planet->GetLand()->AddVehicle(this);
                        
			break;
		}
	
		case ENTITY::TYPE::VEHICLE_ID:
		{	 
			switch(drive_complex.GetTarget()->GetSubTypeId())
			{
				case ENTITY::TYPE::SPACESTATION_ID:
				{
                			SpaceStation* spacestation = ((SpaceStation*)drive_complex.GetTarget());
                        		spacestation->GetLand()->AddVehicle(this);
                        
					break;
				}
				
				case ENTITY::TYPE::SHIP_ID:
				{
					//..
					break;
				}
			}
			
			break;
		}
	}
        
        GetDriveComplex().ResetTarget();
}

void Vehicle::LaunchingEvent()
{
        #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::LaunchingEvent", ENTITY_TRANSACTION_LOG_DIP); 
	#endif
	
	if (parent_vehicleslot != nullptr)
	{
		switch(parent_vehicleslot->GetOwner()->GetTypeId())
		{
			case ENTITY::TYPE::ANGAR_ID:
			{
				int angleInD = getRandInt(0, 360);
				Vec2<float> offset_pos = getRandVec2f(40, 100);
				Vec3<float> offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
				Vec3<float> angle(0,0,angleInD);
                GetStarSystem()->AddVehicle(this, ((BaseSpaceEntity*)land->GetOwner())->GetCenter() + offset_pos3, angle, nullptr);
				land->RemoveVehicle(this);
	
				break;
			}
				
			case ENTITY::TYPE::VEHICLE_ID:
			{
				//..
				break;
			}
		}
	}
	else
	{
		int angleInD = getRandInt(0, 360);
		Vec2<float> offset_pos = getRandVec2f(40, 100);
		Vec3<float> offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
		Vec3<float> angle(0,0,angleInD);
        GetStarSystem()->AddVehicle(this, ((BaseSpaceEntity*)land->GetOwner())->GetCenter() + offset_pos3, angle, nullptr);
		land->RemoveVehicle(this); 
	}


	SetSpecialActionId(SPECIAL_ACTION::INITIATE_LAUNCHING_ID);
	color.a = 0.1;
}
//// 

/* virtual */
void Vehicle::TakeIntoAccountAgressor(Vehicle* agressor)
{
	owner_npc->TakeIntoAccountAgressor(agressor);
}

/* virtual */
void Vehicle::Hit(int damage, bool show_effect)
{
	#if WEAPONSTARGET_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::Hit", WEAPONSTARGET_LOG_DIP);
	#endif
	
	if (god_mode == false)
	{
	
	if (properties.energy < damage)
	{
		properties.hibernate_mode_enabled = true;
		UpdatePropertiesProtection();
	}
	
	damage *= (1.0 - properties.protection*0.01f);
	damage *= owner_npc->GetSkills().GetDefenceNormalized();
	
	GetDataLife().armor -= damage;
	
    if (GetDataLife().armor < 0)
    {
        GetDataLife().is_alive = false;
    }

	if (show_effect == true)
	{
        if (protection_complex.GetProtectorSlot()->GetItem() != nullptr)
        {
            protection_complex.GetShieldEffect()->SetAlpha(1.0);
        }       	
       		
       		VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, GetCenter(), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
       		GetStarSystem()->Add(text); 
       	}
       	
    }
}

/* virtual */
void Vehicle::PostDeathUniqueEvent(bool show_effect)  
{
	int num_items = getRandInt(0, 3);
	for (int i = 0; i<num_items; i++)
	{
		DropRandomItemToSpace();
	}
	
	if (show_effect == true)
     	{
     		ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
        	GetStarSystem()->Add(explosion, GetCenter());        		
        }
}


void Vehicle::CheckNeedsInStatic()
{
        // check armor
        if (GetDataLife().armor < 0.5*data_korpus.armor) { needs.repair_korpus = true; }
        else                                         { needs.repair_korpus = false; }

        //check item damages
        needs.repair_equipment = false;
        for (unsigned int i=0; i<slot_funct_vec.size(); i++)
        {
                if (slot_funct_vec[i]->GetItem() != nullptr)
                {
                        if (slot_funct_vec[i]->GetItem()->GetDamaged() == true)
                        {
                                needs.repair_equipment = true;                                
                        }
                }
        }
        
        //check ammo
        needs.get_ammo = false;
        for (unsigned int i=0; i<slot_funct_vec.size(); i++)
        {
                if (slot_funct_vec[i]->GetItem() != nullptr)
                {
                        if (slot_funct_vec[i]->GetItem()->GetSubTypeId() == ENTITY::TYPE::ROCKET_EQUIPMENT_ID) 
                        {
                                if (slot_funct_vec[i]->GetRocketEquipment()->GetAmmo() == 0)
                                {
                                        needs.get_ammo = true; 
                                }
                        }
                }
        }
        
        // check fuel
        needs.get_fuel = false;
        if (drive_complex.GetBakSlot() != nullptr)
        {
                if (drive_complex.GetBakSlot()->GetItem() != nullptr)
                {
                        if (drive_complex.GetBakSlot()->GetBakEquipment()->GetFuel() < 0.8*drive_complex.GetBakSlot()->GetBakEquipment()->GetFuelMax())
                        {
                                needs.get_fuel = true;
                        } 
                }   
        }
        
        // check credits
        if (owner_npc->GetCredits() < 1000) { needs.get_credits = true; }
        else                                { needs.get_credits = false; }
}


void Vehicle::ResolveNeedsInKosmoportInStatic()
{
        bool result = true;
        
        // buy repair korpus
        if ( (needs.repair_korpus == true) and (result == true) )
        {
                result = ((Angar*)parent_vehicleslot->GetOwner())->RepairVehicle(this);
        }        
      
        // repair equipment
        if ( (needs.repair_equipment == true) and (result == true) )
        {
                for (unsigned int i=0; i<slot_funct_vec.size(); i++)
                {
                        if (slot_funct_vec[i]->GetItem() != nullptr)
                        {
                                if (slot_funct_vec[i]->GetItem()->GetDamaged() == true)
                                {
                                        result = ((Angar*)parent_vehicleslot->GetOwner())->RepairItem(owner_npc, slot_funct_vec[i]->GetItem());
                                }
                        }
                }
        }        
        
        // buy ammo
        if ( (needs.get_ammo == true) and (result == true) )
        {
                for (unsigned int i=0; i<slot_funct_vec.size(); i++)
                {
                        if (slot_funct_vec[i]->GetItem() != nullptr)
                        {
                                if (slot_funct_vec[i]->GetItem()->GetSubTypeId() == ENTITY::TYPE::ROCKET_EQUIPMENT_ID)
                                {
                                        result = ((Angar*)parent_vehicleslot->GetOwner())->ChargeRocketEquipment(owner_npc, slot_funct_vec[i]->GetRocketEquipment());
                                }
                        }
                }
        }
        
        // tank up
        if ( (needs.get_fuel == true) and (result == true) )
        {
                result = ((Angar*)parent_vehicleslot->GetOwner())->TankUpVehicle(this);
        }
       
        //// check credits
        //if (owner_npc->GetCredits() < 1000) { needs.get_credits = true; }
        //else                                { needs.get_credits = false; }
}

void Vehicle::UpdateAllFunctionalItemsInStatic()
{
	for (unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetItem() != nullptr)
		{
			slot_funct_vec[i]->GetItem()->UpdateInStatic();
		}
	}

	for (unsigned int i=0; i<slot_artef_vec.size(); i++)
	{
		if (slot_artef_vec[i]->GetItem() != nullptr)
		{
			slot_artef_vec[i]->GetItem()->UpdateInStatic();
		}
	}
}

void Vehicle::IncreaseMass(int d_mass)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::IncreaseMass", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	ChangeMass(d_mass);
    properties.free_space = data_korpus.space - GetMass();
	UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::DecreaseMass(int d_mass)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::DecreaseMass", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	ChangeMass(-d_mass);
    properties.free_space = data_korpus.space - GetMass();
	UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::UpdatePropertiesSpeed()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesSpeed", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	// speed calculation ////
     	properties.speed = 0;

     	if (drive_complex.GetDriveSlot() != nullptr) 
     	{
                if (drive_complex.GetDriveSlot()->GetItem() != nullptr) 
                {
                        if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)  
                        {
                                float actual_speed = (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetSpeed() - GetMass()*MASS_DECREASE_SPEED_RATE); 
                                if (actual_speed > 0)
                                { 
                                        if (properties.artefact_gravity > 0)
                                        {
                                                properties.speed = (1.0 + properties.artefact_gravity/100.0)*actual_speed;         
                                        }
                                        else
                                        {
                                                properties.speed = actual_speed; 
                                        }
                                        
                                        if (drive_complex.GetDriveSlot()->GetSelected() == true)
                                        {
                                                properties.speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
                                                drive_complex.GetDriveSlot()->GetItem()->UseOverloadDeterioration();
                                        }
                                        else
                                        {
                                                drive_complex.GetDriveSlot()->GetItem()->UseNormalDeterioration();
                                        }
        
                                        
                                        drive_complex.UpdatePath();
                                }
                        }
                }
        }
}

void Vehicle::UpdatePropertiesFire()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesFire", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	weapon_complex.UpdateFireAbility();
     	
	properties.total_damage = weapon_complex.GetTotalDamage();
	properties.total_radius = weapon_complex.GetTotalRadius();
}

void Vehicle::UpdatePropertiesRadar()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesRadar", ITEMINFLUENCE_LOG_DIP);
	#endif
	
        properties.radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
        properties.equipment_radar = false;
	
   	if (radar_slot->GetItem() != nullptr) 
   	{
      		if (radar_slot->GetRadarEquipment()->GetFunctioning() == true)  
      		{
          		properties.radar = radar_slot->GetRadarEquipment()->GetRadius();
          		properties.equipment_radar = true;
      		}
      	}
}

void Vehicle::UpdatePropertiesJump()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesJump", ITEMINFLUENCE_LOG_DIP);
	#endif
	    
	properties.hyper = 0;

        if (drive_complex.GetDriveSlot() != nullptr)
        {
                if (drive_complex.GetDriveSlot()->GetItem() != nullptr)
                {
                        if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)
                        {
                                if (drive_complex.GetBakSlot() != nullptr)
                                {
                                        if (drive_complex.GetBakSlot()->GetItem() != nullptr)
                                        {
                                                if (drive_complex.GetBakSlot()->GetBakEquipment()->GetFunctioning() == true)
                                                {
                                                        if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetHyper() > drive_complex.GetBakSlot()->GetBakEquipment()->GetFuel())
                                                                properties.hyper = drive_complex.GetDriveSlot()->GetDriveEquipment()->GetHyper();
                                                        else
                                                                properties.hyper = drive_complex.GetBakSlot()->GetBakEquipment()->GetFuel();
                                                }
                                        } 
                                }
                        }
                }
        }
}

void Vehicle::UpdatePropertiesEnergy()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesEnergy", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	properties.energy = 0;
	properties.hibernate_mode_enabled = true;

     	if (energizer_slot->GetItem() != nullptr)
     	{
        	if (energizer_slot->GetEnergizerEquipment()->GetFunctioning() == true)
        	{
           		properties.energy = energizer_slot->GetEnergizerEquipment()->GetEnergy();
           		properties.hibernate_mode_enabled = false;
        	}
        }
        
        UpdatePropertiesProtection();
}

void Vehicle::UpdatePropertiesProtection()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesProtection", ITEMINFLUENCE_LOG_DIP);
	#endif
	
        properties.protection = data_korpus.protection;
        properties.shield_effect_enabled = false;

	if (properties.hibernate_mode_enabled == false)
	{
     		if (protection_complex.GetProtectorSlot()->GetItem() != nullptr)
     		{
        		if (protection_complex.GetProtectorSlot()->GetProtectorEquipment()->GetFunctioning() == true)
        		{
           			properties.protection += protection_complex.GetProtectorSlot()->GetProtectorEquipment()->GetProtection();
           			properties.shield_effect_enabled = true;
        		}
     		}
     	}
     	
     	if (properties.artefact_protection > 0)
     	{
     		properties.protection += properties.artefact_protection;
     	}
}

void Vehicle::UpdatePropertiesRepair()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesRepair", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	properties.repair = 0;

     	if (droid_slot->GetItem() != nullptr)
     	{
        	if (droid_slot->GetDroidEquipment()->GetFunctioning() == true)
        	{
            		properties.repair = droid_slot->GetDroidEquipment()->GetRepair();
        	}
        }
}


void Vehicle::IncreaseArmor(int repair)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::IncreaseArmor", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	GetDataLife().armor += repair;
	
	if (GetDataLife().armor > data_korpus.armor)
	{
		GetDataLife().armor = data_korpus.armor;
	}
}

void Vehicle::UpdatePropertiesFreeze()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesFreeze", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	properties.freeze = 0;

     	if (freezer_slot->GetItem() != nullptr)
     	{
        	if (freezer_slot->GetFreezerEquipment()->GetFunctioning() == true)
        	{
           		properties.freeze = freezer_slot->GetFreezerEquipment()->GetFreeze();
        	}
        }
}

void Vehicle::UpdatePropertiesScan()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesScan", ITEMINFLUENCE_LOG_DIP);
	#endif
	
     	properties.scan = 0;

     	if (scaner_slot->GetItem() != nullptr)
     	{
        	if (scaner_slot->GetScanerEquipment()->GetFunctioning() == true)
        	{
           		properties.scan = scaner_slot->GetScanerEquipment()->GetScan();
        	}
        }
}

void Vehicle::UpdatePropertiesGrab()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdatePropertiesGrab", ITEMINFLUENCE_LOG_DIP);
	#endif

        properties.grab_strength = 0;
        properties.grab_radius = 0;
                      			      			
     	if (data_korpus.slot_grapple_num != 0)
     	{
        	if (grapple_slot->GetItem() != nullptr)
           	{
           		if (grapple_slot->GetGrappleEquipment()->GetFunctioning() == true)
              		{
			        properties.grab_strength = grapple_slot->GetGrappleEquipment()->GetStrength();
			        properties.grab_radius = grapple_slot->GetGrappleEquipment()->GetRadius();
              		}
              	}
	}
}                  
        
void Vehicle::UpdateArtefactInfluence()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::UpdateArtefactInfluence", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	properties.artefact_gravity = 0;
	properties.artefact_protection = 0;
	
	for (unsigned int i=0; i<slot_artef_vec.size(); i++)
	{
		if (slot_artef_vec[i]->GetItem() != nullptr)
		{
		        if (slot_artef_vec[i]->GetItem()->GetFunctioning() == true)
              		{
				switch(slot_artef_vec[i]->GetItem()->GetSubTypeId())
				{
					case ENTITY::TYPE::GRAVITY_ARTEFACT_ID:
					{
						properties.artefact_gravity += ((GravityArtefact*)slot_artef_vec[i]->GetItem())->GetGravity();
						break;
					}

					case ENTITY::TYPE::PROTECTOR_ARTEFACT_ID:
					{
						properties.artefact_protection += ((ProtectorArtefact*)slot_artef_vec[i]->GetItem())->GetProtection();
						break;
					}
				}              		
              		}
		}
	}
	
	if (properties.artefact_gravity > 0)
	{
		UpdatePropertiesSpeed();
	}
	
	if (properties.artefact_protection > 0)
	{
		UpdatePropertiesProtection();
	}
}

/* virtual override final */               
void Vehicle::RenderInfoInSpace(const Vec2<float>& scroll_coords, float zoom)
{  
	UpdateInfo(); // virtual
	Vec2<float> pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
	pos /= zoom;
    drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
	if (owner_npc != nullptr)
	{
        Vec2<float> pos2(pos.x + 200, pos.y);
    	owner_npc->RenderInfo(pos2);
	}
}

void Vehicle::RenderInfo(const Vec2<float>& center, int offset_x, int offset_y)
{  
	UpdateInfo(); // virtual
	Vec2<float> pos(center.x - offset_x, center.y - offset_y);
    drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);

    if (owner_npc != nullptr)
    {
        owner_npc->RenderInfo(Vec2<float>(center.x + 190 - offset_x, center.y - offset_y));
    }
}

void Vehicle::RenderGrabTrail() const
{
    grapple_slot->GetGrappleEquipment()->RenderGrabTrail();
}
		
void Vehicle::RenderKorpus() const
{
	drawQuad(GetTextureOb(), GetCenter(), GetSize(), GetAngle().z);
}

void Vehicle::RenderDriveEffect(float scale, float parent_d_alpha) const
{
	drive_complex.GetDriveEffect()->Update();
	drive_complex.GetDriveEffect()->Render(scale, parent_d_alpha);
}


void Vehicle::RenderShieldEffect(float parent_d_alpha) const
{
	protection_complex.GetShieldEffect()->Render(parent_d_alpha);
}

void Vehicle::RenderRadarRange()
{
	if (properties.radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
	{
		radar_slot->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
		radar_slot->DrawRange(GetCenter());
	}
}

void Vehicle::RenderGrappleRange()
{
	if (properties.grab_radius > 0)
	{
		grapple_slot->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
		grapple_slot->DrawRange(GetCenter());
	}
}

bool Vehicle::IsAbleToJumpTo(StarSystem* target_starsystem) const
{
 	float dist = distanceBetween(GetStarSystem()->GetCenter(), target_starsystem->GetCenter());
	if (dist < properties.hyper)
	{
		return true;
	}
	
	return false;
}
		
void Vehicle::RepairKorpusOnAmount(int amount)
{
	GetDataLife().armor += amount;
	if (GetDataLife().armor > data_korpus.armor)
	{
		GetDataLife().armor = data_korpus.armor;
	}
}

bool Vehicle::IsArmorFull() const
{
	if (GetDataLife().armor == data_korpus.armor)
	{
		return true;
	}
	
	return false;
}

int Vehicle::GetArmorMiss() const
{
	return (data_korpus.armor - GetDataLife().armor);
}

bool Vehicle::IsFuelFull() const
{
	if (drive_complex.GetBakSlot()->GetItem() == nullptr)
	{
		return true;
	}
	
	if (GetFuelMiss() == 0)
	{
		return true;
	}
	
	
	return false;
}

int Vehicle::GetFuelMiss() const
{
	return drive_complex.GetBakSlot()->GetBakEquipment()->GetFuelMiss();
}

void Vehicle::LockRandomItem(int locked_turns)
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetItem() != nullptr)
		{
			_equiped_slot_vec.push_back(slot_funct_vec[i]);
		}
	}
	
	if (_equiped_slot_vec.size() > 0)
	{
		unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());	
		_equiped_slot_vec[_rand]->GetItem()->LockEvent(locked_turns);
	}	
}

bool Vehicle::TryToConsumeEnergy(int energy)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::TryToConsumeEnergy(energy="+int2str(energy)+")", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	if (properties.energy > energy)
	{
		properties.energy -= energy;
		energizer_slot->GetEnergizerEquipment()->DecreaseEnergy(energy); 
		
		return true;		
	}
	
	return false;
}

bool Vehicle::TryToGenerateEnergy(int energy)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("Vehicle("+int2str(GetId())+")::TryToGenerateEnergy(energy="+int2str(energy)+")", ITEMINFLUENCE_LOG_DIP);
	#endif
	
	int energy_max = energizer_slot->GetEnergizerEquipment()->GetEnergyMax();
	if (properties.energy < energy_max)
	{
		int diff_energy = energy_max - properties.energy;
		if ( diff_energy < energy)
		{
			energy = diff_energy;
		}
		
		properties.energy += energy;
		energizer_slot->GetEnergizerEquipment()->IncreaseEnergy(energy); 
		
		if (properties.hibernate_mode_enabled == true)
		{
			if (properties.energy > HIBERNATION_ENERGY_THRESHOLD)
			{
				UpdatePropertiesProtection();
			}
		}
		
		return true;
	}
	
	return false;
}

		
void Vehicle::DropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->GetItem() != nullptr)
		{
			_equiped_slot_vec.push_back(slot_total_vec[i]);
		}
	}
	
	if (_equiped_slot_vec.size() > 0)
	{
		_equiped_slot_vec[getRandInt(0, _equiped_slot_vec.size()-1)]->DropItemToSpace();
	}		
}

void Vehicle::UpdateGrappleMicroProgram_inDynamic()
{
	if (properties.grab_radius > 0)
	{
		grapple_slot->GetGrappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
	}     
}
				
void Vehicle::SaveDataUniqueVehicle(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Vehicle("+int2str(GetId())+")::SaveDataUniqueVehicle", SAVELOAD_LOG_DIP);
	#endif

       	save_ptree.put(root+"data_korpus.space", data_korpus.space);       	
       	save_ptree.put(root+"data_korpus.armor", data_korpus.armor);  
       	save_ptree.put(root+"data_korpus.protection", data_korpus.protection); 
       	save_ptree.put(root+"data_korpus.temperature", data_korpus.temperature); 
   
       	save_ptree.put(root+"data_korpus.price", data_korpus.price); 
       	save_ptree.put(root+"data_korpus.draw_turrels", data_korpus.draw_turrels);        	

       	save_ptree.put(root+"data_korpus.slot_grapple_num", data_korpus.slot_grapple_num);  
       	save_ptree.put(root+"data_korpus.slot_drive_num", data_korpus.slot_drive_num);
       	save_ptree.put(root+"data_korpus.slot_protector_num", data_korpus.slot_protector_num);       	
       	save_ptree.put(root+"data_korpus.slot_radar_num", data_korpus.slot_radar_num);
       	save_ptree.put(root+"data_korpus.slot_scaner_num", data_korpus.slot_scaner_num);
       	save_ptree.put(root+"data_korpus.slot_freezer_num", data_korpus.slot_freezer_num);
       	save_ptree.put(root+"data_korpus.slot_weapon_num", data_korpus.slot_weapon_num);       	
       	

       	if (drive_complex.GetTarget() != nullptr) 
       	{
       		save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", drive_complex.GetTarget()->GetId());
       		save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", drive_complex.GetActionId());
       	}
	else 
	{
       		save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE_ID);
       		save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE_ID);
	}
	       	
       	if (land != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.land_id", land->GetId()); }
	else 	          { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE_ID); }
	
       	if (parent_vehicleslot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", parent_vehicleslot->GetId()); }
       	else  			       	{ save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE_ID); }
      
       	if (GetPlaceTypeId() == PLACE::TYPE::HYPER_SPACE_ID) 
       	{ 
       		save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", drive_complex.GetTarget()->GetId()); 
       	}
       	else 
       	{ 
       		save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE_ID); 
       	}  
}

void Vehicle::LoadDataUniqueVehicle(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Vehicle("+int2str(GetId())+")::LoadDataUniqueVehicle", SAVELOAD_LOG_DIP);
	#endif
	
   	data_korpus.space       = load_ptree.get<int>("data_korpus.space");     
   	data_korpus.armor       = load_ptree.get<int>("data_korpus.armor");   
   	data_korpus.protection  = load_ptree.get<int>("data_korpus.protection"); 
   	data_korpus.temperature = load_ptree.get<int>("data_korpus.temperature"); 

   	data_korpus.price        = load_ptree.get<int>("data_korpus.price"); 
   	data_korpus.draw_turrels = load_ptree.get<bool>("data_korpus.draw_turrels"); 

   	data_korpus.slot_grapple_num   = load_ptree.get<int>("data_korpus.slot_grapple_num"); 
   	data_korpus.slot_drive_num     = load_ptree.get<int>("data_korpus.slot_drive_num"); 
   	data_korpus.slot_protector_num = load_ptree.get<int>("data_korpus.slot_protector_num"); 
   	data_korpus.slot_radar_num     = load_ptree.get<int>("data_korpus.slot_radar_num"); 
   	data_korpus.slot_scaner_num    = load_ptree.get<int>("data_korpus.slot_scaner_num"); 
   	data_korpus.slot_freezer_num   = load_ptree.get<int>("data_korpus.slot_freezer_num"); 
   	data_korpus.slot_weapon_num    = load_ptree.get<int>("data_korpus.slot_weapon_num"); 

   	data_unresolved_Vehicle.drive_complex_target_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_target_id"); 
   	data_unresolved_Vehicle.drive_complex_action_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_action_id");    	
   	//data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path"); 
   	data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id"); 
   	data_unresolved_Vehicle.land_id = load_ptree.get<int>("data_unresolved_Vehicle.land_id");
   	data_unresolved_Vehicle.starsystem_hyper_id = load_ptree.get<int>("data_unresolved_Vehicle.starsystem_hyper_id"); 
   	
}

void Vehicle::ResolveDataUniqueVehicle()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Vehicle("+int2str(GetId())+")::ResolveDataUniqueVehicle", SAVELOAD_LOG_DIP);
	#endif
	
       	BaseVehicleBuilder::Instance().CreateKorpusGeometry(this);
        CreateDriveComplexTextureDependedStuff();
       	CreateProtectionComplexTextureDependedStuff();

       	if (data_unresolved_Vehicle.drive_complex_target_id != NONE_ID) 
        { 
        	drive_complex.SetTarget((BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id); 
        }        
                 
       	if (data_unresolved_Vehicle.land_id != NONE_ID) 
        { 
        	SetLand( (BaseLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id) ); 
        }              

        switch(GetPlaceTypeId())
        {
        	case PLACE::TYPE::SPACE_ID: 
        	{
			GetStarSystem()->AddVehicle(this, data_unresolved_Orientation.center, data_unresolved_Orientation.angle, GetParent()); 
			break;
		}
		
		case PLACE::TYPE::KOSMOPORT_ID:
		{	
			((VehicleSlot*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this); 
			break;
		}
		
		case PLACE::TYPE::HYPER_SPACE_ID:
		{
			//std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
			((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.starsystem_hyper_id))->GetHyperSpace().AddVehicle(this);
			//std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
			
			break;
		}
		
		case PLACE::TYPE::NATURELAND_ID:
		{
			((NatureLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id))->AddVehicle(this); 
			break;
		}
	}
	
	weapon_complex.PrepareWeapons();
}
                
void Vehicle::TEST_DamageAndLockRandItems()
{
	int rand_index1 = getRandInt(0, slot_funct_vec.size()-1);
	while (slot_funct_vec[rand_index1]->GetItem() == nullptr)
	{
		rand_index1 = getRandInt(0, slot_funct_vec.size()-1);	
	}
	slot_funct_vec[rand_index1]->GetItem()->LockEvent(3);

	int rand_index2 = getRandInt(0, slot_funct_vec.size()-1);
	while (slot_funct_vec[rand_index2]->GetItem() == nullptr)
	{
		rand_index2 = getRandInt(0, slot_funct_vec.size()-1);	
	}
	
	while (slot_funct_vec[rand_index2]->GetItem()->GetCondition() > 0)
	{
		slot_funct_vec[rand_index2]->GetItem()->DeteriorationEvent();
	}
}
