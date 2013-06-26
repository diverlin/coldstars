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

#include "UserInput.hpp"
#include "BaseButton.hpp"
#include "../world/EntityManager.hpp"
#include "../config/config.hpp"
#include "../render/Screen.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../pilots/Npc.hpp"
#include "../pilots/Player.hpp"
#include "../gui/GuiManager.hpp"

UserInput& UserInput::Instance()
{
	static UserInput instance;
	return instance;
}

UserInput::UserInput()
{
    	moveCamera_axis_x = CAMERADIRECTION::NONE;
        moveCamera_axis_y = CAMERADIRECTION::NONE;
            
	next_turn_ready = false;
}

UserInput::~UserInput()
{}
		
void UserInput::UpdateInSpace(Player* player)
{
	ManageInputsInSpace(player);
       	ManageRealTimeInputsInSpace(player);
	ScrollCamera(player);
}

void UserInput::UpdateInKosmoport(Player* player)
{
	ManageInputsInKosmoport(player);
}

bool UserInput::KeyPressedCommon(Player* player)
{
	switch(event.key.code) 
	{
		case sf::Keyboard::Escape:
		{
			if (GuiManager::Instance().GetGuiVehicleScan()->GetVehicle() != nullptr)
			{
				if (GuiManager::Instance().GetGuiVehicleScan()->GetBlockManualExit() == false)
				{
					if (GuiManager::Instance().GetGuiKosmoport().GetInitDone() == true)
					{
						GuiManager::Instance().GetGuiKosmoport().ExitGuiScan();
					}
					if (GuiManager::Instance().GetGuiSpace().GetInitDone() == true)
					{
						GuiManager::Instance().GetGuiSpace().ExitGuiScan();
					}
				}
			}
			
			if (GuiManager::Instance().GetGuiSpace().GetGuiVehicleTarget().GetVehicle() != nullptr)
			{
				GuiManager::Instance().GetGuiSpace().GetGuiVehicleTarget().Reset();
			}
			
			return true; break;
		}
	}
	
	return false;
}

void UserInput::KeyPressedInSpace(Player* player)
{        
        if (KeyPressedCommon(player) == true)
	{
		return; 
	}

	switch(event.key.code) 
        {
         	case sf::Keyboard::Space:
		{
			if (next_turn_ready == false)
			{
				next_turn_ready = true;
			}

			break;
		} 

		//DRIVE SLOT
		case sf::Keyboard::F: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::DRIVE_SLOT_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}	
		
		// WEAPON SLOTS
		case sf::Keyboard::Num1: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT1_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}		
		case sf::Keyboard::Num2: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT2_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num3: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT3_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num4: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT4_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num5: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT5_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num6: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT6_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num7: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT7_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}
		case sf::Keyboard::Num8: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT8_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		}        		
		case sf::Keyboard::Num9: 
		{ 
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT9_ID);
			if (button)
			{
				button->PressEvent(player); 
			}
			
			break; 
		
		} 
										
		case sf::Keyboard::A:
		{ 
			if (player->GetNpc()->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
			{
				BaseGuiElement* button = nullptr;
				
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT1_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT2_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT3_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT4_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT5_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT6_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT7_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT8_ID);
				if (button)
				{
					button->Reset();
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT9_ID);
				if (button)
				{
					button->Reset();
				}
			}
			else
			{
				BaseGuiElement* button = nullptr;
				
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT1_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT2_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT3_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT4_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT5_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT6_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT7_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT8_ID);
				if (button)
				{
					button->PressEvent(player);
				}
				button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::WEAPON_SLOT9_ID);
				if (button)
				{
					button->PressEvent(player);
				}
			}
			break;
		}

		case sf::Keyboard::C:   
		{
			Screen::Instance().InitiateScrollTo(player->GetNpc()->GetVehicle()->GetCenter());
			break;
		}
				
		case sf::Keyboard::G: // Grapple
		{
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(ENTITY::GRAPPLE_SLOT_ID);
			if (button)
			{
				//button->PressEvent(player);
			}

			break;
		}

		case sf::Keyboard::M: // RADAR
		{
			BaseGuiElement* button = GuiManager::Instance().GetGuiSpace().GetGuiVehiclePlayer().GetGuiElement(GUI::BUTTON::GALAXYMAP_ID);
			if (button)
			{
				button->PressEvent(player);
			}
			
			break;
		}
		
		case sf::Keyboard::R: // RADAR
		{
			player->GetShow().InverseRangeRadar();
			break;
		}

		case sf::Keyboard::O: // Orbits
		{
			player->GetShow().InverseAllOrbits();
			break;
		}

		case sf::Keyboard::P: // Path
		{
			player->GetShow().InverseAllPath();
			break;
		}

		case sf::Keyboard::F1: // god mode on/off
		{	
			std::cout<<"god_mode ="<<!player->GetNpc()->GetVehicle()->GetGodMode()<<std::endl;
			player->GetNpc()->GetVehicle()->SetGodMode(!player->GetNpc()->GetVehicle()->GetGodMode());			
			break;
		}

		case sf::Keyboard::F3: // auto save mode
		{		
			Config::Instance().SetAutoSaveMode(!Config::Instance().GetAutoSaveMode());			
			break;
		}
		
		case sf::Keyboard::F4: // auto load mode
		{		
			Config::Instance().SetAutoLoadMode(!Config::Instance().GetAutoLoadMode());		
			break;
		}
				
		case sf::Keyboard::F5: // save event
		{		
			EntityManager::Instance().SaveRequest();			
			break;
		}
		
		case sf::Keyboard::F6: // slow down GAME SPEED 
		{
			if (Config::Instance().GAME_SPEED > 1)
			{
				Config::Instance().GAME_SPEED--;
			}
			break;
		}

		case sf::Keyboard::F7: // speed up GAME SPEED 
		{
			if (Config::Instance().GAME_SPEED < 10)
			{
				Config::Instance().GAME_SPEED++;
			}	             			
			break;
		}
		
		case sf::Keyboard::F8: // AutoTurn
		{
			Config::Instance().AUTO_TURN_MODE = !Config::Instance().AUTO_TURN_MODE;
			break;
		}
		
		case sf::Keyboard::F9:
		{
			EntityManager::Instance().LoadRequest();
			break;
		}			
	}   
}
        
        
void UserInput::KeyPressedInKosmoport(Player* player)
{
	if (KeyPressedCommon(player) == true)
	{
		return; 
	}
}

void UserInput::MouseButtonPressed(Player* player)
{
	switch(event.key.code) 
	{ 
		case sf::Mouse::Left:  { player->GetCursor().SetLeftMouseButtonClick(true); break; } 
		case sf::Mouse::Right: { player->GetCursor().SetRightMouseButtonClick(true); break; }
	}
}
 
void UserInput::ResetFlags(Player* player)
{       
	next_turn_ready = false;
}
                		
void UserInput::ManageInputsInSpace(Player* player)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().pollEvent(event))
	{
		switch(event.type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().close(); break; }
                        //case sf::Event::Resized:    		{ Screen::Instance().Resize(event.size.x, event.size.y); break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInSpace(player); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}
             		
void UserInput::ManageInputsInKosmoport(Player* player)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().pollEvent(event))
	{
		switch(event.type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().close(); break; }
                        //case sf::Event::Resized:    		{ Screen::Instance().Resize(event.Size.Width, event.Size.Height); break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInKosmoport(player); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}

void UserInput::ManageRealTimeInputsInSpace(Player* player)
{       
	moveCamera_axis_x  = CAMERADIRECTION::NONE;
        moveCamera_axis_y  = CAMERADIRECTION::NONE;
        
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(Screen::Instance().GetWindow());
           
        int mx = player->GetCursor().GetMouseData().mx;
        int my = player->GetCursor().GetMouseData().my;

        int screen_w = Screen::Instance().GetWidth();
        int screen_h = Screen::Instance().GetHeight();
        
        bool mouse_camera_scroll = Config::Instance().GetMouseCameraScroll();
                 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
	{	        	
		moveCamera_axis_x = CAMERADIRECTION::LEFT;
	}   		
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
	{	        	
		moveCamera_axis_x = CAMERADIRECTION::RIGHT;
	}   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
	{	        	
		moveCamera_axis_y = CAMERADIRECTION::UP;
	}   
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true)
	{	        	
		moveCamera_axis_y = CAMERADIRECTION::DOWN;
	}   
	                 	
        if ((mouse_camera_scroll)and(mx < SCROLL_BORDER_OFFSET)) 
        {
      		moveCamera_axis_x = CAMERADIRECTION::LEFT;
        }   
        if ((mouse_camera_scroll)and(mx > (screen_w - SCROLL_BORDER_OFFSET)))
        {
        	moveCamera_axis_x = CAMERADIRECTION::RIGHT;
        }   
        if ((mouse_camera_scroll)and(my > (screen_h - SCROLL_BORDER_OFFSET)))
        {
       		moveCamera_axis_y = CAMERADIRECTION::UP;
        }   
        if ((mouse_camera_scroll)and(my < SCROLL_BORDER_OFFSET)) 
        {
        	moveCamera_axis_y = CAMERADIRECTION::DOWN;
        }   
}

void UserInput::ScrollCamera(Player* player)
{
	int SCROLL_VELOCITY_STEP = Config::Instance().SCROLL_VELOCITY_STEP;
	int SCROLL_VELOCITY_MAX  = Config::Instance().SCROLL_VELOCITY_MAX;	

        // SCROLLING X AXIS         
        switch (moveCamera_axis_x)
        {
        	case CAMERADIRECTION::LEFT:
	        {
	            	scroll_accel.x -= SCROLL_VELOCITY_STEP;
	            	if (fabs(scroll_accel.x) > fabs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.x = -SCROLL_VELOCITY_MAX;
	            	}
	            	
	            	break;
	        }
        
        	case CAMERADIRECTION::RIGHT:
	        {
	            	scroll_accel.x += SCROLL_VELOCITY_STEP;
	            	if (fabs(scroll_accel.x) > fabs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.x = SCROLL_VELOCITY_MAX;
	            	}
	 
	 		break;
	        }

		case CAMERADIRECTION::NONE:
		{
			if (scroll_accel.x != 0)
	            	{
	                	if (scroll_accel.x > 0)
	                	{
	                    		scroll_accel.x -= SCROLL_VELOCITY_STEP; 
	                	} 
	                	else if (scroll_accel.x < 0)
	                	{
	                    		scroll_accel.x += SCROLL_VELOCITY_STEP; 
	                	}   
	            	}
	            	
	            	break;	
		}
	}

	switch(moveCamera_axis_y)
	{
	        case CAMERADIRECTION::UP:
	        {
	            	scroll_accel.y += SCROLL_VELOCITY_STEP;
	            	if (fabs(scroll_accel.y) > fabs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.y = SCROLL_VELOCITY_MAX;
	            	}
	            	
	            	break;
	        }
	        
	        case CAMERADIRECTION::DOWN:
	        {
	            	scroll_accel.y -= SCROLL_VELOCITY_STEP;
	            	if (fabs(scroll_accel.y) > fabs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.y = -SCROLL_VELOCITY_MAX;
	            	}
	            	
	            	break;
	        }
	        
	        case CAMERADIRECTION::NONE:
	        {
	            	if (scroll_accel.y != 0)
	            	{
	                	if (scroll_accel.y > 0)
	                	{
	                    		scroll_accel.y -= SCROLL_VELOCITY_STEP; 
	                	} 
	                	else if (scroll_accel.y < 0)
	                	{
	                    		scroll_accel.y += SCROLL_VELOCITY_STEP; 
	                	}   
	            	}
	        	
	        	break;
	        }
	}
     
      	Screen::Instance().MovingBy(scroll_accel);
}
