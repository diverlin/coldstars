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


LandingArea :: LandingArea(TextureOb* _texOb, float _center_x, float _center_y, int _w, int _h)
{
    	is_BUSY = false;
    	is_CURSORED = false;
    
    	texOb = _texOb;

    	rect = Rect(_center_x - _w/2, _center_y - _h/2, _w, _h);
}
   
LandingArea :: ~LandingArea()
{}


Ship* LandingArea :: getShip()      { return ship; }
Rect LandingArea :: getRect() const { return rect; }
      
bool LandingArea :: getBusyFlag()     const { return is_BUSY; }
bool LandingArea :: getCursoredFlag() const { return is_CURSORED; }
                
void LandingArea :: setBusyFlag(bool _busy_flag)         { is_BUSY = _busy_flag; }
void LandingArea :: setCursoredFlag(bool _cursored_flag) { is_CURSORED = _cursored_flag; }
                
                          
void LandingArea :: placeShip(Ship* _ship)
{
        ship = _ship;
        is_BUSY = true;    
}

void LandingArea :: removeShip()
{
        ship = NULL;
        is_BUSY = false;    
} 

void LandingArea :: renderArea()
{
     	drawTexturedRect(texOb->texture, rect, -1);
}

void LandingArea :: renderInternals()
{
     	if (is_BUSY == true)
     	{
        	ship->getPoints()->setAngle(0);
        	ship->getPoints()->setCenter(rect.getCenter().x, rect.getCenter().y);
        	ship->render_atPlanet();
     	}
}


void LandingArea :: renderInfo()
{
     	if (is_BUSY == true)
     	{
        	if (is_CURSORED == true)
        	{
            		//ship->updateInfo();
            		ship->renderInfo(rect.getCenter().x, rect.getCenter().y, 0, 0);
        	} 
        }
}
