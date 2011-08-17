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


#include "turrel.h"

Turrel :: Turrel()
{
    //////
    points = Points();
    points.addCenterPoint();
    points.addMainQuadPoints();
    //////

    pos_z = -1.5;
}


void Turrel :: setTexOb(TextureOb* _pTo_texOb)
{
    pTo_texOb = _pTo_texOb;
    w = (*pTo_texOb).w;
    h = (*pTo_texOb).h;   
    texture = (*pTo_texOb).texture;   // move this to linkTexture func

    //////
    points.initCenterPoint();
    points.initMainQuadPoints(w, h);
    //////
}


Turrel :: ~Turrel()
{}


void Turrel :: update(float _center_x, float _center_y, float _angle_inD)
{   
    points.setCenter(_center_x, _center_y);
    points.setAngle(_angle_inD);
    points.update();
}


void Turrel :: render()
{
    glBindTexture(GL_TEXTURE_2D, texture); 
    drawFlatQuadPerVertexIn2D(points.bottomLeft_x, points.bottomLeft_y, points.bottomRight_x, points.bottomRight_y, points.topRight_x, points.topRight_y, points.topLeft_x, points.topLeft_y, pos_z);
}
