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

#include "../gui/UserInput.hpp"
#include "../common/SaveLoadManager.hpp"

UserInput& UserInput::Instance()
{
	static UserInput instance;
	return instance;
}

UserInput::UserInput()
{
    	keyboardLeftPressed  = false;
    	keyboardRightPressed = false;    
    	keyboardUpPressed    = false;    
    	keyboardDownPressed  = false;  
    
    	scroll_accel_x = 0; 
    	scroll_accel_y = 0;  
    
	next_turn_ready = false;
}

UserInput::~UserInput()
{}
		
void UserInput::UpdateInSpace(Player* player, GuiManager& gui_manager)
{
	GetSimpleInputsInSpace(player, gui_manager);
        GetRealTimeInputs(player);
       	ScrollCamera(player);
}

void UserInput::UpdateInKosmoport(Player* player)
{
	GetSimpleInputsInKosmoport(player);
}

void UserInput::KeyPressedInSpace(Player* player, GuiManager& gui_manager)
{
	switch(event.Key.Code) 
        {
        	case sf::Key::Escape:
        	{
 			if (player->GetNpc()->GetScanTarget() != NULL)
 			{
       		  		if (player->GetNpc()->GetScanTarget() == player->GetNpc()->GetVehicle())
       		  		{
       		  			player->GetNpc()->GetSkill().Acknowledge();
       		  		}
 
          	  		player->GetNpc()->ResetScanTarget();
         		}
         		
         		break;
         	}

         	case sf::Key::Space:
		{
			if (next_turn_ready == false)
			{
				next_turn_ready = true;
			}

			break;
		} 

		// WEAPON SLOTS
		case sf::Key::Num1: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON1_ACTIVATOR_ID)->PressEvent(); break; }
		case sf::Key::Num2: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON2_ACTIVATOR_ID)->PressEvent(); break; }
		case sf::Key::Num3: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON3_ACTIVATOR_ID)->PressEvent(); break; }
		case sf::Key::Num4: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON4_ACTIVATOR_ID)->PressEvent(); break; }
		case sf::Key::Num5: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON5_ACTIVATOR_ID)->PressEvent(); break; } 
		case sf::Key::Num6: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON6_ACTIVATOR_ID)->PressEvent(); break; } 
		case sf::Key::Num7: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON7_ACTIVATOR_ID)->PressEvent(); break; }
		case sf::Key::Num8: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON8_ACTIVATOR_ID)->PressEvent(); break; }            		
		case sf::Key::Num9: { gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON9_ACTIVATOR_ID)->PressEvent(); break; }     
										
		case sf::Key::A:
		{ 
			if (player->GetWeaponsSelector().StatesAreMixed() == true)
			{
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON1_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON2_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON3_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON4_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON5_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON6_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON7_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON8_ACTIVATOR_ID)->Reset();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON9_ACTIVATOR_ID)->Reset();
			}
			else
			{
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON1_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON2_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON3_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON4_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON5_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON6_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON7_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON8_ACTIVATOR_ID)->PressEvent();
				gui_manager.GetGuiRadar().GetButton(GUI::BUTTON::WEAPON9_ACTIVATOR_ID)->PressEvent();
			}
			break;
		}
		
		case sf::Key::G:   // Grapple
		{
			player->GetShow().InverseRangeGrapple();
			break;
		}

		case sf::Key::R: // RADAR
		{
			player->GetShow().InverseRangeRadar();
			break;
		}

		case sf::Key::O: // Orbits
		{
			player->GetShow().InverseAllOrbits();
			break;
		}

		case sf::Key::P: // Path
		{
			player->GetShow().InverseAllPath();
			break;
		}

		case sf::Key::F5: // save event
		{		
			SaveLoadManager::Instance().PerformDelayedSave();			
			break;
		}
		
		case sf::Key::F6: // slow down GAME SPEED 
		{
			if (Config::Instance().GAMESPEED > 1)
			{
				Config::Instance().GAMESPEED--;
			}
			break;
		}

		case sf::Key::F7: // speed up GAME SPEED 
		{
			if (Config::Instance().GAMESPEED < 10)
			{
				Config::Instance().GAMESPEED++;
			}	             			
			break;
		}
		
		case sf::Key::F8: // AutoTurn
		{
			if (Config::Instance().AUTOTURN_MODE == false)
			{
				Config::Instance().AUTOTURN_MODE = true;
			}
			else
			{
				Config::Instance().AUTOTURN_MODE = false;
			}
			break;
		}
		
		case sf::Key::F9:
		{
			SaveLoadManager::Instance().PerformDelayedLoad();
			break;
		}
	}   
}
        
        
void UserInput::KeyPressedInKosmoport(Player* player)
{
	switch(event.Key.Code) 
        {
        	case sf::Key::Escape:
        	{
 			if (player->GetNpc()->GetScanTarget() != NULL)
 			{
       		  		if (player->GetNpc()->GetScanTarget()->GetId() == player->GetNpc()->GetVehicle()->GetId())
       		  		{
       		  			player->GetNpc()->GetSkill().Acknowledge();
       		  		}
 
          	  		player->GetNpc()->ResetScanTarget();
         		}
         		
         		break;
         	}
	}
}

void UserInput::MouseButtonPressed(Player* player)
{
	switch(event.Key.Code) 
	{ 
		case sf::Mouse::Left:  { player->GetCursor().SetLeftMouseButtonClick(true); break; } 
		case sf::Mouse::Right: { player->GetCursor().SetRightMouseButtonClick(true); break; }
	}
}
 
void UserInput::ResetFlags(Player* player)
{  	
	next_turn_ready = false;
}
                		
void UserInput::GetSimpleInputsInSpace(Player* player, GuiManager& gui_manager)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().GetEvent(event))
	{
		switch(event.Type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().Close(); break; }
                        case sf::Event::Resized:    		{ glViewport(0, 0, event.Size.Width, event.Size.Height); /*Screen::Instance().Resize(event.Size.Width, event.Size.Height);*/ break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInSpace(player, gui_manager); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}
             		
void UserInput::GetSimpleInputsInKosmoport(Player* player)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().GetEvent(event))
	{
		switch(event.Type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().Close(); break; }
                        case sf::Event::Resized:    		{ glViewport(0, 0, event.Size.Width, event.Size.Height); /*Screen::Instance().Resize(event.Size.Width, event.Size.Height);*/ break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInKosmoport(player); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}

void UserInput::GetRealTimeInputs(Player* player)
{       
        const sf::Input& Input = Screen::Instance().GetWindow().GetInput();
              
        keyboardLeftPressed  = Input.IsKeyDown(sf::Key::Left);   
        keyboardRightPressed = Input.IsKeyDown(sf::Key::Right);  
        
        keyboardUpPressed    = Input.IsKeyDown(sf::Key::Up);   
        keyboardDownPressed  = Input.IsKeyDown(sf::Key::Down);  
}

void UserInput::ScrollCamera(Player* player)
{
	int SCROLL_VELOCITY_STEP = Config::Instance().SCROLL_VELOCITY_STEP;
	int SCROLL_VELOCITY_MAX  = Config::Instance().SCROLL_VELOCITY_MAX;	
	
        // SCROLLING X AXIS         
        if(keyboardLeftPressed)
        {
            	scroll_accel_x -= SCROLL_VELOCITY_STEP;
            	if (abs(scroll_accel_x) > abs(SCROLL_VELOCITY_MAX))
            	{
                	scroll_accel_x = -SCROLL_VELOCITY_MAX;
            	}
        }
        
        if(keyboardRightPressed)
        {
            	scroll_accel_x += SCROLL_VELOCITY_STEP;
            	if (abs(scroll_accel_x) > abs(SCROLL_VELOCITY_MAX))
            	{
                	scroll_accel_x = SCROLL_VELOCITY_MAX;
            	}
        }
        
        
        if(!keyboardLeftPressed && !keyboardRightPressed)
        {
            	if (scroll_accel_x != 0)
            	{
                	if (scroll_accel_x > 0)
                	{
                    		scroll_accel_x -= SCROLL_VELOCITY_STEP; 
                	} 
                	else if (scroll_accel_x < 0)
                	{
                    		scroll_accel_x += SCROLL_VELOCITY_STEP; 
                	}   
            	}
        }



        // SCROLLING Y AXIS         
        if(keyboardUpPressed)
        {
            	scroll_accel_y += SCROLL_VELOCITY_STEP;
            	if (abs(scroll_accel_y) > abs(SCROLL_VELOCITY_MAX))
            	{
                	scroll_accel_y = SCROLL_VELOCITY_MAX;
            	}
        }
        
        if(keyboardDownPressed)
        {
            	scroll_accel_y -= SCROLL_VELOCITY_STEP;
            	if (abs(scroll_accel_y) > abs(SCROLL_VELOCITY_MAX))
            	{
                	scroll_accel_y = -SCROLL_VELOCITY_MAX;
            	}
        }
        
        
        if(!keyboardUpPressed && !keyboardDownPressed)
        {
            	if (scroll_accel_y != 0)
            	{
                	if (scroll_accel_y > 0)
                	{
                    		scroll_accel_y -= SCROLL_VELOCITY_STEP; 
                	} 
                	else if (scroll_accel_y < 0)
                	{
                    		scroll_accel_y += SCROLL_VELOCITY_STEP; 
                	}   
            	}
        }
      
      	Screen::Instance().MovingBy(vec2f(scroll_accel_x, scroll_accel_y));
}
