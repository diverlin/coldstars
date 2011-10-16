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
        in_store           = false;
        allow_full_control = false;
        
        ship = NULL;
        skill = NULL;
}

ShipInternal :: ~ShipInternal()
{}


void ShipInternal :: bindShip(Ship* _ship)
{
     	ship =  _ship;
        skill = ship->getNpc()->getSkill();
}

void ShipInternal :: createControlSkillButtons()
{
     	int x = 10;  //self.korpus.kontur_rect.right
     	int y = 50;  //self.korpus.kontur_rect.centery
     	int w = 20;  //skill_w

     	TextureOb* texOb_plus  = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
     	TextureOb* texOb_minus = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);

        //TextureOb* texOb_plus  = g_TEXTURE_MANAGER.particles_texOb_pList[0];
        //TextureOb* texOb_minus = g_TEXTURE_MANAGER.particles_texOb_pList[1]; 

     	increment_attack_button   = new Button(texOb_plus, INCREMENT_ATTACK_BUTTON_ID, x, y - w,   w, w, "");  
     	button_pList.push_back(increment_attack_button);
     	decrement_attack_button   = new Button(texOb_minus, DECREMENT_ATTACK_BUTTON_ID, x, y - 2*w, w, w, "");  
     	button_pList.push_back(decrement_attack_button);
                     
     	increment_defence_button  = new Button(texOb_plus, INCREMENT_DEFENCE_BUTTON_ID, x + w, y - w,   w, w, "");  
     	button_pList.push_back(increment_defence_button);
     	decrement_defence_button  = new Button(texOb_minus, DECREMENT_DEFENCE_BUTTON_ID, x + w, y - 2*w, w, w, "");  
     	button_pList.push_back(decrement_defence_button);
     	        
     	increment_leader_button   = new Button(texOb_plus, INCREMENT_LEADER_BUTTON_ID, x + 2*w, y - w,   w, w, "");  
     	button_pList.push_back(increment_leader_button);
     	decrement_leader_button   = new Button(texOb_minus, DECREMENT_LEADER_BUTTON_ID, x + 2*w, y - 2*w, w, w, ""); 
     	button_pList.push_back(decrement_leader_button);
     	      
     	increment_trader_button   = new Button(texOb_plus, INCREMENT_TRADER_BUTTON_ID, x + 3*w, y - w,   w, w, "");  
     	button_pList.push_back(increment_trader_button);
     	decrement_trader_button   = new Button(texOb_minus, DECREMENT_TRADER_BUTTON_ID, x + 3*w, y - 2*w, w, w, ""); 
     	button_pList.push_back(decrement_trader_button);
    
     	increment_technic_button  = new Button(texOb_plus, INCREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - w,   w, w, "");  
     	button_pList.push_back(increment_technic_button);
     	decrement_technic_button  = new Button(texOb_minus, DECREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - 2*w, w, w, ""); 
     	button_pList.push_back(decrement_technic_button);
     
     	increment_diplomat_button = new Button(texOb_plus, INCREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - w,   w, w, "");  
     	button_pList.push_back(increment_diplomat_button);
     	decrement_diplomat_button = new Button(texOb_minus, DECREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - 2*w, w, w, "");
        button_pList.push_back(decrement_diplomat_button);     
}

void ShipInternal :: manageSkill()
{
     	int mxvp = g_MOUSE_POS_X;
     	int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     	int lmb  = g_MOUSE_LEFT_BUTTON;

	for (unsigned int i = 0; i < button_pList.size(); i++)
	{
		if (button_pList[i]->interaction(mxvp, myvp) == true)
		{
		       	if (lmb == true)
           		{
           		   	int buttonSubTypeId = button_pList[i]->getSubTypeId();
           		   	
           		   	if (buttonSubTypeId == INCREMENT_ATTACK_BUTTON_ID)
           		   	      	skill->incrementAttack();
           		        if (buttonSubTypeId == DECREMENT_ATTACK_BUTTON_ID)
           		   	      	skill->decrementAttack();
           		   	      	
           		   	if (buttonSubTypeId == INCREMENT_DEFENCE_BUTTON_ID)
           		   	      	skill->incrementDefence();
           		        if (buttonSubTypeId == DECREMENT_DEFENCE_BUTTON_ID)
           		   	      	skill->decrementDefence();
           		   	      	
           		   	if (buttonSubTypeId == INCREMENT_LEADER_BUTTON_ID)
           		   	      	skill->incrementLeader();
           		        if (buttonSubTypeId == DECREMENT_LEADER_BUTTON_ID)
           		   	      	skill->decrementLeader();
           		   	      	
           		   	if (buttonSubTypeId == INCREMENT_TRADER_BUTTON_ID)
           		   	      	skill->incrementTrader();
           		        if (buttonSubTypeId == DECREMENT_TRADER_BUTTON_ID)
           		   	      	skill->decrementTrader();
           		   	      	
           		   	if (buttonSubTypeId == INCREMENT_TECHNIC_BUTTON_ID)
           		   	      	skill->incrementTechnic();
           		        if (buttonSubTypeId == DECREMENT_TECHNIC_BUTTON_ID)
           		   	      	skill->decrementTechnic();
           		   	      	
           		   	if (buttonSubTypeId == INCREMENT_DIPLOMAT_BUTTON_ID)
           		   	      	skill->incrementDiplomat();
           		        if (buttonSubTypeId == DECREMENT_DIPLOMAT_BUTTON_ID)
           		   	      	skill->decrementDiplomat();           		   	
           		}
		}
	}
}

void ShipInternal :: renderSkill() const
{
    	int w = 15;
     	int h = 15;

 	for (unsigned int bi = 0; bi < button_pList.size(); bi++)
	{
		button_pList[bi]->render();

		int buttonSubTypeId = button_pList[bi]->getSubTypeId();		

		if (buttonSubTypeId == INCREMENT_ATTACK_BUTTON_ID)
		{
		     	for (int i = 0; i < skill->getAttack(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		      			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		      			     w, h);
         		      			     
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
     			}
 
		}
          		   	      	
		if (buttonSubTypeId == INCREMENT_DEFENCE_BUTTON_ID)
		{
		     	for (int i = 0; i < skill->getDefence(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		      			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		      			     w, h);
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
     			}
		}

	   	if (buttonSubTypeId == INCREMENT_LEADER_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getLeader(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		      			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		      			     w, h);
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
     			}
	   	
	   	}

	   	if (buttonSubTypeId == INCREMENT_TRADER_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getTrader(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		     			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		     			     w, h);
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
    			}
	   	
	   	}

	   	if (buttonSubTypeId == INCREMENT_TECHNIC_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getTechnic(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		      			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		      			     w, h);
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
     			}     
	   	}

	   	if (buttonSubTypeId == INCREMENT_DIPLOMAT_BUTTON_ID)
	   	{
	   		for (int i = 0; i < skill->getDiplomat(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_pList[bi]->getRect().getCenter().x - 10, 
         		      			     button_pList[bi]->getRect().getCenter().y + i*h, 
         		     			     w, h);
         			drawTexturedRect(button_pList[bi]->getTexOb()->texture, tmp_rect, -1.0);
     			}
	   	}

	}
}







void ShipInternal :: resetSlotsRenderInfoFlag()
{
    	//for(std::vector<ItemSlot*>::iterator it = ship->slot_total_pList.begin(); it != ship->slot_total_pList.end(); it++)
    	//{ 
       		//(*it)->setCursoredStatus(false);
    	//}
   
   	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{ 
		ship->slot_total_pList[i]->setCursoredStatus(false);
	}
	
    	ship->gate_slot.setCursoredStatus(false);
}






void ShipInternal :: mouseControl()
{
    	bool lmb = g_MOUSE_LEFT_BUTTON; 
    	bool rmb = g_MOUSE_RIGHT_BUTTON; 

    	bool cursor_has_target = false;

    	Store* pTo_store = NULL;     // move to ship class             
    	if (in_store == true)
        { 
       		pTo_store = ship->getNpc()->getKosmoport()->getStore();    // this is used only for player
        }

    	resetSlotsRenderInfoFlag();


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
				if ( (ship->slot_total_pList[i]->getEquipedStatus() == true) && (pPLAYER->getCursor()->getSlot()->getEquipedStatus() == false))
				{ 
					// equipments
                       			if (ship->slot_total_pList[i]->getItemType() == EQUIPMENT_ID)
                       			{
                       				if (ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getLazerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getRocketEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       			
                       				if (ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getRadarEquipment()) == true)
                       					{
                       						ship->slot_total_pList[i]->removeItem();
                       					}
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getDriveEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getBakEquipment()) == true)
                      						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getEnergizerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                      					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getProtectorEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getDroidEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getFreezerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getScanerEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getGrappleEquipment()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
               				}
                     	
                       			// modules
                       			if (ship->slot_total_pList[i]->getItemType() == MODULE_ID)
                       			{
                       				if (ship->slot_total_pList[i]->getItemSubType() == LAZER_ID)
                       				{
                    					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getLazerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == ROCKET_ID)
                      				{
                      					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getRocketModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == RADAR_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getRadarModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DRIVE_ID)
                       				{
                 					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getDriveModule()) == true)
                      						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == BAK_ID)
                       				{
                      					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getBakModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == ENERGIZER_ID)
                      				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getEnergizerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == PROTECTOR_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getProtectorModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == DROID_ID)
                    				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getDroidModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                       				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == FREEZER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getFreezerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       				if (ship->slot_total_pList[i]->getItemSubType() == SCANER_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getScanerModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                      				if (ship->slot_total_pList[i]->getItemSubType() == GRAPPLE_ID)
                       				{
                       					if (pPLAYER->getCursor()->getSlot()->insertItem(ship->slot_total_pList[i]->getGrappleModule()) == true)
                       						ship->slot_total_pList[i]->removeItem();
                      				}
                       			}
                        	
                       			// artifacts
                       			// bomb
               			}
				//// PUT ITEM to SLOT ////
				else if ( (ship->slot_total_pList[i]->getEquipedStatus() == false) && (pPLAYER->getCursor()->getSlot()->getEquipedStatus() == true) )
				{
                                        // weapons                                      
					if ( (ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pPLAYER->getCursor()->getSlot()->getItemType() == EQUIPMENT_ID)
						{      
                                                        if (pPLAYER->getCursor()->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if ( ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getLazerEquipment()) );
                                                                        pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ROCKET_ID)
							{
								ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getRocketEquipment());
								pPLAYER->getCursor()->getSlot()->removeItem();
							}                                                       
                                                }
                                        }
                                        
                                        // equipment(except weapons)        
					if ( (ship->slot_total_pList[i]->getSubType() == pPLAYER->getCursor()->getSlot()->getItemSubType()) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
					{
						if (pPLAYER->getCursor()->getSlot()->getItemType() == EQUIPMENT_ID)
						{       
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == RADAR_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getRadarEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}	
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DRIVE_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getDriveEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == BAK_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getBakEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ENERGIZER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getEnergizerEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == PROTECTOR_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getProtectorEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DROID_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getDroidEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == FREEZER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getFreezerEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == SCANER_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getScanerEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == GRAPPLE_ID)
							{
								if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getGrappleEquipment()) == true)
									pPLAYER->getCursor()->getSlot()->removeItem();
							}
						}
					
						// modules	
						if (pPLAYER->getCursor()->getSlot()->getItemType() == MODULE_ID)
						{
                        				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == LAZER_ID)
       	                				{
               	            					if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getLazerModule()) == true)
                       	    						pPLAYER->getCursor()->getSlot()->removeItem();
                       					}
                       					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ROCKET_ID)
                       					{
                            					if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getRocketModule()) == true)
       	                    						pPLAYER->getCursor()->getSlot()->removeItem();
               	        				}
                       					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == RADAR_ID)
                       					{ 
                       						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getRadarModule()) == true)
                      							pPLAYER->getCursor()->getSlot()->removeItem();
                       					}
	                   	  			if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DRIVE_ID)
               	        				{
                       	    					if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getDriveModule()) == true)
                       							pPLAYER->getCursor()->getSlot()->removeItem();
               		 				}
      		        	  			if (pPLAYER->getCursor()->getSlot()->getItemSubType() == BAK_ID)
                      					{
                      						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getBakModule()) == true)
                       							pPLAYER->getCursor()->getSlot()->removeItem();
                      					}
               	        				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ENERGIZER_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getEnergizerModule()) == true)
                       							pPLAYER->getCursor()->getSlot()->removeItem();
                      					}
              		       				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == PROTECTOR_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getProtectorModule()) == true)
                       							pPLAYER->getCursor()->getSlot()->removeItem();
                      					}
              		      				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DROID_ID)
                      					{
                       						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getDroidModule()) == true)
                       							pPLAYER->getCursor()->getSlot()->removeItem();
                       					}
              		      				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == FREEZER_ID)
                       					{
                       						if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getFreezerModule()) == true)
                            						pPLAYER->getCursor()->getSlot()->removeItem();
                        				}
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == SCANER_ID)
                        				{
                            					if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getScanerModule()) == true)
                            						pPLAYER->getCursor()->getSlot()->removeItem();
                        				}		
                        				if (pPLAYER->getCursor()->getSlot()->getItemSubType() == GRAPPLE_ID)
                        				{
                            					if (ship->slot_total_pList[i]->insertItem(pPLAYER->getCursor()->getSlot()->getGrappleModule()) == true)
                            						pPLAYER->getCursor()->getSlot()->removeItem();
                        				}
                        			}
                        			// artifacts
                        			// bomb                     			
                    			} 
                		} //// PUT ITEM to SLOT ////
                		//// MERGE MODULE WITH EQUIPMENT ////
                		if ( (ship->slot_total_pList[i]->getEquipedStatus() == true) && (pPLAYER->getCursor()->getSlot()->getEquipedStatus() == true) )
                		{	
					if (pPLAYER->getCursor()->getSlot()->getItemType() == MODULE_ID) 
					{                                               
						if ( (ship->slot_total_pList[i]->getSubType() == WEAPON_SLOT_ID) || (ship->slot_total_pList[i]->getSubType() == UNIVERSAL_SLOT_ID) )
						{   
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if (ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pPLAYER->getCursor()->getSlot()->getLazerModule()) == true)
								{
									pPLAYER->getCursor()->getSlot()->removeItem();
								}    
							}
                                                }

						if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ship->slot_total_pList[i]->getItemSubType())
						{   
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == LAZER_ID)
							{       
								if (ship->slot_total_pList[i]->getLazerEquipment()->insertModule(pPLAYER->getCursor()->getSlot()->getLazerModule()) == true)
								{
									pPLAYER->getCursor()->getSlot()->removeItem();
								}    
							}

		
							if (pPLAYER->getCursor()->getSlot()->getItemSubType() == RADAR_ID)
							{
								if (ship->slot_total_pList[i]->getRadarEquipment()->insertModule(pPLAYER->getCursor()->getSlot()->getRadarModule()) == true)
								{
									pPLAYER->getCursor()->getSlot()->removeItem();
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
				pPLAYER->getPilot()->addCredits(earn_price);
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
				if (pPLAYER->getCursor()->getSlot()->getEquipedStatus() == true)
				{
					Container* _container = createContainer( ship->getPoints()->getCenter() );
										 
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == LAZER_ID)
					{     
                      				_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getLazerEquipment()); 
                      				pPLAYER->getCursor()->getSlot()->removeItem();
                  			}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ROCKET_ID)
					{             
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getRocketEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();  
					}

					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == RADAR_ID)
					{                      
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getRadarEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DRIVE_ID)
					{               
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getDriveEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem(); 
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == BAK_ID)
					{                      
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getBakEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == ENERGIZER_ID)
					{       
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getEnergizerEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();              
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == PROTECTOR_ID)
					{            
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getProtectorEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();         
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == DROID_ID)
					{          
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getDroidEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();          
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == FREEZER_ID)
					{                  
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getFreezerEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();   
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == SCANER_ID)
					{      
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getScanerEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();            
					}
					if (pPLAYER->getCursor()->getSlot()->getItemSubType() == GRAPPLE_ID)
					{                     
						_container->otsec_slot->insertItem(pPLAYER->getCursor()->getSlot()->getGrappleEquipment()); 
						pPLAYER->getCursor()->getSlot()->removeItem();
					}
					ship->getStarSystem()->addContainer(_container); 
				} 
			}
    		}
	}
}



void ShipInternal :: renderItemInfo() const
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





void ShipInternal :: renderInternaly() const
{
	drawTexturedRect(ship->texOb_korpus->texture, ship->kontur_rect, -1.0);

	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{
		ship->slot_total_pList[i]->renderFrame(-1);
	}
	
	ship->gate_slot.renderFrame(-1);
}


void ShipInternal :: configure(Ship* _ship, bool _in_store = false, bool _allow_full_control = false)
{
        bindShip(_ship);                           

        in_store = _in_store;
        allow_full_control = _allow_full_control;  
        
        if ( (pPLAYER->getShip()->getId() == ship->getId()) && (_allow_full_control == false) )
    	{
        	allow_full_control = true;  
        }    	// modify full control for friend ships       
}


void ShipInternal :: update()
{
        mouseControl();

    	if (in_store == false)
    	{
        	manageSkill();
    	}           
        
        pPLAYER->getCursor()->update();
}

void ShipInternal :: render() const
{
	resetRenderTransformation();
	enable_BLEND();
	
	renderInternaly();
	if (!in_store)
	{
		renderSkill();
	}
		
	if (pPLAYER->getCursor()->getSlot()->getEquipedStatus() == false)
	{
        	renderItemInfo();
        }
        
        pPLAYER->getCursor()->render();
                
	disable_BLEND();
}

