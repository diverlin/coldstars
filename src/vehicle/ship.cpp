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


void Ship :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void Ship :: setNpc(Npc* _npc)                      { npc_owner = _npc; }
void Ship :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; }

int Ship :: getId() const           { return data_id.id; }
int Ship :: getTypeId() const       { return data_id.type_id; }
int Ship :: getPlaceTypeId() const  { return place_type_id; } 
bool Ship :: getGarbageReady() const { return data_life.garbage_ready; }
bool Ship :: getAlive() const       { return data_life.is_alive; }
bool* Ship :: getpAlive()           { return &data_life.is_alive; }
int* Ship :: getpPlaceTypeId()      { return &place_type_id; }
int Ship :: getArmor() const        { return data_life.armor; }

Points* Ship :: getPoints() 	    { return &points; }
Navigator* Ship :: getNavigator()   { return navigator; }
StarSystem* Ship :: getStarSystem() { return starsystem; }
Npc*  Ship :: getNpc() 		    { return npc_owner; }
int Ship :: getCollisionRadius() const  { return data_korpus.collision_radius; } 

ItemSlot* Ship :: getEmptyOtsecSlot()
{
      	for (unsigned int si = 0; si < slot_otsec_pList.size(); si++)
      	{
          	if (slot_otsec_pList[si]->getEquipedStatus() == false)
             		return slot_otsec_pList[si];
        }
        
      	return NULL;
}
                
                
Ship :: Ship(TextureOb* _texOb, LifeData _data_life, IdData _data_id, KorpusData _data_korpus)
{
    	data_life = _data_life;
    	data_id   = _data_id;

    	texOb = _texOb;
        texOb_korpus = texOb;  

        turrel1 = NULL;
        turrel2 = NULL;
        turrel3 = NULL;
        turrel4 = NULL;
        turrel5 = NULL;
        	
   	////// Points creation
    	points.initCenterPoint();
    	points.addCenterPoint();

    	points.initMainQuadPoints(texOb->w, texOb->h);
    	points.addMainQuadPoints();

    	points.initShieldQuadPoints();
    	points.addShieldQuadPoints();

    	points.initMidLeftPoint();
    	points.addMidLeftPoint();

    	points.initMidFarLeftPoint();
    	points.addMidFarLeftPoint();
    	// 
	
        data_korpus = _data_korpus;

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
    	texOb_slot   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);
  
   
    	TextureOb* turrelTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.turrel_texOb_pList); 
   
    	if (data_korpus.weapon_slot_num >= 1)
    	{  
       		weapon_slot1 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2);
       					
       		slot_weapon_vec.push_back(&weapon_slot1);
       		slot_total_pList.push_back(&weapon_slot1); 

       		turrel1 = new Turrel(&weapon_slot1, points.getpWeapon1Center());       
       		turrel1->setTexOb(turrelTexOb); // remove
                
       		weapon_slot1.bindTurrel(turrel1);

       
       		if (data_korpus.render_TURRELS == true)
       		{   
           		points.initWeapon1CenterPoint(0, texOb->h/3);
           		points.addWeapon1CenterPoint();
       		} 
    	}
   
    	if (data_korpus.weapon_slot_num >= 2)
    	{  
       		weapon_slot2 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
       					    
       		slot_weapon_vec.push_back(&weapon_slot2);
       		slot_total_pList.push_back(&weapon_slot2); 
       
                turrel2 = new Turrel(&weapon_slot2, points.getpWeapon2Center()); 
       		turrel2->setTexOb(turrelTexOb);
                
              	weapon_slot2.bindTurrel(turrel2);

        
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon2CenterPoint(0, -texOb->h/3);
           		points.addWeapon2CenterPoint();
       		}
    	}

    	if (data_korpus.weapon_slot_num >= 3)
    	{  
       		weapon_slot3 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h); 
       					
       		slot_weapon_vec.push_back(&weapon_slot3);
       		slot_total_pList.push_back(&weapon_slot3); 
              
       		turrel3 = new Turrel(&weapon_slot3, points.getpWeapon3Center()); 
       		turrel3->setTexOb(turrelTexOb);
                
              	weapon_slot3.bindTurrel(turrel3);
       
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon3CenterPoint(-texOb->w/5, texOb->h/3);
           		points.addWeapon3CenterPoint();
       		}
    	}

    	if (data_korpus.weapon_slot_num >= 4)
    	{  
       		weapon_slot4 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
       					
       		slot_weapon_vec.push_back(&weapon_slot4);
       		slot_total_pList.push_back(&weapon_slot4); 
              
       		turrel4 = new Turrel(&weapon_slot4, points.getpWeapon4Center()); 
       		turrel4->setTexOb(turrelTexOb);
                
              	weapon_slot4.bindTurrel(turrel4);

         
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon4CenterPoint(texOb->w/5, -texOb->h/3);
           		points.addWeapon4CenterPoint();
       		}

    	}   

    	if (data_korpus.weapon_slot_num >= 5)
    	{  
       		weapon_slot5 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
       					
       		slot_weapon_vec.push_back(&weapon_slot5);
       		slot_total_pList.push_back(&weapon_slot5); 
              
       		turrel5 = new Turrel(&weapon_slot5, points.getpWeapon5Center()); 
              	turrel5->setTexOb(turrelTexOb);
       
                weapon_slot5.bindTurrel(turrel5);
       		
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon5CenterPoint(-texOb->w/3, -texOb->h/3);
           		points.addWeapon5CenterPoint();           		
       		}
    	} 
    	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//////////// EQUPMENT SLOT ////////////////////////
	drive_slot       = ItemSlot(DRIVE_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&drive_slot);
	
	
	bak_slot         = ItemSlot(BAK_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&bak_slot);
	
	
	radar_slot       = ItemSlot(RADAR_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&radar_slot);	
	
	
	scaner_slot      = ItemSlot(SCANER_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&scaner_slot);
	
	
	energizer_slot   = ItemSlot(ENERGIZER_SLOT_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 2*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2);
				    
    	slot_total_pList.push_back(&energizer_slot);
    		
    		
	if (data_korpus.inhibit_GRAPPLE == false)
	{
		grapple_slot  = ItemSlot(GRAPPLE_SLOT_ID, 
					 this, 
					 texOb_slot, 
					 kontur_rect.getCenter().x - 3*texOb_slot->w, 
					 kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
					 
    		slot_total_pList.push_back(&grapple_slot); 
    	}
    	
    	
	protector_slot   = ItemSlot(PROTECTOR_SLOT_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 3*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h);
				    
    	slot_total_pList.push_back(&protector_slot); 
	
	
	droid_slot       = ItemSlot(DROID_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
				    
    	slot_total_pList.push_back(&droid_slot); 
    	
    	
	freezer_slot     = ItemSlot(FREEZER_SLOT_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h);
				    
	slot_total_pList.push_back(&freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* pTo_otsec_slot = new ItemSlot(CARGO_SLOT_ID, 
         						this, 
         						texOb_slot, 
         						kontur_rect.getCenter().x + (i-6) * texOb_slot->w, 
         						kontur_rect.getCenter().y - 3*texOb_slot->h);
         						
         	slot_otsec_pList.push_back(pTo_otsec_slot); 
         	slot_total_pList.push_back(pTo_otsec_slot);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	gate_slot = ItemSlot(GATE_SLOT_ID, 
    			     this, 
    			     texOb_slot, 
    			     kontur_rect.getCenter().x - 5*texOb_slot->w, 
    			     kontur_rect.getCenter().y + 3*texOb_slot->h);
    	////////////////////////////////////////////////////
 	   	   	

   
       	starsystem = NULL; 
    	npc_owner  = NULL;

    	navigator = new Navigator(this);  
    	    	
      	drive_trail = createTrailEffect(texOb->size_id, points.getpMidLeft(), points.getpMidFarLeft());
      	 
      	TextureOb* _texOb_shield = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shieldEffect_texOb_pList); 
 	shield = new ShieldEffect(this, _texOb_shield);
}



Ship :: ~Ship()
{
	for (unsigned int i = 0; i < slot_otsec_pList.size(); i++)
    	{
		delete slot_otsec_pList[i];  
    	}
    	
    	delete navigator;
    	
    	delete turrel1;
        delete turrel2;
        delete turrel3;
        delete turrel4;
        delete turrel5;
        
        delete drive_trail;
	delete shield;
} 



void Ship :: prepareWeapons()
{
     	// reload wepons
     	// used once at the beginning of turn
     	
	reloadAllWeapons();
	validateAllReloadedWeaponsTarget();
}
    
void Ship :: reloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->getTurrel()->isAmmoAvailable() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
            
     	fire_delay = 10;
     	d_fire_delay = 40;   
}


void Ship :: selectWeapons()
{
        if (data_korpus.weapon_slot_num >= 1)
                weapon_slot1.getTurrel()->setSelectedStatus(weapon_selector.slot_1);
        if (data_korpus.weapon_slot_num >= 2)
                weapon_slot2.getTurrel()->setSelectedStatus(weapon_selector.slot_2);
        if (data_korpus.weapon_slot_num >= 3)
                weapon_slot3.getTurrel()->setSelectedStatus(weapon_selector.slot_3);
        if (data_korpus.weapon_slot_num >= 4)
                weapon_slot4.getTurrel()->setSelectedStatus(weapon_selector.slot_4);
        if (data_korpus.weapon_slot_num >= 5)
                weapon_slot5.getTurrel()->setSelectedStatus(weapon_selector.slot_5);
}


bool Ship :: isAnyWeaponSelected() const
{
	return weapon_selector.isAnySelected();     	
}


template <typename TARGET_TYPE> 
void Ship :: setWeaponsTarget(TARGET_TYPE* _target)
{                          
        float dist = distBetweenPoints(points.getCenter(), _target->getPoints()->getCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
        	if ( slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->getTurrel()->getTargetOb()->getValid() == false )
           		{
           	      		if ( dist < slot_weapon_equiped_vec[i]->getItemRadius() )
           	      		{
                       			slot_weapon_equiped_vec[i]->getTurrel()->setTarget(_target);
                       		}
                       	}
                } 
        }               

}



void Ship :: weaponsFire_TRUE(int timer)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{	
           		if ( slot_weapon_reloaded_vec[i]->getTurrel()->validateTarget() == true )
           		{	
               			if ( slot_weapon_reloaded_vec[i]->getTurrel()->fireEvent_TRUE() == true )
               			{
                   			slot_weapon_reloaded_vec.erase(slot_weapon_reloaded_vec.begin() + i);
                   			fire_delay += d_fire_delay;
                   			break;
               			}
            			else
            			{
               				slot_weapon_reloaded_vec.erase(slot_weapon_reloaded_vec.begin() + i);
               				break;
            			}
            		}
        	}
        }
}

void Ship :: validateAllReloadedWeaponsTarget()
{
	// in STATIC after weapons reloaded
        for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        {	
        	slot_weapon_reloaded_vec[i]->getTurrel()->validateTarget();
	}
}


void Ship :: weaponsFire_FALSE(int timer)
{
        weaponsFire_TRUE(timer);
}




void Ship :: resetDeselectedWeaponTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
            	if (slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == false)
            	{
                	slot_weapon_equiped_vec[i]->getTurrel()->getTargetOb()->reset();
                }
        }
}



void Ship :: update_inSpace_inDynamic_TRUE()
{   
    	if (ableTo.DRIVE == true) 
    	{ 
       		navigator->update_inSpace_inDynamic();
    	}
    

    	if (data_life.is_alive == false)
    	{
       		data_life.dying_time--;
       		if (data_life.dying_time < 0)
       		{
           		death_TRUE();
           	}
    	}    
}

void Ship :: update_inSpace_inDynamic_FALSE()
{   
    	if (ableTo.DRIVE == true) 
    	{
       		navigator->update_inSpace_inDynamic();
       	}
}





//// ******** DOCKING/LAUNCHING ******** 
bool Ship :: jumpEvent()
{
        starsystem->removeShip(data_id.id);  
        starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());  
                                                        
        navigator->getTargetOb()->getStarSystem()->addToHyperJumpQueue(npc_owner);
        navigator->resetTarget();        
        
        return true;
}
                
                
bool Ship :: dockEvent()
{
     	starsystem->removeShip(data_id.id);
     	starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());
        
             	     	     	
     	if (navigator->getTargetTypeId() == PLANET_ID)
     	{
     		navigator->getTargetPlanet()->add(this);
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

bool Ship :: launchingEvent()
{
     	printf("ship id = %i, launchingEvent()\n", data_id.id);

     	starsystem->moveToSpace(this);
     	starsystem->moveToSpace(npc_owner);

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
		
	points.setCenter(navigator->getTargetPlanet()->getPoints()->getCenter());
     	navigator->resetTarget();
     	
    	return true;
}
//// 







void Ship :: hit_TRUE(unsigned int _damage)
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
       	VerticalFlowText* _text = new VerticalFlowText(int2str(_damage), points.getCenter(), color, data_korpus.collision_radius);
       	starsystem->add(_text); 
}

void Ship :: hit_FALSE(unsigned int _damage)
{
    	data_life.armor -= _damage;

    	if (data_life.armor < 0)
    	{
    	       	data_life.is_alive = false;
       		death_FALSE();
       	}
}


void Ship :: death_TRUE()
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

void Ship :: death_FALSE()
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



void Ship :: updateAllStuff()
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




void Ship :: updateFireAbility()
{
     	slot_weapon_equiped_vec.clear();

     	int sum_damage = 0;
     	int sum_fire_radius = 0;

     	for (unsigned int i = 0; i < slot_weapon_vec.size(); i++)
     	{ 
        	if (slot_weapon_vec[i]->getEquipedStatus() == true)
        	{
           		if (slot_weapon_vec[i]->getItemCondition() > 0)
           		{
              			slot_weapon_equiped_vec.push_back(slot_weapon_vec[i]);
              			sum_damage      += slot_weapon_vec[i]->getItemDamage(); 
              			sum_fire_radius += slot_weapon_vec[i]->getItemRadius(); 
           		}
           	}
     	}

     	if (slot_weapon_equiped_vec.size() != 0)
     	{
        	propetries.average_fire_radius = sum_fire_radius/slot_weapon_equiped_vec.size();
        	ableTo.FIRE = true;
     	}
     	else
     	{
        	propetries.average_fire_radius = 0;
        	ableTo.FIRE = false;
     	} 
}






void Ship :: calculateMass()
{
     	propetries.mass = 0;   

    	for (unsigned int i = 0; i < slot_total_pList.size(); i++)
    	{
        	if (slot_total_pList[i]->getEquipedStatus() == true)
           		propetries.mass += slot_total_pList[i]->getItemMass();      
    	}
}


void Ship :: updateDriveAbility()
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


void Ship :: updateRadarAbility()
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
}



void Ship :: updateJumpAbility()
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


void Ship :: updateEnergyAbility()
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



void Ship :: updateProtectionAbility()
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




void Ship :: updateRepairAbility()
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


void Ship :: updateFreezeAbility()
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



void Ship :: updateGrabAbility()
{
     	ableTo.GRAB = false;

     	if (data_korpus.inhibit_GRAPPLE == false)
        	if (grapple_slot.getEquipedStatus() == true)
           		if (grapple_slot.getGrappleEquipment()->getCondition() > 0)
              			ableTo.GRAB = true;
}



void Ship :: updateScanAbility()
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



void Ship :: setMaxArmor()
{
     	data_life.armor = data_korpus.armor;
}

void Ship :: setMaxFuel()
{
     	if (bak_slot.getEquipedStatus() == true)
        	bak_slot.getBakEquipment()->fill();
}


void Ship :: updateInfo()
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

std::string Ship :: returnProtectionStr()
{
    	if (ableTo.PROTECT == true)
       		return int2str(protector_slot.getProtectorEquipment()->getProtection()) + '+' + int2str(data_korpus.protection);
    	else
       		return int2str(data_korpus.protection);
}

void Ship :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x, _pos_y, _offset_x, _offset_y);
     	
     	npc_owner->renderInfo(_pos_x, _pos_y, _offset_x, _offset_y);
}

void Ship :: renderInfo()
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
     	npc_owner->renderInfo(points.getCenter().x, points.getCenter().y);
}
	

void Ship :: updateRenderStuff()
{
    	points.update(); 
    	shield->update();
    	
    	if (ableTo.DRIVE == true)
    	{
       		drive_trail->update();
    	}
}


void Ship :: render_inSpace() const
{   
        if (ableTo.GRAB == true)
        {
                renderGrappleTrail();
        }
        
    	renderKorpus();
    	
    	if (data_korpus.render_TURRELS == true)
    	{
        	renderTurrels();
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


void Ship :: render_atPlanet() const
{
	renderKorpus();
	
	if (data_korpus.render_TURRELS == true)
    	{
        	renderTurrels();
        }
}		

void Ship :: renderGrappleTrail() const
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
        
                        drawLine(g_UNIQUE_TEXTURE_COLLECTOR.texOb_grapple_trail->texture, 
                                points.getCenter().x, 
                                points.getCenter().y, 
                                points.getPosZ(), 
                                len, 
                                angle_inD, 
                                8);
                }
        }
}
		
void Ship :: renderKorpus() const
{
   	glBindTexture(GL_TEXTURE_2D, texOb->texture); 
                                  
    	drawFlatQuadPerVertexIn2D(points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
				  points.getPosZ());
}


void Ship :: renderTurrels() const
{
    	for(unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->getTurrel()->render(points.getAngleDegree());        
    	} 
}


void Ship :: renderDriveTrail() const
{
	drive_trail->render();
}


void Ship :: renderShield() const
{
     	shield->render();
}


void Ship :: renderWeaponIcons() const
{
        enable_BLEND();
        
        int offset = 0;
        for (unsigned int wi = 0; wi < slot_weapon_vec.size(); wi++)
        {
                Turrel* _turrel = slot_weapon_vec[wi]->getTurrel();
                if (_turrel->getTargetOb()->getValid() == true)
                {       
                        Rect _rect(_turrel->getTargetOb()->getpCenter()->x - 40/2 + 23*offset, _turrel->getTargetOb()->getpCenter()->y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[wi]->getItemTexOb()->texture, _rect, -2.0);
                        offset++;
                }        
        }
        
        disable_BLEND();
}



void equip(Ship* ship)
{
    	if (ship->data_korpus.weapon_slot_num >= 1)
    	{
       		LazerEquipment* pTo_lazer1 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot1.insertItem(pTo_lazer1); 
    	}   

    	if (ship->data_korpus.weapon_slot_num >= 2)
    	{
       		LazerEquipment* pTo_lazer2 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot2.insertItem(pTo_lazer2); 
    	}   
    
    	if (ship->data_korpus.weapon_slot_num >= 3)
    	{
       		LazerEquipment* pTo_lazer3 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot3.insertItem(pTo_lazer3); 
       		//RocketEquipment* rocket3 = rocketEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot3.insertItem(rocket3); 
    	}   
        
    	if (ship->data_korpus.weapon_slot_num >= 4)
    	{
       		LazerEquipment* pTo_lazer4 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot4.insertItem(pTo_lazer4);         
       		//RocketEquipment* rocket4 = rocketEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot4.insertItem(rocket4); 
    	}   
    
    	if (ship->data_korpus.weapon_slot_num >= 5) 
    	{
       		LazerEquipment* pTo_lazer5 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot5.insertItem(pTo_lazer5); 
       		//RocketEquipment* rocket5 = rocketEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot5.insertItem(rocket5); 
    	}   
        
    
    
    	RadarEquipment* pTo_radar = radarEquipmentGenerator(RACE_0_ID);    
    	ship->radar_slot.insertItem(pTo_radar); 
    
   	DriveEquipment* pTo_drive = driveEquipmentGenerator(RACE_0_ID);    
    	ship->drive_slot.insertItem(pTo_drive); 

    	BakEquipment* pTo_bak = bakEquipmentGenerator(RACE_0_ID);    
    	ship->bak_slot.insertItem(pTo_bak); 
            
    	EnergizerEquipment* pTo_energizer = energizerEquipmentGenerator(RACE_0_ID);    
    	ship->energizer_slot.insertItem(pTo_energizer); 
    
    	ProtectorEquipment* pTo_protector = protectorEquipmentGenerator(RACE_0_ID);    
    	ship->protector_slot.insertItem(pTo_protector); 
        
    	DroidEquipment* pTo_droid = droidEquipmentGenerator(RACE_0_ID);    
    	ship->droid_slot.insertItem(pTo_droid); 
    
    
    	FreezerEquipment* pTo_freezer = freezerEquipmentGenerator(RACE_0_ID);    
    	ship->freezer_slot.insertItem(pTo_freezer);     

    	ScanerEquipment* pTo_scaner = scanerEquipmentGenerator(RACE_0_ID);    
    	ship->scaner_slot.insertItem(pTo_scaner); 
    
    	if (ship->data_korpus.inhibit_GRAPPLE == false) 
    	{
       		GrappleEquipment* pTo_grapple = grappleEquipmentGenerator(RACE_0_ID);    
       		ship->grapple_slot.insertItem(pTo_grapple); 
   	}
    
                             
    	for (unsigned int i = 0; i < 3; i++) //pTo_ship->otsec_slot_pList.size(); i++)
    	{        
        	LazerEquipment* pTo_lazer = lazerEquipmentGenerator(RACE_0_ID);              
        	ship->slot_otsec_pList[i]->insertItem(pTo_lazer);
    	}


    	for (unsigned int i = 3; i < 6; i++) //pTo_ship->otsec_slot_pList.size(); i++)
    	{        
        	RadarModule* pTo_radarModule = radarModuleGenerator();              
        	ship->slot_otsec_pList[i]->insertItem(pTo_radarModule);
    	}    
}






Ship* shipGenerator(int race_id, int subtype_id, int size_id)
{
    	TextureOb* texOb_ship = g_TEXTURE_MANAGER.returnPointerToRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 
       
        KorpusData data_korpus;
    	data_korpus.space       = 600;
    	data_korpus.armor       = 600;
    	data_korpus.protection  = 3;
    	data_korpus.temperature = 100;
        data_korpus.price = getRandInt(200, 400);
        
        data_korpus.collision_radius = (texOb_ship->w + texOb_ship->h)/3;

        data_korpus.inhibit_GRAPPLE = false;
        data_korpus.weapon_slot_num = getRandInt(1,5);
            
            
        LifeData data_life;
        data_life.armor = data_korpus.armor;
        data_life.dying_time = 60;
       
        IdData data_id;
        data_id.id      = g_SHIP_ID_GENERATOR.getNextId(); 
    	data_id.type_id = SHIP_ID;
    	//subtype_id = ;       

        int size_threshold = 2; 
    	if (texOb_ship->size_id > size_threshold)
       		data_korpus.render_TURRELS = true; 
    	else
       		data_korpus.render_TURRELS = false; 
                           
    	Ship* ship = new Ship(texOb_ship, data_life, data_id, data_korpus);
    	
    	ship->getPoints()->setCenter(getRandInt(0, 800), getRandInt(0, 800)); 
    	ship->getPoints()->setAngle(getRandInt(0, 360));    	
    	ship->getNavigator()->setStaticTargetCoords(vec2f (1200, 1200));    	
    	    
    	return ship;
}


bool Ship :: repair()
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


void Ship :: dropRandomItemToSpace()
{
	std::vector<ItemSlot*> _equiped_slot_vec;
	
	for (unsigned int i = 0; i<slot_total_pList.size(); i++)
	{
		if (slot_total_pList[i]->getEquipedStatus() == true)
		{
			_equiped_slot_vec.push_back(slot_total_pList[i]);
		}
	}
	
	unsigned int _rand = getRandInt(0, _equiped_slot_vec.size());
	
	_equiped_slot_vec[_rand]->dropItemToSpace();
		
}
