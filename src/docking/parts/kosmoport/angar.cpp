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


Angar :: Angar(TextureOb* _texOb_background, TextureOb* _texOb_landingArea)
{
        texOb_background = _texOb_background;

        LandingArea* landingArea0 = new LandingArea(_texOb_landingArea, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2,       ANGAR_SLOT_WIDTH, ANGAR_SLOT_HEIGHT);
        landingArea_vec.push_back(landingArea0);

        LandingArea* landingArea1 = new LandingArea(_texOb_landingArea, g_VIEW_WIDTH/2 + 150, g_VIEW_HEIGHT/2,       ANGAR_SLOT_WIDTH, ANGAR_SLOT_HEIGHT);
        landingArea_vec.push_back(landingArea1);
    
        LandingArea* landingArea2 = new LandingArea(_texOb_landingArea, g_VIEW_WIDTH/2 - 150, g_VIEW_HEIGHT/2,       ANGAR_SLOT_WIDTH, ANGAR_SLOT_HEIGHT);
        landingArea_vec.push_back(landingArea2);

        LandingArea* landingArea3 = new LandingArea(_texOb_landingArea, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 + 150, ANGAR_SLOT_WIDTH, ANGAR_SLOT_HEIGHT);
        landingArea_vec.push_back(landingArea3);

        LandingArea* landingArea4 = new LandingArea(_texOb_landingArea, g_VIEW_WIDTH/2,       g_VIEW_HEIGHT/2 - 150, ANGAR_SLOT_WIDTH, ANGAR_SLOT_HEIGHT);
        landingArea_vec.push_back(landingArea4);
}


int Angar :: getNumFreelandingArea()
{
        int sum_free = 0;
        for (unsigned int la = 0; la < landingArea_vec.size(); la++)
                if (landingArea_vec[la]->getBusyFlag() == false)
                        sum_free++;
        return sum_free; 
}

bool Angar :: addShip(Ship* _ship)
{
        for (unsigned int la = 0; la < landingArea_vec.size(); la++)
        {
                if (landingArea_vec[la]->getBusyFlag() == false)
                {
                        landingArea_vec[la]->insertShip(_ship);
                        return true;
                }
        }
        
        return false;        
}


bool Angar :: removeShipFromlandingAreaById(int _id)
{
        for (unsigned int la = 0; la < landingArea_vec.size(); la++)
        {
                if (landingArea_vec[la]->getBusyFlag() == true)
                {
                        if (landingArea_vec[la]->getShip()->getId() == _id)
                        {
                                landingArea_vec[la]->removeShip();
                                return true;
                        }
                }
        }
    
        return false;       
}


void Angar :: resetSlotsRenderInfoFlag()
{
        for (unsigned int i = 0; i < landingArea_vec.size(); i++)
        {
                landingArea_vec[i]->setCursoredFlag(false);
        }
}


void Angar :: mouseControl()
{
        //bool lmb = g_MOUSE_LEFT_BUTTON; 
        bool rmb = g_MOUSE_RIGHT_BUTTON; 

        for (unsigned int i = 0; i < landingArea_vec.size(); i++)
        { 
                float dist = distBetweenPoints(g_MOUSE_POS_X, 
                                                g_VIEW_HEIGHT - g_MOUSE_POS_Y, 
                                                landingArea_vec[i]->getRect().getCenter().x, 
                                                landingArea_vec[i]->getRect().getCenter().y);
        				
                if (dist < landingArea_vec[i]->getRect().getWidth()/2)
                {
                        landingArea_vec[i]->setCursoredFlag(true);
                        if (rmb == true)
                        {
                                if (landingArea_vec[i]->getBusyFlag() == true)
                                {
                                        pPLAYER->getPilot()->setScanTarget(landingArea_vec[i]->getShip());
                                        pPLAYER->setScanFlag(true);
                                        g_GUI_VEHICLE->configure(pPLAYER->getPilot()->getScanVehicle(), false, false); 
                                }
                        }
                }
        }
}


void Angar :: update()
{
        resetSlotsRenderInfoFlag();
        mouseControl();
}


void Angar :: render() const
{
        clearScreen();
        resetRenderTransformation();
                        
        renderBackground();
                
	enable_BLEND();
        
        renderInternals();
        //renderItemInfo();
        
}

void Angar :: renderBackground() const
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(texOb_background, screen_rect, -2);  
}

void Angar :: renderInternals() const
{
        for (unsigned int li = 0; li < landingArea_vec.size(); li++)
        {
                landingArea_vec[li]->renderArea();
        }

        for (unsigned int li = 0; li < landingArea_vec.size(); li++)
        {
                if (landingArea_vec[li]->getBusyFlag() == true)
                {
                        landingArea_vec[li]->renderInternals();
                }
        }
}

void Angar :: renderItemInfo() const
{
        for (unsigned int li = 0; li < landingArea_vec.size(); li++)
        {
                if (landingArea_vec[li]->getCursoredFlag() == true)
                        if (landingArea_vec[li]->getBusyFlag() == true)
                                landingArea_vec[li]->renderInfo();
        }
}
            

