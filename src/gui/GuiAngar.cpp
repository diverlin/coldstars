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



GuiAngar::GuiAngar()
{	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
        TextureOb* texOb_button = g_GUI_TEXTUREOB_COLLECTOR.dot_green; // fake

    	ButtonSingle* repair_button = new ButtonSingle(texOb_button, 
    	    			   GUI::BUTTON::BUYARMOR_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5),
    				   screen_h - 2*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "buy_repair");
    	button_map.insert(std::make_pair(GUI::BUTTON::BUYARMOR_ID, repair_button));
    				   
    	ButtonSingle* fuel_button   = new ButtonSingle(texOb_button,
    	 			   GUI::BUTTON::BUYFUEL_ID,
    	 			   screen_w - 1 * (GUI::ICON_SIZE + 5),
    	 			   screen_h - 3*GUI::ICON_SIZE, 
    	 			   GUI::ICON_SIZE,  
    	 			   GUI::ICON_SIZE, 
    	 			   "buy fuel");  
    	button_map.insert(std::make_pair(GUI::BUTTON::BUYFUEL_ID, fuel_button));
    	 			   
    	ButtonSingle* launch_button = new ButtonSingle(texOb_button, 
    				   GUI::BUTTON::GETLAUNCH_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5), 
    				   screen_h - 4*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "launch");
    	button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH_ID, launch_button));
}


GuiAngar::~GuiAngar()
{}	
	
void GuiAngar::CheckButtonsLock()
{    	   	
	if (player->GetNpc()->GetVehicle()->IsFuelFull() == true) 	{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOn(); }
	else								{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOff(); }

	if (player->GetNpc()->GetVehicle()->IsArmorFull() == true) 	{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOn(); }
	else								{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOff(); }
}

void GuiAngar::ButtonsAction() const     
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
		if (button->GetPressed() == true)
		{
			switch(button->GetSubTypeId())
	   		{
	   			case GUI::BUTTON::BUYARMOR_ID: 
	   			{
	   				if (button->GetLock() == false)
	   				{  			
	   				      	button->PressEvent();
	   					
	   					player->GetNpc()->GetVehicle()->BuyArmorAsMuchAsPossible();
	   					return; 
	   				}
	   						
	   				break;
	  	 		}
	   		
	   			case GUI::BUTTON::BUYFUEL_ID:
	   			{
	   				if (button->GetLock() == false)
	   				{
	   		       			button->PressEvent();
	   		        		
	   		        		player->GetNpc()->GetVehicle()->BuyFuelAsMuchAsPossible();
	   					return; 
	   				}	   				
	   					
	   				break;
	   			}
	   			
	   			case GUI::BUTTON::GETLAUNCH_ID:
	   			{
	   				MicroTask* microtask = new MicroTask(NULL, MICROSCENARIO::LAUNCHING_ID);
       					player->GetNpc()->GetVehicle()->LaunchingEvent();
       					player->GetNpc()->GetStateMachine()->SetCurrentMicroTask(microtask);
       		   			return; 
       		   				      		   			
       		   			break;
       		   		}
       			}
        	}
        }
}

bool GuiAngar::UpdateMouseVehicleSlotsInteraction(const MouseData& data_mouse, Angar* angar)
{	
        for (unsigned int i = 0; i < angar->vehicleslot_vec.size(); i++)
        { 
                if (angar->vehicleslot_vec[i]->GetRect().CheckInteraction(data_mouse.mx, data_mouse.my) == true)
                {
                        if (data_mouse.right_click == true)
                        {
                                if (angar->vehicleslot_vec[i]->GetVehicle() != NULL)
                                {
                                        player->GetNpc()->SetScanTarget(angar->vehicleslot_vec[i]->GetVehicle());
                                        return true;
                                }
                        }
                }
        }
        
        return false;
}


void GuiAngar::RenderVehicleSlots(Angar* angar) const
{
        for (unsigned int i=0; i<angar->vehicleslot_vec.size(); i++)
        {
                angar->vehicleslot_vec[i]->Render();
        }
}

void GuiAngar::RenderFocusedItemInfo(const MouseData& data_mouse, Angar* angar) const
{
        for (unsigned int i=0; i<angar->vehicleslot_vec.size(); i++)
        { 
		if (angar->vehicleslot_vec[i]->GetVehicle() != NULL)
                {
                       	if (angar->vehicleslot_vec[i]->GetRect().CheckInteraction(data_mouse.mx, data_mouse.my) == true)
                	{
		                angar->vehicleslot_vec[i]->RenderItemInfo();
		                return;
                	}
                }
        }
}
            
