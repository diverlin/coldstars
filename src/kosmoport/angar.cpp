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


#include "angar.hpp"


Angar :: Angar(TextureOb* _pTo_bg_texOb, TextureOb* _pTo_slot_texOb)
{
    pTo_bg_texOb = _pTo_bg_texOb;

    int slot_w = 120;

    LandingArea* pTo_landingArea0 = new LandingArea(_pTo_slot_texOb, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2,       slot_w, slot_w);
    landingArea_pList.push_back(pTo_landingArea0);

    LandingArea* pTo_landingArea1 = new LandingArea(_pTo_slot_texOb, g_VIEW_WIDTH/2 + 150, g_VIEW_HEIGHT/2,       slot_w, slot_w);
    landingArea_pList.push_back(pTo_landingArea1);
    
    LandingArea* pTo_landingArea2 = new LandingArea(_pTo_slot_texOb, g_VIEW_WIDTH/2 - 150, g_VIEW_HEIGHT/2,       slot_w, slot_w);
    landingArea_pList.push_back(pTo_landingArea2);

    LandingArea* pTo_landingArea3 = new LandingArea(_pTo_slot_texOb, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 + 150, slot_w, slot_w);
    landingArea_pList.push_back(pTo_landingArea3);

    LandingArea* pTo_landingArea4 = new LandingArea(_pTo_slot_texOb, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 - 150, slot_w, slot_w);
    landingArea_pList.push_back(pTo_landingArea4);
}

void Angar :: linkTexture()
{
    //background_tex = pTo_bg_texOb->texture
}

void Angar :: unlinkTexture()
{
     //background_tex = -1; ???
}


int Angar :: returnFreelandingAreaNum()
{
    int sum_free = 0;
    for (unsigned int la = 0; la < landingArea_pList.size(); la++)
        if (landingArea_pList[la]->is_BUSY == false)
            sum_free++;
    return sum_free; 
}

bool Angar :: placeShipTolandingArea(Ship* _pTo_ship)
{
    for (unsigned int la = 0; la < landingArea_pList.size(); la++)
        if (landingArea_pList[la]->is_BUSY == false)
        {
           landingArea_pList[la]->placeShip(_pTo_ship);
           return true;
        }    
    return false;        
}


bool Angar :: removeShipFromlandingAreaById(int _id)
{
    for (unsigned int la = 0; la < landingArea_pList.size(); la++)
        if (landingArea_pList[la]->is_BUSY == true)
           if (landingArea_pList[la]->pTo_ship->id == _id)
           {
               landingArea_pList[la]->removeShip();
               return true;
           } 

    return false;       
}


void Angar :: resetSlotsRenderInfoFlag()
{
    for (unsigned int i = 0; i < landingArea_pList.size(); i++)
        landingArea_pList[i]->is_CURSORED = false;
}


void Angar :: mouseControl()
{
    bool lmb = g_MOUSE_LEFT_BUTTON; 
    bool rmb = g_MOUSE_RIGHT_BUTTON; 

    resetSlotsRenderInfoFlag();

    for (unsigned int i = 0; i < landingArea_pList.size(); i++)
    { 
        float dist = distBetweenCenters(g_MOUSE_POS_X, 
        				g_VIEW_HEIGHT - g_MOUSE_POS_Y, 
        				landingArea_pList[i]->rect.getCenter().x, 
        				landingArea_pList[i]->rect.getCenter().y);
        				
        if (dist < landingArea_pList[i]->rect.getWidth()/2)
        {
             landingArea_pList[i]->is_CURSORED = true;
             if (rmb == true)
             {
                 if (landingArea_pList[i]->is_BUSY == true)
                 {
                    pTo_PLAYER->pTo_npc->setScanTarget(landingArea_pList[i]->pTo_ship);
                    pTo_PLAYER->is_SCANNING = true;
                 }
             }
        }
    }
}

void Angar :: renderBackground()
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(pTo_bg_texOb->texture, screen_rect, -2);  
}

void Angar :: renderInternals()
{
     for (unsigned int li = 0; li < landingArea_pList.size(); li++)
     {
         landingArea_pList[li]->renderArea();
     }

     for (unsigned int li = 0; li < landingArea_pList.size(); li++)
     {
         landingArea_pList[li]->renderInternals();
     }
}

void Angar :: renderItemInfo()
{
     for (unsigned int li = 0; li < landingArea_pList.size(); li++)
         landingArea_pList[li]->renderInfo();
}
            

