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
//#include "constants.hpp"


//size 0...9
int returnObjectSize(int w, int h)
{
    	if(w * h < SIZE_1 * SIZE_1)
       		return 1;
    	else if(w * h < SIZE_2 * SIZE_2)
       		return 2;
    	else if(w * h < SIZE_3 * SIZE_3)
       		return 3;
    	else if(w * h < SIZE_4 * SIZE_4)
       		return 4;
    	else if(w * h < SIZE_5 * SIZE_5)
       		return 5;
    	else if(w * h < SIZE_6 * SIZE_6)
       		return 6;
    	else if(w * h < SIZE_7 * SIZE_7)
       		return 7;
    	else if(w * h < SIZE_8 * SIZE_8)
       		return 8;
    	else if(w * h < SIZE_9 * SIZE_9)
       		return 9;
    	else if(w * h >= SIZE_9 * SIZE_9)
       		return 10;
                
        return 0;
}



bool get_dX_dY_ToPoint(float x1, float y1, float x2, float y2, float velocity, float* pTo_dx, float* pTo_dy)
{    
    	float xn, yn; 
    	float lx = x2 - x1;
    	float ly = y2 - y1;
    
    	float l = sqrt(lx*lx + ly*ly);

    	if (l < 0.1)
    	{
       		return false;
    	}
    	else
    	{ 
       		xn = lx/l;
       		yn = ly/l;
     
       		(*pTo_dx) = xn * velocity;
       		(*pTo_dy) = yn * velocity;
       		
       		return true;
    	}
}



void get_dX_dY_angleInD_ToPoint(float x1, float y1, float x2, float y2, float velocity, float* pTo_dx, float* pTo_dy, float* pTo_angle_inD)
{
    	float xn, yn; 
    	float lx = x2 - x1;
    	float ly = y2 - y1;

    	float l = sqrt(lx*lx + ly*ly);

    	if (l!= 0)
    	{
       		xn = lx/l;
       		yn = ly/l;
    	}
    	else
    	{
       		xn = 0; 
       		yn = 0;
    	}
     
    	(*pTo_dx) = xn * velocity;
    	(*pTo_dy) = yn * velocity;
    	(*pTo_angle_inD) = atan2(ly, lx) * RADIAN_TO_DEGREE_RATE;
}


