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


#include "landingarea.hpp"


LandingArea :: LandingArea(TextureOb* _pTo_texOb, float _center_x, float _center_y, int _w, int _h)
{
    is_BUSY = false;
    is_CURSORED = false;
    
    pTo_texOb = _pTo_texOb;
    w = _w; //pTo_texOb->w;
    h = _h; //pTo_texOb->h;

    rect = Rect(_center_x - w/2, _center_y - h/2, w, h);
}
   
LandingArea :: ~LandingArea()
{}

void LandingArea :: placeShip(Ship* _pTo_ship)
{
   pTo_ship = _pTo_ship;
   is_BUSY = true;    
}

void LandingArea :: removeShip()
{
   pTo_ship = NULL;
   is_BUSY = false;    
} 

void LandingArea :: renderArea()
{
     	drawTexturedRect(pTo_texOb->texture, rect, -1);
}

void LandingArea :: renderInternals()
{
     	if (is_BUSY == true)
     	{
        	pTo_ship->getPoints()->setAngle(0);
        	pTo_ship->getPoints()->setCenter(rect.center_x, rect.center_y);
        	pTo_ship->render_atPlanet();
     	}
}


void LandingArea :: renderInfo()
{
     	if (is_BUSY == true)
     	{
        	if (is_CURSORED == true)
        	{
            		//pTo_ship->updateInfo();
            		pTo_ship->renderInfo(rect.center_x, rect.center_y, 0, 0);
        	} 
        }
}
