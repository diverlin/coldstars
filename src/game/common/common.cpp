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



bool get_dPos_ToPoint(const Vec3<float>& p1, const Vec3<float>& p2, float velocity, Vec3<float>& d_pos)
{   	    
    	Vec3<float> dir(p2-p1);

    	if (!dir.IsNull())
    	{
    	    	dir.Normalize();
    	       	d_pos.Set(dir * velocity);       		
       		return true;
    	}
    	else
    	{
    	    	d_pos.Set(0.0, 0.0, 0.0);       		
       		return false;
    	}
}


bool get_dPos_ToPoint(const Vec3<float>& p1, const Vec3<float>& p2, float velocity, Vec3<float>& d_pos, float& rTo_angle_inD)
{
    	Vec3<float> dir(p2-p1);

    	if (!dir.IsNull())
    	{ 	    	
    	    	dir.Normalize();
    	       	d_pos.Set(dir * velocity);   
       		rTo_angle_inD = atan2(dir.x, dir.y) * RADIAN_TO_DEGREE_RATE;
       		
       		return true;
    	}
    	else
    	{
    	    	d_pos.Set(0.0, 0.0, 0.0); 
       		rTo_angle_inD = atan2(0.0, 0.0) * RADIAN_TO_DEGREE_RATE;
       		
       		return false;
    	}    	
}

Color4<float> getColor4fById(int color_id)
{
	Color4<float> color;
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
