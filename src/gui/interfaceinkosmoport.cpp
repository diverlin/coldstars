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



#include "interfaceinkosmoport.h"

InterfaceInKosmoport :: InterfaceInKosmoport()
{
    TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);    // debug

    pTo_angar_screen_button     = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5)), (INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "angar");
    pTo_store_screen_button     = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 2 * (INTERFACE_ICON_SIZE + 5)), (INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "store");
    pTo_shop_screen_button      = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 3 * (INTERFACE_ICON_SIZE + 5)), (INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "shop");
    pTo_galaxymap_screen_button = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 4 * (INTERFACE_ICON_SIZE + 5)), (INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "galaxymap");
    pTo_goverment_screen_button = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 5 * (INTERFACE_ICON_SIZE + 5)), (INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "goverment");

    pTo_repair_button = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5)), (g_VIEW_HEIGHT - 2*INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "buy_repair");
    pTo_fuel_button   = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5)), (g_VIEW_HEIGHT - 3*INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "buy fuel");  
    pTo_launch_button = new Button(pTo_particleTexOb, (g_VIEW_WIDTH - 1 * (INTERFACE_ICON_SIZE + 5)), (g_VIEW_HEIGHT - 4*INTERFACE_ICON_SIZE), INTERFACE_ICON_SIZE,  INTERFACE_ICON_SIZE, "launch");

    angar_screen_SELECTED     = true;
    store_screen_SELECTED     = false;
    shop_screen_SELECTED      = false;
    galaxymap_screen_SELECTED = false;
    goverment_screen_SELECTED = false;
}


InterfaceInKosmoport :: ~InterfaceInKosmoport()
{}


void InterfaceInKosmoport :: mouseInteraction()
{
     bool CURSOR_INTERSECT_OBJECT = false;

     int mxvp = g_MOUSE_POS_X;
     int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     int lmb  = g_MOUSE_LEFT_BUTTON;

     pTo_angar_screen_button->show_info     = false;
     pTo_store_screen_button->show_info     = false;
     pTo_shop_screen_button->show_info      = false;
     pTo_galaxymap_screen_button->show_info = false;
     pTo_goverment_screen_button->show_info = false;

     pTo_repair_button->show_info = false;
     pTo_fuel_button->show_info   = false;
     pTo_launch_button->show_info = false;


     /////////////////////////////////////////////
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_angar_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_angar_screen_button->show_info = true;
           if (lmb == true)
           {
              angar_screen_SELECTED     = true;
              store_screen_SELECTED     = false;
              shop_screen_SELECTED      = false;
              galaxymap_screen_SELECTED = false;
              goverment_screen_SELECTED = false;
           }
        }
     }
     /////////////////////////////////////////////

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_store_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_store_screen_button->show_info = true;
           if (lmb == true)
           {
              angar_screen_SELECTED     = false;
              store_screen_SELECTED     = true;
              shop_screen_SELECTED      = false;
              galaxymap_screen_SELECTED = false;
              goverment_screen_SELECTED = false;
           }
        }
     } 
     /////////////////////////////////////////////


     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_shop_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_shop_screen_button->show_info = true;
           if (lmb == true)
           {
              angar_screen_SELECTED     = false;
              store_screen_SELECTED     = false;
              shop_screen_SELECTED      = true;
              galaxymap_screen_SELECTED = false;
              goverment_screen_SELECTED = false;
           }
        }

     }
     /////////////////////////////////////////////


     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_galaxymap_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_galaxymap_screen_button->show_info = true;
           if (lmb == true)
           {
              angar_screen_SELECTED     = false;
              store_screen_SELECTED     = false;
              shop_screen_SELECTED      = false;
              galaxymap_screen_SELECTED = true;
              goverment_screen_SELECTED = false;
           }
        }

     }
     /////////////////////////////////////////////


     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_goverment_screen_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_goverment_screen_button->show_info = true;
           if (lmb == true)
           {
              angar_screen_SELECTED     = false;
              store_screen_SELECTED     = false;
              shop_screen_SELECTED      = false;
              galaxymap_screen_SELECTED = false;
              goverment_screen_SELECTED = true;
           }
        }

     }
     /////////////////////////////////////////////


     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_repair_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_repair_button->show_info = true;
           if (lmb == true)
           {
              pTo_PLAYER->pTo_ship->setMaxArmor(); 
           }
        }

     }
     /////////////////////////////////////////////

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_fuel_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_fuel_button->show_info = true;
           if (lmb == true)
           {
              pTo_PLAYER->pTo_ship->setMaxFuel(); 
           }
        }

     }
     /////////////////////////////////////////////


     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_launch_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           pTo_launch_button->show_info = true;
           if (lmb == true)
           {
              pTo_PLAYER->pTo_npc->createLaunchingSequence(); 
              pTo_PLAYER->in_SPACE = true;
           }
        }

     }
     /////////////////////////////////////////////
}

void InterfaceInKosmoport :: render()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glLoadIdentity();
    
    pTo_angar_screen_button->render();
    pTo_store_screen_button->render();
    pTo_shop_screen_button->render();
    pTo_galaxymap_screen_button->render();
    pTo_goverment_screen_button->render();

    if (angar_screen_SELECTED == true)
    {
        pTo_repair_button->render();
        pTo_fuel_button->render();  
        pTo_launch_button->render();
    } 
}


void InterfaceInKosmoport :: renderInfo()
{
    if (pTo_angar_screen_button->show_info == true)
        pTo_angar_screen_button->renderInfo();

    if (pTo_store_screen_button->show_info == true)
        pTo_store_screen_button->renderInfo();

    if (pTo_shop_screen_button->show_info == true)
        pTo_shop_screen_button->renderInfo();

    if (pTo_galaxymap_screen_button->show_info == true)
        pTo_galaxymap_screen_button->renderInfo();

    if (pTo_goverment_screen_button->show_info == true)
        pTo_goverment_screen_button->renderInfo();

    if (angar_screen_SELECTED == true)
    {
        if (pTo_repair_button->show_info == true)
            pTo_repair_button->renderInfo();

        if (pTo_fuel_button->show_info == true)
            pTo_fuel_button->renderInfo();  

        if (pTo_launch_button->show_info == true)
            pTo_launch_button->renderInfo();
    } 
        
}
