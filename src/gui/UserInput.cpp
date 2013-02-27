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
		
void UserInput::UpdateInSpace(Player* player, GuiManager& gui_manager)
{
	ManageInputsInSpace(player, gui_manager);
        ManageRealTimeInputsInSpace(player);
       	ScrollCamera(player);
}

void UserInput::UpdateInKosmoport(Player* player, GuiManager& gui_manager)
{
	ManageInputsInKosmoport(player, gui_manager);
}

bool UserInput::KeyPressedCommon(Player* player, GuiManager& gui_manager)
{
	switch(event.Key.Code) 
        {
        	case sf::Key::Escape:
        	{
        		if (player->GetGuiManager().GetGuiVehicleScan()->GetVehicle() != NULL)
			{
				if (player->GetGuiManager().GetGuiVehicleScan()->GetBlockManualExit() == false)
				{
					if (player->GetGuiManager().GetGuiKosmoport().GetInitDone() == true)
					{
						player->GetGuiManager().GetGuiKosmoport().ExitGuiScan();
					}
					if (player->GetGuiManager().GetGuiSpace().GetInitDone() == true)
					{
						player->GetGuiManager().GetGuiSpace().ExitGuiScan();
					}
				}
			}
			
			if (player->GetGuiManager().GetGuiSpace().GetGuiVehicleTarget().GetVehicle() != NULL)
			{
				player->GetGuiManager().GetGuiSpace().GetGuiVehicleTarget().Reset();
			}
         		
         		return true; break;
         	}
	}
	
	return false;
}

void UserInput::KeyPressedInSpace(Player* player, GuiManager& gui_manager)
{
	if (KeyPressedCommon(player, gui_manager) == true)
	{
		return; 
	}
	
	switch(event.Key.Code) 
        {
         	case sf::Key::Space:
		{
			if (next_turn_ready == false)
			{
				next_turn_ready = true;
			}

			break;
		} 

		//DRIVE SLOT
		case sf::Key::F: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::DRIVE_SLOT_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}	
		
		// WEAPON SLOTS
		case sf::Key::Num1: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT1_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}		
		case sf::Key::Num2: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT2_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num3: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT3_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num4: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT4_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num5: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT5_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num6: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT6_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num7: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT7_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}
		case sf::Key::Num8: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT8_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		}        		
		case sf::Key::Num9: 
		{ 
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT9_ID);
			if (button)
			{
				button->PressEvent(); 
			}
			
			break; 
		
		} 
										
		case sf::Key::A:
		{ 
			if (player->GetNpc()->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
			{
				BaseButton* button = NULL;
				
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT1_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT2_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT3_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT4_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT5_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT6_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT7_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT8_ID);
				if (button)
				{
					button->Reset();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT9_ID);
				if (button)
				{
					button->Reset();
				}
			}
			else
			{
				BaseButton* button = NULL;
				
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT1_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT2_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT3_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT4_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT5_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT6_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT7_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT8_ID);
				if (button)
				{
					button->PressEvent();
				}
				button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::WEAPON_SLOT9_ID);
				if (button)
				{
					button->PressEvent();
				}
			}
			break;
		}

		case sf::Key::C:   
		{
			Screen::Instance().InitiateScrollTo(player->GetNpc()->GetVehicle()->GetPoints().GetCenter());
			break;
		}
				
		case sf::Key::G: // Grapple
		{
			BaseButton* button = gui_manager.GetGuiSpace().GetGuiVehiclePlayer().GetButton(ENTITY::GRAPPLE_SLOT_ID);
			if (button)
			{
				button->PressEvent();
			}

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

		case sf::Key::F1: // god mode on/off
		{	
			std::cout<<"god_mode ="<<!player->GetNpc()->GetVehicle()->GetGodMode()<<std::endl;
			player->GetNpc()->GetVehicle()->SetGodMode(!player->GetNpc()->GetVehicle()->GetGodMode());			
			break;
		}

		case sf::Key::F3: // auto save mode
		{		
			Config::Instance().SetAutoSaveMode(!Config::Instance().GetAutoSaveMode());			
			break;
		}
		
		case sf::Key::F4: // auto load mode
		{		
			Config::Instance().SetAutoLoadMode(!Config::Instance().GetAutoLoadMode());		
			break;
		}
				
		case sf::Key::F5: // save event
		{		
			EntityManager::Instance().SaveRequest();			
			break;
		}
		
		case sf::Key::F6: // slow down GAME SPEED 
		{
			if (Config::Instance().GAME_SPEED > 1)
			{
				Config::Instance().GAME_SPEED--;
			}
			break;
		}

		case sf::Key::F7: // speed up GAME SPEED 
		{
			if (Config::Instance().GAME_SPEED < 10)
			{
				Config::Instance().GAME_SPEED++;
			}	             			
			break;
		}
		
		case sf::Key::F8: // AutoTurn
		{
			Config::Instance().AUTO_TURN_MODE = !Config::Instance().AUTO_TURN_MODE;
			break;
		}
		
		case sf::Key::F9:
		{
			EntityManager::Instance().LoadRequest();
			break;
		}
	}   
}
        
        
void UserInput::KeyPressedInKosmoport(Player* player, GuiManager& gui_manager)
{
	if (KeyPressedCommon(player, gui_manager) == true)
	{
		return; 
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
                		
void UserInput::ManageInputsInSpace(Player* player, GuiManager& gui_manager)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().GetEvent(event))
	{
		switch(event.Type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().Close(); break; }
                        case sf::Event::Resized:    		{ Screen::Instance().Resize(event.Size.Width, event.Size.Height); break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInSpace(player, gui_manager); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}
             		
void UserInput::ManageInputsInKosmoport(Player* player, GuiManager& gui_manager)
{
	ResetFlags(player);
			
	while (Screen::Instance().GetWindow().GetEvent(event))
	{
		switch(event.Type)
	        {
	        	case sf::Event::Closed:     		{ Screen::Instance().GetWindow().Close(); break; }
                        case sf::Event::Resized:    		{ Screen::Instance().Resize(event.Size.Width, event.Size.Height); break; }
	        	case sf::Event::KeyPressed: 		{ KeyPressedInKosmoport(player, gui_manager); break; }
	                case sf::Event::MouseButtonPressed: 	{ MouseButtonPressed(player); break; }
	        }	      
	 }
}

void UserInput::ManageRealTimeInputsInSpace(Player* player)
{       
        const sf::Input& Input = Screen::Instance().GetWindow().GetInput();
        
        moveCamera_axis_x  = CAMERADIRECTION::NONE;
        moveCamera_axis_y  = CAMERADIRECTION::NONE;
           
        int mx = player->GetCursor().GetMouseData().mx;
        int my = player->GetCursor().GetMouseData().my;
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
        
        bool mouse_camera_scroll = Config::Instance().GetMouseCameraScroll();
                           	
        if ( (Input.IsKeyDown(sf::Key::Left) == true) or ((mouse_camera_scroll)and(mx < SCROLL_BORDER_OFFSET)) )
        {
      		moveCamera_axis_x = CAMERADIRECTION::LEFT;
        }   
        if ( (Input.IsKeyDown(sf::Key::Right) == true) or ((mouse_camera_scroll)and(mx > (screen_w - SCROLL_BORDER_OFFSET))) )
        {
        	moveCamera_axis_x = CAMERADIRECTION::RIGHT;
        }   
        if ( (Input.IsKeyDown(sf::Key::Up) == true) or ((mouse_camera_scroll)and(my > (screen_h - SCROLL_BORDER_OFFSET))) )
        {
       		moveCamera_axis_y = CAMERADIRECTION::UP;
        }   
        if ( (Input.IsKeyDown(sf::Key::Down) == true) or ((mouse_camera_scroll)and(my < SCROLL_BORDER_OFFSET)) )
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
	            	if (abs(scroll_accel.x) > abs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.x = -SCROLL_VELOCITY_MAX;
	            	}
	            	
	            	break;
	        }
        
        	case CAMERADIRECTION::RIGHT:
	        {
	            	scroll_accel.x += SCROLL_VELOCITY_STEP;
	            	if (abs(scroll_accel.x) > abs(SCROLL_VELOCITY_MAX))
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
		}
	}

	switch(moveCamera_axis_y)
	{
	        case CAMERADIRECTION::UP:
	        {
	            	scroll_accel.y += SCROLL_VELOCITY_STEP;
	            	if (abs(scroll_accel.y) > abs(SCROLL_VELOCITY_MAX))
	            	{
	                	scroll_accel.y = SCROLL_VELOCITY_MAX;
	            	}
	            	
	            	break;
	        }
	        
	        case CAMERADIRECTION::DOWN:
	        {
	            	scroll_accel.y -= SCROLL_VELOCITY_STEP;
	            	if (abs(scroll_accel.y) > abs(SCROLL_VELOCITY_MAX))
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
