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
    pTo_galaxymap_screen_button = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - (INTERFACE_ICON_SIZE + 5)), (g_VIEW_HEIGHT - (INTERFACE_ICON_SIZE + 5)), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "galaxy map");
}


InterfaceInSpace :: ~InterfaceInSpace()
{}


void InterfaceInSpace :: mouseInteraction()
{
     bool CURSOR_INTERSECT_OBJECT = false;

     int mxvp = g_MOUSE_POS_X;
     int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     int lmb  = g_MOUSE_LEFT_BUTTON;

     /////////////////////////////////////////////
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_galaxymap_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
              if (pTo_PLAYER->in_WORLDMAP == false)
                 pTo_PLAYER->in_WORLDMAP = true;
              else
                 pTo_PLAYER->in_WORLDMAP = false;
           }
        }
     }
     /////////////////////////////////////////////
}

void InterfaceInSpace :: render()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glLoadIdentity();
    
    pTo_galaxymap_screen_button->render();
}
