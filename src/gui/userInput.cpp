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


UserInput :: UserInput(Player* player)
{
	this->player = player;
	
    	keyboardLeftPressed  = false;
    	keyboardRightPressed = false;    
    	keyboardUpPressed    = false;    
    	keyboardDownPressed  = false;  
    
    	scroll_accel_x = 0; 
    	scroll_accel_y = 0;  
    
	next_turn_ready = false;
}



UserInput :: ~UserInput()
{}


bool UserInput :: getNextTurnReady() const { return next_turn_ready; }
		
void UserInput :: Update_inSpace()
{
	getSimpleInputs();
        getRealTimeInputs();
        scrollCamera();
}

void UserInput :: update_inKosmoport()
{
	getSimpleInputs();
        getRealTimeInputs();
}

void UserInput :: getSimpleInputs()
{
   	player->GetCursor()->setLeftMouseButton(false);
   	player->GetCursor()->setRightMouseButton(false);

	next_turn_ready = false;

	sf::Event event;

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
              				if (player->weapon_selector.slot_1 == false)
              				{
                		  		player->weapon_selector.slot_1 = true;
                		  		printf("pPLAYER->weapon slot 1 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.slot_1 = false;
                		  		printf("pPLAYER->weapon slot 1 -> NO\n");
              				}
  					break;
                		}

           			case sf::Key::Num2:
                		{
              				if (player->weapon_selector.slot_2 == false)
              				{
                	  			player->weapon_selector.slot_2 = true;
                	  			printf("pPLAYER->weapon slot 2 -> YES\n");
              				}
              				else
              				{
                				player->weapon_selector.slot_2 = false;
                	  			printf("pPLAYER->weapon slot 2 -> NO\n");
              				}
                	       		 break;
                		}

           			case sf::Key::Num3:
               		 	{
              				if (player->weapon_selector.slot_3 == false)
              				{
                		  		player->weapon_selector.slot_3 = true;
                		  		printf("pPLAYER->weapon slot 3 -> YES\n");
              				}
              				else
              				{
                		  		player->weapon_selector.slot_3 = false;
                		 	 	printf("pPLAYER->weapon slot 3 -> NO\n");
              				}
                		     	break;
                		}


          			case sf::Key::Num4:
                		{
              				if (player->weapon_selector.slot_4 == false)
              				{
                		 		 player->weapon_selector.slot_4 = true;
                		 		 printf("pPLAYER->weapon slot 4 -> YES\n");
             				}
             				else
             				{
                				 player->weapon_selector.slot_4 = false;
          				         printf("pPLAYER->weapon slot 4 -> NO\n");
              				}
 					break;
                		}	


           			case sf::Key::Num5:
                		{
                			if (player->weapon_selector.slot_5 == false)
             				{
                		  		player->weapon_selector.slot_5 = true;
                		  		printf("pPLAYER->weapon slot 5 -> YES\n");
             				}
             				else
              				{
                		  		player->weapon_selector.slot_5 = false;
                		  		printf("pPLAYER->weapon slot 5 -> NO\n");
              				}
               		 	        break;
 				}


           			case sf::Key::A:
                		{ 
	        		      	if ( (player->weapon_selector.slot_1 == true) && (player->weapon_selector.slot_2 == true) && (player->weapon_selector.slot_3 == true) && (player->weapon_selector.slot_4 == true) && (player->weapon_selector.slot_5 == true) )
              				{
                		  		player->weapon_selector.slot_1 = false;
                		  		player->weapon_selector.slot_2 = false;
                		  		player->weapon_selector.slot_3 = false;
                		  		player->weapon_selector.slot_4 = false;
                		  		player->weapon_selector.slot_5 = false;
                		  		printf("pPLAYER->weapon slot 1,2,3,4,5 -> NO\n");
              				}
              				else
              				{
                		  		player->weapon_selector.slot_1 = true;
                		  		player->weapon_selector.slot_2 = true;
                		  		player->weapon_selector.slot_3 = true;
                		  		player->weapon_selector.slot_4 = true;
                		  		player->weapon_selector.slot_5 = true;
                		  		printf("pPLAYER->weapon slot 1,2,3,4,5 -> YES\n");
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
					//GalaxyBuilder::Instance().SaveEvent(player->GetNpc()->GetStarSystem()->GetGalaxy());
					EntityManager::Instance().SaveEvent();
					break;
				}
				
				case sf::Key::F9:
				{
                                        //delete player->GetNpc()->GetStarSystem()->GetGalaxy();
                                        //delete player;

                                        SaveManager::Instance().LoadFile("save.info");
                                                                                
                                        GalaxyBuilder::Instance().CreateNewGalaxy();
                                        GalaxyBuilder::Instance().LoadGalaxy("galaxy.");
                                        Galaxy* galaxy = GalaxyBuilder::Instance().GetGalaxy();
                                        
                                        //PlayerBuilder::Instance().CreateNewPlayer();
                                        //player = PlayerBuilder::Instance().GetPlayer();
                                        

                                        //player->LoadEvent();                                        
					//player->GetNpc()->GetStarSystem()->GetGalaxy()->LoadEvent();
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
	              			player->GetCursor()->setLeftMouseButton(true);
	              			break;
	              		} 
	
	           		case sf::Mouse::Right:
	           		{
	              			player->GetCursor()->setRightMouseButton(true);
	              			break;
	              		}
	              	}
	        }

	      
	 } // endwhile
}

void UserInput :: getRealTimeInputs()
{       
        const sf::Input& Input = Gui::GetWindow().GetInput();
              
        // KEYBOARD input
        keyboardLeftPressed  = Input.IsKeyDown(sf::Key::Left);   
        keyboardRightPressed = Input.IsKeyDown(sf::Key::Right);  
        
        keyboardUpPressed    = Input.IsKeyDown(sf::Key::Up);   
        keyboardDownPressed  = Input.IsKeyDown(sf::Key::Down);  
}


void UserInput :: scrollCamera()
{
	int SCROLL_VELOCITY_STEP = Config::Instance().SCROLL_VELOCITY_STEP;
	int SCROLL_VELOCITY_MAX = Config::Instance().SCROLL_VELOCITY_MAX;	
	
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
      
      	player->GetScreen()->bottomLeftGlobalCoordIncrease(vec2f(scroll_accel_x, scroll_accel_y));
}
