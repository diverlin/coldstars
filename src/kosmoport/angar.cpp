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


Angar :: Angar(TextureOb* _texOb_background, TextureOb* _texOb_slot)
{
        texOb_background = _texOb_background;

        int slot_w = 120;

        LandingArea* pTo_landingArea0 = new LandingArea(_texOb_slot, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2,       slot_w, slot_w);
        landingArea_pList.push_back(pTo_landingArea0);

        LandingArea* pTo_landingArea1 = new LandingArea(_texOb_slot, g_VIEW_WIDTH/2 + 150, g_VIEW_HEIGHT/2,       slot_w, slot_w);
        landingArea_pList.push_back(pTo_landingArea1);
    
        LandingArea* pTo_landingArea2 = new LandingArea(_texOb_slot, g_VIEW_WIDTH/2 - 150, g_VIEW_HEIGHT/2,       slot_w, slot_w);
        landingArea_pList.push_back(pTo_landingArea2);

        LandingArea* pTo_landingArea3 = new LandingArea(_texOb_slot, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 + 150, slot_w, slot_w);
        landingArea_pList.push_back(pTo_landingArea3);

        LandingArea* pTo_landingArea4 = new LandingArea(_texOb_slot, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 - 150, slot_w, slot_w);
        landingArea_pList.push_back(pTo_landingArea4);
}


int Angar :: getNumFreelandingArea()
{
        int sum_free = 0;
        for (unsigned int la = 0; la < landingArea_pList.size(); la++)
                if (landingArea_pList[la]->getBusyFlag() == false)
                        sum_free++;
        return sum_free; 
}

bool Angar :: addShip(Ship* _pTo_ship)
{
        for (unsigned int la = 0; la < landingArea_pList.size(); la++)
        {
                if (landingArea_pList[la]->getBusyFlag() == false)
                {
                        landingArea_pList[la]->placeShip(_pTo_ship);
                        return true;
                }
        }
        
        return false;        
}


bool Angar :: removeShipFromlandingAreaById(int _id)
{
        for (unsigned int la = 0; la < landingArea_pList.size(); la++)
        {
                if (landingArea_pList[la]->getBusyFlag() == true)
                {
                        if (landingArea_pList[la]->getShip()->id == _id)
                        {
                                landingArea_pList[la]->removeShip();
                                return true;
                        }
                }
        }
    
        return false;       
}


void Angar :: resetSlotsRenderInfoFlag()
{
        for (unsigned int i = 0; i < landingArea_pList.size(); i++)
        {
                landingArea_pList[i]->setCursoredFlag(false);
        }
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
                                                landingArea_pList[i]->getRect().getCenter().x, 
                                                landingArea_pList[i]->getRect().getCenter().y);
        				
                if (dist < landingArea_pList[i]->getRect().getWidth()/2)
                {
                        landingArea_pList[i]->setCursoredFlag(true);
                        if (rmb == true)
                        {
                                if (landingArea_pList[i]->getBusyFlag() == true)
                                {
                                        pPLAYER->getPilot()->setScanTarget(landingArea_pList[i]->getShip());
                                        pPLAYER->is_SCANNING = true;
                                }
                        }
                }
        }
}

void Angar :: renderBackground()
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(texOb_background->texture, screen_rect, -2);  
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
        {
                landingArea_pList[li]->renderInfo();
        }
}
            

