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



#include "interfaceinspace.hpp"

InterfaceInSpace :: InterfaceInSpace()
{
    	TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);    // debug
    	galaxymap_screen_button = new Button(pTo_particleTexOb, 
        				     GALAXYMAP_SCREEN_ID,
    					     g_VIEW_WIDTH - (INTERFACE_ICON_SIZE + 5),
    					     g_VIEW_HEIGHT - (INTERFACE_ICON_SIZE + 5), 
    					     INTERFACE_ICON_SIZE,  
    					     INTERFACE_ICON_SIZE, 
    					     "galaxy map");
    					     
    	button_common_pList.push_back(galaxymap_screen_button);
}


InterfaceInSpace :: ~InterfaceInSpace()
{}


void InterfaceInSpace :: update()
{
	resetInfoFlags();
	mouseInteraction();
}
		

void InterfaceInSpace :: resetInfoFlags()
{
    	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
       		button_common_pList[i]->setShowInfoFlag(false);
        }
}


void InterfaceInSpace :: mouseInteraction()
{
     	int mxvp = g_MOUSE_POS_X;
     	int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     	int lmb  = g_MOUSE_LEFT_BUTTON;

	for (unsigned int i = 0; i < button_common_pList.size(); i++)
     	{ 
        	if (button_common_pList[i]->interaction(mxvp, myvp) == true)
        	{
           		if (lmb == true)
           		{
           			if (button_common_pList[i]->getSubTypeId() == GALAXYMAP_SCREEN_ID)
              			{
              				if (pPLAYER->show_WORLDMAP == false)
                 				pPLAYER->show_WORLDMAP = true;
              				else
                 				pPLAYER->show_WORLDMAP = false;
                 		}
           		}
        	}
     	}
}


void InterfaceInSpace :: render()
{
    	resetRenderTransformation();

	enable_BLEND();    						
		renderInternal();
		renderInfo();
	disable_BLEND();
}


void InterfaceInSpace :: renderInternal() const
{
	for (unsigned int i = 0; i < button_common_pList.size(); i++)
     	{ 
		button_common_pList[i]->render();
     	}
}

void InterfaceInSpace :: renderInfo() const
{

	for (unsigned int i = 0; i< button_common_pList.size(); i++)
	{
	    	if (button_common_pList[i]->getShowInfoFlag() == true)
	    	{
        		button_common_pList[i]->renderInfo();
        		break;
        	}
        }       
}
        


