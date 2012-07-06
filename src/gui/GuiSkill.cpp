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



GuiSkill::GuiSkill(Player* player)
{
	this->player = player;
	
     	texOb_skill = g_UNIQUE_TEXTURE_COLLECTOR.texOb_skill;
     	     	

     	vec2i center(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);
     	int w = 20;  //skill_w
     	TextureOb* texOb_icon_plus  = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_plus;
     	TextureOb* texOb_icon_minus = g_UNIQUE_TEXTURE_COLLECTOR.texOb_icon_minus;
     	     	
     	Button* Increment_attack_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID, center.x, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_attack_button);
     	Button* Decrement_attack_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_ATTACK_ID, center.x, center.y - 2*w, w, w, "");  
     	button_vec.push_back(Decrement_attack_button);
                     
     	Button* Increment_defence_button  = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID, center.x + w, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_defence_button);
     	Button* Decrement_defence_button  = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_DEFENCE_ID, center.x + w, center.y - 2*w, w, w, "");  
     	button_vec.push_back(Decrement_defence_button);
     	        
     	Button* Increment_leader_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_LEADER_ID, center.x + 2*w, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_leader_button);
     	Button* Decrement_leader_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_LEADER_ID, center.x + 2*w, center.y - 2*w, w, w, ""); 
     	button_vec.push_back(Decrement_leader_button);
     	      
     	Button* Increment_trader_button   = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_TRADER_ID, center.x + 3*w, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_trader_button);
     	Button* Decrement_trader_button   = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_TRADER_ID, center.x + 3*w, center.y - 2*w, w, w, ""); 
     	button_vec.push_back(Decrement_trader_button);
    
     	Button* Increment_technic_button  = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID, center.x + 4*w, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_technic_button);
     	Button* Decrement_technic_button  = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_TECHNIC_ID, center.x + 4*w, center.y - 2*w, w, w, ""); 
     	button_vec.push_back(Decrement_technic_button);
     
     	Button* Increment_diplomat_button = new Button(texOb_icon_plus, GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID, center.x + 5*w, center.y - w,   w, w, "");  
     	button_vec.push_back(Increment_diplomat_button);
     	Button* Decrement_diplomat_button = new Button(texOb_icon_minus, GUI::BUTTON::SKILL::DECREMENT_DIPLOMAT_ID, center.x + 5*w, center.y - 2*w, w, w, "");
        button_vec.push_back(Decrement_diplomat_button);     
}

GuiSkill::~GuiSkill()
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
		delete button_vec[i];
	}
}

bool GuiSkill::UpdateMouseInteraction(int mxvp, int myvp, int lmb, int rmb, Skill* skill)
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
		if (button_vec[i]->CheckInteraction(mxvp - offset.x, myvp - offset.y) == true)
		{
	       		if (lmb == true)
        		{
        	   		switch(button_vec[i]->GetSubTypeId())
        	   		{
        	   	   		case GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID:   { skill->IncrementAttack(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_ATTACK_ID:   { skill->DecrementAttack(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID:  { skill->IncrementDefence(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_DEFENCE_ID:  { skill->DecrementDefence(); break; }
          		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_LEADER_ID:   { skill->IncrementLeader(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_LEADER_ID:   { skill->DecrementLeader(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_TRADER_ID:   { skill->IncrementTrader(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_TRADER_ID:   { skill->DecrementTrader(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID:  { skill->IncrementTechnic(); break; }
        	       			case GUI::BUTTON::SKILL::DECREMENT_TECHNIC_ID:  { skill->DecrementTechnic(); break; }
           		   	      	
        	   			case GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID: { skill->IncrementDiplomat(); break; }
        	        		case GUI::BUTTON::SKILL::DECREMENT_DIPLOMAT_ID: { skill->DecrementDiplomat(); break; }        
           	        	}  		   	
           		}
		
			return true;
		}
	}
}


void GuiSkill::Render(Skill* skill) const
{    	
    	int w = button_vec[0]->GetRect().GetWidth();
     	int h = button_vec[0]->GetRect().GetHeight();

	glPushMatrix();
	{
		glTranslatef(offset.x, offset.y, 0);
 		for (unsigned int bi = 0; bi < button_vec.size(); bi++)
		{
			button_vec[bi]->Render();

			switch(button_vec[bi]->GetSubTypeId())		
			{
				case GUI::BUTTON::SKILL::INCREMENT_ATTACK_ID:
				{
		     			for (int i = 0; i < skill->GetAttack(); i++) 
     					{ 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		      					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		      					     w, h);
         		      			     
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     					}
 			
 					break;
				}
			
				case GUI::BUTTON::SKILL::INCREMENT_DEFENCE_ID:
				{
		     			for (int i = 0; i < skill->GetDefence(); i++) 
     					{		 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		      					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		      					     w, h);
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     					}
				
					break;
				}

				case GUI::BUTTON::SKILL::INCREMENT_LEADER_ID:
				{
	   		     		for (int i = 0; i < skill->GetLeader(); i++) 
     					{ 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		      					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		      					     w, h);
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     					}
				
					break;
	   			}

	   			case GUI::BUTTON::SKILL::INCREMENT_TRADER_ID:
	   			{
	   	     			for (int i = 0; i < skill->GetTrader(); i++) 
     					{ 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		     					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		     					     w, h);
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
    					}
				
					break;
	   	   		}
			
	   			case GUI::BUTTON::SKILL::INCREMENT_TECHNIC_ID:
	   			{
	   	     			for (int i = 0; i < skill->GetTechnic(); i++) 
     					{ 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		      					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		      					     w, h);
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     					}     
	   				break;
	   			}

	   			case GUI::BUTTON::SKILL::INCREMENT_DIPLOMAT_ID:
	   			{
	   				for (int i = 0; i < skill->GetDiplomat(); i++) 
     					{ 
         					Rect tmp_rect = Rect(button_vec[bi]->GetRect().GetCenter().x - w/2, 
         		      					     button_vec[bi]->GetRect().GetCenter().y + h/2 + i*h, 
         		     					     w, h);
         					drawTexturedRect(texOb_skill, tmp_rect, -1.0);
     					}
	   				break;
	   			}
	   		}
		}
	}
	glPopMatrix();
}




