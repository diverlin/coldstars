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


#include "ship.hpp"

void Ship :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void Ship :: setNpc(Npc* _npc)                      { npc_owner = _npc; }
void Ship :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; }

int Ship :: getId() const           { return id; }
int Ship :: getTypeId() const       { return type_id; }
int Ship :: getPlaceTypeId() const  { return place_type_id; } 
bool Ship :: getAliveFlag() const { return is_alive; }
bool* Ship :: get_pAliveFlag() { return &is_alive; }

Points* Ship :: getPoints() 	    { return &points; }
Navigator* Ship :: getNavigator()   { return navigator; }
StarSystem* Ship :: getStarSystem() { return starsystem; }
Npc*  Ship :: getNpc() 		    { return npc_owner; }
                   

                
                
Ship :: Ship(TextureOb* _texOb, KorpusData _korpusData)
{  	
    	is_alive    = true;
    	is_dying    = false;
    	is_explosed = false;

    	navigator = new Navigator(this);  
    
    

    	dying_time = 60;

    	id      = g_ENTITY_ID_GENERATOR.returnNextId(); 
    	type_id = SHIP_ID;
    	//subtype_id = ;


    	texOb = _texOb;
        texOb_korpus = texOb;



    	angle_inD = 0;
   

   	////// Points creation
    	points = Points();

        points.setPosZ(-500.0);
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

    	points.setAngle(randIntInRange(0, 360));
    	points.setCenter(randIntInRange(0, 500), randIntInRange(0, 500)); 

    	//w_orig = texOb->w;
    	//h_orig = texOb->h;


        korpusData = _korpusData;
        propetries.armor      = korpusData.armor;

    	starsystem = NULL; 
    	npc_owner    = NULL;


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
   
    	if (korpusData.weapon_slot_num >= 1)
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
       
       		if (korpusData.render_TURRELS == true)
       		{   
           		points.initWeapon1CenterPoint(0, texOb->h/3);
           		points.addWeapon1CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon1Center());
       		} 
    	}
   
    	if (korpusData.weapon_slot_num >= 2)
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
        
       		if (korpusData.render_TURRELS == true)
       		{  
           		points.initWeapon2CenterPoint(0, -texOb->h/3);
           		points.addWeapon2CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon2Center());
       		}
    	}

    	if (korpusData.weapon_slot_num >= 3)
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
       
       		if (korpusData.render_TURRELS == true)
       		{  
           		points.initWeapon3CenterPoint(-texOb->w/5, texOb->h/3);
           		points.addWeapon3CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon3Center());
       		}
    	}

    	if (korpusData.weapon_slot_num >= 4)
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
         
       		if (korpusData.render_TURRELS == true)
       		{  
           		points.initWeapon4CenterPoint(texOb->w/5, -texOb->h/3);
           		points.addWeapon4CenterPoint();
           		turrel_center_pList.push_back(points.getpWeapon4Center());

       		}

    	}   

    	if (korpusData.weapon_slot_num >= 5)
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
       
       		if (korpusData.render_TURRELS == true)
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
    		
    		
	if (korpusData.inhibit_GRAPPLE == false)
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





   	//TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList);
   	TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);

   	int pNum       = 5;
   	int pSize      = 25;
   	float pVelocity  = 1.2;
   	float pAlphaInit = 0.6;
   	float pAlphaEnd  = 0.0;
   	float pd_alpha   = 0.05;

   	//drive_jet = DriveTrailEffect(TextureOb* _pTo_texOb, float* _pTo_OB_angle_inD, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_target_pos_x, float* _pTo_target_pos_y, int _num_particles, float _size, float _velocity_orig, float _alpha_start, float _alpha_end, float _d_alpha)
   	drive_jet = new DriveTrailEffect(pTo_particleTexOb, 
   					 points.getpAngleDegree(), 
   					 points.getpMidLeft(),  
   					 points.getpMidFarLeft(), 
   					 pNum, 
   					 pSize, 
   					 pVelocity, 
   					 pAlphaInit, 
   					 pAlphaEnd, 
   					 pd_alpha);

   	needsToDo.REPAIR     = false;
   	needsToDo.CHARGE     = false;
   	needsToDo.GETBULLETS = false;
   	needsToDo.BUY        = false;
   	needsToDo.SELL       = false;
   
   	//self.shield_texOb = TEXTURE_MANAGER.returnShieldEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id)
   	TextureOb* _texOb_shield = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shieldEffect_texOb_pList); 
   	shield = new ShieldEffect(this, _texOb_shield);
   	
        weapon_selector.setAll(false);
}



Ship :: ~Ship()
{
     	//for (unsigned int lei = 0; lei < effect_LAZERTRACE_pList.size(); lei++)   
         	//delete effect_LAZERTRACE_pList[lei];
            
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


void Ship :: reloadAllWeapons()
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
        if (korpusData.weapon_slot_num >= 1)
                weapon_slot1.getTurrel()->setSelectedStatus(weapon_selector.slot_1);
        if (korpusData.weapon_slot_num >= 2)
                weapon_slot2.getTurrel()->setSelectedStatus(weapon_selector.slot_2);
        if (korpusData.weapon_slot_num >= 3)
                weapon_slot3.getTurrel()->setSelectedStatus(weapon_selector.slot_3);
        if (korpusData.weapon_slot_num >= 4)
                weapon_slot4.getTurrel()->setSelectedStatus(weapon_selector.slot_4);
        if (korpusData.weapon_slot_num >= 5)
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

    	if (is_dying == true)
    	{
       		dying_time--;
       		if (dying_time < 0)
           		death();
    	}    
}

void Ship :: update_inSpace_inDynamic_FALSE()
{   
    	if (ableTo.DRIVE == true) 
       		updatePosition();
}





//// ******** DOCKING/LAUNCHING ******** 
//bool Ship :: checkDocking()
//{  
     	//if (navigator->checkDocking() == true)
        	//return true;
     	//else    
        	//return false;
//}

//bool Ship :: getDockingPermission()
//{
     	//if (navigator->getDockingPermission() == true) 
        	//return true;
    	//else
        	//return false;
//}

bool Ship :: dockingEvent()
{
     	printf("id = %i, dockingEvent()\n", id);
     	starsystem->removeShipById(id);
     	starsystem->removeNpc(npc_owner->getId(), npc_owner->getRaceId(), npc_owner->getSubTypeId());
     	     	     	
     	if (navigator->getFollowingTypeId() == PLANET_TYPE_ID)
     	{
     		navigator->getTargetPlanet()->addShip(this);
		navigator->getTargetPlanet()->addNpc(npc_owner);
		
		if (navigator->getTargetPlanet()->getSubTypeId() == KOSMOPORT_TYPE_ID)
		{
			npc_owner->setKosmoport(navigator->getTargetPlanet()->getKosmoport());
		}
		
		if (navigator->getTargetPlanet()->getSubTypeId() == LAND_ID)
		{
			npc_owner->setLand(navigator->getTargetPlanet()->getLand());
		}
	}
     	//printf("id = %i, dockingEvent() EEEEENNNNNDDDDD\n", id);
    	return true;
}

bool Ship :: launchingEvent()
{
     	printf("id = %i, launchingEvent()\n", id);

     	starsystem->addShipToSpace(this);
     	starsystem->addNpcToSpace(npc_owner);

     	navigator->getTargetPlanet()->removeShipById(id);
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

//// ******** DOCKING/LAUNCHING ******** 







void Ship :: hit_TRUE(int _damage)
{
    	propetries.armor -= _damage;
    	if (ableTo.PROTECT == true)
       		shield->setAlpha(1.0);

    	if (propetries.armor < 0)
       		is_dying = true; 
}

void Ship :: hit_FALSE(int _damage)
{
    	propetries.armor -= _damage;

    	if (propetries.armor < 0)
       		death();
}


void Ship :: death()
{
     	is_alive = false;   

     	if (is_explosed == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), korpusData.size_id);
        	is_explosed = true;
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
        propetries.protection = korpusData.protection;
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

     	if (korpusData.inhibit_GRAPPLE == false)
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
     	propetries.armor = korpusData.armor;
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
    	info.addNameStr("id/ss_id:");          info.addValueStr( int2str(id) + " / " + int2str(starsystem->getId()) );
    	info.addNameStr("ship/pilot race:");   info.addValueStr( returnRaceStringByRaceId(texOb->race_id) + "/" + returnRaceStringByRaceId(owner_race_id) ); 
    	info.addNameStr("armor/max/size");     info.addValueStr( int2str(propetries.armor) + "/" + int2str(korpusData.armor) + "/" + int2str(korpusData.size_id) );
    	info.addNameStr("space/free/mass:");   info.addValueStr( int2str(korpusData.space) + "/" + int2str(korpusData.space - propetries.mass) + "/" + int2str(propetries.mass) );
    	info.addNameStr("energy:");            info.addValueStr( int2str(propetries.energy) );
	info.addNameStr("temperature:");       info.addValueStr( int2str(korpusData.temperature) );
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
       		return int2str(protector_slot.getProtectorEquipment()->getProtection()) + '+' + int2str(korpusData.protection);
    	else
       		return int2str(korpusData.protection);
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
}


void Ship :: render_inSpace() const
{   
    	renderKorpus();

    	if (ableTo.PROTECT == true)
        	renderShield(); 

    	if (ableTo.DRIVE == true)
    	{
       		drive_jet->update();

       		enable_POINTSPRITE();
       			drive_jet->render();
       		disable_POINTSPRITE();
    	}
}


void Ship :: render_atPlanet() const
{
	renderKorpus();
}		
		
void Ship :: renderKorpus() const
{
   	glBindTexture(GL_TEXTURE_2D, texOb->texture); 
                                  
    	drawFlatQuadPerVertexIn2D(points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
				  points.getPosZ());
                                  
    	if (korpusData.render_TURRELS == true)
        	renderTurrels();
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
    	if (ship->korpusData.weapon_slot_num >= 1)
    	{
       		LazerEquipment* pTo_lazer1 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot1.insertItem(pTo_lazer1); 
    	}   

    	if (ship->korpusData.weapon_slot_num >= 2)
    	{
       		LazerEquipment* pTo_lazer2 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot2.insertItem(pTo_lazer2); 
    	}   
    
    	if (ship->korpusData.weapon_slot_num >= 3)
    	{
       		//LazerEquipment* pTo_lazer3 = lazerGenerator(RACE_0_ID);    
       		//pTo_ship->weapon_slot3.insertLazerEquipment(pTo_lazer3); 
       		RocketEquipment* pTo_rocket3 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot3.insertItem(pTo_rocket3); 
    	}   
        
    	if (ship->korpusData.weapon_slot_num >= 4)
    	{
       		LazerEquipment* pTo_lazer4 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot4.insertItem(pTo_lazer4);         
       		//RocketEquipment* pTo_rocket4 = rocketGenerator(RACE_0_ID);    
       		//(*pTo_ship).weapon_slot4.insertRocketEquipment(pTo_rocket4); 
    	}   
    
    	if (ship->korpusData.weapon_slot_num >= 5) 
    	{
       		LazerEquipment* pTo_lazer5 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->weapon_slot5.insertItem(pTo_lazer5); 
       		//RocketEquipment* pTo_rocket5 = rocketGenerator(RACE_0_ID);    
       		//(*pTo_ship).weapon_slot5.insertRocketEquipment(pTo_rocket5); 
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
    
    	if (ship->korpusData.inhibit_GRAPPLE == false) 
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
       
        KorpusData korpusData;
    	korpusData.space = 600;
    	korpusData.armor  = 600;
    	korpusData.protection  = 3;
    	korpusData.temperature = 100;
        korpusData.price = randIntInRange(200, 400);
        
        korpusData.collision_radius = (texOb_ship->w + texOb_ship->h)/3;
        korpusData.size_id = returnObjectSize(texOb_ship->w, texOb_ship->h);
        korpusData.inhibit_GRAPPLE = false;
        korpusData.weapon_slot_num = randIntInRange(1,5);
            
        int size_threshold = 2; 
    	if (korpusData.size_id > size_threshold)
       		korpusData.render_TURRELS = true; 
    	else
       		korpusData.render_TURRELS = false; 
                           
    	Ship* ship = new Ship(texOb_ship, korpusData);
    
    	return ship;
}
