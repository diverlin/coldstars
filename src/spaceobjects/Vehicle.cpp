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


KorpusData :: KorpusData()
{        
        space       = 0;
        armor       = 0;
        protection  = 0; 
        temperature = 0;   
        
        price = 0;
       
        draw_turrels = false;
        gui_scale = 1.0;
        
        slot_grapple_num   = 0;
        slot_drive_num     = 0;
        slot_protector_num = 0;
        slot_radar_num     = 0;
        slot_scaner_num    = 0;
        slot_freezer_num   = 0;
	slot_weapon_num    = 0;
}


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
}

/*virtual*/
Vehicle::~Vehicle()
{
    	delete weapon_complex;
    	delete drive_complex;
	delete protection_complex;
} 

void Vehicle::AddSlot(ItemSlot* slot, Rect rect) 
{ 
        slot->SetOwnerVehicle(this); 
        slot->SetRect(rect.GetBottomLeft().x, rect.GetBottomLeft().y, rect.GetWidth(), rect.GetHeight());        
        
	switch(slot->GetSubTypeId())
	{
                case SLOT::WEAPON_ID:    
                {
                 	points.Add(slot->GetTurrel()->GetPoints().GetpCenter(), slot->GetTurrel()->GetPoints().GetpParentCenter());  
                	weapon_complex->AddSlot(slot); break; 
                }
                case SLOT::DRIVE_ID:     { drive_complex->SetDriveSlot(slot); break; }
                case SLOT::BAK_ID:       { drive_complex->SetBakSlot(slot); break; }
                case SLOT::PROTECTOR_ID: { protection_complex->SetProtectorSlot(slot); break; }
		case SLOT::RADAR_ID:     { radar_slot  = slot; break; }
		case SLOT::SCANER_ID:    { scaner_slot = slot; break; }
		
		case SLOT::ENERGIZER_ID: { energizer_slot = slot; break; }
		case SLOT::GRAPPLE_ID:   { grapple_slot   = slot; break; }
		case SLOT::DROID_ID:     { droid_slot     = slot; break; }
		case SLOT::FREEZER_ID:   { freezer_slot   = slot; break; }
		
		case SLOT::CARGO_ID:     { slot_otsec_vec.push_back(slot); break; }
		case SLOT::GATE_ID:      { gate_slot      = slot; break; }
	}
        
	if (slot->GetSubTypeId() != SLOT::GATE_ID)
	{
		slot_total_vec.push_back(slot); 
	}
}

bool Vehicle::AddItemToOtsec(BaseItem* item)
{
	for (unsigned int i=0; i<slot_otsec_vec.size(); i++)
	{
		if (!slot_otsec_vec[i]->GetEquipedStatus())
		{
			slot_otsec_vec[i]->InsertItem(item);
			return true;
		}
	}
	
	return false;                
} 

ItemSlot* Vehicle::GetEmptyOtsecSlot()
{
      	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
      	{
          	if (slot_otsec_vec[i]->GetEquipedStatus() == false)
          	{
             		return slot_otsec_vec[i];
             	}
        }
        
      	return NULL;
}

ItemSlot* Vehicle::GetCargoSlotWithGoods(int requested_goods_subtype_id)
{
      	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
      	{
          	if (slot_otsec_vec[i]->GetEquipedStatus() == true)
          	{
          		if (slot_otsec_vec[i]->GetItem()->GetTypeId() == ENTITY::GOODS_ID)
          		{
          			if (slot_otsec_vec[i]->GetItem()->GetSubTypeId() == requested_goods_subtype_id)
          			{
          				return slot_otsec_vec[i];
          			}
          		}
          	}             		
        }
        
      	return NULL;
}


void Vehicle::RecalculateCollisionRadius()
{
	collision_radius = (textureOb->getFrameWidth() + textureOb->getFrameHeight())/3;
}



//// ******** DOCKING/LAUNCHING ******** 
void Vehicle::HyperJumpEvent()
{
        starsystem->RemoveShip(data_id.id);  
        starsystem->RemoveNpc(owner_npc->GetId(), owner_npc->GetSubTypeId());  
                                                        
        ((StarSystem*)drive_complex->getTarget())->AddToHyperJumpQueue(this);
        drive_complex->resetTarget();        
}
                
                
void Vehicle::DockingEvent()
{
     	starsystem->RemoveShip(data_id.id);
     	starsystem->RemoveNpc(owner_npc->GetId(), owner_npc->GetSubTypeId());
        
             	     	     	
     	if (drive_complex->getTarget()->GetTypeId() == ENTITY::PLANET_ID)
     	{
                Planet* planet = ((Planet*)drive_complex->getTarget());
                
     		planet->GetLand()->Add((Ship*)this);
		planet->GetLand()->Add(owner_npc);
		
		owner_npc->SetLand(planet->GetLand());
	}
	
	if (drive_complex->getTarget()->GetTypeId() == ENTITY::SPACESTATION_ID)
	{
                SpaceStation* spacestation = ((SpaceStation*)drive_complex->getTarget());
                                
	     	spacestation->GetLand()->Add((Ship*)this);
		spacestation->GetLand()->Add(owner_npc);
		
		owner_npc->SetLand(spacestation->GetLand());
	}
}

void Vehicle::LaunchingEvent()
{
     	printf("vehicle id = %i, launchingEvent()\n", data_id.id);

     	if (drive_complex->getTarget()->GetTypeId() == ENTITY::PLANET_ID)
     	{
     		starsystem->Add(this, drive_complex->getTarget()->GetPoints().GetCenter(), 0, NULL);

     		((Planet*)drive_complex->getTarget())->GetLand()->Remove(this);
     		((Planet*)drive_complex->getTarget())->GetLand()->Remove(owner_npc);
	}
	
     	if (drive_complex->getTarget()->GetTypeId() == ENTITY::SPACESTATION_ID)
     	{
     		starsystem->Add(this, drive_complex->getTarget()->GetPoints().GetCenter(), 0, NULL);

     		((SpaceStation*)drive_complex->getTarget())->GetLand()->Remove(this);
     		((SpaceStation*)drive_complex->getTarget())->GetLand()->Remove(owner_npc);
	}	

     	drive_complex->resetTarget();
}
//// 


void Vehicle::Hit(int _damage, bool show_effect)
{
    	data_life.armor -= _damage;

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
       		VerticalFlowText* text = new VerticalFlowText(int2str(_damage), points.GetCenter(), color, collision_radius);
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
     	//ableTo.FIRE = 
     	weapon_complex->UpdateFireAbility();
}

void Vehicle::RecalculateMass()
{
     	mass = 0;   

    	for (unsigned int i = 0; i < slot_total_vec.size(); i++)
    	{
        	if (slot_total_vec[i]->GetEquipedStatus() == true)
        	{
           		mass += slot_total_vec[i]->GetItem()->GetMass();  
           	}    
    	}
}


void Vehicle::UpdateDriveAbility()
{
     	//// calculate mass and then actual ship speed depending on drive power and actual mass
     	//// used each time when ship picked up/bought or drop/sold something.
     	RecalculateMass();   	  

     	//// speed calculation ////
     	propetries.speed = 0;
     	ableTo.DRIVE = false;

     	if (drive_complex->GetDriveSlot()->GetEquipedStatus() == true) 
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
   	if (radar_slot->GetEquipedStatus() == true) 
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

     	if (drive_complex->GetDriveSlot()->GetEquipedStatus() == true)
        	if (drive_complex->GetDriveSlot()->GetDriveEquipment()->GetCondition() > 0)
           		if (drive_complex->GetBakSlot()->GetEquipedStatus() == true)
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

     	if (energizer_slot->GetEquipedStatus() == true)
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


     	if (protection_complex->GetProtectorSlot()->GetEquipedStatus() == true)
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

     	if (droid_slot->GetEquipedStatus() == true)
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

     	if (freezer_slot->GetEquipedStatus() == true)
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
        	if (grapple_slot->GetEquipedStatus() == true)
           		if (grapple_slot->GetGrappleEquipment()->GetCondition() > 0)
              			ableTo.GRAB = true;
}


void Vehicle::UpdateScanAbility()
{
     	propetries.scan = 0;
     	ableTo.SCAN = false;

     	if (scaner_slot->GetEquipedStatus() == true)
     	{
        	if (scaner_slot->GetScanerEquipment()->GetCondition() > 0)
        	{
           		propetries.scan = scaner_slot->GetScanerEquipment()->GetScan();
           		ableTo.SCAN = true;
        	}
        }
}

void Vehicle::SetMaxArmor()
{
     	data_life.armor = data_korpus.armor;
}

void Vehicle::SetMaxFuel()
{
     	if (drive_complex->GetBakSlot()->GetEquipedStatus() == true)
     	{
        	drive_complex->GetBakSlot()->GetBakEquipment()->SetFuel(drive_complex->GetBakSlot()->GetBakEquipment()->GetFuelMax());
        }
}

std::string Vehicle::returnProtectionStr()
{
    	if (ableTo.PROTECT == true)
       		return int2str(protection_complex->GetProtectorSlot()->GetProtectorEquipment()->GetProtection()) + '+' + int2str(data_korpus.protection);
    	else
       		return int2str(data_korpus.protection);
}

void Vehicle::RenderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        this->UpdateInfo(); // virtual, overriding
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x, _pos_y, _offset_x, _offset_y);
     	
     	if (owner_npc != NULL)
     	{
     		owner_npc->RenderInfo(_pos_x, _pos_y, _offset_x, _offset_y);
     	}
}

void Vehicle::RenderInfoInSpace(vec2f scroll_coords)
{  
	RenderInfo(points.GetCenter().x, points.GetCenter().y, scroll_coords.x, scroll_coords.y);
}

void Vehicle::RenderGrappleTrail() const
{
        for (unsigned int i = 0; i<grapple_slot->GetGrappleEquipment()->target_vec.size(); i++)
        {
                //if (grapple_slot->GetGrappleEquipment()->target_vec[i]->getValid() == true)
                {              
                    	float xl = grapple_slot->GetGrappleEquipment()->target_vec[i]->GetPoints().GetCenter().x - points.GetCenter().x;
                        float yl = grapple_slot->GetGrappleEquipment()->target_vec[i]->GetPoints().GetCenter().y - points.GetCenter().y;

                        float len = sqrt((xl*xl) + (yl*yl));

                        float angle_inR = atan2(yl, xl);

                        float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;
        
                        drawLine(g_UNIQUE_TEXTURE_COLLECTOR.texOb_grapple_trail, 
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
	drive_complex->renderTrail();
}


void Vehicle::RenderShield() const
{
     	protection_complex->GetShieldEffect()->Render();
}

void Vehicle::RenderRadarRange()
{
	glPushMatrix();
		glTranslatef(points.GetCenter().x, points.GetCenter().y, 0.0f);
		radar_slot->UpdateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_yellow);
             	radar_slot->DrawRange();
	glPopMatrix();
}

void Vehicle::RenderGrappleRange()
{
	glPushMatrix();
		glTranslatef(points.GetCenter().x, points.GetCenter().y, 0.0f);
		grapple_slot->UpdateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue);
             	grapple_slot->DrawRange();
	glPopMatrix();
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


void Vehicle::DropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i = 0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->GetEquipedStatus() == true)
		{
			_equiped_slot_vec.push_back(slot_total_vec[i]);
		}
	}
	
	if (_equiped_slot_vec.size() > 0)
	{
		unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());
	
		_equiped_slot_vec[_rand]->DropItemToSpace();
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
       					ItemSlot* _slot = GetEmptyOtsecSlot();
                                        Container* _container = (Container*)grapple_slot->GetGrappleEquipment()->target_vec[i];
       				        if (_slot != NULL)
       					{
                                                _slot->InsertItem(_container->GetItemSlot()->GetItem());
                                                _container->GetItemSlot()->RemoveItem();    
       						_container->SetPlaceTypeId(NONE_ID);
       					}
					grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_container);
       					break;
       				}        			
        				
       				case ENTITY::SHIP_ID:
       				{
       					ItemSlot* _slot = GetEmptyOtsecSlot();
                                        Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
       				        if (_slot != NULL)
       					{
       						//_slot->InsertItem(_vehicle);
       						starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
       					}
					grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
       					break;
       				}
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
       	
       	save_ptree.put(root+"data_unresolved_Vehicle.npc_id", owner_npc->GetId());       	
       	save_ptree.put(root+"data_unresolved_Vehicle.texOb_korpus_path", texOb_korpus->path);       	
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

   	data_unresolved_Vehicle.npc_id            = load_ptree.get<int>("data_unresolved_Vehicle.npc_id"); 
   	data_unresolved_Vehicle.texOb_korpus_path = load_ptree.get<std::string>("data_unresolved_Vehicle.texOb_korpus_path"); 
}

void Vehicle::ResolveDataUniqueVehicle()
{
        texOb_korpus = g_TEXTURE_MANAGER.GetTextureObByPath(data_unresolved_Vehicle.texOb_korpus_path);

        //create_internals (slot, complex)
}
                
