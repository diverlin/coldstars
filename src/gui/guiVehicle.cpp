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



GuiVehicle :: GuiVehicle()
{
        in_store           = false;
        allow_full_control = false;
        
        vehicle = NULL;
        skill = NULL;
}

GuiVehicle :: ~GuiVehicle()
{
	for (unsigned int i = 0; i < button_vec.size(); i++)
	{
		delete button_vec[i];
	}
}


void GuiVehicle :: bind(VehicleBase* vehicle)
{
	this->vehicle = vehicle;
        skill = vehicle->getNpc()->getSkill();
}

void GuiVehicle :: createControlSkillButtons()
{
     	int x = 10;  //self.korpus.kontur_rect.right
     	int y = 50;  //self.korpus.kontur_rect.centery
     	int w = 20;  //skill_w

     	TextureOb* texOb_icon_plus  = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_plus;
     	TextureOb* texOb_icon_minus = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_minus;
     	     	
     	Button* increment_attack_button   = new Button(texOb_icon_plus, INCREMENT_ATTACK_BUTTON_ID, x, y - w,   w, w, "");  
     	button_vec.push_back(increment_attack_button);
     	Button* decrement_attack_button   = new Button(texOb_icon_minus, DECREMENT_ATTACK_BUTTON_ID, x, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_attack_button);
                     
     	Button* increment_defence_button  = new Button(texOb_icon_plus, INCREMENT_DEFENCE_BUTTON_ID, x + w, y - w,   w, w, "");  
     	button_vec.push_back(increment_defence_button);
     	Button* decrement_defence_button  = new Button(texOb_icon_minus, DECREMENT_DEFENCE_BUTTON_ID, x + w, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_defence_button);
     	        
     	Button* increment_leader_button   = new Button(texOb_icon_plus, INCREMENT_LEADER_BUTTON_ID, x + 2*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_leader_button);
     	Button* decrement_leader_button   = new Button(texOb_icon_minus, DECREMENT_LEADER_BUTTON_ID, x + 2*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_leader_button);
     	      
     	Button* increment_trader_button   = new Button(texOb_icon_plus, INCREMENT_TRADER_BUTTON_ID, x + 3*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_trader_button);
     	Button* decrement_trader_button   = new Button(texOb_icon_minus, DECREMENT_TRADER_BUTTON_ID, x + 3*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_trader_button);
    
     	Button* increment_technic_button  = new Button(texOb_icon_plus, INCREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_technic_button);
     	Button* decrement_technic_button  = new Button(texOb_icon_minus, DECREMENT_TECHNIC_BUTTON_ID, x + 4*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_technic_button);
     
     	Button* increment_diplomat_button = new Button(texOb_icon_plus, INCREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_diplomat_button);
     	Button* decrement_diplomat_button = new Button(texOb_icon_minus, DECREMENT_DIPLOMAT_BUTTON_ID, x + 5*w, y - 2*w, w, w, "");
        button_vec.push_back(decrement_diplomat_button);     
}

void GuiVehicle :: manageSkill()
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
           		   	switch(button_vec[i]->getSubTypeId())
           		   	{
           		   	   	case INCREMENT_ATTACK_BUTTON_ID:   { skill->incrementAttack(); break; }
           		        	case DECREMENT_ATTACK_BUTTON_ID:   { skill->decrementAttack(); break; }
           		   	      	
           		   		case INCREMENT_DEFENCE_BUTTON_ID:  { skill->incrementDefence(); break; }
           		        	case DECREMENT_DEFENCE_BUTTON_ID:  { skill->decrementDefence(); break; }
           		   	      	
           		   		case INCREMENT_LEADER_BUTTON_ID:   { skill->incrementLeader(); break; }
           		        	case DECREMENT_LEADER_BUTTON_ID:   { skill->decrementLeader(); break; }
           		   	      	
           		   		case INCREMENT_TRADER_BUTTON_ID:   { skill->incrementTrader(); break; }
           		        	case DECREMENT_TRADER_BUTTON_ID:   { skill->decrementTrader(); break; }
           		   	      	
           		   		case INCREMENT_TECHNIC_BUTTON_ID:  { skill->incrementTechnic(); break; }
           		       		case DECREMENT_TECHNIC_BUTTON_ID:  { skill->decrementTechnic(); break; }
           		   	      	
           		   		case INCREMENT_DIPLOMAT_BUTTON_ID: { skill->incrementDiplomat(); break; }
           		        	case DECREMENT_DIPLOMAT_BUTTON_ID: { skill->decrementDiplomat(); break; }        
           		        }  		   	
           		}
		}
	}
}

void GuiVehicle :: renderSkill() const
{
    	int w = button_vec[0]->getRect().getWidth();
     	int h = button_vec[0]->getRect().getHeight();
     	
     	TextureOb* texOb_skill = g_UNIQUE_TEXTURE_COLLECTOR.texOb_skill;

 	for (unsigned int bi = 0; bi < button_vec.size(); bi++)
	{
		button_vec[bi]->render();

		switch(button_vec[bi]->getSubTypeId())		
		{
			case INCREMENT_ATTACK_BUTTON_ID:
			{
		     		for (int i = 0; i < skill->getAttack(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         		      			     
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
 			break;
			}
			
			case INCREMENT_DEFENCE_BUTTON_ID:
			{
		     		for (int i = 0; i < skill->getDefence(); i++) 
     				{		 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
			break;
			}

			case INCREMENT_LEADER_BUTTON_ID:
			{
	   		     	for (int i = 0; i < skill->getLeader(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
			break;
	   		}

	   		case INCREMENT_TRADER_BUTTON_ID:
	   		{
	   	     		for (int i = 0; i < skill->getTrader(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		     				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		     				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
    				}
			break;
	   	   	}
			
	   		case INCREMENT_TECHNIC_BUTTON_ID:
	   		{
	   	     		for (int i = 0; i < skill->getTechnic(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}     
	   		break;
	   		}

	   		case INCREMENT_DIPLOMAT_BUTTON_ID:
	   		{
	   			for (int i = 0; i < skill->getDiplomat(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->getRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->getRect().getCenter().y + h/2 + i*h, 
         		     				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
	   		break;
	   		}
	   	}
	}
}




void GuiVehicle :: mouseControl()
{
    	bool lmb = g_MOUSE_LEFT_BUTTON; 
    	//bool rmb = g_MOUSE_RIGHT_BUTTON; 

    	bool cursor_has_target = false;

    	Store* pTo_store = NULL;     // move to ship class             
    	if (in_store == true)
        { 
       		pTo_store = vehicle->getNpc()->getKosmoport()->getStore();    // this is used only for player
        }

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
		{  
			pPLAYER->getCursor()->setInfoSlot(vehicle->slot_total_vec[i]);
			cursor_has_target = true;

			if (lmb == true)
			{
				if ( (allow_full_control == true) && (in_store == false) )
				{				
					pPLAYER->getCursor()->getSlot()->SwapItemWith(vehicle->slot_total_vec[i]);                		    
            			}          		
				else if ( in_store == true )
				{
					if (pTo_store->buyItemFromSlot(vehicle->slot_total_vec[i]) == true)\
					{
						pPLAYER->getPilot()->increaseCredits(vehicle->slot_total_vec[i]->getItem()->getPrice());
					}
				}
			} 
       		}        	
        }         
            
            

	// GATE SLOT
	if (cursor_has_target == false)
	{
		if (vehicle->getGateSlot()->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
		{
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




void GuiVehicle :: renderInternaly() const
{
	drawTexturedRect(vehicle->texOb_korpus, vehicle->kontur_rect, -1.0);

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{
		vehicle->slot_total_vec[i]->render(-1);
	}
	
	vehicle->getGateSlot()->render(-1);
}


void GuiVehicle :: configure(VehicleBase* _vehicle, bool _in_store = false, bool _allow_full_control = false)
{
        bind(_vehicle);                           

        in_store = _in_store;
        allow_full_control = _allow_full_control;  
        
        if ( (pPLAYER->getVehicle()->getId() == vehicle->getId()) && (_allow_full_control == false) )
    	{
        	allow_full_control = true;  
        }    	// modify full control for friend ships       
}


void GuiVehicle :: update()
{
        mouseControl();

    	if (in_store == false)
    	{
        	manageSkill();
    	}           
        
        pPLAYER->getCursor()->update();
}

void GuiVehicle :: render() const
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
        	pPLAYER->getCursor()->renderInfoSlot();
        }
        
        pPLAYER->getCursor()->render();
                
	disable_BLEND();
}

