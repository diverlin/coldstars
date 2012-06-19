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
		
void UserInput::Update(Player* player)
{
	GetSimpleInputs(player);
        GetRealTimeInputs();
        if (player->GetNpc()->GetPlaceTypeId() == ENTITY::SPACE_ID)
        {
        	ScrollCamera(player);
        }
}

void UserInput::GetSimpleInputs(Player* player)
{
   	player->GetCursor()->SetLeftMouseButton(false);
   	player->GetCursor()->SetRightMouseButton(false);

	next_turn_ready = false;

	sf::Event event;
	
	save = false;
	load = false;
			
	while (Gui::GetWindow().GetEvent(event))
	{
	        // Close window : exit
	        if (event.Type == sf::Event::Closed)
		    	Gui::GetWindow().Close();
                          
	        // Resize event : adjust viewport
	        if (event.Type == sf::Event::Resized)
	            	glViewport(0, 0, event.Size.Width, event.Size.Height);
           
	        if (event.Type == sf::Event::KeyPressed)
       		{
           		switch(event.Key.Code) 
           		{
           			case sf::Key::Escape:
               			{
              				if (player->GetNpc()->GetScanTarget() != NULL)
              				{
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
           			case sf::Key::Num1:
               		 	{
              				if (player->weapon_selector.GetSingle(1) == false)
              				{
                		  		player->weapon_selector.SetSingle(1, true);
                		  		printf("player->weapon slot 1 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(1, false);
                		  		printf("player->weapon slot 1 -> NO\n");
              				}
  					break;
                		}

           			case sf::Key::Num2:
                		{
              				if (player->weapon_selector.GetSingle(2) == false)
              				{
                		  		player->weapon_selector.SetSingle(2, true);
                		  		printf("player->weapon slot 2 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(2, false);
                		  		printf("player->weapon slot 2 -> NO\n");
              				}
  					break;
                		}

           			case sf::Key::Num3:
               		 	{
              				if (player->weapon_selector.GetSingle(3) == false)
              				{
                		  		player->weapon_selector.SetSingle(3, true);
                		  		printf("player->weapon slot 3 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(3, false);
                		  		printf("player->weapon slot 3 -> NO\n");
              				}
  					break;
                		}

          			case sf::Key::Num4:
                		{
              				if (player->weapon_selector.GetSingle(4) == false)
              				{
                		  		player->weapon_selector.SetSingle(4, true);
                		  		printf("player->weapon slot 4 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(4, false);
                		  		printf("player->weapon slot 4 -> NO\n");
              				}
  					break;
                		}	

           			case sf::Key::Num5:
                		{
              				if (player->weapon_selector.GetSingle(5) == false)
              				{
                		  		player->weapon_selector.SetSingle(5, true);
                		  		printf("player->weapon slot 5 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(5, false);
                		  		printf("player->weapon slot 5 -> NO\n");
              				}
  					break;
 				}

           			case sf::Key::Num6:
                		{
              				if (player->weapon_selector.GetSingle(6) == false)
              				{
                		  		player->weapon_selector.SetSingle(6, true);
                		  		printf("player->weapon slot 6 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(6, false);
                		  		printf("player->weapon slot 6 -> NO\n");
              				}
  					break;
 				}

           			case sf::Key::Num7:
                		{
              				if (player->weapon_selector.GetSingle(7) == false)
              				{
                		  		player->weapon_selector.SetSingle(7, true);
                		  		printf("player->weapon slot 7 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(7, false);
                		  		printf("player->weapon slot 7 -> NO\n");
              				}
  					break;
 				}

           			case sf::Key::Num8:
                		{
              				if (player->weapon_selector.GetSingle(8) == false)
              				{
                		  		player->weapon_selector.SetSingle(8, true);
                		  		printf("player->weapon slot 8 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(8, false);
                		  		printf("player->weapon slot 8 -> NO\n");
              				}
  					break;
 				}

           			case sf::Key::Num9:
                		{
              				if (player->weapon_selector.GetSingle(9) == false)
              				{
                		  		player->weapon_selector.SetSingle(9, true);
                		  		printf("player->weapon slot 9 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetSingle(9, false);
                		  		printf("player->weapon slot 9 -> NO\n");
              				}
  					break;
 				}
 				 				 				
           			case sf::Key::A:
                		{ 
	        		      	if (player->weapon_selector.IsAllTrue() == true)
              				{
                		  		player->weapon_selector.SetAll(false);
                		  		printf("pPLAYER->weapon slot 1,2,3,4,5,6,7,8,9 -> NO\n");
              				}
              				else
              				{
                		  		player->weapon_selector.SetAll(true);
                		  		printf("pPLAYER->weapon slot 1,2,3,4,5,6,7,8,9 -> YES\n");
              				}
                		        break;
				}


          	
	           		case sf::Key::G:   // Grapple
	               	 	{
	                	        if (player->GetShowGrappleRange() == false)
	            			{
	                 			player->SetShowGrappleRange(true);
	              			}   
	              			else
	              			{
	                 			player->SetShowGrappleRange(false);
	              			}
	                       		break;
	 			}


	           		case sf::Key::R: // RADAR
	                	{
	              			if (player->GetShowRadarRange() == false)
	              			{
	                			player->SetShowRadarRange(true);
	             			}
	              			else
	              			{
	                			player->SetShowRadarRange(false);
	             			}
	                 	      	break;
				}

	           		case sf::Key::O: // Orbits
	                	{
	              			if (player->GetShowAllOrbit() == false)
	              			{
	                			player->SetShowAllOrbit(true);
	             			}
	              			else
	              			{
	                			player->SetShowAllOrbit(false);
	             			}
	                 	      	break;
				}

	           		case sf::Key::P: // Path
	                	{
	              			if (player->GetShowAllPath() == false)
	              			{
	                			player->SetShowAllPath(true);
	             			}
	              			else
	              			{
	                			player->SetShowAllPath(false);
	             			}
	                 	      	break;
				}
				
				case sf::Key::F5:
				{		
					save = true;			
					break;
				}
				
				case sf::Key::F9:
				{
					load = true;
					break;
				}
				
	        	} // end switch      
	        } //enfif 


	        if (event.Type == sf::Event::MouseButtonPressed)
	        {
	                switch(event.Key.Code) 
	                { 
	           		case sf::Mouse::Left:
	           		{              
	              			player->GetCursor()->SetLeftMouseButton(true);
	              			break;
	              		} 
	
	           		case sf::Mouse::Right:
	           		{
	              			player->GetCursor()->SetRightMouseButton(true);
	              			break;
	              		}
	              	}
	        }

	      
	 } // endwhile
}

void UserInput::GetRealTimeInputs()
{       
        const sf::Input& Input = Gui::GetWindow().GetInput();
              
        // KEYBOARD input
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
      
      	player->GetScreen()->MovingBy(vec2f(scroll_accel_x, scroll_accel_y));
}
