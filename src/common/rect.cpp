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


#include "rect.hpp"

Rect :: Rect()
{}


Rect :: Rect(float _bottomLeft_x, float _bottomLeft_y, int _w, int _h)
{
    	bottomLeft.x = _bottomLeft_x;
    	bottomLeft.y = _bottomLeft_y;
    	
    	w = _w;
    	h = _h;

    	calcCenter();
}


Rect :: Rect(vec2f _bottomLeft, int _w, int _h)
{
    	bottomLeft = _bottomLeft;

    	w = _w;
    	h = _h;

    	calcCenter();
}


Rect :: ~Rect()
{}


vec2f Rect :: getCenter() const     { return center; }
vec2f Rect :: getBottomLeft() const { return bottomLeft; }
int Rect :: getWidth() const 	    { return w; }
int Rect :: getHeight() const 	    { return h; }   		
      		
void Rect :: calcCenter()
{
    	center.x = bottomLeft.x + w/2;
    	center.y = bottomLeft.y + h/2;
}


void Rect :: setNewCenter(vec2f _center)
{
    	float dx = center.x - _center.x;
    	float dy = center.y - _center.y;

    	bottomLeft.x -= dx;
    	bottomLeft.y -= dy; 

    	center = _center;
}


void Rect :: setNewCenter(float _center_x, float _center_y)
{
    	float dx = center.x - _center_x;
    	float dy = center.y - _center_y;

    	bottomLeft.x -= dx;
    	bottomLeft.y -= dy; 

    	center.x = _center_x;
    	center.y = _center_y;
}



void Rect ::  setNewBottomLeftPos(vec2f _bottomLeft)
{
    	bottomLeft.x = _bottomLeft.x;
    	bottomLeft.y = _bottomLeft.y;

    	calcCenter();
}
