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



GuiSkill :: GuiSkill(Player* player)
{
	this->player = player;
	
	createControlSkillButtons();
}

GuiSkill :: ~GuiSkill()
{
	for (unsigned int i = 0; i < button_vec.size(); i++)
	{
		delete button_vec[i];
	}
}


void GuiSkill :: createControlSkillButtons()
{
     	int x = 10;  //self.korpus.kontur_rect.right
     	int y = 50;  //self.korpus.kontur_rect.centery
     	int w = 20;  //skill_w

     	TextureOb* texOb_icon_plus  = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_plus;
     	TextureOb* texOb_icon_minus = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_minus;
     	     	
     	Button* increment_attack_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID, x, y - w,   w, w, "");  
     	button_vec.push_back(increment_attack_button);
     	Button* decrement_attack_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_ATTACK_ID, x, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_attack_button);
                     
     	Button* increment_defence_button  = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID, x + w, y - w,   w, w, "");  
     	button_vec.push_back(increment_defence_button);
     	Button* decrement_defence_button  = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_DEFENCE_ID, x + w, y - 2*w, w, w, "");  
     	button_vec.push_back(decrement_defence_button);
     	        
     	Button* increment_leader_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_LEADER_ID, x + 2*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_leader_button);
     	Button* decrement_leader_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_LEADER_ID, x + 2*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_leader_button);
     	      
     	Button* increment_trader_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_TRADER_ID, x + 3*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_trader_button);
     	Button* decrement_trader_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_TRADER_ID, x + 3*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_trader_button);
    
     	Button* increment_technic_button  = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID, x + 4*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_technic_button);
     	Button* decrement_technic_button  = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_TECHNIC_ID, x + 4*w, y - 2*w, w, w, ""); 
     	button_vec.push_back(decrement_technic_button);
     
     	Button* increment_diplomat_button = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID, x + 5*w, y - w,   w, w, "");  
     	button_vec.push_back(increment_diplomat_button);
     	Button* decrement_diplomat_button = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_DIPLOMAT_ID, x + 5*w, y - 2*w, w, w, "");
        button_vec.push_back(decrement_diplomat_button);     
}

void GuiSkill :: update()
{
	int mxvp = player->GetCursor()->getMousePos().x;
     	int myvp = player->GetScreen()->getHeight()  - player->GetCursor()->getMousePos().y;         
     	int lmb  = player->GetCursor()->getMouseLeftButton();;

	Skill* skill = player->GetNpc()->GetSkill();

	for (unsigned int i = 0; i < button_vec.size(); i++)
	{
		if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
		{
	       		if (lmb == true)
        		{
        	   		switch(button_vec[i]->GetSubTypeId())
        	   		{
        	   	   		case GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID:   { skill->incrementAttack(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_ATTACK_ID:   { skill->decrementAttack(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID:  { skill->incrementDefence(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_DEFENCE_ID:  { skill->decrementDefence(); break; }
          		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_LEADER_ID:   { skill->incrementLeader(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_LEADER_ID:   { skill->decrementLeader(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_TRADER_ID:   { skill->incrementTrader(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_TRADER_ID:   { skill->decrementTrader(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID:  { skill->incrementTechnic(); break; }
        	       			case GUI::BUTTON::SKILL::DECREMENT_TECHNIC_ID:  { skill->decrementTechnic(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID: { skill->incrementDiplomat(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_DIPLOMAT_ID: { skill->decrementDiplomat(); break; }        
           	        	}  		   	
           		}
		}
	}
}


void GuiSkill :: Render() const
{
	Skill* skill = player->GetNpc()->GetScanTarget()->GetOwnerNpc()->GetSkill();
     	TextureOb* texOb_skill = g_UNIQUE_TEXTURE_COLLECTOR.texOb_skill;
     	
    	int w = button_vec[0]->GetRect().getWidth();
     	int h = button_vec[0]->GetRect().getHeight();

 	for (unsigned int bi = 0; bi < button_vec.size(); bi++)
	{
		button_vec[bi]->Render();

		switch(button_vec[bi]->GetSubTypeId())		
		{
			case GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID:
			{
		     		for (int i = 0; i < skill->getAttack(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         		      			     
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
 			break;
			}
			
			case GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID:
			{
		     		for (int i = 0; i < skill->getDefence(); i++) 
     				{		 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
			break;
			}

			case GUI::BUTTON::SKILL::INCREMENT_LEADER_ID:
			{
	   		     	for (int i = 0; i < skill->getLeader(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
			break;
	   		}

	   		case GUI::BUTTON::SKILL::INCREMENT_TRADER_ID:
	   		{
	   	     		for (int i = 0; i < skill->getTrader(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		     				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		     				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
    				}
			break;
	   	   	}
			
	   		case GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID:
	   		{
	   	     		for (int i = 0; i < skill->getTechnic(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		      				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}     
	   		break;
	   		}

	   		case GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID:
	   		{
	   			for (int i = 0; i < skill->getDiplomat(); i++) 
     				{ 
         				Rect tmp_rect = Rect(button_vec[bi]->GetRect().getCenter().x - w/2, 
         		      				     button_vec[bi]->GetRect().getCenter().y + h/2 + i*h, 
         		     				     w, h);
         				drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     				}
	   		break;
	   		}
	   	}
	}
}




