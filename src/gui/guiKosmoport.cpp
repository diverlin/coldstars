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
	
        TextureOb* texOb_button = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; // fake

    	angar_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::ANGAR_ID,
    					     SCREEN_WIDTH_MIN - 1 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "angar");    					     
    	button_common_pList.push_back(angar_screen_button);
    	
    	store_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::STORE_ID,
    					     SCREEN_WIDTH_MIN - 2 * (INTERFACE_ICON_SIZE + 5),
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "store");
	button_common_pList.push_back(store_screen_button);
    					        	
    	shop_screen_button      = new Button(texOb_button, 
    					     GUI::SCREEN::SHOP_ID,
    					     SCREEN_WIDTH_MIN - 3 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "shop");
    	button_common_pList.push_back(shop_screen_button);
    					     
    	galaxymap_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GALAXYMAP_ID,
    					     SCREEN_WIDTH_MIN - 4 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "galaxymap");
        button_common_pList.push_back(galaxymap_screen_button);
    					     
    	goverment_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GOVERMENT_ID,
    					     SCREEN_WIDTH_MIN - 5 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE,
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "goverment");
    	button_common_pList.push_back(goverment_screen_button);

    	repair_button = new Button(texOb_button, 
    	    			   REPAIR_BUTTON_ID,
    				   SCREEN_WIDTH_MIN - 1 * (INTERFACE_ICON_SIZE + 5),
    				   SCREEN_HEIGHT_MIN - 2*INTERFACE_ICON_SIZE, 
    				   INTERFACE_ICON_SIZE,  
    				   INTERFACE_ICON_SIZE, 
    				   "buy_repair");
    	button_angar_pList.push_back(repair_button);
    				   
    	fuel_button   = new Button(texOb_button,
    	 			   FUEL_BUTTON_ID,
    	 			   SCREEN_WIDTH_MIN - 1 * (INTERFACE_ICON_SIZE + 5),
    	 			   SCREEN_HEIGHT_MIN - 3*INTERFACE_ICON_SIZE, 
    	 			   INTERFACE_ICON_SIZE,  
    	 			   INTERFACE_ICON_SIZE, 
    	 			   "buy fuel");  
    	button_angar_pList.push_back(fuel_button);
    	 			   
    	launch_button = new Button(texOb_button, 
    				   LAUNCH_BUTTON_ID,
    				   SCREEN_WIDTH_MIN - 1 * (INTERFACE_ICON_SIZE + 5), 
    				   SCREEN_HEIGHT_MIN - 4*INTERFACE_ICON_SIZE, 
    				   INTERFACE_ICON_SIZE,  
    				   INTERFACE_ICON_SIZE, 
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
       			
		
void GuiKosmoport :: mouseInteraction()
{
     	int mxvp = player->getCursor()->getMousePos().x;
     	int myvp = player->getScreen()->getHeight() - player->getCursor()->getMousePos().y;         
     	int lmb  = player->getCursor()->getMouseLeftButton();;

    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		if (button_common_pList[i]->interaction(mxvp, myvp) == true)
       		{
       		        button_common_pList[i]->setShowInfoFlag(true);
       			if (lmb == true)
       			{	
       			   	active_screen_id = button_common_pList[i]->getSubTypeId();       			   	
       			}
       			break;
       		}
        }
        

     	if (active_screen_id == GUI::SCREEN::ANGAR_ID)
    	{
     		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
       			if (button_angar_pList[i]->interaction(mxvp, myvp) == true)
       			{
       		        	button_angar_pList[i]->setShowInfoFlag(true);
       				if (lmb == true)
       				{	
		   			if (button_angar_pList[i]->getSubTypeId() == REPAIR_BUTTON_ID)
		   			{
		   				player->getNpc()->getVehicle()->SetMaxArmor(); 
		   			}
		   			if (button_angar_pList[i]->getSubTypeId() == FUEL_BUTTON_ID)
		   			{
		   		        	player->getNpc()->getVehicle()->SetMaxFuel();
		   			}
		   			if (button_angar_pList[i]->getSubTypeId() == LAUNCH_BUTTON_ID)
		   			{
       						player->getNpc()->getVehicle()->LaunchingEvent();
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
       		button_common_pList[i]->render();
        }

    	if (active_screen_id == GUI::SCREEN::ANGAR_ID)
    	{
    		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
       			button_angar_pList[i]->render();
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
        mouseInteraction(); 
}
                
                
void GuiKosmoport :: render() const
{
        resetRenderTransformation();
        
        enable_BLEND();   
                renderInternal(); 
                renderInfo();    
        disable_BLEND(); 
}
