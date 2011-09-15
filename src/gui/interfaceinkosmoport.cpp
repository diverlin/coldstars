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



#include "interfaceinkosmoport.hpp"

InterfaceInKosmoport :: InterfaceInKosmoport()
{
    	TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);    // debug

    	angar_screen_button     = new Button(pTo_particleTexOb, 
    					     ANGAR_SCREEN_ID,
    					     g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "angar");    					     
    	button_common_pList.push_back(angar_screen_button);
    	
    	store_screen_button     = new Button(pTo_particleTexOb, 
    					     STORE_SCREEN_ID,
    					     g_VIEW_WIDTH - 2 * (INTERFACE_ICON_SIZE + 5),
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "store");
	button_common_pList.push_back(store_screen_button);
    					        	
    	shop_screen_button      = new Button(pTo_particleTexOb, 
    					     SHOP_SCREEN_ID,
    					     g_VIEW_WIDTH - 3 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "shop");
    	button_common_pList.push_back(shop_screen_button);
    					     
    	galaxymap_screen_button = new Button(pTo_particleTexOb, 
    					     GALAXYMAP_SCREEN_ID,
    					     g_VIEW_WIDTH - 4 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE, 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "galaxymap");
        button_common_pList.push_back(galaxymap_screen_button);
    					     
    	goverment_screen_button = new Button(pTo_particleTexOb, 
    					     GOVERMENT_SCREEN_ID,
    					     g_VIEW_WIDTH - 5 * (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE,
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "goverment");
    	button_common_pList.push_back(goverment_screen_button);

    	repair_button = new Button(pTo_particleTexOb, 
    	    			   REPAIR_BUTTON_ID,
    				   g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5),
    				   g_VIEW_HEIGHT - 2*INTERFACE_ICON_SIZE, 
    				   INTERFACE_ICON_SIZE,  
    				   INTERFACE_ICON_SIZE, 
    				   "buy_repair");
    	button_angar_pList.push_back(repair_button);
    				   
    	fuel_button   = new Button(pTo_particleTexOb,
    	 			   FUEL_BUTTON_ID,
    	 			   g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5),
    	 			   g_VIEW_HEIGHT - 3*INTERFACE_ICON_SIZE, 
    	 			   INTERFACE_ICON_SIZE,  
    	 			   INTERFACE_ICON_SIZE, 
    	 			   "buy fuel");  
    	button_angar_pList.push_back(fuel_button);
    	 			   
    	launch_button = new Button(pTo_particleTexOb, 
    				   LAUNCH_BUTTON_ID,
    				   g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5), 
    				   g_VIEW_HEIGHT - 4*INTERFACE_ICON_SIZE, 
    				   INTERFACE_ICON_SIZE,  
    				   INTERFACE_ICON_SIZE, 
    				   "launch");
    	button_angar_pList.push_back(launch_button);

	active_screen_id = ANGAR_SCREEN_ID;
}


InterfaceInKosmoport :: ~InterfaceInKosmoport()
{}


int InterfaceInKosmoport :: getActiveScreenId() const { return active_screen_id; }
	
	

void InterfaceInKosmoport :: resetInfoFlags()
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
       			
		
void InterfaceInKosmoport :: mouseInteraction()
{
     	int mxvp = g_MOUSE_POS_X;
     	int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     	int lmb  = g_MOUSE_LEFT_BUTTON;

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
        

     	if (active_screen_id == ANGAR_SCREEN_ID)
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
		   				pTo_PLAYER->pTo_ship->setMaxArmor(); 
		   			}
		   			if (button_angar_pList[i]->getSubTypeId() == FUEL_BUTTON_ID)
		   			{
		   		        	pTo_PLAYER->pTo_ship->setMaxFuel();
		   			}
		   			if (button_angar_pList[i]->getSubTypeId() == LAUNCH_BUTTON_ID)
		   			{
       						pTo_PLAYER->pTo_npc->createLaunchingSequence(); 
       						pTo_PLAYER->in_SPACE = true;
       			   		}
       				}
       				break;
       			}
        	}
	}

}


void InterfaceInKosmoport :: render() const
{
   
    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		button_common_pList[i]->render();
        }

    	if (active_screen_id == ANGAR_SCREEN_ID)
    	{
    		for (unsigned int i = 0; i< button_angar_pList.size(); i++)
		{
       			button_angar_pList[i]->render();
        	}
    	} 
}


void InterfaceInKosmoport :: renderInfo() const
{

	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
	    	if (button_common_pList[i]->getShowInfoFlag() == true)
	    	{
        		button_common_pList[i]->renderInfo();
        		break;
        	}
        }       

    	if (active_screen_id == ANGAR_SCREEN_ID)
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
