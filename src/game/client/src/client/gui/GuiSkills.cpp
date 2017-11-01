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

#include "GuiSkills.hpp"
#include <client/resources/GuiTextureObCollector.hpp>
#include <common/constants.hpp>
#include <jeti/Render.hpp>
#include "ButtonSingle.hpp"

namespace gui {

GuiSkills::GuiSkills():
attack_undo(0),
defence_undo(0),
leader_undo(0),
trader_undo(0),
technic_undo(0),
diplomat_undo(0)
{
    //textureOb_skill = GuiTextureObCollector::Instance().skill;
    //textureOb_skill_transparent = GuiTextureObCollector::Instance().skill_transparent;                  
    
    //int button_w = GUI::BUTTON::SKILLS::BUTTON_WIDTH;  
    //int button_h = GUI::BUTTON::SKILLS::BUTTON_HEIGHT; 
    
    //TextureOb* texOb_icon_plus  = GuiTextureObCollector::Instance().icon_plus;
    //TextureOb* texOb_icon_minus = GuiTextureObCollector::Instance().icon_minus;
         
    //float zpos = -1;
    //float zsize = 1;
    
    {
        //ButtonSingle* Increment_attack_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_ATTACK, "increment attack");  
        //glm::vec3 center(0, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_attack_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_ATTACK, Increment_attack_button));
    }
    
    {
        //ButtonSingle* Decrement_attack_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_ATTACK, "decrement attack");  
        //glm::vec3 center(0, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_attack_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_ATTACK, Decrement_attack_button));
    }
     
    {            
        //ButtonSingle* Increment_defence_button  = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_DEFENCE, "increment defence");  
        //glm::vec3 center(button_w, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_defence_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_DEFENCE, Increment_defence_button));
    }
    
    {
        //ButtonSingle* Decrement_defence_button  = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_DEFENCE, "decrement defence");  
        //glm::vec3 center(button_w, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_defence_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_DEFENCE, Decrement_defence_button));
    }     
    
    {        
        //ButtonSingle* Increment_leader_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_LEADER, "increment leader");  
        //glm::vec3 center(2*button_w, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_leader_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_LEADER, Increment_leader_button));
    }
    
    {
        //ButtonSingle* Decrement_leader_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_LEADER, "decrement leader"); 
        //glm::vec3 center(2*button_w, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_leader_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_LEADER, Decrement_leader_button));
    }
     
    {     
        //ButtonSingle* Increment_trader_button   = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_TRADER, "increment trader");  
        //glm::vec3 center(3*button_w, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_trader_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_TRADER, Increment_trader_button));
    }
    
    {
        //ButtonSingle* Decrement_trader_button   = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_TRADER, "decrement trader"); 
        //glm::vec3 center(3*button_w, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_trader_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_TRADER, Decrement_trader_button));
    }
    
    {
        //ButtonSingle* Increment_technic_button  = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_TECHNIC, "increment technic");  
        //glm::vec3 center(4*button_w, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_technic_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_TECHNIC, Increment_technic_button));
    }
    
    {
        //ButtonSingle* Decrement_technic_button  = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_TECHNIC, "decrement technic"); 
        //glm::vec3 center(4*button_w, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_technic_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_TECHNIC, Decrement_technic_button));
    }
    
    {
        //ButtonSingle* Increment_diplomat_button = new ButtonSingle(texOb_icon_plus, GUI::BUTTON::INCREMENT_DIPLOMAT, "increment diplomat");  
        //glm::vec3 center(5*button_w, -button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Increment_diplomat_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::INCREMENT_DIPLOMAT, Increment_diplomat_button));
    }
    
    {
        //ButtonSingle* Decrement_diplomat_button = new ButtonSingle(texOb_icon_minus, GUI::BUTTON::DECREMENT_DIPLOMAT, "decrement diplomat");
        //glm::vec3 center(5*button_w, -2*button_h, zpos);
        //glm::vec3 size(button_w, button_h, zsize);
        //Box box(center, size);
        //Decrement_diplomat_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::DECREMENT_DIPLOMAT, Decrement_diplomat_button));    
    }
    
    //background_rect.Set(0, 0, 6*button_w, SKILLS::ATTACK_MAX*button_h);    
    textureOb_background = GuiTextureObCollector::Instance().text_background;
}

GuiSkills::~GuiSkills()
{}

void GuiSkills::Acknowledge()
{
    attack_undo   = 0;
    defence_undo  = 0;
    leader_undo   = 0;
    trader_undo   = 0;
    technic_undo  = 0;
    diplomat_undo = 0;
}

void GuiSkills::ButtonsAction(Skills& skills)
{
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
        //BaseButton* button = iterator->second;
        //if (button->GetPressed() == true)
        //{
                //switch(button->subTypeId())
                //{
                    //case GUI::BUTTON::INCREMENT_ATTACK:   
                                //{
                                        //if (skills.IncrementAttack() == true) 
                                        //{
                                            //attack_undo++; 
                                        //}
                                                                        
                                        //break; 
                                //}                    
                                //case GUI::BUTTON::DECREMENT_ATTACK:   
                                //{       
                                        //if (attack_undo > 0)
                                        //{
                                                //skills.DecrementAttack();
                                                //attack_undo--;
                                        //}
                                        
                                        //break; 
                                //}
                                    
                    //case GUI::BUTTON::INCREMENT_DEFENCE:  
                                //{ 
                                        //if (skills.IncrementDefence() == true) 
                                        //{
                                            //defence_undo++;
                                        //}
                                        
                                        //break; 
                                //}                                
                    //case GUI::BUTTON::DECREMENT_DEFENCE:  
                                //{ 
                                        //if (defence_undo > 0)
                                        //{
                                                //skills.DecrementDefence();
                                                //defence_undo--; 
                                        //}
                                        
                                        //break; 
                                //}
                                   
                    //case GUI::BUTTON::INCREMENT_LEADER:   
                                //{ 
                                        //if (skills.IncrementLeader() == true) 
                                        //{
                                            //leader_undo++;
                                        //}
                                        
                                        //break; 
                                //}                                
                    //case GUI::BUTTON::DECREMENT_LEADER:   
                                //{ 
                                        //if (leader_undo > 0)
                                        //{
                                                //skills.DecrementLeader(); 
                                                //leader_undo--;
                                        //}
                                        
                                        //break; 
                                //}
                                    
                    //case GUI::BUTTON::INCREMENT_TRADER:   
                                //{ 
                                        //if (skills.IncrementTrader() == true)
                                        //{
                                            //trader_undo++;
                                        //}
                                        
                                        //break; 
                                //}
                    //case GUI::BUTTON::DECREMENT_TRADER:   
                                //{ 
                                        //if (trader_undo > 0)
                                        //{
                                                //skills.DecrementTrader(); 
                                                //trader_undo--;
                                        //}
                                        
                                        //break; 
                                //}

                    //case GUI::BUTTON::INCREMENT_TECHNIC:  
                                //{ 
                                    //if (skills.IncrementTechnic() == true) 
                                        //{
                                            //technic_undo++;
                                        //}
                                        
                                        //break; 
                                //}
                                //case GUI::BUTTON::DECREMENT_TECHNIC:  
                                //{
                                        //if (technic_undo > 0) 
                                        //{
                                                //skills.DecrementTechnic(); 
                                                //technic_undo--;
                                        //}
                                        
                                        //break; 
                                //}
                                    
                    //case GUI::BUTTON::INCREMENT_DIPLOMAT: 
                                //{ 
                                        //if (skills.IncrementDiplomat() == true) 
                                        //{
                                            //diplomat_undo++;
                                        //}
                                        
                                        //break; 
                                //}
                    //case GUI::BUTTON::DECREMENT_DIPLOMAT: 
                                //{
                                        //if (diplomat_undo > 0)
                                        //{
                                                //skills.DecrementDiplomat(); 
                                                //diplomat_undo--;
                                        //}
                                        //break; 
                                //}        
                   //}
        //}
    //}
}


void GuiSkills::RenderSkills(const Skills& skills) const
{
    //glPushMatrix();
    //{
        //glTranslatef(GetGuiOffset().x, GetGuiOffset().y, 0);
    
        //drawTexturedRect(textureOb_background, background_rect, -1.0);
        //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
        //{
            //BaseButton* button = iterator->second;
            //switch(button->subTypeId())
            //{
                //case GUI::BUTTON::INCREMENT_ATTACK:
                //{              
                         //for (int i=0; i<SKILLS::ATTACK_MAX; i++) 
                         //{ 
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                             //button->GetBox().center().y + button_h/2 + i*button_h, 
                                             //button_w, button_h);

                             //if (i<skills.GetAttack())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                         //}
             
                     //break;
                //}
            
                //case GUI::BUTTON::INCREMENT_DEFENCE:
                //{
                         //for (int i=0; i<SKILLS::DEFENCE_MAX; i++) 
                         //{         
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                             //button->GetBox().center().y + button_h/2 + i*button_h, 
                                             //button_w, button_h);
                             //if (i<skills.GetDefence())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                         //}
                
                    //break;
                //}

                //case GUI::BUTTON::INCREMENT_LEADER:
                //{
                            //for (int i=0; i<SKILLS::LEADER_MAX; i++) 
                         //{ 
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                             //button->GetBox().center().y + button_h/2 + i*button_h, 
                                             //button_w, button_h);
                             //if (i<skills.GetLeader())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                         //}
                
                    //break;
                   //}

                   //case GUI::BUTTON::INCREMENT_TRADER:
                   //{
                            //for (int i=0; i<SKILLS::TRADER_MAX; i++) 
                         //{ 
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                            //button->GetBox().center().y + button_h/2 + i*button_h, 
                                            //button_w, button_h);
                             //if (i<skills.GetTrader())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                        //}
                
                    //break;
                      //}
            
                   //case GUI::BUTTON::INCREMENT_TECHNIC:
                   //{
                            //for (int i=0; i<SKILLS::TECHNIC_MAX; i++) 
                         //{ 
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                             //button->GetBox().center().y + button_h/2 + i*button_h, 
                                             //button_w, button_h);
                             //if (i<skills.GetTechnic())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                         //}     
                       //break;
                   //}

                   //case GUI::BUTTON::INCREMENT_DIPLOMAT:
                   //{
                       //for (int i=0; i<SKILLS::DIPLOMAT_MAX; i++) 
                         //{ 
                             //Rect tmp_rect(button->GetBox().center().x - button_w/2, 
                                             //button->GetBox().center().y + button_h/2 + i*button_h, 
                                            //button_w, button_h);
                             //if (i<skills.GetDiplomat())     { drawTexturedRect(textureOb_skill, tmp_rect, -1.0); }    
                             //else                 { drawTexturedRect(textureOb_skill_transparent, tmp_rect, -1.0); }
                         //}
                       //break;
                   //}
               //}
        //}
    //}
    //glPopMatrix();
}

} // namespace gui


