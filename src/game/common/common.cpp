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

#include <cmath>

#include "common.hpp"
#include "constants.hpp"
#include "Logger.hpp"

int getObjectSize(int w, int h)
{
	int area = w*h;
    	if(area < SIZE_1_AREA) return SIZE_1_ID;
    	if(area < SIZE_2_AREA) return SIZE_2_ID;
    	if(area < SIZE_3_AREA) return SIZE_3_ID;
    	if(area < SIZE_4_AREA) return SIZE_4_ID;
    	if(area < SIZE_5_AREA) return SIZE_5_ID;
    	if(area < SIZE_6_AREA) return SIZE_6_ID;
    	if(area < SIZE_7_AREA) return SIZE_7_ID;
    	if(area < SIZE_8_AREA) return SIZE_8_ID;
    	if(area < SIZE_9_AREA) return SIZE_9_ID;
    	if(area >= SIZE_9_AREA) return SIZE_10_ID;
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

Color4f getColor4fById(int color_id)
{
	Color4f color;
        switch(color_id)
        {	
        	case COLOR::YELLOW_ID:
		{
			color.r = 255/255.0;
			color.g = 255/255.0;
			color.b = 235/255.0;
			color.a = 1.0;
			
			break;
		}
	
		case COLOR::BLUE_ID:
		{
			color.r = 220/255.0;
			color.g = 255/255.0;
			color.b = 255/255.0;
			color.a = 1.0;
			
			break;
		}
	}
	
	return color;
}
