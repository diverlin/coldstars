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

#include "constants.hpp"

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



bool get_dPos_ToPoint(const vec2f& p1, const vec2f& p2, float velocity, vec2f& d_pos)
{    
    	float lx = p2.x - p1.x;
    	float ly = p2.y - p1.y;
    
    	float l = sqrt(lx*lx + ly*ly);

    	if (l != 0.0f)
    	{
    	       	d_pos.x = lx/l * velocity;
       		d_pos.y = ly/l * velocity;
       		
       		return true;
    	}
    	else
    	{
    	    	d_pos.x = 0.0f;
       		d_pos.y = 0.0f;
       		
       		return false;
    	}
}


bool get_dPos_ToPoint(const vec2f& p1, const vec2f& p2, float velocity, vec2f& d_pos, float& rTo_angle_inD)
{
    	float lx = p2.x - p1.x;
    	float ly = p2.y - p1.y;
    
    	float l = sqrt(lx*lx + ly*ly);

    	if (l != 0.0f)
    	{
    	       	d_pos.x = lx/l * velocity;
       		d_pos.y = ly/l * velocity;
       		rTo_angle_inD = atan2(ly, lx) * RADIAN_TO_DEGREE_RATE;
       		
       		return true;
    	}
    	else
    	{
    	    	d_pos.x = 0.0f;
       		d_pos.y = 0.0f;
       		rTo_angle_inD = atan2(ly, lx) * RADIAN_TO_DEGREE_RATE;
       		
       		return false;
    	}    	
}

template <typename T>
T getMin(T val1, T val2)
{
	if (val1<val2) 	return val1;
	else		return val2;
}

template <typename T>
T getMin(T val1, T val2, T val3)
{
	int min2 = getMin(val1, val2);
	return getMin(min2, val3);
}
