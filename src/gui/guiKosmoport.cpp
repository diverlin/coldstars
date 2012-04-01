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



GuiKosmoport :: GuiKosmoport(Player* player)
{
	this->player = player;
	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
        TextureOb* texOb_button = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; // fake

    	angar_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::ANGAR_ID,
    					     screen_w - 1 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "angar");    					     
    	button_common_pList.push_back(angar_screen_button);
    	
    	store_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::STORE_ID,
    					     screen_w - 2 * (GUI::ICON_SIZE + 5),
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "store");
	button_common_pList.push_back(store_screen_button);
    					        	
    	shop_screen_button      = new Button(texOb_button, 
    					     GUI::SCREEN::SHOP_ID,
    					     screen_w - 3 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "shop");
    	button_common_pList.push_back(shop_screen_button);
    					     
    	galaxymap_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GALAXYMAP_ID,
    					     screen_w - 4 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "galaxymap");
        button_common_pList.push_back(galaxymap_screen_button);
    					     
    	goverment_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GOVERMENT_ID,
    					     screen_w - 5 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE,
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "goverment");
    	button_common_pList.push_back(goverment_screen_button);

    	repair_button = new Button(texOb_button, 
    	    			   GUI::BUTTON::GETREPAIR_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5),
    				   screen_h - 2*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "buy_repair");
    	button_angar_pList.push_back(repair_button);
    				   
    	fuel_button   = new Button(texOb_button,
    	 			   GUI::BUTTON::GETFUEL_ID,
    	 			   screen_w - 1 * (GUI::ICON_SIZE + 5),
    	 			   screen_h - 3*GUI::ICON_SIZE, 
    	 			   GUI::ICON_SIZE,  
    	 			   GUI::ICON_SIZE, 
    	 			   "buy fuel");  
    	button_angar_pList.push_back(fuel_button);
    	 			   
    	launch_button = new Button(texOb_button, 
    				   GUI::BUTTON::GETLAUNCH_ID,
    				   screen_w - 1 * (GUI::ICON_SIZE + 5), 
    				   screen_h - 4*GUI::ICON_SIZE, 
    				   GUI::ICON_SIZE,  
    				   GUI::ICON_SIZE, 
    				   "launch");
    	button_angar_pList.push_back(launch_button);

	active_screen_id = GUI::SCREEN::ANGAR_ID;
}


GuiKosmoport :: ~GuiKosmoport()
{}


int GuiKosmoport :: getActiveScreenId() const { return active_screen_id; }
	
	

void GuiKosmoport :: resetInfoFlags()
{
    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		button_common_pList[i]->setShowInfoFlag(false);
        }
        
    	for (unsigned int i = 0; i< button_angar_pList.size(); i++)
	{
       		button_angar_pList[i]->setShowInfoFlag(false);
        }
}
       			
		
void GuiKosmoport :: mouseCheckInteraction()
{
     	int mxvp = player->getCursor()->getMousePos().x;
     	int myvp = player->getScreen()->getHeight() - player->getCursor()->getMousePos().y;         
     	int lmb  = player->getCursor()->getMouseLeftButton();;

    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		if (button_common_pList[i]->CheckInteraction(mxvp, myvp) == true)
       		{
       		        button_common_pList[i]->setShowInfoFlag(true);
       			if (lmb == true)
       			{	
       			   	active_screen_id = button_common_pList[i]->GetSubTypeId();       			   	
       			}
       			break;
       		}
        }
        

     	if (active_screen_id == GUI::SCREEN::ANGAR_ID)
    	{
     		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
       			if (button_angar_pList[i]->CheckInteraction(mxvp, myvp) == true)
       			{
       		        	button_angar_pList[i]->setShowInfoFlag(true);
       				if (lmb == true)
       				{	
		   			if (button_angar_pList[i]->GetSubTypeId() == GUI::BUTTON::GETREPAIR_ID)
		   			{
		   				player->getNpc()->GetVehicle()->SetMaxArmor(); 
		   			}
		   			if (button_angar_pList[i]->GetSubTypeId() == GUI::BUTTON::GETFUEL_ID)
		   			{
		   		        	player->getNpc()->GetVehicle()->SetMaxFuel();
		   			}
		   			if (button_angar_pList[i]->GetSubTypeId() == GUI::BUTTON::GETLAUNCH_ID)
		   			{
       						player->getNpc()->GetVehicle()->LaunchingEvent();
       			   		}
       				}
       				break;
       			}
        	}
	}

}


void GuiKosmoport :: renderInternal() const
{
   
    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		button_common_pList[i]->Render();
        }

    	if (active_screen_id == GUI::SCREEN::ANGAR_ID)
    	{
    		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
       			button_angar_pList[i]->Render();
        	}
    	} 
}


void GuiKosmoport :: renderInfo() const
{

	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
	    	if (button_common_pList[i]->getShowInfoFlag() == true)
	    	{
        		button_common_pList[i]->renderInfo();
        		break;
        	}
        }       

    	if (active_screen_id == GUI::SCREEN::ANGAR_ID)
    	{
    		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
		
    			if (button_angar_pList[i]->getShowInfoFlag() == true)
	    		{
        			button_angar_pList[i]->renderInfo();
        			break;
        		}
        	}
    	} 
        
}

void GuiKosmoport :: update()
{
        resetInfoFlags(); 
        mouseCheckInteraction(); 
}
                
                
void GuiKosmoport :: Render() const
{
        resetRenderTransformation();
        
        enable_BLEND();   
                renderInternal(); 
                renderInfo();    
        disable_BLEND(); 
}
