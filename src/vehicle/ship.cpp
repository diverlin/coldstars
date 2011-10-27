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
bool Ship :: getAlive() const { return data_life.is_alive; }
bool* Ship :: getpAlive()     { return &data_life.is_alive; }
int Ship :: getArmor() const  { return data_life.armor; }

Points* Ship :: getPoints() 	    { return &points; }
Navigator* Ship :: getNavigator()   { return navigator; }
StarSystem* Ship :: getStarSystem() { return starsystem; }
Npc*  Ship :: getNpc() 		    { return npc_owner; }
int Ship :: getCollisionRadius() const  { return data_korpus.collision_radius; } 

                
                
Ship :: Ship(TextureOb* _texOb, LifeData _data_life, IdData _data_id, KorpusData _data_korpus)
{
    	data_life = _data_life;
    	data_id   = _data_id;

    	texOb = _texOb;
        texOb_korpus = texOb;  

   	////// Points creation
    	points = Points();

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
       					
       		slot_weapon_pList.push_back(&weapon_slot1);
       		slot_total_pList.push_back(&weapon_slot1); 
       
       		turrel1.placed(points.getpWeapon1Center());
       		turrel1.bindSlot(&weapon_slot1);
       		weapon_slot1.bindTurrel(&turrel1);
       		turrel1.setTexOb(turrelTexOb); // remove
       
       		if (data_korpus.render_TURRELS == true)
       		{   
           		points.initWeapon1CenterPoint(0, texOb->h/3);
           		points.addWeapon1CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon1Center());
       		} 
    	}
   
    	if (data_korpus.weapon_slot_num >= 2)
    	{  
       		weapon_slot2 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
       					    
       		slot_weapon_pList.push_back(&weapon_slot2);
       		slot_total_pList.push_back(&weapon_slot2); 
       
       		turrel2.placed(points.getpWeapon2Center());
       		turrel2.bindSlot(&weapon_slot2);
              	weapon_slot2.bindTurrel(&turrel2);
       		turrel2.setTexOb(turrelTexOb);
        
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon2CenterPoint(0, -texOb->h/3);
           		points.addWeapon2CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon2Center());
       		}
    	}

    	if (data_korpus.weapon_slot_num >= 3)
    	{  
       		weapon_slot3 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h); 
       					
       		slot_weapon_pList.push_back(&weapon_slot3);
       		slot_total_pList.push_back(&weapon_slot3); 
              
       		turrel3.placed(points.getpWeapon3Center());  
       		turrel3.bindSlot(&weapon_slot3);
              	weapon_slot3.bindTurrel(&turrel3);
       		turrel3.setTexOb(turrelTexOb);
       
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon3CenterPoint(-texOb->w/5, texOb->h/3);
           		points.addWeapon3CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon3Center());
       		}
    	}

    	if (data_korpus.weapon_slot_num >= 4)
    	{  
       		weapon_slot4 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
       					
       		slot_weapon_pList.push_back(&weapon_slot4);
       		slot_total_pList.push_back(&weapon_slot4); 
              
       		turrel4.placed(points.getpWeapon4Center());
       		turrel4.bindSlot(&weapon_slot4);
              	weapon_slot4.bindTurrel(&turrel4);
       		turrel4.setTexOb(turrelTexOb);
         
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon4CenterPoint(texOb->w/5, -texOb->h/3);
           		points.addWeapon4CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon4Center());

       		}

    	}   

    	if (data_korpus.weapon_slot_num >= 5)
    	{  
       		weapon_slot5 = ItemSlot(WEAPON_SLOT_ID, 
       					this, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*texOb_slot->w, 
       					kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
       					
       		slot_weapon_pList.push_back(&weapon_slot5);
       		slot_total_pList.push_back(&weapon_slot5); 
              
       		turrel5.placed(points.getpWeapon5Center());
       		turrel5.bindSlot(&weapon_slot5);
              	weapon_slot5.bindTurrel(&turrel5);
       		turrel5.setTexOb(turrelTexOb);
       
       		if (data_korpus.render_TURRELS == true)
       		{  
           		points.initWeapon5CenterPoint(-texOb->w/3, -texOb->h/3);
           		points.addWeapon5CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon5Center());
       		}
    	} 
    	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//////////// EQUPMENT SLOT ////////////////////////
	drive_slot       = ItemSlot(DRIVE_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&drive_slot);
	
	
	bak_slot         = ItemSlot(BAK_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 5*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&bak_slot);
	
	
	radar_slot       = ItemSlot(RADAR_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&radar_slot);	
	
	
	scaner_slot      = ItemSlot(SCANER_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x + 4*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h/2);
				    
	slot_total_pList.push_back(&scaner_slot);
	
	
	energizer_slot   = ItemSlot(ENERGIZER_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 2*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2);
				    
    	slot_total_pList.push_back(&energizer_slot);
    		
    		
	if (data_korpus.inhibit_GRAPPLE == false)
	{
		grapple_slot  = ItemSlot(GRAPPLE_ID, 
					 this, 
					 texOb_slot, 
					 kontur_rect.getCenter().x - 3*texOb_slot->w, 
					 kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
					 
    		slot_total_pList.push_back(&grapple_slot); 
    	}
    	
    	
	protector_slot   = ItemSlot(PROTECTOR_ID, 
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 3*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h);
				    
    	slot_total_pList.push_back(&protector_slot); 
	
	
	droid_slot       = ItemSlot(DROID_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 + 1.1*texOb_slot->h);
				    
    	slot_total_pList.push_back(&droid_slot); 
    	
    	
	freezer_slot     = ItemSlot(FREEZER_ID,
				    this, 
				    texOb_slot, 
				    kontur_rect.getCenter().x - 1*texOb_slot->w, 
				    kontur_rect.getCenter().y - texOb_slot->h/2 - 1.1*texOb_slot->h);
				    
	slot_total_pList.push_back(&freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* pTo_otsec_slot = new ItemSlot(UNIVERSAL_SLOT_ID, 
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
	delete drive_trail;
	delete shield;
	
	for (unsigned int i = 0; i < slot_otsec_pList.size(); i++)
    	{
		delete slot_otsec_pList[i];  
    	}
} 


//void Ship :: calculateWayToCoord(float _pos_x, float _pos_y)
//{    
//    setTargetPosCoord(_pos_x, _pos_y);
//    calculateDetaledWayToPosition();  // under constraction
    //calculateTurnWayToPosition();     // remove (perform if ship is selected by cursor)
    //calculateWayVisualisation();      // remove (perform if ship is selected by cursor)
//}


    
void Ship :: updatePosition()
{
        navigator->updatePosition();
}


void Ship :: reloadWeapons()
{
     	// reload wepons
     	// used once at the beginning of turn

     	//reloaded_weapon_pList.clear();
     	slot_weapon_reloaded_pList.clear();
     	for (unsigned int i = 0; i < slot_weapon_equiped_pList.size(); i++)
         	if (slot_weapon_equiped_pList[i]->getTurrel()->isAmmoAvailable() == true)
             		slot_weapon_reloaded_pList.push_back(slot_weapon_equiped_pList[i]);
            
     	fire_delay = 10;
     	d_fire_delay = 40;   // 0;
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


template <typename TARGET_TYPE> 
void Ship :: setWeaponsTarget(TARGET_TYPE* _target)
{                          
        float dist = distBetweenCenters(points.getCenter(), _target->getPoints()->getCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_pList.size(); i++)
        {
        	if ( slot_weapon_equiped_pList[i]->getTurrel()->getSelectedStatus() == true )
        	{
           		if ( slot_weapon_equiped_pList[i]->getTurrel()->getHasTargetStatus() == false )
           		{
           	      		if ( dist < slot_weapon_equiped_pList[i]->getItemRadius() )
           	      		{
                       			slot_weapon_equiped_pList[i]->getTurrel()->setTarget(_target);
                       		}
                       	}
                } 
        }               

}



void Ship :: weaponsFire_TRUE(int timer)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (unsigned int i = 0; i < slot_weapon_reloaded_pList.size(); i++)
        	{	
           		if ( slot_weapon_reloaded_pList[i]->getTurrel()->fireCheck() == true )
           		{	
               			if ( slot_weapon_reloaded_pList[i]->getTurrel()->fireEvent_TRUE() == true )
               			{
                   			slot_weapon_reloaded_pList.erase(slot_weapon_reloaded_pList.begin() + i);
                   			fire_delay += d_fire_delay;
                   			break;
               			}
            			else
            			{
               				slot_weapon_reloaded_pList.erase(slot_weapon_reloaded_pList.begin() + i);
               				break;
            			}
            		}
        	}
        }
}


void Ship :: weaponsFire_FALSE(int timer)
{
        weaponsFire_TRUE(timer);
}




void Ship :: resetDeselectedWeaponTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_pList.size(); i++)
        {
            	if (slot_weapon_equiped_pList[i]->getTurrel()->getSelectedStatus() == false)
            	{
                	slot_weapon_equiped_pList[i]->getTurrel()->resetTarget();
                }
        }
}


void Ship :: removeWeaponSlotDeadTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_pList.size(); i++)
        {
                if (slot_weapon_equiped_pList[i]->getTurrel()->getHasTargetStatus() == true)
                {
                        if (slot_weapon_equiped_pList[i]->getTurrel()->isTargetAlive() == false)
                        {
                                slot_weapon_equiped_pList[i]->getTurrel()->resetTarget();
                        }
                }
       }       
}



ItemSlot* Ship :: return_pToEmptyOtsecSlot()
{
      	for (unsigned int si = 0; si < slot_otsec_pList.size(); si++)
      	{
          	if (slot_otsec_pList[si]->getEquipedStatus() == false)
             		return slot_otsec_pList[si];
        }
        
      	return NULL;
}


void Ship :: update_inSpace_inDynamic_TRUE()
{   
    	if (ableTo.DRIVE == true) 
    	{ 
       		updatePosition();
    	}
    
    	//for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)   // moved to ship
       		//effect_LAZERTRACE_pList[i]->update(); 

    	if (data_life.is_dying == true)
    	{
       		data_life.dying_time--;
       		if (data_life.dying_time < 0)
           		death_TRUE();
    	}    
}

void Ship :: update_inSpace_inDynamic_FALSE()
{   
    	if (ableTo.DRIVE == true) 
       		updatePosition();
}





//// ******** DOCKING/LAUNCHING ******** 
bool Ship :: jumpingEvent()
{
        printf("ship id = %i, jumpingEvent()\n", data_id.id);
        starsystem->removeShip(data_id.id);  
        starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());  
                                                        
        navigator->getTargetStarSystem()->addToHyperJumpQueue(npc_owner);        
}
                
                
bool Ship :: dockingEvent()
{
     	printf("ship id = %i, dockingEvent()\n", data_id.id);
     	starsystem->removeShip(data_id.id);
     	starsystem->removeNpc(npc_owner->getId(), npc_owner->getSubTypeId());
        
             	     	     	
     	if (navigator->getFollowingTypeId() == PLANET_ID)
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
     	navigator->removeTarget();
     	
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
       		data_life.is_dying = true;
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
       		death_FALSE();
       	}
}


void Ship :: death_TRUE()
{
     	data_life.is_alive = false;   

     	if (data_life.is_explosed == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);
        	data_life.is_explosed = true;
     	}
}

void Ship :: death_FALSE()
{
     	data_life.is_alive = false;   

     	if (data_life.is_explosed == false)
     	{   
        	data_life.is_explosed = true;
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
     	slot_weapon_equiped_pList.clear();

     	int sum_damage = 0;
     	int sum_fire_radius = 0;

     	for (unsigned int i = 0; i < slot_weapon_pList.size(); i++)
     	{ 
        	if (slot_weapon_pList[i]->getEquipedStatus() == true)
        	{
           		if (slot_weapon_pList[i]->getItemCondition() > 0)
           		{
              			slot_weapon_equiped_pList.push_back(slot_weapon_pList[i]);
              			sum_damage      += slot_weapon_pList[i]->getItemDamage(); 
              			sum_fire_radius += slot_weapon_pList[i]->getItemRadius(); 
           		}
           	}
     	}

     	if (slot_weapon_equiped_pList.size() != 0)
     	{
        	propetries.average_fire_radius = sum_fire_radius/slot_weapon_equiped_pList.size();
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

    	//////////////// WEAPON SLOT ////////////////////////
     	//for (unsigned int i = 0; i < weapon_slot_pList.size(); i++)
     	//{ 
        	//if (weapon_slot_pList[i]->is_EQUIPED == true)
           		//mass += weapon_slot_pList[i]->returnEquipedItemMass(); 
     	//}



    	////////////// EQUPMENT SLOT ////////////////////////
    	//if (drive_slot.is_EQUIPED == true)
       		//mass += drive_slot.pTo_driveEquipment->mass;

    	//if (bak_slot.is_EQUIPED == true)
       		//mass += bak_slot.pTo_bakEquipment->mass;

    	//if (radar_slot.is_EQUIPED == true)
       		//mass += radar_slot.pTo_radarEquipment->mass;

    	//if (scaner_slot.is_EQUIPED == true)
       		//mass += scaner_slot.pTo_scanerEquipment->mass;

    	//if (energizer_slot.is_EQUIPED == true)
       		//mass += energizer_slot.pTo_energizerEquipment->mass;

    	//if (inhibit_GRAPPLE == false)
       		//if (grapple_slot.is_EQUIPED == true)
          		//mass += grapple_slot.pTo_grappleEquipment->mass;

    	//if (protector_slot.is_EQUIPED == true)
       		//mass += protector_slot.pTo_protectorEquipment->mass;

    	//if (droid_slot.is_EQUIPED == true)
       		//mass += droid_slot.pTo_droidEquipment->mass;

    	//if (freezer_slot.is_EQUIPED == true)
       		//mass += freezer_slot.pTo_freezerEquipment->mass;


    	//////// OTSEC SLOT ////////////////////////////////
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

    	int owner_race_id = npc_owner->getRaceId();

    	info.addTitleStr("SHIP");
    	info.addNameStr("id/npc_id/ss_id:");   info.addValueStr( int2str(data_id.id) + " / " + int2str(npc_owner->getId()) + " / " + int2str(starsystem->getId()) );
    	info.addNameStr("ship/pilot race:");   info.addValueStr( returnRaceStringByRaceId(texOb->race_id) + "/" + returnRaceStringByRaceId(owner_race_id) ); 
    	info.addNameStr("armor/max/size");     info.addValueStr( int2str(data_life.armor) + "/" + int2str(data_korpus.armor) + "/" + int2str(texOb->size_id) );
    	info.addNameStr("space/free/mass:");   info.addValueStr( int2str(data_korpus.space) + "/" + int2str(data_korpus.space - propetries.mass) + "/" + int2str(propetries.mass) );
    	info.addNameStr("energy:");            info.addValueStr( int2str(propetries.energy) );
	info.addNameStr("temperature:");       info.addValueStr( int2str(data_korpus.temperature) );
        info.addNameStr("observe radius:");    info.addValueStr( int2str(propetries.radius) );
    	info.addNameStr("protection:");        info.addValueStr( returnProtectionStr() );
	info.addNameStr("speed x 100:");       info.addValueStr(int2str(int(propetries.speed*100)) );
	
	


    	//info_pList.push_back(&str5);
    	//if self.name != 'plr':
       		//self.info.append(self.returnCurTaskStr(self.task_id_being_exec))   # debug
       		//self.info.append(self.returnQuestTaskListStr())                    # debug
       		//self.info.append(self.returnNeedsTaskListStr())                    # debug
}


   //def returnQuestTaskListStr(self):
        //str = 'QTL: '
        //for task in self.QUEST_TASK_queue:
            //str += self.returnCurTaskStr(task) + ";   "
        //return str

    //def returnNeedsTaskListStr(self):
        //str = 'NTL: '
        //for task in self.NEEDS_TASK_queue:
            //str += self.returnCurTaskStr(task) + ";   "
        //return str

    //def returnCurTaskStr(self, task_id):
        //if task_id == HYPER_JUMP_task_id:
           //return 'HYPER_JUMP_to_' + self.returnTargetSsnameStr()
        //elif task_id == DESTROY_ALIEN_task_id:
             //return 'DESTROY_ALIEN_task_id'
        //elif task_id == LANDING_task_id:
             //return 'LANDING_task_id'
        //elif task_id == LAUNCHING_task_id:
             //return 'LAUNCHING_task_id'
        //elif task_id == AREST_REQUEST_task_id:
             //return 'AREST_REQUEST_task_id'
        //elif task_id == TERROR_REQUEST_task_id:
             //return 'TERROR_REQUEST_task_id'
        //elif task_id == FIRE_LOW_task_id:
             //return 'FIRE_LOW_task_id'
        //elif task_id == FIRE_HIGH_task_id:
             //return 'FIRE_HIGH_task_id'
        //elif task_id == FIND_PLACE_TO_SELL_GOODS_task_id:
             //return 'FIND_PLACE_TO_SELL_GOODS_task_id'
        //elif task_id == BUY_GOODS_task_id:
             //return 'BUY_GOODS_task_id'
        //elif task_id == SELL_GOODS_task_id:
             //return 'SELL_GOODS_task_id'
        //elif task_id == GRABBING_MINERAL_task_id:
             //return 'GRABBING_MINERAL_task_id, items:' + str(len(self.korpus.grapple_slot.item.grapple_list))
        //elif task_id == GRABBING_CONTAINER_task_id:
             //return 'GRABBING_CONTAINER_task_id, items:'+ str(len(self.korpus.grapple_slot.item.grapple_list))
        //elif task_id == None:
             //return 'None'
        //else:
             //return 'unknown'

    //def returnTargetSsnameStr(self):
        //if self.target_starsystem != None:
           //return self.target_starsystem.name
        //else:
           //return ''

    //def returnTypeStr(self):
        //if self.subtype == RANGER_ID:
           //if self.subsubtype == WARRIOR_ID:
              //return 'ranger-warrior'
           //elif self.subsubtype == PIRAT_ID:
                //return 'ranger-pirat'
           //elif self.subsubtype == TRADER_ID:
                //return 'ranger-trader'
           //elif self.subsubtype == DIPLOMAT_ID:
                //return 'ranger-diplomat'

           //else:
                //return "ranger-unknown"

        //elif self.subtype == WARRIOR_ID:
             //return 'warrior'
        //elif self.subtype == PIRAT_ID:
             //return 'pirat'
        //elif self.subtype == TRADER_ID:
             //return 'trader'
        //elif self.subtype == DIPLOMAT_ID:
             //return 'diplomat'

        //else:
             //return "unknown"


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
}

void Ship :: renderInfo()
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
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
    	for(unsigned int i = 0; i < slot_weapon_equiped_pList.size(); i++)
    	{
        	float tur_angle_inD;
        	if (slot_weapon_equiped_pList[i]->getTurrel()->getHasTargetStatus() == true)
        	{
              		float tur_xl = (*(slot_weapon_equiped_pList[i]->getTurrel()->getTarget_pCenterX())) - (turrel_center_pList[i]->x);
              		float tur_yl = (*(slot_weapon_equiped_pList[i]->getTurrel()->getTarget_pCenterY())) - (turrel_center_pList[i]->y);

              		float tur_angle_inR = atan2(tur_yl, tur_xl);
              		tur_angle_inD = tur_angle_inR * RADIAN_TO_DEGREE_RATE;
        	}
        	else
        	{
        		tur_angle_inD = points.getAngleDegree();
        	} 

		//printf("xy target =%f,%f\n", turrel_center_pList[i]->x, turrel_center_pList[i]->y);
		//slot_weapon_equiped_pList[i]->getTurrel()->updatePosition(200, 200, tur_angle_inD); 
        	slot_weapon_equiped_pList[i]->getTurrel()->updatePosition(turrel_center_pList[i]->x, turrel_center_pList[i]->y, tur_angle_inD); 
        	slot_weapon_equiped_pList[i]->getTurrel()->render();        
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
        for (unsigned int wi = 0; wi < slot_weapon_pList.size(); wi++)
        {
                Turrel* _turrel = slot_weapon_pList[wi]->getTurrel();
                if (_turrel->getHasTargetStatus() == true)
                {       
                        Rect _rect(*_turrel->getTarget_pCenterX() - 40/2 + 23*offset, *_turrel->getTarget_pCenterY() + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_pList[wi]->getItemTexOb()->texture, _rect, -2.0);
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
       		//LazerEquipment* pTo_lazer3 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot3.insertItem(pTo_lazer3); 
       		RocketEquipment* rocket3 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot3.insertItem(rocket3); 
    	}   
        
    	if (ship->data_korpus.weapon_slot_num >= 4)
    	{
       		//LazerEquipment* pTo_lazer4 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot4.insertItem(pTo_lazer4);         
       		RocketEquipment* rocket4 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot4.insertItem(rocket4); 
    	}   
    
    	if (ship->data_korpus.weapon_slot_num >= 5) 
    	{
       		//LazerEquipment* pTo_lazer5 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot5.insertItem(pTo_lazer5); 
       		RocketEquipment* rocket5 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot5.insertItem(rocket5); 
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
    
    	return ship;
}


bool Ship :: repair()
{
        int _fix = data_korpus.armor - data_life.armor;
        int _price = _fix/10;
        
        if (npc_owner->getCredits() > _price)
        {
                data_life.armor = data_korpus.armor;
                npc_owner->removeCredits(_price);
                return true;  
        }
        
        return false;        
}
