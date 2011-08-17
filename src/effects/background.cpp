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


#include "background.h"

distantStarBgEffect :: distantStarBgEffect(TextureOb* _pTo_texOb, float _center_x, float _center_y, float _particleSize)
{
    pTo_texOb = _pTo_texOb; 
    texture = (*pTo_texOb).texture;
    center_x = _center_x; 
    center_y = _center_y;
    particleSize = _particleSize;
    distance_rate = _particleSize / 1000;
}


void distantStarBgEffect :: render(float vx, float vy)
{   //glLoadIdentity(); 
    glPointSize(particleSize);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_POINTS);
    glVertex3f(center_x - vx*distance_rate, center_y - vy*distance_rate , -2.0);
    glEnd();
}

   



distantNebulaBgEffect :: distantNebulaBgEffect(TextureOb* _pTo_texOb, float _center_x, float _center_y)
{
    pTo_texOb = _pTo_texOb;
    texture = (*pTo_texOb).texture;

    w = (*pTo_texOb).w;
    h = (*pTo_texOb).h;
    updateWHRenderConstants();

    if(w*h>300000)
      { distance_rate =  1/60.0; }
    else
      { distance_rate =  1/40.0; }

    is_rotated = (*pTo_texOb).is_rotated;

    if(is_rotated)
    {
        angleInDegree = randIntInRange(0, 360);
        d_angleInDegree = randIntInRange(8,12)*0.001;
        if(randIntInRange(1,2) == 1) 
          d_angleInDegree = -1*d_angleInDegree; 

    }
    else
    {
        angleInDegree = 0;
        d_angleInDegree = 0;
    }

    center_x = _center_x; 
    center_y = _center_y;
    pos_z = -999.0;
}
   
   
void distantNebulaBgEffect :: update()
{
     angleInDegree += d_angleInDegree;  
}        


void distantNebulaBgEffect :: updateWHRenderConstants()
{
    // constants needs for render
    // decreases the math during game loop
    minus_half_w = -w/2;
    minus_half_h = -h/2;
    plus_half_w  =  w/2;
    plus_half_h  =  h/2;
}


void distantNebulaBgEffect :: render(float vx, float vy)
{ 
   glBindTexture(GL_TEXTURE_2D, texture);
   drawDynamic(center_x - vx*distance_rate, center_y - vy*distance_rate, angleInDegree, minus_half_w, minus_half_h, plus_half_w, plus_half_h, pos_z);
}
              

