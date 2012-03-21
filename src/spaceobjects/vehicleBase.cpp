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



void VehicleBase :: setNpc(Npc* _npc)   { npc_owner = _npc; }
void VehicleBase :: setKorpusData(KorpusData data_korpus) { this->data_korpus = data_korpus; }
void VehicleBase :: add(ItemSlot* slot) { slot_total_vec.push_back(slot); }
                
WeaponComplex* VehicleBase :: getWeaponComplex() const { return weapon_complex; }
DriveComplex* VehicleBase :: getDriveComplex()   const { return drive_complex; }

ItemSlot* VehicleBase :: getRadarSlot()     const { return radar_slot; }
ItemSlot* VehicleBase :: getScanerSlot()    const { return scaner_slot; }
ItemSlot* VehicleBase :: getEnergizerSlot() const { return energizer_slot; }
ItemSlot* VehicleBase :: getGrappleSlot()   const { return grapple_slot; }
ItemSlot* VehicleBase :: getProtectorSlot() const { return protector_slot; }
ItemSlot* VehicleBase :: getDroidSlot()     const { return droid_slot; }
ItemSlot* VehicleBase :: getFreezerSlot()   const { return freezer_slot; }
        	               
ItemSlot* VehicleBase :: getGateSlot()   const { return gate_slot; }

Npc* VehicleBase :: getNpc() 	        { return npc_owner; }

TextureOb* VehicleBase :: getSlotTexOb() const { return texOb_slot; }
Rect VehicleBase :: getKonturRect()      const { return kontur_rect; }
        	
// needs for grabbing interface
int VehicleBase :: getFunctionalSlotSubTypeId() const { return NONE_SLOT_ID; } 
void VehicleBase :: bindSlot(ItemSlot* slot)          { return; }	   	
void VehicleBase :: updateOwnerPropetries()	       { return; }	   
//
       	        
float VehicleBase :: getVisionRadius() const { return propetries.radius; }

ItemSlot* VehicleBase :: getEmptyOtsecSlot()
{
      	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
      	{
          	if (slot_otsec_vec[i]->getEquipedStatus() == false)
          	{
             		return slot_otsec_vec[i];
             	}
        }
        
      	return NULL;
}


ItemSlot* VehicleBase :: getOtsecSlotWithGoods(int requested_goods_subtype_id)
{
      	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
      	{
          	if (slot_otsec_vec[i]->getEquipedStatus() == true)
          	{
          		if (slot_otsec_vec[i]->getItem()->getTypeId() == GOODS_ID)
          		{
          			if (slot_otsec_vec[i]->getItem()->getSubTypeId() == requested_goods_subtype_id)
          			{
          				return slot_otsec_vec[i];
          			}
          		}
          	}             		
        }
        
      	return NULL;
}


                
                
VehicleBase :: VehicleBase()
{
	npc_owner = NULL;
}

VehicleBase :: ~VehicleBase()
{
	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
    	{
		delete slot_otsec_vec[i];  
    	}
    	
        delete radar_slot;
        delete scaner_slot;
        delete energizer_slot;
        delete grapple_slot;
        delete protector_slot;
        delete droid_slot;
        delete freezer_slot;
                                                
       	delete gate_slot;
        	
    	delete drive_complex;
    	delete weapon_complex;
        
        delete drive_trail;
	delete shield;
} 




void VehicleBase :: postCreateInit()
{
	this->calcCollisionRadius();
	texOb_korpus = texOb;  
        	
   	////// Points creation
	this->createCenter();

    	points.initMainQuadPoints(texOb->getFrameWidth(), texOb->getFrameHeight());
    	points.addMainQuadPoints();

    	points.initShieldQuadPoints();
    	points.addShieldQuadPoints();

    	points.initMidLeftPoint();
    	points.addMidLeftPoint();

    	points.initMidFarLeftPoint();
    	points.addMidFarLeftPoint();
    	// 

    	/////////////////////////////////////////////////
    	///////////////////// KONTUR RECT ///////////////  
    	float kontur_w, kontur_h;
    	if (texOb->getFrameWidth() > texOb->getFrameHeight())
    	{
        	kontur_w = 500; 
        	kontur_h = texOb->getFrameHeight() * kontur_w / (float)texOb->getFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
        	kontur_w = texOb->getFrameWidth() * kontur_h / (float)texOb->getFrameHeight();
    	}               

    	kontur_rect = Rect(0, 0, kontur_w, kontur_h); 
    	kontur_rect.setCenter(SCREEN_WIDTH_MIN/2, SCREEN_HEIGHT_MIN/2); 
    	/////////////////////////////////////////////////


    	/////////////////////////////////////////////////
    	//////////////////////// WEAPONS SLOT ///////////
    	texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);  

	///////////////////////////////////////////////////
	//////////// EQUPMENT SLOT ////////////////////////
	radar_slot       = new ItemSlot(RADAR_SLOT_ID, this, texOb_slot);
				 
	radar_slot->setRect( kontur_rect.getCenter().x + 4*SHIP_SLOT_WIDTH, 
			     kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT/2,
			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(radar_slot);	
	
	
	scaner_slot      = new ItemSlot(SCANER_SLOT_ID, this, texOb_slot); 

	scaner_slot->setRect(  kontur_rect.getCenter().x + 4*SHIP_SLOT_WIDTH, 
			       kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT/2,
			       SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(scaner_slot);
	
	
	energizer_slot   = new ItemSlot(ENERGIZER_SLOT_ID, this, texOb_slot);
	
	energizer_slot->setRect(  kontur_rect.getCenter().x - 2*SHIP_SLOT_WIDTH, 
				  kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2,
				  SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(energizer_slot);
    		
    		
	if (data_korpus.inhibit_GRAPPLE == false)
	{
		grapple_slot  = new ItemSlot(GRAPPLE_SLOT_ID, this, texOb_slot);
				
		grapple_slot->setRect(  kontur_rect.getCenter().x - 3*SHIP_SLOT_WIDTH, 
					kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
					SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
					 
    		slot_total_vec.push_back(grapple_slot); 
    	}
    	
    	
	protector_slot   = new ItemSlot(PROTECTOR_SLOT_ID, this, texOb_slot);
			
	protector_slot->setRect(  kontur_rect.getCenter().x - 3*SHIP_SLOT_WIDTH, 
				  kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
				  SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(protector_slot); 
	
	
	droid_slot       = new ItemSlot(DROID_SLOT_ID, this, texOb_slot);
				    
	droid_slot->setRect(  kontur_rect.getCenter().x - 1*SHIP_SLOT_WIDTH, 
			      kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
			      SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(droid_slot); 
    	
    	
	freezer_slot     = new ItemSlot(FREEZER_SLOT_ID, this, texOb_slot);
				    
	freezer_slot->setRect(  kontur_rect.getCenter().x - 1*SHIP_SLOT_WIDTH, 
			       kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
			       SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
	
	slot_total_vec.push_back(freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* otsec_slot = new ItemSlot(CARGO_SLOT_ID, this, texOb_slot);
         		
         	otsec_slot->setRect( kontur_rect.getCenter().x + (i-6) * SHIP_SLOT_WIDTH, 
         			     kontur_rect.getCenter().y - 3*SHIP_SLOT_HEIGHT,
         			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
         					
         	slot_otsec_vec.push_back(otsec_slot); 
         	slot_total_vec.push_back(otsec_slot);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	gate_slot = new ItemSlot(GATE_SLOT_ID, this, texOb_slot);
    			     
    	gate_slot->setRect(  kontur_rect.getCenter().x - 5*SHIP_SLOT_WIDTH, 
    			     kontur_rect.getCenter().y + 3*SHIP_SLOT_HEIGHT,
    			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
    	////////////////////////////////////////////////////
 	   	   	

   
       	starsystem = NULL; 
    	npc_owner  = NULL;

    	drive_complex = new DriveComplex(this);  
    	    	
      	drive_trail = createTrailEffect(texOb->size_id, points.getpMidLeft(), points.getpMidFarLeft());
      	 
      	TextureOb* _texOb_shield = g_TEXTURE_MANAGER.getRandomTexOb(SHIELD_EFFECT_TEXTURE_ID); 
 	shield = new ShieldEffect(this, _texOb_shield);
 	
 	weapon_complex = new WeaponComplex(this);
 	weapon_complex->postCreateInit(data_korpus.weapon_slot_num, data_korpus.render_TURRELS);
}        	


void VehicleBase :: calcCollisionRadius()
{
	collision_radius = (texOb->getFrameWidth() + texOb->getFrameHeight())/3;
}
        	


	




//// ******** DOCKING/LAUNCHING ******** 
void VehicleBase :: jumpEvent()
{
        starsystem->removeShip(data_id.id);  
        starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());  
                                                        
        ((StarSystem*)drive_complex->getTarget())->addToHyperJumpQueue(npc_owner);
        drive_complex->resetTarget();        
}
                
                
void VehicleBase :: dockEvent()
{
     	starsystem->removeShip(data_id.id);
     	starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());
        
             	     	     	
     	if (drive_complex->getTarget()->getTypeId() == PLANET_ID)
     	{
                Planet* planet = ((Planet*)drive_complex->getTarget());
                
     		planet->getLand()->add((Ship*)this);
		planet->getLand()->add(npc_owner);
		
		npc_owner->setLand(planet->getLand());
	}
	
	if (drive_complex->getTarget()->getTypeId() == SPACESTATION_ID)
	{
                SpaceStation* spacestation = ((SpaceStation*)drive_complex->getTarget());
                                
	     	spacestation->getLand()->add((Ship*)this);
		spacestation->getLand()->add(npc_owner);
		
		npc_owner->setLand(spacestation->getLand());
	}
}

void VehicleBase :: launchingEvent()
{
     	printf("vehicle id = %i, launchingEvent()\n", data_id.id);

     	if (drive_complex->getTarget()->getTypeId() == PLANET_ID)
     	{
     		starsystem->addToSpace(this, drive_complex->getTarget()->getPoints()->getCenter(), 0, NULL);
     		starsystem->addToSpace(npc_owner);

     		((Planet*)drive_complex->getTarget())->getLand()->remove(this);
     		((Planet*)drive_complex->getTarget())->getLand()->remove(npc_owner);
	}
	
     	if (drive_complex->getTarget()->getTypeId() == SPACESTATION_ID)
     	{
     		starsystem->addToSpace(this, drive_complex->getTarget()->getPoints()->getCenter(), 0, NULL);
     		starsystem->addToSpace(npc_owner);

     		((SpaceStation*)drive_complex->getTarget())->getLand()->remove(this);
     		((SpaceStation*)drive_complex->getTarget())->getLand()->remove(npc_owner);
	}	

     	drive_complex->resetTarget();
}
//// 






void VehicleBase :: hit(int _damage, bool show_effect)
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
       			shield->setAlpha(1.0);
       		}       	
       		// improove
       		Color4i color;  	       		
       		VerticalFlowText* _text = new VerticalFlowText(int2str(_damage), points.getCenter(), color, collision_radius);
       		starsystem->addToSpace(_text); 
       	}
}


void VehicleBase :: postDeathUniqueEvent(bool show_effect)  /* virtual */
{
	int num_items = getRandInt(0, 3);
	for (int i = 0; i<num_items; i++)
	{
		dropRandomItemToSpace();
	}
	
	if (show_effect == true)
     	{
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);        		
        }
}


void VehicleBase :: updateAllStuff()
{
    	// this function set actual ship propretries relying to all equipment placed in slots
    	// used when ship change items in slot
    	// !!! all this stuff can be called separately by item deterioration function if item becomes broken !!!

    	updateDriveAbility();
    	updateRadarAbility();
    	updateJumpAbility();
    	updateEnergyAbility();  // make reurtn true, and add below if condition 
    	updateProtectionAbility(); // because energy shield depends on energy and consume it much
    	updateFireAbility();

    	updateRepairAbility();
    	updateFreezeAbility();
    	updateGrabAbility();
    	updateScanAbility();
}




void VehicleBase :: updateFireAbility()
{
     	//ableTo.FIRE = 
     	weapon_complex->updateFireAbility();
}






void VehicleBase :: calculateMass()
{
     	propetries.mass = 0;   

    	for (unsigned int i = 0; i < slot_total_vec.size(); i++)
    	{
        	if (slot_total_vec[i]->getEquipedStatus() == true)
        	{
           		propetries.mass += slot_total_vec[i]->getItem()->getMass();  
           	}    
    	}
}


void VehicleBase :: updateDriveAbility()
{
     	//// calculate mass and then actual ship speed depending on drive power and actual mass
     	//// used each time when ship picked up/bought or drop/sold something.
     	calculateMass();   	  

     	//// speed calculation ////
     	propetries.speed = 0;
     	ableTo.DRIVE = false;

     	if (drive_complex->getDriveSlot()->getEquipedStatus() == true) 
     	{
        	if (drive_complex->getDriveSlot()->getDriveEquipment()->getCondition() > 0)  
        	{
           		float val = (drive_complex->getDriveSlot()->getDriveEquipment()->getSpeed() - propetries.mass/70);
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


void VehicleBase :: updateRadarAbility()
{
   	if (radar_slot->getEquipedStatus() == true) 
   	{
      		if (radar_slot->getRadarEquipment()->getCondition() > 0)  
      		{
          		propetries.radius = radar_slot->getRadarEquipment()->getRadius();
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



void VehicleBase :: updateJumpAbility()
{    
	propetries.hyper = 0;
     	ableTo.HJUMP = false;

     	if (drive_complex->getDriveSlot()->getEquipedStatus() == true)
        	if (drive_complex->getDriveSlot()->getDriveEquipment()->getCondition() > 0)
           		if (drive_complex->getBakSlot()->getEquipedStatus() == true)
              			if (drive_complex->getBakSlot()->getBakEquipment()->getCondition() > 0)
              			{
                 			if (drive_complex->getDriveSlot()->getDriveEquipment()->getHyper() > drive_complex->getBakSlot()->getBakEquipment()->getFuel())
                    				propetries.hyper = drive_complex->getDriveSlot()->getDriveEquipment()->getHyper();
                 			else
                    				propetries.hyper = drive_complex->getBakSlot()->getBakEquipment()->getFuel();

                 			ableTo.HJUMP = true;
              			}    
}


void VehicleBase :: updateEnergyAbility()
{
     	propetries.energy = 0;
     	ableTo.ENERGIZE = false;

     	if (energizer_slot->getEquipedStatus() == true)
     	{
        	if (energizer_slot->getEnergizerEquipment()->getCondition() > 0)
        	{
           		propetries.energy = energizer_slot->getEnergizerEquipment()->getEnergy();
           		ableTo.ENERGIZE = true;
        	}
        }
}



void VehicleBase :: updateProtectionAbility()
{
        propetries.protection = data_korpus.protection;
        ableTo.PROTECT = false;


     	if (protector_slot->getEquipedStatus() == true)
     	{
        	if (protector_slot->getProtectorEquipment()->getCondition() > 0)
        	{
           		propetries.protection += protector_slot->getProtectorEquipment()->getProtection();
           		ableTo.PROTECT = true;
        	}       
     	}   
}




void VehicleBase :: updateRepairAbility()
{
     	propetries.repair = 0;
     	ableTo.REPAIR = false;

     	if (droid_slot->getEquipedStatus() == true)
     	{
        	if (droid_slot->getDroidEquipment()->getCondition() > 0)
        	{
            		propetries.repair = droid_slot->getDroidEquipment()->getRepair();
            		ableTo.REPAIR = true;
        	}
        }
}

void VehicleBase :: droidRepair()
{
	if (ableTo.REPAIR == true)
	{
		if (data_life.armor < data_korpus.armor)
		{
			data_life.armor += propetries.repair;
			droid_slot->getDroidEquipment()->deterioration();
		}
		
		if (data_life.armor > data_korpus.armor)
		{
			data_life.armor = data_korpus.armor;
		}
	}
}

void VehicleBase :: updateFreezeAbility()
{
     	propetries.freeze = 0;
     	ableTo.FREEZE = false;

     	if (freezer_slot->getEquipedStatus() == true)
     	{
        	if (freezer_slot->getFreezerEquipment()->getCondition() > 0)
        	{
           		propetries.freeze = freezer_slot->getFreezerEquipment()->getFreeze();
           		ableTo.FREEZE = true;
        	}
        }
}



void VehicleBase :: updateGrabAbility()
{
     	ableTo.GRAB = false;

     	if (data_korpus.inhibit_GRAPPLE == false)
        	if (grapple_slot->getEquipedStatus() == true)
           		if (grapple_slot->getGrappleEquipment()->getCondition() > 0)
              			ableTo.GRAB = true;
}



void VehicleBase :: updateScanAbility()
{
     	propetries.scan = 0;
     	ableTo.SCAN = false;

     	if (scaner_slot->getEquipedStatus() == true)
     	{
        	if (scaner_slot->getScanerEquipment()->getCondition() > 0)
        	{
           		propetries.scan = scaner_slot->getScanerEquipment()->getScan();
           		ableTo.SCAN = true;
        	}
        }
}



void VehicleBase :: setMaxArmor()
{
     	data_life.armor = data_korpus.armor;
}

void VehicleBase :: setMaxFuel()
{
     	if (drive_complex->getBakSlot()->getEquipedStatus() == true)
     	{
        	drive_complex->getBakSlot()->getBakEquipment()->fill();
        }
}



std::string VehicleBase :: returnProtectionStr()
{
    	if (ableTo.PROTECT == true)
       		return int2str(protector_slot->getProtectorEquipment()->getProtection()) + '+' + int2str(data_korpus.protection);
    	else
       		return int2str(data_korpus.protection);
}

void VehicleBase :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        this->updateInfo(); // virtual, overriding
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x, _pos_y, _offset_x, _offset_y);
     	
     	if (npc_owner != NULL)
     	{
     		npc_owner->renderInfo(_pos_x, _pos_y, _offset_x, _offset_y);
     	}
}

void VehicleBase :: renderInfo_inSpace(vec2f scroll_coords)
{  
	renderInfo(points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);
}

void VehicleBase :: renderGrappleTrail() const
{
        for (unsigned int i = 0; i<grapple_slot->getGrappleEquipment()->target_vec.size(); i++)
        {
                //if (grapple_slot->getGrappleEquipment()->target_vec[i]->getValid() == true)
                {              
                    	float xl = grapple_slot->getGrappleEquipment()->target_vec[i]->getPoints()->getpCenter()->x - points.getCenter().x;
                        float yl = grapple_slot->getGrappleEquipment()->target_vec[i]->getPoints()->getpCenter()->y - points.getCenter().y;

                        float len = sqrt((xl*xl) + (yl*yl));

                        float angle_inR = atan2(yl, xl);

                        float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;
        
                        drawLine(g_UNIQUE_TEXTURE_COLLECTOR.texOb_grapple_trail, 
                                points.getCenter(), 
                                points.getPosZ(), 
                                len, 
                                angle_inD, 
                                8);
                }
        }
}
		
void VehicleBase :: renderKorpus() const
{
    	drawFlatQuadPerVertexIn2D(texOb,
    				  points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
				  points.getPosZ());
}


void VehicleBase :: renderDriveTrail() const
{
	drive_trail->render();
}


void VehicleBase :: renderShield() const
{
     	shield->render();
}

void VehicleBase :: renderRadarRange()
{
	glPushMatrix();
		glTranslatef(points.getCenter().x, points.getCenter().y, 0.0f);
		radar_slot->updateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_yellow);
             	radar_slot->drawRange();
	glPopMatrix();
}

void VehicleBase :: renderGrappleRange()
{
	glPushMatrix();
		glTranslatef(points.getCenter().x, points.getCenter().y, 0.0f);
		grapple_slot->updateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue);
             	grapple_slot->drawRange();
	glPopMatrix();
}


bool VehicleBase :: repair()
{
        unsigned int _fix = data_korpus.armor - data_life.armor;
        unsigned int _price = _fix/10;
        
        if (npc_owner->getCredits() > _price)
        {
                data_life.armor = data_korpus.armor;
                npc_owner->decreaseCredits(_price);
                return true;  
        }
        
        return false;        
}


void VehicleBase :: dropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i = 0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->getEquipedStatus() == true)
		{
			_equiped_slot_vec.push_back(slot_total_vec[i]);
		}
	}
	
	if (_equiped_slot_vec.size() > 0)
	{
		unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());
	
		_equiped_slot_vec[_rand]->dropItemToSpace();
	}
		
}

void VehicleBase :: grappleScenario()
{
        grapple_slot->getGrappleEquipment()->validateTargets();  
                
        for (unsigned int i = 0; i < grapple_slot->getGrappleEquipment()->target_vec.size(); i++)
        {
               	grapple_slot->getGrappleEquipment()->target_vec[i]->movingByExternalForce(points.getCenter(), grapple_slot->getGrappleEquipment()->getStrength());        	
       	
       		float dist = distBetweenPoints(points.getCenter(), grapple_slot->getGrappleEquipment()->target_vec[i]->getPoints()->getCenter() ); 
       		if (dist < getCollisionRadius()/4.0f)
       		{
       			switch(grapple_slot->getGrappleEquipment()->target_vec[i]->getTypeId())
       			{
       				case MINERAL_ID:
       				{
       					ItemSlot* _slot;
                                        Mineral* _mineral = (Mineral*)grapple_slot->getGrappleEquipment()->target_vec[i];
                                        
       					_slot = getOtsecSlotWithGoods(MINERAL_ID);
       					if (_slot != NULL)
       					{
       						_slot->getGoodsPack()->increase(_mineral->getMass());
       						_mineral->setPlaceTypeId(NONE_ID);
       					}
       					else
       					{
       						GoodsPack* _goodsPack = getNewGoodsPack(MINERAL_ID);
       						_goodsPack->increase(_mineral->getMass());
       						_slot = getEmptyOtsecSlot();
       						if (_slot != NULL)
       						{
       							_slot->insertItem(_goodsPack);
       							_mineral->setPlaceTypeId(NONE_ID);
       						}
       					}
       					grapple_slot->getGrappleEquipment()->addToRemoveQueue(_mineral);
       					break;			
       				}
        			
      				case CONTAINER_ID:
       				{
       					ItemSlot* _slot = getEmptyOtsecSlot();
                                        Container* _container = (Container*)grapple_slot->getGrappleEquipment()->target_vec[i];
       				        if (_slot != NULL)
       					{
       						_slot->extractContainer(_container);
       						_container->setPlaceTypeId(NONE_ID);
       					}
					grapple_slot->getGrappleEquipment()->addToRemoveQueue(_container);
       					break;
       				}        			
        				
       				case SHIP_ID:
       				{
       					ItemSlot* _slot = getEmptyOtsecSlot();
                                        VehicleBase* _vehicle = (VehicleBase*)grapple_slot->getGrappleEquipment()->target_vec[i];
       				        if (_slot != NULL)
       					{
       						//_slot->insertItem(_vehicle);
       						starsystem->addToRemoveFromOuterSpaceQueue(_vehicle);
       					}
					grapple_slot->getGrappleEquipment()->addToRemoveQueue(_vehicle);
       					break;
       				}
       			}

       		}
       	}
}




void equip(VehicleBase* vehicle)
{
    	if (vehicle->data_korpus.weapon_slot_num >= 1)
    	{
       		//vehicle->weapon_slot1.insertItem(lazerEquipmentGenerator(RACE_0_ID)); 
       		vehicle->getWeaponComplex()->getWeaponSlot1()->insertItem(getNewRocketEquipment(RACE_0_ID));     	
    	}   

    	if (vehicle->data_korpus.weapon_slot_num >= 2)
    	{
       		vehicle->getWeaponComplex()->getWeaponSlot2()->insertItem(getNewLazerEquipment(RACE_0_ID)); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 3)
    	{
       		vehicle->getWeaponComplex()->getWeaponSlot3()->insertItem(getNewLazerEquipment(RACE_0_ID)); 
       		//vehicle->weapon_slot3.insertItem(rocketEquipmentGenerator(RACE_0_ID)); 
    	}   
        
    	if (vehicle->data_korpus.weapon_slot_num >= 4)
    	{
       		//vehicle->weapon_slot4.insertItem(lazerEquipmentGenerator(RACE_0_ID));         
       		vehicle->getWeaponComplex()->getWeaponSlot4()->insertItem(getNewRocketEquipment(RACE_0_ID)); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 5) 
    	{
       		//vehicle->weapon_slot5.insertItem(lazerEquipmentGenerator(RACE_0_ID)); 
       		vehicle->getWeaponComplex()->getWeaponSlot5()->insertItem(getNewRocketEquipment(RACE_0_ID)); 
    	}   
        
    	vehicle->getRadarSlot()->insertItem(getNewRadarEquipment(RACE_0_ID)); 
 
    	vehicle->getDriveComplex()->getDriveSlot()->insertItem(getNewDriveEquipment(RACE_0_ID)); 
    	vehicle->getDriveComplex()->getBakSlot()->insertItem(getNewBakEquipment(RACE_0_ID)); 
    	vehicle->getEnergizerSlot()->insertItem(getNewEnergizerEquipment(RACE_0_ID));     
    	vehicle->getProtectorSlot()->insertItem(getNewProtectorEquipment(RACE_0_ID)); 
   	vehicle->getDroidSlot()->insertItem(getNewDroidEquipment(RACE_0_ID)); 
   	vehicle->getFreezerSlot()->insertItem(getNewFreezerEquipment(RACE_0_ID));  
   	vehicle->getScanerSlot()->insertItem(getNewScanerEquipment(RACE_0_ID)); 
    
    	if (vehicle->data_korpus.inhibit_GRAPPLE == false) 
    	{
      		vehicle->getGrappleSlot()->insertItem(getNewGrappleEquipment(RACE_0_ID)); 
   	}
    
                             
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
                vehicle->slot_otsec_vec[i]->insertItem(getNewLazerEquipment(RACE_0_ID));
    	}


    	for (unsigned int i = 3; i < 6; i++) 
    	{        
        	vehicle->slot_otsec_vec[i]->insertItem(getNewRadarModule());
    	}  
    	
    	for (unsigned int i = 6; i < 8; i++) 
    	{        
                vehicle->slot_otsec_vec[i]->insertItem(getNewBomb());
    	}   
}







