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
#include "../effects/particlesystem/explosion.hpp"

#include "../resources/textureManager.hpp"
#include "../resources/resources.hpp"

Vehicle::Vehicle()
{
	owner_npc = NULL;
       	starsystem = NULL; 
      	
    	weapon_complex     = NULL;
    	drive_complex      = NULL;
    	protection_complex = NULL;
    	
    	radar_slot     = NULL;
        scaner_slot    = NULL;
        energizer_slot = NULL;
        grapple_slot   = NULL;
        droid_slot     = NULL;
        freezer_slot   = NULL;
        
        gate_slot = NULL;
        
        textureOb_gui = NULL;
        
        land  = NULL;
}

/*virtual*/
Vehicle::~Vehicle()
{
	EntityManager::Instance().RemoveEntity(this);
	
    	delete weapon_complex; weapon_complex = NULL;
    	delete drive_complex;  drive_complex = NULL;
	delete protection_complex; protection_complex = NULL;
	
	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		delete slot_total_vec[i];
	}
	slot_total_vec.clear();
} 

bool Vehicle::HasSomeGoodsInCargo() const
{
	for(unsigned int i=0; i<slot_cargo_vec.size(); i++)
	{
		if (slot_cargo_vec[i]->GetEquiped() == true)
		{
			if (slot_cargo_vec[i]->GetItem()->GetTypeId() == ENTITY::GOODS_ID)
			{
				return true;
			}
		}
	}	
	
	return false;
}
        	
void Vehicle::AddItemSlot(ItemSlot* slot, const Rect& rect) 
{ 
	assert(slot);
        slot->SetOwner(this); 
        slot->SetRect(rect.GetBottomLeft().x, rect.GetBottomLeft().y, rect.GetWidth(), rect.GetHeight());        
                
	switch(slot->GetSubTypeId())
	{
                case ITEMSLOT::WEAPON_ID:    
                {
                	int w = textureOb->GetFrameWidth();
                	int h = textureOb->GetFrameHeight();
                	float border_start = 0.2;
                	float border_end   = 0.8;
                	int pos_x = getRandInt(border_start*w, border_end*w) - w/2;
                	int pos_y = getRandInt(border_start*h, border_end*h) - h/2;
			slot->GetTurrel()->GetPoints().SetParentCenter(vec2f(pos_x, pos_y));
                 	points.Add(slot->GetTurrel()->GetPoints().GetpCenter(), slot->GetTurrel()->GetPoints().GetpParentCenter()); 
                	weapon_complex->AddSlot(slot); break; 
                }
                case ITEMSLOT::DRIVE_ID:     { drive_complex->SetDriveSlot(slot); break; }
                case ITEMSLOT::BAK_ID:       { drive_complex->SetBakSlot(slot); break; }
                case ITEMSLOT::PROTECTOR_ID: { protection_complex->SetProtectorSlot(slot); break; }
		case ITEMSLOT::RADAR_ID:     { radar_slot  = slot; break; }
		case ITEMSLOT::SCANER_ID:    { scaner_slot = slot; break; }
		
		case ITEMSLOT::ENERGIZER_ID: { energizer_slot = slot; break; }
		case ITEMSLOT::GRAPPLE_ID:   { grapple_slot   = slot; break; }
		case ITEMSLOT::DROID_ID:     { droid_slot     = slot; break; }
		case ITEMSLOT::FREEZER_ID:   { freezer_slot   = slot; break; }
		
		case ITEMSLOT::CARGO_ID:     { slot_cargo_vec.push_back(slot); break; }
		case ITEMSLOT::GATE_ID:      { gate_slot      = slot; break; }
	}
        
	if (slot->GetSubTypeId() != ITEMSLOT::GATE_ID)
	{
		slot_total_vec.push_back(slot); 
	}
}

ItemSlot* Vehicle::GetEmptyCargoSlot()
{
      	for (unsigned int i = 0; i < slot_cargo_vec.size(); i++)
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
        if (dist < propetries.radius)
        {
               	return true;
        }
        
        return false;
}	
	
void Vehicle::RecalculateCollisionRadius()
{
	collision_radius = (textureOb->GetFrameWidth() + textureOb->GetFrameHeight())/3;
}

//bool Vehicle::DockingEffect()
//{
	//if (color.a > 0.01)
	//{
		//color.a -= 0.02;
		//return false;
	//}
	//else
	//{
		//color.a = 0.0;
		//return true;
	//}
//}

//bool Vehicle::LaunchingEffect()
//{
	//if (color.a < 1.0)
	//{
		//std::cout<<"LaunchingEffect works"<<std::endl;
		//color.a += 0.02;
		//return false;
	//}
	//else
	//{
		//std::cout<<"LaunchingEffect finished"<<std::endl;
		//color.a = 1.0;
		//return true;
	//}
//}

/// ******** DOCKING/LAUNCHING ******** 
void Vehicle::HyperJumpEvent()
{
        starsystem->RemoveVehicle(data_id.id);  
                                                        
        ((StarSystem*)drive_complex->GetTarget())->AddToHyperJumpQueue(this);
        drive_complex->ResetTarget();        
}
                
                
void Vehicle::DockingEvent()
{
     	starsystem->RemoveVehicle(data_id.id);
            
        switch(drive_complex->GetTarget()->GetTypeId())         	     	     	
     	{
     		case ENTITY::PLANET_ID:
     		{
                	Planet* planet = ((Planet*)drive_complex->GetTarget());                
     			planet->GetLand()->Add((Ship*)this);
			break;
		}
	
		case ENTITY::VEHICLE_ID:
		{	 
			switch(drive_complex->GetTarget()->GetSubTypeId())
			{
				case ENTITY::SPACESTATION_ID:
				{
                			SpaceStation* spacestation = ((SpaceStation*)drive_complex->GetTarget());
                        		spacestation->GetLand()->Add((Ship*)this);
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
        
        GetDriveComplex()->ResetTarget();
}

void Vehicle::LaunchingEvent()
{
     	printf("vehicle id = %i, launchingEvent()\n", data_id.id);

	switch(parent_vehicleslot->GetOwner()->GetTypeId())
	{
		case ENTITY::ANGAR_ID:
		{
			Base* place = ((Angar*)parent_vehicleslot->GetOwner())->GetOwnerKosmoport()->GetOwner();
		     	starsystem->AddVehicle(this, ((Planet*)place)->GetPoints().GetCenter(), 0, NULL);
			parent_vehicleslot->Release();
			break;
		}
			
		case ENTITY::VEHICLE_ID:
		{
			//..
			break;
		}
	}
}
//// 


void Vehicle::Hit(int damage, bool show_effect)
{
	damage = damage * ( 1.0 - (owner_npc->GetSkill()->GetDefence()/SKILL::DEFENCE_NORMALIZED_RATE + propetries.protection/100.0) );
	
	data_life.armor -= damage;
	
    	if (data_life.armor < 0)
    	{
       		data_life.is_alive = false;
       	}

	if (show_effect == true)
	{
    		if (ableTo.PROTECT == true)
    		{
       			protection_complex->GetShieldEffect()->SetAlpha(1.0);
       		}       	
       		// improove
       		Color4i color;  	       		
       		VerticalFlowText* text = new VerticalFlowText(int2str(damage), points.GetCenter(), color, collision_radius);
       		starsystem->Add(text); 
       	}
}


void Vehicle::PostDeathUniqueEvent(bool show_effect)  /* virtual */
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


void Vehicle::UpdateAllPropertiesAndAbilities()
{
    	// this function set actual ship propretries relying to all equipment placed in slots
    	// used when ship change items in slot
    	// !!! all this stuff can be called separately by item deterioration function if item becomes broken !!!
     	RecalculateMass();
     
    	UpdateDriveAbility(); 
    	UpdateRadarAbility();
    	UpdateJumpAbility();
    	UpdateEnergyAbility();  // make reurtn true, and add below if condition 
    	UpdateProtectionAbility(); // because energy shield depends on energy and consume it much
    	UpdateFireAbility();

    	UpdateRepairAbility();
    	UpdateFreezeAbility();
    	UpdateGrabAbility();
    	UpdateScanAbility();
}

void Vehicle::UpdateFireAbility()
{
     	weapon_complex->UpdateFireAbility();
}

void Vehicle::RecalculateMass()
{
     	// calculate mass and then actual ship speed depending on drive power and actual mass
     	// used each time when ship picked up/bought or drop/sold something. 
     	
     	mass = 0;   
    	for (unsigned int i=0; i<slot_total_vec.size(); i++)
    	{
        	if (slot_total_vec[i]->GetEquiped() == true)
        	{
           		mass += slot_total_vec[i]->GetItem()->GetMass();  
           	}    
    	}
    	
    	propetries.free_space = data_korpus.space - mass;
}


void Vehicle::UpdateDriveAbility()
{
     	//// speed calculation ////
     	propetries.speed = 0;
     	ableTo.DRIVE = false;

     	if (drive_complex->GetDriveSlot()->GetEquiped() == true) 
     	{
        	if (drive_complex->GetDriveSlot()->GetDriveEquipment()->GetCondition() > 0)  
        	{
           		float val = (drive_complex->GetDriveSlot()->GetDriveEquipment()->GetSpeed() - mass/70);
           		if (val > 0)
           		{ 
              			propetries.speed = val;
              			ableTo.DRIVE = true;              
           		}
        	}
        }
     //speed = 200;    // debug
     //printf("speed= %i\n,", speed); 
     //// constants for direction visualization ////
     //   self.turn_step = self.speed * TURN_TIME
     //   self.draw_step = self.turn_step/ int(4*self.speed/DRIVE_SPEED_MIN)
}


void Vehicle::UpdateRadarAbility()
{
   	if (radar_slot->GetEquiped() == true) 
   	{
      		if (radar_slot->GetRadarEquipment()->GetCondition() > 0)  
      		{
          		propetries.radius = radar_slot->GetRadarEquipment()->GetRadius();
          		ableTo.RADAR = true;
      		}
       		else
      		{
          		propetries.radius = VISIBLE_DISTANCE_WITHOUT_RADAR;
          		ableTo.RADAR = false;
      		}
      	}
      	else
      	{
      	        propetries.radius = VISIBLE_DISTANCE_WITHOUT_RADAR;
          	ableTo.RADAR = false;
      	}
}



void Vehicle::UpdateJumpAbility()
{    
	propetries.hyper = 0;
     	ableTo.HJUMP = false;

     	if (drive_complex->GetDriveSlot()->GetEquiped() == true)
        	if (drive_complex->GetDriveSlot()->GetDriveEquipment()->GetCondition() > 0)
           		if (drive_complex->GetBakSlot()->GetEquiped() == true)
              			if (drive_complex->GetBakSlot()->GetBakEquipment()->GetCondition() > 0)
              			{
                 			if (drive_complex->GetDriveSlot()->GetDriveEquipment()->GetHyper() > drive_complex->GetBakSlot()->GetBakEquipment()->GetFuel())
                    				propetries.hyper = drive_complex->GetDriveSlot()->GetDriveEquipment()->GetHyper();
                 			else
                    				propetries.hyper = drive_complex->GetBakSlot()->GetBakEquipment()->GetFuel();

                 			ableTo.HJUMP = true;
              			}    
}


void Vehicle::UpdateEnergyAbility()
{
     	propetries.energy = 0;
     	ableTo.ENERGIZE = false;

     	if (energizer_slot->GetEquiped() == true)
     	{
        	if (energizer_slot->GetEnergizerEquipment()->GetCondition() > 0)
        	{
           		propetries.energy = energizer_slot->GetEnergizerEquipment()->GetEnergy();
           		ableTo.ENERGIZE = true;
        	}
        }
}



void Vehicle::UpdateProtectionAbility()
{
        propetries.protection = data_korpus.protection;
        ableTo.PROTECT = false;

     	if (protection_complex->GetProtectorSlot()->GetEquiped() == true)
     	{
        	if (protection_complex->GetProtectorSlot()->GetProtectorEquipment()->GetCondition() > 0)
        	{
           		propetries.protection += protection_complex->GetProtectorSlot()->GetProtectorEquipment()->GetProtection();
           		ableTo.PROTECT = true;
        	}       
     	}   
}

void Vehicle::UpdateRepairAbility()
{
     	propetries.repair = 0;
     	ableTo.REPAIR = false;

     	if (droid_slot->GetEquiped() == true)
     	{
        	if (droid_slot->GetDroidEquipment()->GetCondition() > 0)
        	{
            		propetries.repair = droid_slot->GetDroidEquipment()->GetRepair();
            		ableTo.REPAIR = true;
        	}
        }
}

void Vehicle::SelfRepairEvent()
{
	if (ableTo.REPAIR == true)
	{
		if (data_life.armor < data_korpus.armor)
		{
			data_life.armor += propetries.repair;
			droid_slot->GetDroidEquipment()->Deterioration();
		}
		
		if (data_life.armor > data_korpus.armor)
		{
			data_life.armor = data_korpus.armor;
		}
	}
}

void Vehicle::UpdateFreezeAbility()
{
     	propetries.freeze = 0;
     	ableTo.FREEZE = false;

     	if (freezer_slot->GetEquiped() == true)
     	{
        	if (freezer_slot->GetFreezerEquipment()->GetCondition() > 0)
        	{
           		propetries.freeze = freezer_slot->GetFreezerEquipment()->GetFreeze();
           		ableTo.FREEZE = true;
        	}
        }
}


void Vehicle::UpdateGrabAbility()
{
     	ableTo.GRAB = false;

     	if (data_korpus.slot_grapple_num != 0)
        	if (grapple_slot->GetEquiped() == true)
           		if (grapple_slot->GetGrappleEquipment()->GetCondition() > 0)
              			ableTo.GRAB = true;
}


void Vehicle::UpdateScanAbility()
{
     	propetries.scan = 0;
     	ableTo.SCAN = false;

     	if (scaner_slot->GetEquiped() == true)
     	{
        	if (scaner_slot->GetScanerEquipment()->GetCondition() > 0)
        	{
           		propetries.scan = scaner_slot->GetScanerEquipment()->GetScan();
           		ableTo.SCAN = true;
        	}
        }
}

               
               
std::string Vehicle::returnProtectionStr()
{
    	if (ableTo.PROTECT == true)
       		return int2str(protection_complex->GetProtectorSlot()->GetProtectorEquipment()->GetProtection()) + '+' + int2str(data_korpus.protection);
    	else
       		return int2str(data_korpus.protection);
}

void Vehicle::RenderInfoInSpace(const vec2f& scroll_coords)
{  
	UpdateInfo(); // virtual
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.GetCenter().x - scroll_coords.x, points.GetCenter().y - scroll_coords.y);
     	
     	if (owner_npc != NULL)
     	{
     		owner_npc->RenderInfo(vec2f(points.GetCenter().x + 190 - scroll_coords.x, points.GetCenter().y - scroll_coords.y));
     	}
}

void Vehicle::RenderInfo(const vec2f& center)
{  
	UpdateInfo(); // virtual
     	drawInfoIn2Column(&info.title_list, &info.value_list, center.x, center.y);
     	
     	if (owner_npc != NULL)
     	{
     		owner_npc->RenderInfo(vec2f(center.x + 190, center.y));
     	}
}

void Vehicle::RenderGrappleTrail() const
{
        for (unsigned int i = 0; i<grapple_slot->GetGrappleEquipment()->target_vec.size(); i++)
        {
                //if (grapple_slot->GetGrappleEquipment()->target_vec[i]->GetValid() == true)
                {              
                    	float xl = grapple_slot->GetGrappleEquipment()->target_vec[i]->GetPoints().GetCenter().x - points.GetCenter().x;
                        float yl = grapple_slot->GetGrappleEquipment()->target_vec[i]->GetPoints().GetCenter().y - points.GetCenter().y;

                        float len = sqrt((xl*xl) + (yl*yl));

                        float angle_inR = atan2(yl, xl);

                        float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;
        
                        drawLine(GuiTextureObCollector::Instance().grapple_trail, 
                                 points.GetCenter(), 
                                 points.GetPosZ(), 
                                 len, 
                                 angle_inD, 
                                 8);
                }
        }
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

void Vehicle::RenderDriveTrail() const
{
	drive_complex->RenderTrail();
}


void Vehicle::RenderShield() const
{
     	protection_complex->GetShieldEffect()->Render();
}

void Vehicle::RenderRadarRange()
{
	if (ableTo.RADAR)
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
	if (ableTo.GRAB)
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
	if (GetArmorMiss() == 0)
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
	return GetDriveComplex()->GetBakSlot()->GetBakEquipment()->GetFuelMiss();
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
	GetDriveComplex()->GetBakSlot()->GetBakEquipment()->IncreaseFuel(fuel);
}

void Vehicle::DropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i = 0; i<slot_total_vec.size(); i++)
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

void Vehicle::GrappleMicroProgramm()
{
        grapple_slot->GetGrappleEquipment()->ValidateTargets();  
                
        for (unsigned int i = 0; i < grapple_slot->GetGrappleEquipment()->target_vec.size(); i++)
        {
               	grapple_slot->GetGrappleEquipment()->target_vec[i]->MovingByExternalForce(points.GetCenter(), grapple_slot->GetGrappleEquipment()->GetStrength());        	
       	
       		float dist = distBetweenPoints(points.GetCenter(), grapple_slot->GetGrappleEquipment()->target_vec[i]->GetPoints().GetCenter() ); 
       		if (dist < GetCollisionRadius()/4.0f)
       		{
       			switch(grapple_slot->GetGrappleEquipment()->target_vec[i]->GetTypeId())
       			{
      				case ENTITY::CONTAINER_ID:
       				{
       					Container* container = (Container*)grapple_slot->GetGrappleEquipment()->target_vec[i];
       					if (UnpackContainerItemToCargoSlot(container) == true)
					{
						container->GetItemSlot()->RemoveItem();    
       						container->SetPlaceTypeId(NONE_ID); // this needs for destroy
       			
						grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(container);
       					}
       					
       					break;
       				}        			
        				
       				//case ENTITY::VEHICLE_ID:
       				//{
       					//ItemSlot* _slot = GetEmptyOtsecSlot();
                                        //Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
       				        //if (_slot != NULL)
       					//{
       						////_slot->InsertItem(_vehicle);
       						//starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
       					//}
					//grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
       					//break;
       				//}
       			}
       		}
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
       	
        save_ptree.put(root+"data_unresolved_Vehicle.textureOb_gui_path", textureOb_gui->path);      
       	
       	if (land) save_ptree.put(root+"unresolved.land_id", land->GetId());
	else save_ptree.put(root+"unresolved.land_id", NONE_ID);
	
       	if (place_type_id == ENTITY::VEHICLESLOT_ID) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", parent_vehicleslot->GetId()); }
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

   	data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path"); 
   	data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id"); 
   	
   	data_unresolved_Vehicle.land_id = load_ptree.get<int>("unresolved.land_id");
}

void Vehicle::ResolveDataUniqueVehicle()
{
       	textureOb_gui = TextureManager::Instance().GetTextureObByPath(data_unresolved_Vehicle.textureOb_gui_path);
       	
       	if (data_unresolved_Vehicle.land_id != NONE_ID) 
        { 
        	SetLand( (BaseLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id) ); 
        }              
}
                
