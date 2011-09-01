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


#include "shipInternal.h"

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


void ShipInternal :: bindShip(Ship* _pTo_ship)
{
     pTo_ship = _pTo_ship;
}

void ShipInternal :: bindSkill(Skill* _pTo_skill)
{
     pTo_skill = _pTo_skill;
     createControlSkillButtons();
}

void ShipInternal :: createControlSkillButtons()
{
     int x = 10; //self.korpus.kontur_rect.right
     int y = 50; //self.korpus.kontur_rect.centery
     int w = 20;  //skill_w

     TextureOb* pTo_plus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
     TextureOb* pTo_minus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);

     pTo_increment_attack_button   = new Button(pTo_plus_texOb,  x, y - w,   w, w, "");  
     pTo_decrement_attack_button   = new Button(pTo_minus_texOb, x, y - 2*w, w, w, "");  
                
     pTo_increment_defence_button  = new Button(pTo_plus_texOb,  x + w, y - w,   w, w, "");  
     pTo_decrement_defence_button  = new Button(pTo_minus_texOb, x + w, y - 2*w, w, w, "");  
        
     pTo_increment_leader_button   = new Button(pTo_plus_texOb,  x + 2*w, y - w,   w, w, "");  
     pTo_decrement_leader_button   = new Button(pTo_minus_texOb, x + 2*w, y - 2*w, w, w, ""); 
      
     pTo_increment_trader_button   = new Button(pTo_plus_texOb,  x + 3*w, y - w,   w, w, "");  
     pTo_decrement_trader_button   = new Button(pTo_minus_texOb, x + 3*w, y - 2*w, w, w, ""); 
    
     pTo_increment_technic_button  = new Button(pTo_plus_texOb,  x + 4*w, y - w,   w, w, "");  
     pTo_decrement_technic_button  = new Button(pTo_minus_texOb, x + 4*w, y - 2*w, w, w, ""); 
     
     pTo_increment_diplomat_button = new Button(pTo_plus_texOb,  x + 5*w, y - w,   w, w, "");  
     pTo_decrement_diplomat_button = new Button(pTo_minus_texOb, x + 5*w, y - 2*w, w, w, "");
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
               pTo_skill->incrementAttack();
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
               pTo_skill->decrementAttack();
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
               pTo_skill->incrementDefence();
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
               pTo_skill->decrementDefence();
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
               pTo_skill->incrementLeader();
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
               pTo_skill->decrementLeader();
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
               pTo_skill->incrementTrader();
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
               pTo_skill->decrementTrader();
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
               pTo_skill->incrementTechnic();
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
               pTo_skill->decrementTechnic();
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
               pTo_skill->incrementDiplomat();
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
               pTo_skill->decrementDiplomat();
           }
        }
     }
     //### DIPLOMAT 
}

void ShipInternal :: renderSkill()
{
     int w = 15;
     int h = 15;

     for (int i = 0; i < pTo_skill->attack; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_attack_button->rect.center_x - 10, pTo_increment_attack_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_attack_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_attack_button->render();
     pTo_decrement_attack_button->render();
                    
     for (int i = 0; i < pTo_skill->defence; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_defence_button->rect.center_x - 10, pTo_increment_defence_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_defence_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_defence_button->render();
     pTo_decrement_defence_button->render();

     for (int i = 0; i < pTo_skill->leader; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_leader_button->rect.center_x - 10, pTo_increment_leader_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_leader_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_leader_button->render();
     pTo_decrement_leader_button->render();
        
     for (int i = 0; i < pTo_skill->trader; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_trader_button->rect.center_x - 10, pTo_increment_trader_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_trader_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_trader_button->render();
     pTo_decrement_trader_button->render();
        
     for (int i = 0; i < pTo_skill->technic; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_technic_button->rect.center_x - 10, pTo_increment_technic_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_technic_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_technic_button->render();
     pTo_decrement_technic_button->render();
                    
     for (int i = 0; i < pTo_skill->diplomat; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_diplomat_button->rect.center_x - 10, pTo_increment_diplomat_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_diplomat_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_diplomat_button->render();
     pTo_decrement_diplomat_button->render();
}












void ShipInternal :: resetSlotsRenderInfoFlag()
{
    for(std::vector<ItemSlot*>::iterator it = pTo_ship->slot_total_pList.begin(); it != pTo_ship->slot_total_pList.end(); it++)
    { 
       (*it)->setCursoredStatus(false);
    }
   
    pTo_ship->gate_slot.setCursoredStatus(false);
}






void ShipInternal :: mouseControl(bool allow_full_control, bool in_store)
{
    bool lmb = g_MOUSE_LEFT_BUTTON; 
    bool rmb = g_MOUSE_RIGHT_BUTTON; 

    bool cursor_has_target = false;

    Store* pTo_store = NULL;     // move to ship class             
    if (in_store == true) 
       pTo_store = pTo_ship->pTo_npc_owner->pTo_kosmoport->pTo_store;    // this is used only for player


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
	for(unsigned int i = 0; i < pTo_ship->slot_total_pList.size(); i++)
	{ 
		if (pTo_ship->slot_total_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
		{  
			pTo_ship->slot_total_pList[i]->setCursoredStatus(true);
			cursor_has_target = true;

			if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
			{				
				//// TAKE ITEM from SLOT ////
				if ( (pTo_ship->slot_total_pList[i]->getEquipedStatus() == true) && (pTo_CURSOR->pTo_otsec_slot->getEquipedStatus() == false))
				{ 
					// equipments
                       			if (pTo_ship->slot_total_pList[i]->getItemType() == EQUIPMENT_ID)
                       			{
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getLazerEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getRocketEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       			
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getRadarEquipment()) == true)
                       					{
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       					}
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getDriveEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getBakEquipment()) == true)
                      						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getEnergizerEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                      					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getProtectorEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getDroidEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getFreezerEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getScanerEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getGrappleEquipment()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
               				}
                     	
                       			// modules
                       			if (pTo_ship->slot_total_pList[i]->getItemType() == MODULE_ID)
                       			{
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                    					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getLazerModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (pTo_ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                      				{
                      					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getRocketModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getRadarModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                 					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getDriveModule()) == true)
                      						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (pTo_ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                      					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getBakModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                      				if (pTo_ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                      				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getEnergizerModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getProtectorModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                    				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getDroidModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getFreezerModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (pTo_ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getScanerModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (pTo_ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->slot_total_pList[i]->getGrappleModule()) == true)
                       						pTo_ship->slot_total_pList[i]->removeItem();
                      				}
                       			}
                        	
                       			// artifacts
                       			// bomb
               			}
				//// PUT ITEM to SLOT ////
				else if ( (pTo_ship->slot_total_pList[i]->getEquipedStatus() == false) && (pTo_CURSOR->pTo_otsec_slot->getEquipedStatus() == true) )
				{
                                        // weapons                                      
					if ( (pTo_ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (pTo_ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pTo_CURSOR->pTo_otsec_slot->getItemType() == EQUIPMENT_ID)
						{      
                                                        if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == LAZER_ID)
							{       
								if ( pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getLazerEquipment()) );
                                                                        pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ROCKET_ID)
							{
								pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getRocketEquipment());
								pTo_CURSOR->pTo_otsec_slot->removeItem();
							}                                                       
                                                }
                                        }
                                        
                                        // equipment(except weapons)        
					if ( (pTo_ship->slot_total_pList[i]->getSubType() == pTo_CURSOR->pTo_otsec_slot->getItemSubType()) || (pTo_ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pTo_CURSOR->pTo_otsec_slot->getItemType() == EQUIPMENT_ID)
						{       
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == RADAR_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getRadarEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}	
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DRIVE_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getDriveEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == BAK_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getBakEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ENERGIZER_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getEnergizerEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == PROTECTOR_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getProtectorEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DROID_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getDroidEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == FREEZER_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getFreezerEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == SCANER_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getScanerEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == GRAPPLE_ID)
							{
								if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getGrappleEquipment()) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
						}
					
						// modules	
						if (pTo_CURSOR->pTo_otsec_slot->getItemType() == MODULE_ID)
						{
                        				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == LAZER_ID)
       	                				{
               	            					if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getLazerModule()) == true)
                       	    						pTo_CURSOR->pTo_otsec_slot->removeItem();
                       					}
                       					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ROCKET_ID)
                       					{
                            					if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getRocketModule()) == true)
       	                    						pTo_CURSOR->pTo_otsec_slot->removeItem();
               	        				}
                       					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == RADAR_ID)
                       					{ 
                       						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getRadarModule()) == true)
                      							pTo_CURSOR->pTo_otsec_slot->removeItem();
                       					}
	                   	  			if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DRIVE_ID)
               	        				{
                       	    					if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getDriveModule()) == true)
                       							pTo_CURSOR->pTo_otsec_slot->removeItem();
               		 				}
      		        	  			if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == BAK_ID)
                      					{
                      						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getBakModule()) == true)
                       							pTo_CURSOR->pTo_otsec_slot->removeItem();
                      					}
               	        				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ENERGIZER_ID)
                       					{
                       						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getEnergizerModule()) == true)
                       							pTo_CURSOR->pTo_otsec_slot->removeItem();
                      					}
              		       				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == PROTECTOR_ID)
                       					{
                       						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getProtectorModule()) == true)
                       							pTo_CURSOR->pTo_otsec_slot->removeItem();
                      					}
              		      				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DROID_ID)
                      					{
                       						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getDroidModule()) == true)
                       							pTo_CURSOR->pTo_otsec_slot->removeItem();
                       					}
              		      				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == FREEZER_ID)
                       					{
                       						if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getFreezerModule()) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == SCANER_ID)
                        				{
                            					if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getScanerModule()) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}		
                        				if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == GRAPPLE_ID)
                        				{
                            					if (pTo_ship->slot_total_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->getGrappleModule()) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                        			}
                        			// artifacts
                        			// bomb                     			
                    			} 
                		} //// PUT ITEM to SLOT ////
                		//// MERGE MODULE WITH EQUIPMENT ////
                		if ( (pTo_ship->slot_total_pList[i]->getEquipedStatus() == true) && (pTo_CURSOR->pTo_otsec_slot->getEquipedStatus() == true) )
                		{	
					if (pTo_CURSOR->pTo_otsec_slot->getItemType() == MODULE_ID) 
					{                                               
						if ( (pTo_ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (pTo_ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
						{   
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == LAZER_ID)
							{       
								if (pTo_ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pTo_CURSOR->pTo_otsec_slot->getLazerModule()) == true)
								{
									pTo_CURSOR->pTo_otsec_slot->removeItem();
								}    
							}
                                                }

						if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == pTo_ship->slot_total_pList[i]->getItemSubType())
						{   
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == LAZER_ID)
							{       
								if (pTo_ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pTo_CURSOR->pTo_otsec_slot->getLazerModule()) == true)
								{
									pTo_CURSOR->pTo_otsec_slot->removeItem();
								}    
							}

		
							if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == RADAR_ID)
							{
								if (pTo_ship->slot_total_pList[i]->getRadarEquipment()->insertModule(pTo_CURSOR->pTo_otsec_slot->getRadarModule()) == true)
								{
									pTo_CURSOR->pTo_otsec_slot->removeItem();
								}    
							}
						}  

					
					}               		
                		
                		}             		
                		    
            		}
			// SELL ITEM TO STORE //
			else if ( (lmb == true) && (in_store == true) )
			{
				int earn_price = pTo_store->buyOtsecSlotItem(pTo_ship->slot_total_pList[i]);
				pTo_PLAYER->pTo_npc->credits += earn_price;
			} 


       		}
        	
        }
                    



            
            
            

	// GATE SLOT
	if (cursor_has_target == false)
	{
		if (pTo_ship->gate_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
		{
			pTo_ship->gate_slot.setCursoredStatus(true);
			cursor_has_target = true;

			//// DROP ITEM TO OUTERSPACE ////
			if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
			{
				if (pTo_CURSOR->pTo_otsec_slot->getEquipedStatus() == true)
				{
					Container* _container = createContainer( pTo_ship->getPoints()->getCenter() );
										 
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == LAZER_ID)
					{     
                      				_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getLazerEquipment()); 
                      				pTo_CURSOR->pTo_otsec_slot->removeItem();
                  			}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ROCKET_ID)
					{             
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getRocketEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();  
					}

					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == RADAR_ID)
					{                      
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getRadarEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DRIVE_ID)
					{               
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getDriveEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem(); 
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == BAK_ID)
					{                      
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getBakEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == ENERGIZER_ID)
					{       
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getEnergizerEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();              
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == PROTECTOR_ID)
					{            
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getProtectorEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();         
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == DROID_ID)
					{          
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getDroidEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();          
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == FREEZER_ID)
					{                  
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getFreezerEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();   
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == SCANER_ID)
					{      
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getScanerEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();            
					}
					if (pTo_CURSOR->pTo_otsec_slot->getItemSubType() == GRAPPLE_ID)
					{                     
						_container->otsec_slot->insertItem(pTo_CURSOR->pTo_otsec_slot->getGrappleEquipment()); 
						pTo_CURSOR->pTo_otsec_slot->removeItem();
					}
					pTo_ship->starsystem->addContainer(_container); 
				} 
			}
    		}
	}
}



void ShipInternal :: renderItemInfo()
{
	for(unsigned int i = 0; i < pTo_ship->slot_total_pList.size(); i++)
	{ 
		if (pTo_ship->slot_total_pList[i]->getCursoredStatus() == true)
		{
			if (pTo_ship->slot_total_pList[i]->getEquipedStatus() == true)
			{
				pTo_ship->slot_total_pList[i]->renderItemInfo();
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

	drawTexturedRect(pTo_ship->pTo_texOb->texture, pTo_ship->kontur_rect, -1.0);

	for(unsigned int i = 0; i < pTo_ship->slot_total_pList.size(); i++)
	{
		pTo_ship->slot_total_pList[i]->renderFrame(-1);
	}
	
	pTo_ship->gate_slot.renderFrame(-1);
}



