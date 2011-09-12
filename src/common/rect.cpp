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
    bottomLeft_x = _bottomLeft_x;
    bottomLeft_y = _bottomLeft_y;

    w = _w;
    h = _h;

    calcCenter();
}


Rect :: ~Rect()
{}


void Rect :: calcCenter()
{
    center_x = bottomLeft_x + w/2;
    center_y = bottomLeft_y + h/2;
}


void Rect :: setNewCenter(float _center_x, float _center_y)
{
    float dx = center_x - _center_x;
    float dy = center_y - _center_y;

    bottomLeft_x -= dx;
    bottomLeft_y -= dy; 

    center_x = _center_x;
    center_y = _center_y;
}


void Rect ::  setNewBottomLeftPos(float _bottomLeft_x, float _bottomLeft_y)
{
    bottomLeft_x = _bottomLeft_x;
    bottomLeft_y = _bottomLeft_y;

    calcCenter();
}
