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
#include "../common/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../docking/Kosmoport.hpp"
#include "../render/Render.hpp"
#include "../effects/particlesystem/ExplosionEffect.hpp"

#include "../resources/TextureManager.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../builder/BaseVehicleBuilder.hpp"

#include "../common/Logger.hpp"

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
#include "Container.hpp"
#include "../parts/WeaponComplex.hpp"

#include "../text/VerticalFlowText.hpp" 
#include "../slots/VehicleSlot.hpp" 

#include "../docking/Angar.hpp"

Vehicle::Vehicle()
{
	god_mode = false;
	
	special_action_id = SPECIAL_ACTION::NONE_ID;
	
	owner_npc = NULL;
       	starsystem = NULL; 
      	
    	weapon_complex.SetOwnerVehicle(this);
    	drive_complex.SetOwnerVehicle(this);
    	protection_complex.SetOwnerVehicle(this);
    	
    	radar_slot     = NULL;
        scaner_slot    = NULL;
        energizer_slot = NULL;
        grapple_slot   = NULL;
        droid_slot     = NULL;
        freezer_slot   = NULL;
        
        land  = NULL;
}

/*virtual*/
Vehicle::~Vehicle()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Vehicle(), id="+int2str(GetId()));
	#endif

	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		delete slot_total_vec[i];
	}
} 

void Vehicle::CreateDriveComplexTextureDependedStuff()
{
    	GetPoints().initMidLeftPoint();
    	GetPoints().addMidLeftPoint();

    	GetPoints().initMidFarLeftPoint();
    	GetPoints().addMidFarLeftPoint();
    	
	DriveEffect* drive_effect = GetNewDriveEffect(GetTextureOb()->size_id, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
 	GetDriveComplex().SetDriveEffect(drive_effect);
}    

void Vehicle::CreateProtectionComplexTextureDependedStuff()
{
     protection_complex.GetShieldEffect()->SetParent(this);
     protection_complex.GetShieldEffect()->GetPoints().initMainQuadPoints(1.2*textureOb->GetFrameWidth(), 1.2*textureOb->GetFrameHeight());	
}

void Vehicle::SetKorpusData(const VehicleKorpusData& data_korpus) 
{ 
        this->data_korpus = data_korpus; 
        propetries.protection = data_korpus.protection;
}
                
GoodsPack* Vehicle::GetGoodsPack() const
{
	for(unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetEquiped() == true)
		{
			if (slot_cargo_vec[i]->GetItem()->GetTypeId() == ENTITY::GOODS_ID)
			{
				return slot_cargo_vec[i]->GetGoodsPack();
			}
		}
	}	
	
	return NULL;
}
        	
void Vehicle::AddItemSlot(ItemSlot* slot) 
{ 
        slot->SetOwner(this); 
                
	switch(slot->GetSubTypeId())
	{
                case ENTITY::WEAPON_SLOT_ID:    
                {
                	int w = textureOb->GetFrameWidth();
                	int h = textureOb->GetFrameHeight();
                	float border_start = 0.2;
                	float border_end   = 0.8;
                	int pos_x = getRandInt(border_start*w, border_end*w) - w/2;
                	int pos_y = getRandInt(border_start*h, border_end*h) - h/2;
			slot->GetTurrel()->GetPoints().SetParentCenter(vec2f(pos_x, pos_y));
                 	points.Add(slot->GetTurrel()->GetPoints().GetpCenter(), slot->GetTurrel()->GetPoints().GetpParentCenter()); 
                	weapon_complex.AddSlot(slot); 
                	
                	break; 
                }
                case ENTITY::DRIVE_SLOT_ID:     { drive_complex.SetDriveSlot(slot); break; }
                case ENTITY::BAK_SLOT_ID:       { drive_complex.SetBakSlot(slot); break; }
                case ENTITY::PROTECTOR_SLOT_ID: { protection_complex.SetProtectorSlot(slot); break; }
		case ENTITY::RADAR_SLOT_ID:     { radar_slot  = slot; break; }
		case ENTITY::SCANER_SLOT_ID:    { scaner_slot = slot; break; }
		
		case ENTITY::ENERGIZER_SLOT_ID: { energizer_slot = slot; break; }
		case ENTITY::GRAPPLE_SLOT_ID:   { grapple_slot   = slot; break; }
		case ENTITY::DROID_SLOT_ID:     { droid_slot     = slot; break; }
		case ENTITY::FREEZER_SLOT_ID:   { freezer_slot   = slot; break; }
	}
        
	slot_total_vec.push_back(slot); 

	if ( (slot->GetSubTypeId() != ENTITY::ARTEFACT_SLOT_ID) and (slot->GetSubTypeId() != ENTITY::CARGO_SLOT_ID) )
	{
		slot_funct_vec.push_back(slot);
	}
	
	if (slot->GetSubTypeId() == ENTITY::ARTEFACT_SLOT_ID)
	{
		slot_artef_vec.push_back(slot);
	}
	
	if (slot->GetSubTypeId() == ENTITY::CARGO_SLOT_ID)
	{
		slot_cargo_vec.push_back(slot); 
	}
		
}

ItemSlot* Vehicle::GetEmptyCargoSlot()
{
      	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
      	{
          	if (!slot_cargo_vec[i]->GetEquiped())
          	{
             		return slot_cargo_vec[i];
             	}
        }
        
      	return NULL;
}

bool Vehicle::UnpackContainerItemToCargoSlot(Container* container)
{	
 	if (AddItemToCargoSlot(container->GetItemSlot()->GetItem()) == true)
       	{      
       		container->GetItemSlot()->RemoveItem();    
       		container->SilentKill();
       								
       		return true;
      	}
      	
      	return false;
} 

bool Vehicle::AddItemToCargoSlot(BaseItem* item)
{
	if (item->GetTypeId() == ENTITY::GOODS_ID)
	{
		if (MergeIdenticalGoods(item) == true)
		{       		
			return true;
		}
	}
	
	return AddItemToEmptyCargoSlot(item);          
} 


	
	

bool Vehicle::MergeIdenticalGoods(BaseItem* item)
{
	ItemSlot* cargo_slot = GetCargoSlotWithGoods(item->GetSubTypeId());
	if (cargo_slot != NULL)
	{
		cargo_slot->GetGoodsPack()->Increase(item->GetMass());
		// delete item; dangerrr
		return true;
	}
	
	return false;                
} 

bool Vehicle::AddItemToEmptyCargoSlot(BaseItem* item)
{
	ItemSlot* empty_cargo = GetEmptyCargoSlot();
	if (empty_cargo != NULL)
	{
		empty_cargo->InsertItem(item);
		return true;
	}
	
	return false;                
} 

ItemSlot* Vehicle::GetCargoSlotWithGoods(int requested_goods_subtype_id)
{
      	for (unsigned int i=0; i<slot_cargo_vec.size(); i++)
      	{
          	if (slot_cargo_vec[i]->GetEquiped() == true)
          	{
          		if (slot_cargo_vec[i]->GetItem()->GetTypeId() == ENTITY::GOODS_ID)
          		{
          			if (slot_cargo_vec[i]->GetItem()->GetSubTypeId() == requested_goods_subtype_id)
          			{
          				return slot_cargo_vec[i];
          			}
          		}
          	}             		
        }
        
      	return NULL;
}

void Vehicle::BindOwnerNpc(Npc* owner_npc) 	           
{ 
	this->owner_npc = owner_npc; 
	owner_npc->SetVehicle(this); 
} 

bool Vehicle::IsObjectWithinRadarRange(BaseGameEntity* object) const
{
        float dist = distBetweenPoints(points.GetCenter(), object->GetPoints().GetCenter());
        if (dist < propetries.radar)
        {
               	return true;
        }
        
        return false;
}	
	
void Vehicle::RecalculateCollisionRadius()
{
	collision_radius = (textureOb->GetFrameWidth() + textureOb->GetFrameHeight())/3;
}

void Vehicle::UpdateSpecialAction()
{
	if (special_action_id != SPECIAL_ACTION::NONE_ID)
	{
		switch(special_action_id)
		{
			case SPECIAL_ACTION::INITIATE_DOCKING_ID:
			{
				if (UpdateFadeInEffect() == true)
				{
					DockingEvent();
					special_action_id = SPECIAL_ACTION::NONE_ID;
				}
				
				break;			
			}
						
			case SPECIAL_ACTION::INITIATE_LAUNCHING_ID:
			{
				if (UpdateFadeOutEffect() == true)
				{
					special_action_id = SPECIAL_ACTION::NONE_ID;
				}
				
				break;
			}

			case SPECIAL_ACTION::INITIATE_JUMPIN_ID:
			{
				if (UpdateFadeInEffect() == true)
				{
			                HyperJumpEvent();
			                special_action_id = SPECIAL_ACTION::INITIATE_JUMPOUT_ID;
			        }
			
				break;
			}
			
			case SPECIAL_ACTION::INITIATE_JUMPOUT_ID:
			{
				if (UpdateFadeOutEffect() == true)
				{
			                special_action_id = SPECIAL_ACTION::NONE_ID;
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
void Vehicle::HyperJumpEvent()
{
        starsystem->RemoveVehicle(this);  
                                                        
        ((StarSystem*)drive_complex.GetTarget())->AddToHyperJumpQueue(this);
        drive_complex.ResetTarget();  
        
        #if LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(GetId())+" jumpEvent()", 2); 
	#endif      
}
                
                
void Vehicle::DockingEvent()
{
     	starsystem->RemoveVehicle(this);
            
        switch(drive_complex.GetTarget()->GetTypeId())         	     	     	
     	{
     		case ENTITY::PLANET_ID:
     		{
                	Planet* planet = ((Planet*)drive_complex.GetTarget());                
     			planet->GetLand()->AddVehicle(this);
			break;
		}
	
		case ENTITY::VEHICLE_ID:
		{	 
			switch(drive_complex.GetTarget()->GetSubTypeId())
			{
				case ENTITY::SPACESTATION_ID:
				{
                			SpaceStation* spacestation = ((SpaceStation*)drive_complex.GetTarget());
                        		spacestation->GetLand()->AddVehicle(this);
					break;
				}
				
				case ENTITY::SHIP_ID:
				{
					//..
					break;
				}
			}
			
			break;
		}                          		
	}
        
        GetDriveComplex().ResetTarget();
        
        #if LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(GetId())+" DockingEvent()", 2); 
	#endif
}

void Vehicle::LaunchingEvent()
{
	switch(parent_vehicleslot->GetOwner()->GetTypeId())
	{
		case ENTITY::ANGAR_ID:
		{
			Base* place = ((Angar*)parent_vehicleslot->GetOwner())->GetOwnerKosmoport()->GetOwner();
		     	starsystem->AddVehicle(this, ((Planet*)place)->GetPoints().GetCenter(), 0, NULL);
			parent_vehicleslot->Release(); //((Planet*)place)->GetLand()->RemoveVehicle(this); 
			
			break;
		}
			
		case ENTITY::VEHICLE_ID:
		{
			//..
			break;
		}
	}
	
	color.a = 0.1;
	
	#if LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(GetId())+" launchingEvent()", 2); 
	#endif
}
//// 


/* virtual */
void Vehicle::Hit(int damage, bool show_effect)
{
	if (god_mode == false)
	{
	
	damage = damage * ( 1.0 - (owner_npc->GetSkill().GetDefence()*SKILL::DEFENCE_NORMALIZED_RATE + propetries.protection*0.01f) );
	
	data_life.armor -= damage;
	
	//if (getRandInt(1, 30) == 1)
	//{
		//LockRandomItem(getRandInt(1,3));
	//}

    	if (data_life.armor < 0)
    	{
       		data_life.is_alive = false;
       	}

	if (show_effect == true)
	{
    		if (protection_complex.GetProtectorSlot()->GetEquiped() == true)
    		{
       			protection_complex.GetShieldEffect()->SetAlpha(1.0);
       		}       	
       		// improove
       		Color4i color;  	       		
       		VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, points.GetCenter(), color, collision_radius);
       		starsystem->Add(text); 
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
        	createExplosion(starsystem, points.GetCenter(), textureOb->size_id);        		
        }
}

void Vehicle::UpdateAllFunctionalItemsInStatic()
{
	for (unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetEquiped() == true)
		{
			slot_funct_vec[i]->GetItem()->UpdateInStatic();
		}
	}

	for (unsigned int i=0; i<slot_artef_vec.size(); i++)
	{
		if (slot_artef_vec[i]->GetEquiped() == true)
		{
			slot_artef_vec[i]->GetItem()->UpdateInStatic();
		}
	}
}

void Vehicle::ChangeMass(int d_mass)
{
	mass += d_mass;
    	propetries.free_space = data_korpus.space - mass;
	UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::UpdatePropertiesFire()
{
     	weapon_complex.UpdateFireAbility();
     	weapon_complex.PrepareWeapons();
}

void Vehicle::UpdatePropertiesSpeed()
{
     	// speed calculation ////
     	propetries.speed = 0;

     	if (drive_complex.GetDriveSlot()->GetEquiped() == true) 
     	{
        	if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)  
        	{
           		float actual_speed = (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetSpeed() - (float)mass/70); //70 = MINIM_SHIP_SPACE, probably shuld be used unique value for each ship size
           		if (actual_speed > 0)
           		{ 
           			if (propetries.artefact_gravity > 0)
           			{
              				propetries.speed = (1.0 + propetries.artefact_gravity/100.0)*actual_speed;         
           			}
           			else
           			{
           				propetries.speed = actual_speed; 
           			}
                                
                                if (drive_complex.GetDriveSlot()->GetSelected() == true)
                                {
                                        propetries.speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
                                        drive_complex.GetDriveSlot()->GetItem()->UseOverloadDeterioration();
                                }
                                else
                                {
                                        drive_complex.GetDriveSlot()->GetItem()->UseNormalDeterioration();
                                }

           			
           			drive_complex.CalcPath();
           		}
        	}
        }
}


void Vehicle::UpdatePropertiesRadar()
{
        propetries.radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
        propetries.equipment_radar = false;
	
   	if (radar_slot->GetEquiped() == true) 
   	{
      		if (radar_slot->GetRadarEquipment()->GetFunctioning() == true)  
      		{
          		propetries.radar = radar_slot->GetRadarEquipment()->GetRadius();
          		propetries.equipment_radar = true;
      		}
      	}
}



void Vehicle::UpdatePropertiesJump()
{    
	propetries.hyper = 0;

     	if (drive_complex.GetDriveSlot()->GetEquiped() == true)
     	{
        	if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)
           	{
           		if (drive_complex.GetBakSlot()->GetEquiped() == true)
              		{
              			if (drive_complex.GetBakSlot()->GetBakEquipment()->GetFunctioning() == true)
              			{
                 			if (drive_complex.GetDriveSlot()->GetDriveEquipment()->GetHyper() > drive_complex.GetBakSlot()->GetBakEquipment()->GetFuel())
                    				propetries.hyper = drive_complex.GetDriveSlot()->GetDriveEquipment()->GetHyper();
                 			else
                    				propetries.hyper = drive_complex.GetBakSlot()->GetBakEquipment()->GetFuel();
              			}
              		}    
		}
	}
}


//void Vehicle::UpdateEnergyAbility()
//{
     	//propetries.energy = 0;
     	//ableTo.ENERGIZE = false;

     	//if (energizer_slot->GetEquiped() == true)
     	//{
        	//if (energizer_slot->GetEnergizerEquipment()->GetFunctioning() == true)
        	//{
           		//propetries.energy = energizer_slot->GetEnergizerEquipment()->GetEnergy();
           		//ableTo.ENERGIZE = true;
        	//}
        //}
//}

void Vehicle::UpdatePropertiesProtection()
{
        propetries.protection = data_korpus.protection;
        propetries.equipment_protector = false;

     	if (protection_complex.GetProtectorSlot()->GetEquiped() == true)
     	{
        	if (protection_complex.GetProtectorSlot()->GetProtectorEquipment()->GetFunctioning() == true)
        	{
           		propetries.protection += protection_complex.GetProtectorSlot()->GetProtectorEquipment()->GetProtection();
           		propetries.equipment_protector = true;
        	}       
     	}   
     	
     	if (propetries.artefact_protection > 0)
     	{
     		propetries.protection += propetries.artefact_protection;
     	}
}

void Vehicle::UpdatePropertiesRepair()
{
     	propetries.repair = 0;

     	if (droid_slot->GetEquiped() == true)
     	{
        	if (droid_slot->GetDroidEquipment()->GetFunctioning() == true)
        	{
            		propetries.repair = droid_slot->GetDroidEquipment()->GetRepair();
        	}
        }
}


void Vehicle::IncreaseArmor(int repair)
{
	data_life.armor += repair;
	
	if (data_life.armor > data_korpus.armor)
	{
		data_life.armor = data_korpus.armor;
	}
}

//void Vehicle::UpdateFreezeAbility()
//{
     	//propetries.freeze = 0;
     	//ableTo.FREEZE = false;

     	//if (freezer_slot->GetEquiped() == true)
     	//{
        	//if (freezer_slot->GetFreezerEquipment()->GetFunctioning() == true)
        	//{
           		//propetries.freeze = freezer_slot->GetFreezerEquipment()->GetFreeze();
           		//ableTo.FREEZE = true;
        	//}
        //}
//}

void Vehicle::UpdatePropertiesScan()
{
     	propetries.scan = 0;

     	if (scaner_slot->GetEquiped() == true)
     	{
        	if (scaner_slot->GetScanerEquipment()->GetFunctioning() == true)
        	{
           		propetries.scan = scaner_slot->GetScanerEquipment()->GetScan();
        	}
        }
}

void Vehicle::UpdatePropertiesGrab()
{
     	if (data_korpus.slot_grapple_num != 0)
     	{
        	if (grapple_slot->GetEquiped() == true)
           	{
           		if (grapple_slot->GetGrappleEquipment()->GetFunctioning() == true)
              		{
              		
              		}
              	}
	}
}
        
void Vehicle::UpdateArtefactInfluence()
{
	propetries.artefact_gravity = 0;
	propetries.artefact_protection = 0;
	
	for (unsigned int i=0; i<slot_artef_vec.size(); i++)
	{
		if (slot_artef_vec[i]->GetEquiped() == true)
		{
		        if (slot_artef_vec[i]->GetItem()->GetFunctioning() == true)
              		{
				switch(slot_artef_vec[i]->GetItem()->GetSubTypeId())
				{
					case ENTITY::GRAVITY_ARTEFACT_ID:
					{
						propetries.artefact_gravity += ((GravityArtefact*)slot_artef_vec[i]->GetItem())->GetGravity();
						break;
					}

					case ENTITY::PROTECTOR_ARTEFACT_ID:
					{
						propetries.artefact_protection += ((ProtectorArtefact*)slot_artef_vec[i]->GetItem())->GetProtection();
						break;
					}
				}              		
              		}
		}
	}
	
	if (propetries.artefact_gravity > 0)
	{
		UpdatePropertiesSpeed();
	}
	
	if (propetries.artefact_protection > 0)
	{
		UpdatePropertiesProtection();
	}
}
               
void Vehicle::RenderInfoInSpace(const vec2f& scroll_coords)
{  
	UpdateInfo(); // virtual
     	drawInfoIn2Column(info.title_list, info.value_list, points.GetCenter().x - scroll_coords.x, points.GetCenter().y - scroll_coords.y);
     	
     	if (owner_npc != NULL)
     	{
     		owner_npc->RenderInfo(vec2f(points.GetCenter().x + 190 - scroll_coords.x, points.GetCenter().y - scroll_coords.y));
     	}
}

void Vehicle::RenderInfo(const vec2f& center, int offset_x, int offset_y)
{  
	UpdateInfo(); // virtual
     	drawInfoIn2Column(info.title_list, info.value_list, center.x - offset_x, center.y - offset_y);
     	
     	if (owner_npc != NULL)
     	{
     		owner_npc->RenderInfo(vec2f(center.x + 190 - offset_x, center.y - offset_y));
     	}
}

void Vehicle::RenderGrabTrail() const
{
        grapple_slot->GetGrappleEquipment()->RenderGrabTrail();
}
		
void Vehicle::RenderKorpus() const
{
    	drawFlatQuadPerVertexIn2D(textureOb,
    				  points.GetBottomLeft(), 
                                  points.GetBottomRight(), 
                                  points.GetTopRight(), 
                                  points.GetTopLeft(), 
				  points.GetPosZ());
}

void Vehicle::RenderDriveEffect(float parent_d_alpha) const
{
	drive_complex.GetDriveEffect()->Update();
	drive_complex.GetDriveEffect()->Render(parent_d_alpha);
}


void Vehicle::RenderShieldEffect(float parent_d_alpha) const
{
     	protection_complex.GetShieldEffect()->Render(parent_d_alpha);
}

void Vehicle::RenderRadarRange()
{
	if (propetries.radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
	{
		glPushMatrix();
			glTranslatef(points.GetCenter().x, points.GetCenter().y, 0.0f);
			radar_slot->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
             		radar_slot->DrawRange();
		glPopMatrix();
	}
}

void Vehicle::RenderGrappleRange()
{
	if (propetries.grab_radius > 0)
	{
		glPushMatrix();
			glTranslatef(points.GetCenter().x, points.GetCenter().y, 0.0f);
			grapple_slot->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
             		grapple_slot->DrawRange();
		glPopMatrix();
	}
}

bool Vehicle::ExternalRepairEvent()
{
        unsigned int _fix = data_korpus.armor - data_life.armor;
        unsigned int _price = _fix/10;
        
        if (owner_npc->GetCredits() > _price)
        {
                data_life.armor = data_korpus.armor;
                owner_npc->DecreaseCredits(_price);
                return true;  
        }
        
        return false;        
}




bool Vehicle::IsArmorFull() const
{
	if (data_life.armor == data_korpus.armor)
	{
		return true;
	}
	
	return false;
}

int Vehicle::GetArmorMiss() const
{
	return (data_korpus.armor - data_life.armor);
}

void Vehicle::BuyArmorAsMuchAsPossible()
{
	int price_for_one = ((Kosmoport*)land)->GetAngar()->GetPriceArmor();
	int armor_to_buy_max = owner_npc->GetCredits() / price_for_one;
	int armor_to_buy_need = GetArmorMiss();
	
	int armor;
	if (armor_to_buy_max > armor_to_buy_need )
	{		
		armor = armor_to_buy_need;
	}
	else
	{
		armor = armor_to_buy_max;
	}

	owner_npc->DecreaseCredits(armor * price_for_one);
	data_life.armor += armor;
}



bool Vehicle::IsFuelFull() const
{
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

void Vehicle::BuyFuelAsMuchAsPossible()
{
	int price_for_one = ((Kosmoport*)land)->GetAngar()->GetPriceFuel();
	int fuel_to_buy_max =  owner_npc->GetCredits() / price_for_one;
	int fuel_to_buy_need = GetFuelMiss();
	
	int fuel;
	if (fuel_to_buy_max > fuel_to_buy_need )
	{		
		fuel = fuel_to_buy_need;
	}
	else
	{
		fuel = fuel_to_buy_max;
	}

	owner_npc->DecreaseCredits(fuel * price_for_one);
	GetDriveComplex().GetBakSlot()->GetBakEquipment()->IncreaseFuel(fuel);
}

void Vehicle::LockItemInItemSlot(ItemSlot* item_slot, int locked_turns)
{
	item_slot->GetItem()->LockEvent(locked_turns);	
}

void Vehicle::LockRandomItem(int locked_turns)
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i=0; i<slot_funct_vec.size(); i++)
	{
		if (slot_funct_vec[i]->GetEquiped() == true)
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

		
void Vehicle::DropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->GetEquiped() == true)
		{
			_equiped_slot_vec.push_back(slot_total_vec[i]);
		}
	}
	
	if (_equiped_slot_vec.size() > 0)
	{
		unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());
	
		_equiped_slot_vec[_rand]->DropItemToSpace(this);
	}		
}

void Vehicle::UpdateGrappleMicroProgram()
{
        grapple_slot->GetGrappleEquipment()->UpdateGrabScenarioProgram();  
}
	
void Vehicle::RemoveChildFromEntityManager()
{
	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		EntityManager::Instance().RemoveEntity(slot_total_vec[i]);	
		slot_total_vec[i]->RemoveChildFromEntityManager();
	}
}
				
void Vehicle::SaveDataUniqueVehicle(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
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
       	
       	if (land) save_ptree.put(root+"unresolved.land_id", land->GetId());
	else save_ptree.put(root+"unresolved.land_id", NONE_ID);
	
       	if (place_type_id == ENTITY::VEHICLE_SLOT_ID) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", parent_vehicleslot->GetId()); }
       	else { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE_ID); }  	
}

void Vehicle::LoadDataUniqueVehicle(const boost::property_tree::ptree& load_ptree)
{
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

   	//data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path"); 
   	data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id"); 
   	
   	data_unresolved_Vehicle.land_id = load_ptree.get<int>("unresolved.land_id");
}

void Vehicle::ResolveDataUniqueVehicle()
{
       	BaseVehicleBuilder::Instance().CreateKorpusGeometry(this);
        CreateDriveComplexTextureDependedStuff();
        if (data_id.subtype_id != ENTITY::ROCKETBULLET_ID)
        {
        	CreateProtectionComplexTextureDependedStuff();
        }
         
       	if (data_unresolved_Vehicle.land_id != NONE_ID) 
        { 
        	SetLand( (BaseLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id) ); 
        }              
}
                
