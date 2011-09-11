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


#include "keyEventsInSpace.h"

KeyEventsInSpace :: KeyEventsInSpace()
{
    // KEYBOARD INPUT
    keyboardLeftPressed  = false;
    keyboardRightPressed = false;    
    keyboardUpPressed    = false;    
    keyboardDownPressed  = false;  
    
    scroll_accel_x = 0; 
    scroll_accel_y = 0;  
    
    //self.RUNNING = True
    //self.UPDATE = UPDATE

    //reset_turn_timer = false;
}



KeyEventsInSpace :: ~KeyEventsInSpace()
{}



void KeyEventsInSpace :: getSimpleInputs()
{
   	g_MOUSE_LEFT_BUTTON = false;
  	g_MOUSE_RIGHT_BUTTON = false;

	while (g_APP.GetEvent(g_EVENT))
	{
	        // Close window : exit
	        if (g_EVENT.Type == sf::Event::Closed)
		    	g_APP.Close();
                          
	        // Resize event : adjust viewport
	        if (g_EVENT.Type == sf::Event::Resized)
	            	glViewport(0, 0, g_EVENT.Size.Width, g_EVENT.Size.Height);
           
	        if (g_EVENT.Type == sf::Event::KeyPressed)
       		{
           		switch(g_EVENT.Key.Code) 
           		{
           			case sf::Key::Escape:
               			{
              				if (pTo_PLAYER->is_SCANNING == true)
              				{
                		  		pTo_PLAYER->is_SCANNING = false;
                		  		pTo_PLAYER->pTo_npc->removeScanTarget(); 
              				}
              				break;
                		}

          			case sf::Key::Space:
               		 	{
              				if (g_TIMER < 0)
               	 	 		g_TIMER = TURN_TIME;
                		        break;
                		} 



         	  		// WEAPON SLOTS
           			case sf::Key::Num1:
               		 	{
              				if (pTo_PLAYER->weapon_slot_1_SELECTED == false)
              				{
                		  		pTo_PLAYER->weapon_slot_1_SELECTED = true;
                		  		printf("pTo_PLAYER->weapon_slot_1_SELECTED -> YES\n");
              				}
              				else
              				{
                		  		pTo_PLAYER->weapon_slot_1_SELECTED = false;
                		  		printf("pTo_PLAYER->weapon_slot_1_SELECTED -> NO\n");
              				}
  					break;
                		}

           			case sf::Key::Num2:
                		{
              				if (pTo_PLAYER->weapon_slot_2_SELECTED == false)
              				{
                	  			pTo_PLAYER->weapon_slot_2_SELECTED = true;
                	  			printf("pTo_PLAYER->weapon_slot_2_SELECTED -> YES\n");
              				}
              				else
              				{
                				  pTo_PLAYER->weapon_slot_2_SELECTED = false;
                	  			printf("pTo_PLAYER->weapon_slot_2_SELECTED -> NO\n");
              				}
                	       		 break;
                		}

           			case sf::Key::Num3:
               		 	{
              				if (pTo_PLAYER->weapon_slot_3_SELECTED == false)
              				{
                		  		pTo_PLAYER->weapon_slot_3_SELECTED = true;
                		  		printf("pTo_PLAYER->weapon_slot_3_SELECTED -> YES\n");
              				}
              				else
              				{
                		  		pTo_PLAYER->weapon_slot_3_SELECTED = false;
                		 	 	printf("pTo_PLAYER->weapon_slot_3_SELECTED -> NO\n");
              				}
                		     	break;
                		}


          			case sf::Key::Num4:
                		{
              				if (pTo_PLAYER->weapon_slot_4_SELECTED == false)
              				{
                		 		 pTo_PLAYER->weapon_slot_4_SELECTED = true;
                		 		 printf("pTo_PLAYER->weapon_slot_4_SELECTED -> YES\n");
             				}
             				else
             				{
                				 pTo_PLAYER->weapon_slot_4_SELECTED = false;
          				         printf("pTo_PLAYER->weapon_slot_4_SELECTED -> NO\n");
              				}
 					break;
                		}	


           			case sf::Key::Num5:
                		{
                			if (pTo_PLAYER->weapon_slot_5_SELECTED == false)
             				{
                		  		pTo_PLAYER->weapon_slot_5_SELECTED = true;
                		  		printf("pTo_PLAYER->weapon_slot_5_SELECTED -> YES\n");
             				}
             				else
              				{
                		  		pTo_PLAYER->weapon_slot_5_SELECTED = false;
                		  		printf("pTo_PLAYER->weapon_slot_5_SELECTED -> NO\n");
              				}
               		 	        break;
 				}


           			case sf::Key::A:
                		{ 
	        		      	if ( (pTo_PLAYER->weapon_slot_1_SELECTED == true) && (pTo_PLAYER->weapon_slot_2_SELECTED == true) && (pTo_PLAYER->weapon_slot_3_SELECTED == true) && (pTo_PLAYER->weapon_slot_4_SELECTED == true) && (pTo_PLAYER->weapon_slot_5_SELECTED == true) )
              				{
                		  		pTo_PLAYER->weapon_slot_1_SELECTED = false;
                		  		pTo_PLAYER->weapon_slot_2_SELECTED = false;
                		  		pTo_PLAYER->weapon_slot_3_SELECTED = false;
                		  		pTo_PLAYER->weapon_slot_4_SELECTED = false;
                		  		pTo_PLAYER->weapon_slot_5_SELECTED = false;
                		  		printf("pTo_PLAYER->weapon slot 1,2,3,4,5 -> NO, targets are reset\n");
              				}
              				else
              				{
                		  		pTo_PLAYER->weapon_slot_1_SELECTED = true;
                		  		pTo_PLAYER->weapon_slot_2_SELECTED = true;
                		  		pTo_PLAYER->weapon_slot_3_SELECTED = true;
                		  		pTo_PLAYER->weapon_slot_4_SELECTED = true;
                		  		pTo_PLAYER->weapon_slot_5_SELECTED = true;
                		  		printf("pTo_PLAYER->weapon slot 1,2,3,4,5 -> YES\n");
              				}
                		        break;
				}


          	
	           		case sf::Key::G:   // GARPUN
	               	 	{
	                	        if (pTo_PLAYER->garpun_slot_SELECTED == false)
	            			{
	                 			pTo_PLAYER->garpun_slot_SELECTED = true;
	                 			printf("garpun_slot_SELECTED -> YES\n");
	              			}   
	              			else
	              			{
	                 			pTo_PLAYER->garpun_slot_SELECTED = false;
	                 			printf("garpun_slot_SELECTED -> NO\n");
	              			}
	                       		break;
	 			}


	           		case sf::Key::R: // RADAR
	                	{
	              			if (pTo_PLAYER->radar_range_SHOW == false)
	              			{
	                			pTo_PLAYER->radar_range_SHOW = true;
	                 			printf("radar_range_SHOW -> YES\n");
	             			}
	              			else
	              			{
	                			pTo_PLAYER->radar_range_SHOW = false;
	                 			printf("radar_range_SHOW -> NO\n");
	             			}
	                 	      	break;
				}


	        	} // end switch      
	        } //enfif 


	        if (g_EVENT.Type == sf::Event::MouseButtonPressed)
	        {
	                switch(g_EVENT.Key.Code) 
	                { 
	           		case sf::Mouse::Left:
	           		{              
	              			g_MOUSE_LEFT_BUTTON = true;
	              			break;
	              		} 
	
	           		case sf::Mouse::Right:
	           		{
	              			g_MOUSE_RIGHT_BUTTON = true;
	              			break;
	              		}
	              	}
	        }

	      
	 } // endwhile
}

void KeyEventsInSpace :: getRealTimeInputs()
{       
        const sf::Input& Input = g_APP.GetInput();

        //// MOUSE input
        g_MOUSE_POS_X = Input.GetMouseX();
        g_MOUSE_POS_Y = Input.GetMouseY();
        //printf("mouse x,y = %i,%i\n", g_MOUSE_POS_X, g_MOUSE_POS_Y);
      
        // KEYBOARD input
        keyboardLeftPressed  = Input.IsKeyDown(sf::Key::Left);   
        keyboardRightPressed = Input.IsKeyDown(sf::Key::Right);  
        
        keyboardUpPressed    = Input.IsKeyDown(sf::Key::Up);   
        keyboardDownPressed  = Input.IsKeyDown(sf::Key::Down);  
}


void KeyEventsInSpace :: scrollCamera()
{
        // SCROLLING X AXIS         
        if(keyboardLeftPressed)
        {
            scroll_accel_x -= g_SCROLL_VELOCITY_STEP;
            if (abs(scroll_accel_x) > abs(g_SCROLL_VELOCITY_MAX))
            {
                scroll_accel_x = -g_SCROLL_VELOCITY_MAX;
            }
        }
        
        if(keyboardRightPressed)
        {
            scroll_accel_x += g_SCROLL_VELOCITY_STEP;
            if (abs(scroll_accel_x) > abs(g_SCROLL_VELOCITY_MAX))
            {
                scroll_accel_x = g_SCROLL_VELOCITY_MAX;
            }
        }
        
        
        if(!keyboardLeftPressed && !keyboardRightPressed)
        {
            if (scroll_accel_x != 0)
            {
                if (scroll_accel_x > 0)
                {
                    scroll_accel_x -= g_SCROLL_VELOCITY_STEP; 
                } 
                else if (scroll_accel_x < 0)
                {
                    scroll_accel_x += g_SCROLL_VELOCITY_STEP; 
                }   
            }
        }



        // SCROLLING Y AXIS         
        if(keyboardUpPressed)
        {
            scroll_accel_y += g_SCROLL_VELOCITY_STEP;
            if (abs(scroll_accel_y) > abs(g_SCROLL_VELOCITY_MAX))
            {
                scroll_accel_y = g_SCROLL_VELOCITY_MAX;
            }
        }
        
        if(keyboardDownPressed)
        {
            scroll_accel_y -= g_SCROLL_VELOCITY_STEP;
            if (abs(scroll_accel_y) > abs(g_SCROLL_VELOCITY_MAX))
            {
                scroll_accel_y = -g_SCROLL_VELOCITY_MAX;
            }
        }
        
        
        if(!keyboardUpPressed && !keyboardDownPressed)
        {
            if (scroll_accel_y != 0)
            {
                if (scroll_accel_y > 0)
                {
                    scroll_accel_y -= g_SCROLL_VELOCITY_STEP; 
                } 
                else if (scroll_accel_y < 0)
                {
                    scroll_accel_y += g_SCROLL_VELOCITY_STEP; 
                }   
            }
        }
      
        g_SCROLL_COORD_X += scroll_accel_x;
        g_SCROLL_COORD_Y += scroll_accel_y;                
}
