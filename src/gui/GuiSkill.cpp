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



GuiSkill::GuiSkill()
{
     	textureOb_skill = GuiTextureObCollector::Instance().skill;
     	textureOb_skill_transparent = GuiTextureObCollector::Instance().skill_transparent;     	     	

     	button_w = GUI::BUTTON::SKILL::BUTTON_WIDTH;  
     	button_h = GUI::BUTTON::SKILL::BUTTON_HEIGHT; 
     	
     	vec2i center(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);
     	TextureOb* texOb_icon_plus  = GuiTextureObCollector::Instance().icon_plus;
     	TextureOb* texOb_icon_minus = GuiTextureObCollector::Instance().icon_minus;
     	     	
     	ButtonSingle* Increment_attack_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_ATTACK_ID, "increment attack");  
     	Increment_attack_button->SetRect(Rect(center.x, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_ATTACK_ID, Increment_attack_button));
     	
     	ButtonSingle* Decrement_attack_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_ATTACK_ID, "decrement attack");  
     	Decrement_attack_button->SetRect(Rect(center.x, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_ATTACK_ID, Decrement_attack_button));
        
                     
     	ButtonSingle* Increment_defence_button  = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_DEFENCE_ID, "increment defence");  
     	Increment_defence_button->SetRect(Rect(center.x + button_w, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_DEFENCE_ID, Increment_defence_button));
     	
     	ButtonSingle* Decrement_defence_button  = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_DEFENCE_ID, "decrement defence");  
     	Decrement_defence_button->SetRect(Rect(center.x + button_w, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_DEFENCE_ID, Decrement_defence_button));
     	     
     	        
     	ButtonSingle* Increment_leader_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_LEADER_ID, "increment leader");  
     	Increment_leader_button->SetRect(Rect(center.x + 2*button_w, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_LEADER_ID, Increment_leader_button));
     	
     	ButtonSingle* Decrement_leader_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_LEADER_ID, "decrement leader"); 
     	Decrement_leader_button->SetRect(Rect(center.x + 2*button_w, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_LEADER_ID, Decrement_leader_button));
     	
     	      
     	ButtonSingle* Increment_trader_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_TRADER_ID, "increment trader");  
     	Increment_trader_button->SetRect(Rect(center.x + 3*button_w, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_TRADER_ID, Increment_trader_button));
     	
     	ButtonSingle* Decrement_trader_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_TRADER_ID, "decrement trader"); 
     	Decrement_trader_button->SetRect(Rect(center.x + 3*button_w, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_TRADER_ID, Decrement_trader_button));
    
    
     	ButtonSingle* Increment_technic_button  = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_TECHNIC_ID, "increment technic");  
 	Increment_technic_button->SetRect(Rect(center.x + 4*button_w, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_TECHNIC_ID, Increment_technic_button));
    
     	ButtonSingle* Decrement_technic_button  = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_TECHNIC_ID, "decrement technic"); 
        Decrement_technic_button->SetRect(Rect(center.x + 4*button_w, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_TECHNIC_ID, Decrement_technic_button));
     
     	ButtonSingle* Increment_diplomat_button = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_DIPLOMAT_ID, "increment diplomat");  
     	Increment_diplomat_button->SetRect(Rect(center.x + 5*button_w, center.y - button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_DIPLOMAT_ID, Increment_diplomat_button));
     	
     	ButtonSingle* Decrement_diplomat_button = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_DIPLOMAT_ID, "decrement diplomat");
     	Decrement_diplomat_button->SetRect(Rect(center.x + 5*button_w, center.y - 2*button_h, button_w, button_h));
     	button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_DIPLOMAT_ID, Decrement_diplomat_button));    

	background_rect.Set(center.x, center.y, 6*button_w, SKILL::ATTACK_MAX*button_h);	
	textureOb_background = GuiTextureObCollector::Instance().text_background;
}

GuiSkill::~GuiSkill()
{}

void GuiSkill::ButtonsAction(Skill& skill) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
		if (button->GetPressed() == true)
		{
        		switch(button->GetSubTypeId())
        		{
        			case GUI::BUTTON::INCREMENT_ATTACK_ID:   { skill.IncrementAttack(); break; }
        			case GUI::BUTTON::DECREMENT_ATTACK_ID:   { skill.DecrementAttack(); break; }
           		   	      	
        			case GUI::BUTTON::INCREMENT_DEFENCE_ID:  { skill.IncrementDefence(); break; }
        			case GUI::BUTTON::DECREMENT_DEFENCE_ID:  { skill.DecrementDefence(); break; }
          		   	      	
        			case GUI::BUTTON::INCREMENT_LEADER_ID:   { skill.IncrementLeader(); break; }
        			case GUI::BUTTON::DECREMENT_LEADER_ID:   { skill.DecrementLeader(); break; }
           		   	      	
        			case GUI::BUTTON::INCREMENT_TRADER_ID:   { skill.IncrementTrader(); break; }
        			case GUI::BUTTON::DECREMENT_TRADER_ID:   { skill.DecrementTrader(); break; }
           		   	      	
        			case GUI::BUTTON::INCREMENT_TECHNIC_ID:  { skill.IncrementTechnic(); break; }
        			case GUI::BUTTON::DECREMENT_TECHNIC_ID:  { skill.DecrementTechnic(); break; }
           		   	      	
        			case GUI::BUTTON::INCREMENT_DIPLOMAT_ID: { skill.IncrementDiplomat(); break; }
        			case GUI::BUTTON::DECREMENT_DIPLOMAT_ID: { skill.DecrementDiplomat(); break; }        
           		}  		   	
		}
	}
}


void GuiSkill::RenderSkills(const Skill& skill) const
{
	glPushMatrix();
	{
		glTranslatef(offset.x, offset.y, 0);
	
		drawTexturedRect(textureOb_background, background_rect, -1.0);
		for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
		{
			BaseButton* button = iterator->second;
			switch(button->GetSubTypeId())		
			{
				case GUI::BUTTON::INCREMENT_ATTACK_ID:
				{  			
		     			for (int i=0; i<SKILL::ATTACK_MAX; i++) 
     					{ 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		      				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		      				      button_w, button_h);

     						if (i<skill.GetAttack()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
     					}
 			
 					break;
				}
			
				case GUI::BUTTON::INCREMENT_DEFENCE_ID:
				{
		     			for (int i=0; i<SKILL::DEFENCE_MAX; i++) 
     					{		 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		      				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		      				      button_w, button_h);
         					if (i<skill.GetDefence()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
     					}
				
					break;
				}

				case GUI::BUTTON::INCREMENT_LEADER_ID:
				{
	   		     		for (int i=0; i<SKILL::LEADER_MAX; i++) 
     					{ 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		      				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		      				      button_w, button_h);
         					if (i<skill.GetLeader()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
     					}
				
					break;
	   			}

	   			case GUI::BUTTON::INCREMENT_TRADER_ID:
	   			{
	   	     			for (int i=0; i<SKILL::TRADER_MAX; i++) 
     					{ 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		     				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		     				      button_w, button_h);
         					if (i<skill.GetTrader()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
    					}
				
					break;
	   	   		}
			
	   			case GUI::BUTTON::INCREMENT_TECHNIC_ID:
	   			{
	   	     			for (int i=0; i<SKILL::TECHNIC_MAX; i++) 
     					{ 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		      				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		      				      button_w, button_h);
         					if (i<skill.GetTechnic()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
     					}     
	   				break;
	   			}

	   			case GUI::BUTTON::INCREMENT_DIPLOMAT_ID:
	   			{
	   				for (int i=0; i<SKILL::DIPLOMAT_MAX; i++) 
     					{ 
         					Rect tmp_rect(button->GetRect().GetCenter().x - button_w/2, 
         		      				      button->GetRect().GetCenter().y + button_h/2 + i*button_h, 
         		     				      button_w, button_h);
         					if (i<skill.GetDiplomat()) 	{ drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }	
     						else 				{ drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
     					}
	   				break;
	   			}
	   		}
		}
	}
	glPopMatrix();
}




