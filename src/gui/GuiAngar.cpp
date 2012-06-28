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



GuiAngar::GuiAngar(Player* player)
{
	this->player = player;
	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
        TextureOb* texOb_button = g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_green; // fake

    	Button* repair_button = new Button(texOb_button, 
    	    			   GUI::BUTTON::GETREPAIR_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5),
    				   screen_h - 2*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "buy_repair");
    	button_vec.push_back(repair_button);
    				   
    	Button* fuel_button   = new Button(texOb_button,
    	 			   GUI::BUTTON::GETFUEL_ID,
    	 			   screen_w - 1 * (GUI::ICON_SIZE + 5),
    	 			   screen_h - 3*GUI::ICON_SIZE, 
    	 			   GUI::ICON_SIZE,  
    	 			   GUI::ICON_SIZE, 
    	 			   "buy fuel");  
    	button_vec.push_back(fuel_button);
    	 			   
    	Button* launch_button = new Button(texOb_button, 
    				   GUI::BUTTON::GETLAUNCH_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5), 
    				   screen_h - 4*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "launch");
    	button_vec.push_back(launch_button);
}


GuiAngar::~GuiAngar()
{}
	
void GuiAngar::ResetInfoFlags()
{     
    	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
       		button_vec[i]->setShowInfoFlag(false);
        }
}       	
		
void GuiAngar::UpdateMouseInteraction(int mxvp, int myvp, int lmb)
{
	ResetInfoFlags();

	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
       		if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
       		{
       	        	button_vec[i]->setShowInfoFlag(true);
       			if (lmb == true)
       			{	
	   			switch(button_vec[i]->GetSubTypeId())
	   			{
	   				case GUI::BUTTON::GETREPAIR_ID: 
	   				{
	   					player->GetNpc()->GetVehicle()->SetMaxArmor(); 
	   					return; break;
	   				}
	   				case GUI::BUTTON::GETFUEL_ID:
	   				{
	   		        		player->GetNpc()->GetVehicle()->SetMaxFuel();
	   					return; break;
	   				}
	   				case GUI::BUTTON::GETLAUNCH_ID:
	   				{
	   					MicroTask* microtask = new MicroTask(NULL, MICROSCENARIO::LAUNCHING_ID);
       						player->GetNpc()->GetVehicle()->LaunchingEvent();
       						player->GetNpc()->GetStateMachine()->SetCurrentMicroTask(microtask);
       		   				return; break;
       		   			}
       				}
       				
       			}
       			break;
        	}
        }
}


void GuiAngar::RenderInternal() const
{
	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
		button_vec[i]->Render();
       	}
}

void GuiAngar::RenderInfo() const
{
	for (unsigned int i = 0; i< button_vec.size(); i++)
	{		
    		if (button_vec[i]->getShowInfoFlag() == true)
		{
        		button_vec[i]->renderInfo();
        		return; break;
        	}
        }
}
