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



void Vehicle :: setNpc(Npc* _npc)   { npc_owner = _npc; }
void Vehicle :: setKorpusData(KorpusData data_korpus) { this->data_korpus = data_korpus; }
void Vehicle :: add(ItemSlot* slot) { slot_total_vec.push_back(slot); }
                
WeaponComplex* Vehicle :: getWeaponComplex() const { return weapon_complex; }
                


Navigator* Vehicle :: getNavigator()    { return navigator; }
Npc*  Vehicle :: getNpc() 	      { return npc_owner; }

// needs for grabbing interface
int Vehicle :: getFunctionalSlotSubTypeId() const { return NONE_SLOT_ID; } 
void Vehicle :: bindSlot(ItemSlot* slot)          { return; }	   	
void Vehicle :: updateOwnerPropetries()	       { return; }	   
//
       	        
float Vehicle :: getVisionRadius() const { return propetries.radius; }

ItemSlot* Vehicle :: getEmptyOtsecSlot()
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


ItemSlot* Vehicle :: getOtsecSlotWithGoods(int requested_goods_subtype_id)
{
      	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
      	{
          	if (slot_otsec_vec[i]->getEquipedStatus() == true)
          	{
          		if (slot_otsec_vec[i]->getItemTypeId() == GOODS_ID)
          		{
          			if (slot_otsec_vec[i]->getItemSubTypeId() == requested_goods_subtype_id)
          			{
          				return slot_otsec_vec[i];
          			}
          		}
          	}             		
        }
        
      	return NULL;
}


                
                
Vehicle :: Vehicle()
{}

Vehicle :: ~Vehicle()
{
	for (unsigned int i = 0; i < slot_otsec_vec.size(); i++)
    	{
		delete slot_otsec_vec[i];  
    	}
    	
    	//delete drive_slot;
        //delete bak_slot;
        //delete radar_slot;
        //delete scaner_slot;
        //delete energizer_slot;
        //delete grapple_slot;
        //delete protector_slot;
        //delete droid_slot;
        //delete freezer_slot;
                                                
       	//delete gate_slot;
        	
    	delete navigator;
    	delete weapon_complex;
        
        delete drive_trail;
	delete shield;
} 




void Vehicle :: postCreateInit()
{
	this->calcCollisionRadius();
	texOb_korpus = texOb;  
        	
   	////// Points creation
	this->createCenter();

    	points.initMainQuadPoints(texOb->w, texOb->h);
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
    	if (texOb->w > texOb->h)
    	{
        	kontur_w = 500; 
        	kontur_h = texOb->h * kontur_w / (float)texOb->w;
    	}
    	else
    	{
        	kontur_h = 500; 
        	kontur_w = texOb->w * kontur_h / (float)texOb->h;
    	}               

    	kontur_rect = Rect(0, 0, kontur_w, kontur_h); 
    	kontur_rect.setNewCenter(g_VIEW_WIDTH/2, g_VIEW_HEIGHT/2); 
    	/////////////////////////////////////////////////


    	/////////////////////////////////////////////////
    	//////////////////////// WEAPONS SLOT ///////////
    	texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);  

	///////////////////////////////////////////////////
	//////////// EQUPMENT SLOT ////////////////////////
	drive_slot       = ItemSlot(DRIVE_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT/2,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(&drive_slot);
	
	
	bak_slot         = ItemSlot(BAK_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT/2,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(&bak_slot);
	
	
	radar_slot       = ItemSlot(RADAR_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT/2,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(&radar_slot);	
	
	
	scaner_slot      = ItemSlot(SCANER_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT/2,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(&scaner_slot);
	
	
	energizer_slot   = ItemSlot(ENERGIZER_SLOT_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 2*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(&energizer_slot);
    		
    		
	if (data_korpus.inhibit_GRAPPLE == false)
	{
		grapple_slot  = ItemSlot(GRAPPLE_SLOT_ID, 
					 this, 
					 texOb_slot, 
					 kontur_rect.getCenter().x - 3*SHIP_SLOT_WIDTH, 
					 kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
					 SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
					 
    		slot_total_vec.push_back(&grapple_slot); 
    	}
    	
    	
	protector_slot   = ItemSlot(PROTECTOR_SLOT_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 3*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(&protector_slot); 
	
	
	droid_slot       = ItemSlot(DROID_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	slot_total_vec.push_back(&droid_slot); 
    	
    	
	freezer_slot     = ItemSlot(FREEZER_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*SHIP_SLOT_WIDTH, 
				    kontur_rect.getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
				    SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	slot_total_vec.push_back(&freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* otsec_slot = new ItemSlot(CARGO_SLOT_ID, 
         						this, 
         						texOb_slot, 
         						kontur_rect.getCenter().x + (i-6) * SHIP_SLOT_WIDTH, 
         						kontur_rect.getCenter().y - 3*SHIP_SLOT_HEIGHT,
         						SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
         						
         	slot_otsec_vec.push_back(otsec_slot); 
         	slot_total_vec.push_back(otsec_slot);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	gate_slot = ItemSlot(GATE_SLOT_ID, 
    			     this, 
    			     texOb_slot, 
    			     kontur_rect.getCenter().x - 5*SHIP_SLOT_WIDTH, 
    			     kontur_rect.getCenter().y + 3*SHIP_SLOT_HEIGHT,
    			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
    	////////////////////////////////////////////////////
 	   	   	

   
       	starsystem = NULL; 
    	npc_owner  = NULL;

    	navigator = new Navigator(this);  
    	    	
      	drive_trail = createTrailEffect(texOb->size_id, points.getpMidLeft(), points.getpMidFarLeft());
      	 
      	TextureOb* _texOb_shield = g_TEXTURE_MANAGER.getRandomTexOb(SHIELD_EFFECT_TEXTURE_ID); 
 	shield = new ShieldEffect(this, _texOb_shield);
 	
 	weapon_complex = new WeaponComplex();
 	weapon_complex->postCreateInit(data_korpus.weapon_slot_num, kontur_rect, this, data_korpus.render_TURRELS, texOb);
}        	


void Vehicle :: calcCollisionRadius()
{
	collision_radius = (texOb->w + texOb->h)/3;
}
        	
void Vehicle :: update_inSpace_inDynamic_TRUE()
{   
	points.update(); 

    	if (ableTo.DRIVE == true) 
    	{ 
       		navigator->update_inSpace_inDynamic();
    	}
    
    	if (ableTo.GRAB == true)
    	{
    		grappleScenario();
    	}
}

void Vehicle :: update_inSpace_inDynamic_FALSE()
{   
    	if (ableTo.DRIVE == true) 
    	{
       		navigator->update_inSpace_inDynamic();
       	}
}

	

void Vehicle :: updateDyingEffect_TRUE()
{
	if (data_life.is_alive == false)
     	{
        	data_life.dying_time--;
        	if (data_life.dying_time < 0)
        	{
           		death_TRUE();
           	}
     	}  
}

void Vehicle :: updateDyingEffect_FALSE()
{
	if (data_life.is_alive == false)
     	{
       		death_FALSE();
     	}  
}


//// ******** DOCKING/LAUNCHING ******** 
bool Vehicle :: jumpEvent()
{
        starsystem->removeShip(data_id.id);  
        starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());  
                                                        
        navigator->getTargetOb()->getStarSystem()->addToHyperJumpQueue(npc_owner);
        navigator->resetTarget();        
        
        return true;
}
                
                
bool Vehicle :: dockEvent()
{
     	starsystem->removeShip(data_id.id);
     	starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());
        
             	     	     	
     	if (navigator->getTargetTypeId() == PLANET_ID)
     	{
     		navigator->getTargetPlanet()->add((Ship*)this);
		navigator->getTargetPlanet()->add(npc_owner);
		
		if (navigator->getTargetPlanet()->getSubTypeId() == KOSMOPORT_ID)
		{
			npc_owner->setKosmoport(navigator->getTargetPlanet()->getKosmoport());
		}
		
		if (navigator->getTargetPlanet()->getSubTypeId() == LAND_ID)
		{
			npc_owner->setLand(navigator->getTargetPlanet()->getLand());
		}
	}
    	return true;
}

bool Vehicle :: launchingEvent()
{
     	printf("vehicle id = %i, launchingEvent()\n", data_id.id);

     	starsystem->addToSpace(this, navigator->getTargetPlanet()->getPoints()->getCenter(), 0);
     	starsystem->addToSpace(npc_owner);

     	navigator->getTargetPlanet()->removeShipById(data_id.id);
     	navigator->getTargetPlanet()->removeNpcById(npc_owner->getId());

	//if (navigator->getTargetPlanet()->getSubTypeId() == KOSMOPORT_ID)
	//{
		//npc_owner->setKosmoport(NULL);
	//}
	//if (navigator->getTargetPlanet()->getSubTypeId() == LAND_ID)
	//{
		//npc_owner->setLand(NULL);
	//}
     	navigator->resetTarget();
     	
    	return true;
}
//// 






void Vehicle :: hit_TRUE(unsigned int _damage)
{
    	data_life.armor -= _damage;
    	if (ableTo.PROTECT == true)
    	{
       		shield->setAlpha(1.0);
       	}

    	if (data_life.armor < 0)
    	{
       		data_life.is_alive = false;
       	}
       	
       	// improove
       	Color4i color;  	       		
       	VerticalFlowText* _text = new VerticalFlowText(int2str(_damage), points.getCenter(), color, collision_radius);
       	starsystem->add(_text); 
}

void Vehicle :: hit_FALSE(unsigned int _damage)
{
    	data_life.armor -= _damage;

    	if (data_life.armor < 0)
    	{
    	       	data_life.is_alive = false;
       		death_FALSE();
       	}
}


void Vehicle :: death_TRUE()
{
     	if (data_life.garbage_ready == false)
     	{   
      		int num_items = getRandInt(0, 3);
     		for (int i = 0; i<num_items; i++)
     		{
     			dropRandomItemToSpace();
     		}
     	
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);
        	data_life.garbage_ready = true;
     	}
}

void Vehicle :: death_FALSE()
{
     	if (data_life.garbage_ready == false)
     	{   
      		int num_items = getRandInt(0, 3);
     		for (int i = 0; i<num_items; i++)
     		{
     			dropRandomItemToSpace();
     		}
     		
        	data_life.garbage_ready = true;
     	}
}



void Vehicle :: updateAllStuff()
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




void Vehicle :: updateFireAbility()
{
     	//ableTo.FIRE = 
     	weapon_complex->updateFireAbility();
}






void Vehicle :: calculateMass()
{
     	propetries.mass = 0;   

    	for (unsigned int i = 0; i < slot_total_vec.size(); i++)
    	{
        	if (slot_total_vec[i]->getEquipedStatus() == true)
        	{
           		propetries.mass += slot_total_vec[i]->getItemMass();  
           	}    
    	}
}


void Vehicle :: updateDriveAbility()
{
     	//// calculate mass and then actual ship speed depending on drive power and actual mass
     	//// used each time when ship picked up/bought or drop/sold something.
     	calculateMass();   	  

     	//// speed calculation ////
     	propetries.speed = 0;
     	ableTo.DRIVE = false;

     	if (drive_slot.getEquipedStatus() == true) 
     	{
        	if (drive_slot.getDriveEquipment()->getCondition() > 0)  
        	{
           		float val = (drive_slot.getDriveEquipment()->getSpeed() - propetries.mass/70);
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


void Vehicle :: updateRadarAbility()
{
   	if (radar_slot.getEquipedStatus() == true) 
   	{
      		if (radar_slot.getRadarEquipment()->getCondition() > 0)  
      		{
          		propetries.radius = radar_slot.getRadarEquipment()->getRadius();
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



void Vehicle :: updateJumpAbility()
{    
	propetries.hyper = 0;
     	ableTo.HJUMP = false;

     	if (drive_slot.getEquipedStatus() == true)
        	if (drive_slot.getDriveEquipment()->getCondition() > 0)
           		if (bak_slot.getEquipedStatus() == true)
              			if (bak_slot.getBakEquipment()->getCondition() > 0)
              			{
                 			if (drive_slot.getDriveEquipment()->getHyper() > bak_slot.getBakEquipment()->getFuel())
                    				propetries.hyper = drive_slot.getDriveEquipment()->getHyper();
                 			else
                    				propetries.hyper = bak_slot.getBakEquipment()->getFuel();

                 			ableTo.HJUMP = true;
              			}    
}


void Vehicle :: updateEnergyAbility()
{
     	propetries.energy = 0;
     	ableTo.ENERGIZE = false;

     	if (energizer_slot.getEquipedStatus() == true)
     	{
        	if (energizer_slot.getEnergizerEquipment()->getCondition() > 0)
        	{
           		propetries.energy = energizer_slot.getEnergizerEquipment()->getEnergy();
           		ableTo.ENERGIZE = true;
        	}
        }
}



void Vehicle :: updateProtectionAbility()
{
        propetries.protection = data_korpus.protection;
        ableTo.PROTECT = false;


     	if (protector_slot.getEquipedStatus() == true)
     	{
        	if (protector_slot.getProtectorEquipment()->getCondition() > 0)
        	{
           		propetries.protection += protector_slot.getProtectorEquipment()->getProtection();
           		ableTo.PROTECT = true;
        	}       
     	}   
}




void Vehicle :: updateRepairAbility()
{
     	propetries.repair = 0;
     	ableTo.REPAIR = false;

     	if (droid_slot.getEquipedStatus() == true)
     	{
        	if (droid_slot.getDroidEquipment()->getCondition() > 0)
        	{
            		propetries.repair = droid_slot.getDroidEquipment()->getRepair();
            		ableTo.REPAIR = true;
        	}
        }
}

void Vehicle :: droidRepair()
{
	if (ableTo.REPAIR == true)
	{
		if (data_life.armor < data_korpus.armor)
		{
			data_life.armor += propetries.repair;
			droid_slot.getDroidEquipment()->deterioration();
		}
		
		if (data_life.armor > data_korpus.armor)
		{
			data_life.armor = data_korpus.armor;
		}
	}
}

void Vehicle :: updateFreezeAbility()
{
     	propetries.freeze = 0;
     	ableTo.FREEZE = false;

     	if (freezer_slot.getEquipedStatus() == true)
     	{
        	if (freezer_slot.getFreezerEquipment()->getCondition() > 0)
        	{
           		propetries.freeze = freezer_slot.getFreezerEquipment()->getFreeze();
           		ableTo.FREEZE = true;
        	}
        }
}



void Vehicle :: updateGrabAbility()
{
     	ableTo.GRAB = false;

     	if (data_korpus.inhibit_GRAPPLE == false)
        	if (grapple_slot.getEquipedStatus() == true)
           		if (grapple_slot.getGrappleEquipment()->getCondition() > 0)
              			ableTo.GRAB = true;
}



void Vehicle :: updateScanAbility()
{
     	propetries.scan = 0;
     	ableTo.SCAN = false;

     	if (scaner_slot.getEquipedStatus() == true)
     	{
        	if (scaner_slot.getScanerEquipment()->getCondition() > 0)
        	{
           		propetries.scan = scaner_slot.getScanerEquipment()->getScan();
           		ableTo.SCAN = true;
        	}
        }
}



void Vehicle :: setMaxArmor()
{
     	data_life.armor = data_korpus.armor;
}

void Vehicle :: setMaxFuel()
{
     	if (bak_slot.getEquipedStatus() == true)
     	{
        	bak_slot.getBakEquipment()->fill();
        }
}


void Vehicle :: updateInfo()
{
	info.clear();

    	info.addTitleStr("SHIP");
    	info.addNameStr("id/ss_id:");          	info.addValueStr( int2str(data_id.id) + " / " + int2str(starsystem->getId()) );
    	info.addNameStr("race:");   		info.addValueStr( returnRaceStringByRaceId(texOb->race_id) ); 
    	info.addNameStr("armor/max:");     	info.addValueStr( int2str(data_life.armor) + "/" + int2str(data_korpus.armor) );
    	info.addNameStr("size id:");     	info.addValueStr( int2str(texOb->size_id) );
    	info.addNameStr("space/free:");   	info.addValueStr( int2str(data_korpus.space) + "/" + int2str(data_korpus.space - propetries.mass) );
    	info.addNameStr("mass:");   		info.addValueStr( int2str(propetries.mass) );
    	info.addNameStr("energy:");            	info.addValueStr( int2str(propetries.energy) );
	info.addNameStr("temp.:");       	info.addValueStr( int2str(data_korpus.temperature) );
        info.addNameStr("radius:");    		info.addValueStr( int2str(propetries.radius) );
    	info.addNameStr("protect:");        	info.addValueStr( returnProtectionStr() );
	info.addNameStr("speedx:");       	info.addValueStr(int2str(int(propetries.speed*100)) );
}

std::string Vehicle :: returnProtectionStr()
{
    	if (ableTo.PROTECT == true)
       		return int2str(protector_slot.getProtectorEquipment()->getProtection()) + '+' + int2str(data_korpus.protection);
    	else
       		return int2str(data_korpus.protection);
}

void Vehicle :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x, _pos_y, _offset_x, _offset_y);
     	
     	npc_owner->renderInfo(_pos_x, _pos_y, _offset_x, _offset_y);
}

void Vehicle :: renderInfo()
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
     	npc_owner->renderInfo(points.getCenter().x, points.getCenter().y);
}
	

void Vehicle :: updateRenderStuff()
{
    	//points.update(); 
    	shield->update();
    	
    	if (ableTo.DRIVE == true)
    	{
       		drive_trail->update();
    	}
}


void Vehicle :: render_inSpace() const
{   
        if (ableTo.GRAB == true)
        {
                renderGrappleTrail();
        }
        
    	renderKorpus();
    	
    	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }

    	if (ableTo.DRIVE == true)
    	{
		renderDriveTrail();
    	}
    	
    	if (ableTo.PROTECT == true)
    	{
        	renderShield(); 
        }
}


void Vehicle :: render_atPlanet() const
{
	renderKorpus();
	
	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }
}		

void Vehicle :: renderGrappleTrail() const
{
        for (unsigned int i = 0; i<grapple_slot.getGrappleEquipment()->target_vec.size(); i++)
        {
                if (grapple_slot.getGrappleEquipment()->target_vec[i]->getValid() == true)
                {              
                    	float xl = grapple_slot.getGrappleEquipment()->target_vec[i]->getpCenter()->x - points.getCenter().x;
                        float yl = grapple_slot.getGrappleEquipment()->target_vec[i]->getpCenter()->y - points.getCenter().y;

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
		
void Vehicle :: renderKorpus() const
{
    	drawFlatQuadPerVertexIn2D(texOb,
    				  points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
				  points.getPosZ());
}


void Vehicle :: renderDriveTrail() const
{
	drive_trail->render();
}


void Vehicle :: renderShield() const
{
     	shield->render();
}

void Vehicle :: renderRadarRange()
{
	glPushMatrix();
		glTranslatef(points.getCenter().x, points.getCenter().y, 0.0f);
		radar_slot.updateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_yellow);
             	radar_slot.drawRange();
	glPopMatrix();
}

void Vehicle :: renderGrappleRange()
{
	glPushMatrix();
		glTranslatef(points.getCenter().x, points.getCenter().y, 0.0f);
		grapple_slot.updateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue);
             	grapple_slot.drawRange();
	glPopMatrix();
}


bool Vehicle :: repair()
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


void Vehicle :: dropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i = 0; i<slot_total_vec.size(); i++)
	{
		if (slot_total_vec[i]->getEquipedStatus() == true)
		{
			_equiped_slot_vec.push_back(slot_total_vec[i]);
		}
	}
	
	unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());
	
	_equiped_slot_vec[_rand]->dropItemToSpace();
		
}

void Vehicle :: grappleScenario()
{
        grapple_slot.getGrappleEquipment()->validationTargets();  
                
        for (unsigned int i = 0; i < grapple_slot.getGrappleEquipment()->target_vec.size(); i++)
        {	//printf("blablabla\n");
                if (grapple_slot.getGrappleEquipment()->target_vec[i]->getValid() == true)
                {
                	//printf("blablabla\n");
                       	grapple_slot.getGrappleEquipment()->target_vec[i]->moveExternalyToPosition(points.getCenter());        	
       	
        		float dist = distBetweenPoints(points.getCenter(), *grapple_slot.getGrappleEquipment()->target_vec[i]->getpCenter() ); 
        		if (dist < getCollisionRadius()/4.0f)
        		{
        			switch(grapple_slot.getGrappleEquipment()->target_vec[i]->getObTypeId())
        			{
        				case MINERAL_ID:
        				{
        					ItemSlot* _slot;
        					_slot = getOtsecSlotWithGoods(MINERAL_ID);
        					if (_slot != NULL)
        					{
        						_slot->getGoodsPack()->increase(grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->getMass());
        						        							
        						grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->setPlaceTypeId(NONE_ID);
        					}
        					else
        					{
        						GoodsPack* _goodsPack = createGoodsPack(MINERAL_ID);
        						_goodsPack->increase(grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->getMass());
        						_slot = getEmptyOtsecSlot();
        						if (_slot != NULL)
        						{
        							_slot->insertGoods(_goodsPack);
        							grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->setPlaceTypeId(NONE_ID);
        						}
        					}
        					grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        					break;			
        				}
        			
        				case CONTAINER_ID:
        				{
        					ItemSlot* _slot = getEmptyOtsecSlot();
        				        if (_slot != NULL)
        					{
        						_slot->insertContainer(grapple_slot.getGrappleEquipment()->target_vec[i]->getContainer());
        						grapple_slot.getGrappleEquipment()->target_vec[i]->getContainer()->setPlaceTypeId(NONE_ID);
        					}
       						grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        					break;
        				}
        			
        				case BOMB_ID:
        				{
        					ItemSlot* _slot = getEmptyOtsecSlot();
        				        if (_slot != NULL)
        					{
        						_slot->insertItem(grapple_slot.getGrappleEquipment()->target_vec[i]->getBomb());
        						starsystem->addToRemoveFromOuterSpaceQueue(grapple_slot.getGrappleEquipment()->target_vec[i]->getBomb());
        					}
       						grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        					break;
        				}
        				
        				case SHIP_ID:
        				{
        					ItemSlot* _slot = getEmptyOtsecSlot();
        				        if (_slot != NULL)
        					{
        						_slot->insertItem(grapple_slot.getGrappleEquipment()->target_vec[i]->getVehicle());
        						starsystem->addToRemoveFromOuterSpaceQueue(grapple_slot.getGrappleEquipment()->target_vec[i]->getVehicle());
        					}
       						grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        					break;
        				}
        			}

        		}
        	}
        
        }
}



void Vehicle :: moveExternalyToPosition(vec2f _target)
{
	vec2f d_pos;
        get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, _target.x, _target.y, 10*propetries.speed, &d_pos.x, &d_pos.y);
        points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
        //points.setCenter(points.getCenter() + d_pos);
}






