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


#include "shipInternal.hpp"

ShipInternal :: ShipInternal()
{
     pTo_increment_attack_button   = NULL;  
     pTo_decrement_attack_button   = NULL;  
                
     pTo_increment_defence_button  = NULL;  
     pTo_decrement_defence_button  = NULL;  
        
     pTo_increment_leader_button   = NULL;  
     pTo_decrement_leader_button   = NULL; 
      
     pTo_increment_trader_button   = NULL;  
     pTo_decrement_trader_button   = NULL; 
    
     pTo_increment_technic_button  = NULL;  
     pTo_decrement_technic_button  = NULL; 
     
     pTo_increment_diplomat_button = NULL;  
     pTo_decrement_diplomat_button = NULL;
}

ShipInternal :: ~ShipInternal()
{}


void ShipInternal :: bindShip(Ship* _ship)
{
     	ship = _ship;
}

void ShipInternal :: bindSkill(Skill* _skill)
{
     	skill = _skill;
     	createControlSkillButtons();
}

void ShipInternal :: createControlSkillButtons()
{
     int x = 10; //self.korpus.kontur_rect.right
     int y = 50; //self.korpus.kontur_rect.centery
     int w = 20;  //skill_w

     TextureOb* pTo_plus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
     TextureOb* pTo_minus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);

     pTo_increment_attack_button   = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x, y - w,   w, w, "");  
     pTo_decrement_attack_button   = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x, y - 2*w, w, w, "");  
                
     pTo_increment_defence_button  = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x + w, y - w,   w, w, "");  
     pTo_decrement_defence_button  = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x + w, y - 2*w, w, w, "");  
        
     pTo_increment_leader_button   = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x + 2*w, y - w,   w, w, "");  
     pTo_decrement_leader_button   = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x + 2*w, y - 2*w, w, w, ""); 
      
     pTo_increment_trader_button   = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x + 3*w, y - w,   w, w, "");  
     pTo_decrement_trader_button   = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x + 3*w, y - 2*w, w, w, ""); 
    
     pTo_increment_technic_button  = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x + 4*w, y - w,   w, w, "");  
     pTo_decrement_technic_button  = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x + 4*w, y - 2*w, w, w, ""); 
     
     pTo_increment_diplomat_button = new Button(pTo_plus_texOb, INCREMENT_BUTTON_ID, x + 5*w, y - w,   w, w, "");  
     pTo_decrement_diplomat_button = new Button(pTo_minus_texOb, DECREMENT_BUTTON_ID, x + 5*w, y - 2*w, w, w, "");
}

void ShipInternal :: manageSkill(bool allow_full_control)
{
     bool CURSOR_INTERSECT_OBJECT = false;

     int mxvp = g_MOUSE_POS_X;
     int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     int lmb  = g_MOUSE_LEFT_BUTTON;


     //### ATTACK
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_attack_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementAttack();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_attack_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementAttack();
           }
        }
     }
     //### ATTACK


     //### DEFENCE
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_defence_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementDefence();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_defence_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementDefence();
           }
        }
     }
     //### DEFENCE


     //### LEADER 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_leader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementLeader();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_leader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementLeader();
           }
        }
     }
     //### LEADER 



     //### TRADER 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_trader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementTrader();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_trader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementTrader();
           }
        }
     }
     //### TRADER 



     //### TECHNIC 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_technic_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementTechnic();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_technic_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementTechnic();
           }
        }
     }
     //### TECHNIC 



     //### DIPLOMAT 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_diplomat_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->incrementDiplomat();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_diplomat_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               skill->decrementDiplomat();
           }
        }
     }
     //### DIPLOMAT 
}

void ShipInternal :: renderSkill()
{
     int w = 15;
     int h = 15;

     for (int i = 0; i < skill->getAttack(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_attack_button->getRect().getCenter().x - 10, 
         		      pTo_increment_attack_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_attack_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_attack_button->render();
     pTo_decrement_attack_button->render();
                    
     for (int i = 0; i < skill->getDefence(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_defence_button->getRect().getCenter().x - 10, 
         		      pTo_increment_defence_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_defence_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_defence_button->render();
     pTo_decrement_defence_button->render();

     for (int i = 0; i < skill->getLeader(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_leader_button->getRect().getCenter().x - 10, 
         		      pTo_increment_leader_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_leader_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_leader_button->render();
     pTo_decrement_leader_button->render();
        
     for (int i = 0; i < skill->getTrader(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_trader_button->getRect().getCenter().x - 10, 
         		      pTo_increment_trader_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_trader_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_trader_button->render();
     pTo_decrement_trader_button->render();
        
     for (int i = 0; i < skill->getTechnic(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_technic_button->getRect().getCenter().x - 10, 
         		      pTo_increment_technic_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_technic_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_technic_button->render();
     pTo_decrement_technic_button->render();
                    
     for (int i = 0; i < skill->getDiplomat(); i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_diplomat_button->getRect().getCenter().x - 10, 
         		      pTo_increment_diplomat_button->getRect().getCenter().y + i*h, 
         		      w, h);
         drawTexturedRect(pTo_increment_diplomat_button->getTexOb()->texture, tmp_rect, -1.0);
     }
     pTo_increment_diplomat_button->render();
     pTo_decrement_diplomat_button->render();
}












void ShipInternal :: resetSlotsRenderInfoFlag()
{
    	for(std::vector<ItemSlot*>::iterator it = ship->slot_total_pList.begin(); it != ship->slot_total_pList.end(); it++)
    	{ 
       		(*it)->setCursoredStatus(false);
    	}
   
    	ship->gate_slot.setCursoredStatus(false);
}






void ShipInternal :: mouseControl(bool allow_full_control, bool in_store)
{
    bool lmb = g_MOUSE_LEFT_BUTTON; 
    bool rmb = g_MOUSE_RIGHT_BUTTON; 

    bool cursor_has_target = false;

    Store* pTo_store = NULL;     // move to ship class             
    if (in_store == true) 
       pTo_store = ship->getNpc()->getKosmoport()->pTo_store;    // this is used only for player


    resetSlotsRenderInfoFlag();

    //// WEAPON SLOT
    //for (unsigned int i = 0; i < pTo_ship->weapon_slot_pList.size(); i++)
    //{ 
        //if (pTo_ship->weapon_slot_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
        //{  
            //pTo_ship->weapon_slot_pList[i]->is_CURSORED = true;
            //cursor_has_target = true;
  
            //if (pTo_ship->weapon_slot_pList[i]->is_EQUIPED == true)      
            //{   // SLOT IS EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) ) 
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item 
                        //if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_lazerEquipment);
                            //pTo_ship->weapon_slot_pList[i]->removeLazerEquipment();
                        //}

                        //if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_rocketEquipment);
                            //pTo_ship->weapon_slot_pList[i]->removeRocketEquipment();
                        //} 
                    //}
                    //else  
                    //{   // merge module with item                    
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
                        //{
                            //if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ID)
                            //{
                                //if (pTo_ship->weapon_slot_pList[i]->pTo_lazerEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_lazerModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}   

                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                        //{
                            //if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ID)
                            //{
                                //if (pTo_ship->weapon_slot_pList[i]->pTo_rocketEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_rocketModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}                         
                    //}
                //}
                
                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyWeaponSlotItem(pTo_ship->weapon_slot_pList[i]);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 
            //}  

            
            //else                              
            //{   // SLOT IS EMPTY     
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item 
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
                        //{
                            //pTo_ship->weapon_slot_pList[i]->insertLazerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_lazerEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                        //{
                            //pTo_ship->weapon_slot_pList[i]->insertRocketEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_rocketEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}                     
                    //} 
                //}    
            //}

           
        //}
    //}



	// TOTAL SLOT START
	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{ 
		if (ship->slot_total_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
		{  
			ship->slot_total_pList[i]->setCursoredStatus(true);
			cursor_has_target = true;

			if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
			{				
				//// TAKE ITEM from SLOT ////
				if ( (ship->slot_total_pList[i]->getEquipedStatus() == true) && (pTo_CURSOR->getSlot()->getEquipedStatus() == false))
				{ 
					// equipments
                       			if (ship->slot_total_pList[i]->getItemType() == EQUIPMENT_ID)
                       			{
                       				if (ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getLazerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getRocketEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       			
                       				if (ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getRadarEquipment()) == true)
                       					{
                       						ship->slot_total_pList[i]->removeItem();
                       					}
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getDriveEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getBakEquipment()) == true)
                      						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getEnergizerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                      					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getProtectorEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getDroidEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getFreezerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getScanerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getGrappleEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
               				}
                     	
                       			// modules
                       			if (ship->slot_total_pList[i]->getItemType() == MODULE_ID)
                       			{
                       				if (ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                    					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getLazerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                      				{
                      					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getRocketModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getRadarModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                 					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getDriveModule()) == true)
                      						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                      					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getBakModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                      				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getEnergizerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getProtectorModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                    				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getDroidModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getFreezerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getScanerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pTo_CURSOR->getSlot()->insertItem(ship->slot_total_pList[i]->getGrappleModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       			}
                        	
                       			// artifacts
                       			// bomb
               			}
				//// PUT ITEM to SLOT ////
				else if ( (ship->slot_total_pList[i]->getEquipedStatus() == false) && (pTo_CURSOR->getSlot()->getEquipedStatus() == true) )
				{
                                        // weapons                                      
					if ( (ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pTo_CURSOR->getSlot()->getItemType() == EQUIPMENT_ID)
						{      
                                                        if (pTo_CURSOR->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if ( ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getLazerEquipment()) );
                                                                        pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == ROCKET_ID)
							{
								ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getRocketEquipment());
								pTo_CURSOR->getSlot()->removeItem();
							}                                                       
                                                }
                                        }
                                        
                                        // equipment(except weapons)        
					if ( (ship->slot_total_pList[i]->getSubType() == pTo_CURSOR->getSlot()->getItemSubType()) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pTo_CURSOR->getSlot()->getItemType() == EQUIPMENT_ID)
						{       
							if (pTo_CURSOR->getSlot()->getItemSubType() == RADAR_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getRadarEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}	
							if (pTo_CURSOR->getSlot()->getItemSubType() == DRIVE_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getDriveEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == BAK_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getBakEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == ENERGIZER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getEnergizerEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == PROTECTOR_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getProtectorEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == DROID_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getDroidEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == FREEZER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getFreezerEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == SCANER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getScanerEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
							if (pTo_CURSOR->getSlot()->getItemSubType() == GRAPPLE_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getGrappleEquipment()) == true)
									pTo_CURSOR->getSlot()->removeItem();
							}
						}
					
						// modules	
						if (pTo_CURSOR->getSlot()->getItemType() == MODULE_ID)
						{
                        				if (pTo_CURSOR->getSlot()->getItemSubType() == LAZER_ID)
       	                				{
               	            					if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getLazerModule()) == true)
                       	    						pTo_CURSOR->getSlot()->removeItem();
                       					}
                       					if (pTo_CURSOR->getSlot()->getItemSubType() == ROCKET_ID)
                       					{
                            					if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getRocketModule()) == true)
       	                    						pTo_CURSOR->getSlot()->removeItem();
               	        				}
                       					if (pTo_CURSOR->getSlot()->getItemSubType() == RADAR_ID)
                       					{ 
                       						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getRadarModule()) == true)
                      							pTo_CURSOR->getSlot()->removeItem();
                       					}
	                   	  			if (pTo_CURSOR->getSlot()->getItemSubType() == DRIVE_ID)
               	        				{
                       	    					if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getDriveModule()) == true)
                       							pTo_CURSOR->getSlot()->removeItem();
               		 				}
      		        	  			if (pTo_CURSOR->getSlot()->getItemSubType() == BAK_ID)
                      					{
                      						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getBakModule()) == true)
                       							pTo_CURSOR->getSlot()->removeItem();
                      					}
               	        				if (pTo_CURSOR->getSlot()->getItemSubType() == ENERGIZER_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getEnergizerModule()) == true)
                       							pTo_CURSOR->getSlot()->removeItem();
                      					}
              		       				if (pTo_CURSOR->getSlot()->getItemSubType() == PROTECTOR_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getProtectorModule()) == true)
                       							pTo_CURSOR->getSlot()->removeItem();
                      					}
              		      				if (pTo_CURSOR->getSlot()->getItemSubType() == DROID_ID)
                      					{
                       						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getDroidModule()) == true)
                       							pTo_CURSOR->getSlot()->removeItem();
                       					}
              		      				if (pTo_CURSOR->getSlot()->getItemSubType() == FREEZER_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getFreezerModule()) == true)
                            						pTo_CURSOR->getSlot()->removeItem();
                        				}
							if (pTo_CURSOR->getSlot()->getItemSubType() == SCANER_ID)
                        				{
                            					if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getScanerModule()) == true)
                            						pTo_CURSOR->getSlot()->removeItem();
                        				}		
                        				if (pTo_CURSOR->getSlot()->getItemSubType() == GRAPPLE_ID)
                        				{
                            					if (ship->slot_total_pList[i]->insertItem(pTo_CURSOR->getSlot()->getGrappleModule()) == true)
                            						pTo_CURSOR->getSlot()->removeItem();
                        				}
                        			}
                        			// artifacts
                        			// bomb                     			
                    			} 
                		} //// PUT ITEM to SLOT ////
                		//// MERGE MODULE WITH EQUIPMENT ////
                		if ( (ship->slot_total_pList[i]->getEquipedStatus() == true) && (pTo_CURSOR->getSlot()->getEquipedStatus() == true) )
                		{	
					if (pTo_CURSOR->getSlot()->getItemType() == MODULE_ID) 
					{                                               
						if ( (ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
						{   
							if (pTo_CURSOR->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if (ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pTo_CURSOR->getSlot()->getLazerModule()) == true)
								{
									pTo_CURSOR->getSlot()->removeItem();
								}    
							}
                                                }

						if (pTo_CURSOR->getSlot()->getItemSubType() == ship->slot_total_pList[i]->getItemSubType())
						{   
							if (pTo_CURSOR->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if (ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pTo_CURSOR->getSlot()->getLazerModule()) == true)
								{
									pTo_CURSOR->getSlot()->removeItem();
								}    
							}

		
							if (pTo_CURSOR->getSlot()->getItemSubType() == RADAR_ID)
							{
								if (ship->slot_total_pList[i]->getRadarEquipment()->insertModule(pTo_CURSOR->getSlot()->getRadarModule()) == true)
								{
									pTo_CURSOR->getSlot()->removeItem();
								}    
							}
						}  

					
					}               		
                		
                		}             		
                		    
            		}
			// SELL ITEM TO STORE //
			else if ( (lmb == true) && (in_store == true) )
			{
				int earn_price = pTo_store->buyOtsecSlotItem(ship->slot_total_pList[i]);
				pTo_PLAYER->pTo_npc->addCredits(earn_price);
			} 


       		}
        	
        }
                    



            
            
            

	// GATE SLOT
	if (cursor_has_target == false)
	{
		if (ship->gate_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
		{
			ship->gate_slot.setCursoredStatus(true);
			cursor_has_target = true;

			//// DROP ITEM TO OUTERSPACE ////
			if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
			{
				if (pTo_CURSOR->getSlot()->getEquipedStatus() == true)
				{
					Container* _container = createContainer( ship->getPoints()->getCenter() );
										 
					if (pTo_CURSOR->getSlot()->getItemSubType() == LAZER_ID)
					{     
                      				_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getLazerEquipment()); 
                      				pTo_CURSOR->getSlot()->removeItem();
                  			}
					if (pTo_CURSOR->getSlot()->getItemSubType() == ROCKET_ID)
					{             
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getRocketEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();  
					}

					if (pTo_CURSOR->getSlot()->getItemSubType() == RADAR_ID)
					{                      
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getRadarEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == DRIVE_ID)
					{               
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getDriveEquipment()); 
						pTo_CURSOR->getSlot()->removeItem(); 
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == BAK_ID)
					{                      
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getBakEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == ENERGIZER_ID)
					{       
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getEnergizerEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();              
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == PROTECTOR_ID)
					{            
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getProtectorEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();         
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == DROID_ID)
					{          
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getDroidEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();          
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == FREEZER_ID)
					{                  
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getFreezerEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();   
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == SCANER_ID)
					{      
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getScanerEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();            
					}
					if (pTo_CURSOR->getSlot()->getItemSubType() == GRAPPLE_ID)
					{                     
						_container->otsec_slot->insertItem(pTo_CURSOR->getSlot()->getGrappleEquipment()); 
						pTo_CURSOR->getSlot()->removeItem();
					}
					ship->getStarSystem()->addContainer(_container); 
				} 
			}
    		}
	}
}



void ShipInternal :: renderItemInfo()
{
	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{ 
		if (ship->slot_total_pList[i]->getCursoredStatus() == true)
		{
			if (ship->slot_total_pList[i]->getEquipedStatus() == true)
			{
				ship->slot_total_pList[i]->renderItemInfo();
				break;
			}
		}	
	}
}





void ShipInternal :: renderInternaly()
{
	glLoadIdentity();    // !!!!

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	drawTexturedRect(ship->texOb->texture, ship->kontur_rect, -1.0);

	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{
		ship->slot_total_pList[i]->renderFrame(-1);
	}
	
	ship->gate_slot.renderFrame(-1);
}



