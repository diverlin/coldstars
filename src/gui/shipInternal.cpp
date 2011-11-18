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

     	TextureOb* texOb_icon_plus  = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_plus;
     	TextureOb* texOb_icon_minus = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_minus;
     	     	
     	increment_attack_button   = new Button(texOb_icon_plus, INCREMENT_ATTACK_BUTTON_ID, x, y - w,   w, w, "");  
     	button_vec.push_back(increment_attack_button);
     	decrement_attack_button   = new Button(texOb_icon_minus, DECREMENT_ATTACK_BUTTON_ID, x, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_attack_button);
                     
     	increment_defence_button  = new Button(texOb_icon_plus, INCREMENT_DEFENCE_BUTTON_ID, x + w, y - w,   w, w, "");  
     	button_vec.push_back(increment_defence_button);
     	decrement_defence_button  = new Button(texOb_icon_minus, DECREMENT_DEFENCE_BUTTON_ID, x + w, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_defence_button);
     	        
     	increment_leader_button   = new Button(texOb_icon_plus, INCREMENT_LEADER_BUTTON_ID, x + 2*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_leader_button);
     	decrement_leader_button   = new Button(texOb_icon_minus, DECREMENT_LEADER_BUTTON_ID, x + 2*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_leader_button);
     	      
     	increment_trader_button   = new Button(texOb_icon_plus, INCREMENT_TRADER_BUTTON_ID, x + 3*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_trader_button);
     	decrement_trader_button   = new Button(texOb_icon_minus, DECREMENT_TRADER_BUTTON_ID, x + 3*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_trader_button);
    
     	increment_technic_button  = new Button(texOb_icon_plus, INCREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_technic_button);
     	decrement_technic_button  = new Button(texOb_icon_minus, DECREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_technic_button);
     
     	increment_diplomat_button = new Button(texOb_icon_plus, INCREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_diplomat_button);
     	decrement_diplomat_button = new Button(texOb_icon_minus, DECREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - 2*w, w, w, "");
        button_vec.push_back(decrement_diplomat_button);     
}

void ShipInternal :: manageSkill()
{
     	int mxvp = g_MOUSE_POS_X;
     	int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     	int lmb  = g_MOUSE_LEFT_BUTTON;

	for (unsigned int i = 0; i < button_vec.size(); i++)
	{
		if (button_vec[i]->interaction(mxvp, myvp) == true)
		{
		       	if (lmb == true)
           		{
           		   	int buttonSubTypeId = button_vec[i]->getSubTypeId();
           		   	
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
    	int w = button_vec[0]->getRect().getWidth();
     	int h = button_vec[0]->getRect().getHeight();
     	
     	TextureOb* texOb_skill = g_UNIQUE_TEXTURE_COLLECTOR.texOb_skill;

 	for (unsigned int bi = 0; bi < button_vec.size(); bi++)
	{
		button_vec[bi]->render();

		int buttonSubTypeId = button_vec[bi]->getSubTypeId();		

		if (buttonSubTypeId == INCREMENT_ATTACK_BUTTON_ID)
		{
		     	for (int i = 0; i < skill->getAttack(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      			     w, h);
         		      			     
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
     			}
 
		}
          		   	      	
		if (buttonSubTypeId == INCREMENT_DEFENCE_BUTTON_ID)
		{
		     	for (int i = 0; i < skill->getDefence(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      			     w, h);
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
     			}
		}

	   	if (buttonSubTypeId == INCREMENT_LEADER_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getLeader(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      			     w, h);
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
     			}
	   	
	   	}

	   	if (buttonSubTypeId == INCREMENT_TRADER_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getTrader(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		     			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		     			     w, h);
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
    			}
	   	
	   	}

	   	if (buttonSubTypeId == INCREMENT_TECHNIC_BUTTON_ID)
	   	{
	   	     	for (int i = 0; i < skill->getTechnic(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      			     w, h);
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
     			}     
	   	}

	   	if (buttonSubTypeId == INCREMENT_DIPLOMAT_BUTTON_ID)
	   	{
	   		for (int i = 0; i < skill->getDiplomat(); i++) 
     			{ 
         			Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      			     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		     			     w, h);
         			drawTexturedRect(texOb_skill->texture, tmp_rect, -1.0);
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
    	//bool rmb = g_MOUSE_RIGHT_BUTTON; 

    	bool cursor_has_target = false;

    	Store* pTo_store = NULL;     // move to ship class             
    	if (in_store == true)
        { 
       		pTo_store = ship->getNpc()->getKosmoport()->getStore();    // this is used only for player
        }

    	resetSlotsRenderInfoFlag();


	for(unsigned int i = 0; i < ship->slot_total_pList.size(); i++)
	{ 
		if (ship->slot_total_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
		{  
			ship->slot_total_pList[i]->setCursoredStatus(true);
			cursor_has_target = true;

			if (lmb == true)
			{
				if ( (allow_full_control == true) && (in_store == false) )
				{				
					pPLAYER->getCursor()->getSlot()->SwapItemWith(ship->slot_total_pList[i]);                		    
            			}          		
				else if ( in_store == true )
				{
					if (pTo_store->buyItemFromSlot(ship->slot_total_pList[i]) == true)\
					{
						pPLAYER->getPilot()->increaseCredits(ship->slot_total_pList[i]->getItemPrice());
					}
				}
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
					pPLAYER->getCursor()->getSlot()->dropItemToSpace();	
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

