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
    if(area < SIZE_1_AREA) return SIZE_1;
    if(area < SIZE_2_AREA) return SIZE_2;
    if(area < SIZE_3_AREA) return SIZE_3;
    if(area < SIZE_4_AREA) return SIZE_4;
    if(area < SIZE_5_AREA) return SIZE_5;
    if(area < SIZE_6_AREA) return SIZE_6;
    if(area < SIZE_7_AREA) return SIZE_7;
    if(area < SIZE_8_AREA) return SIZE_8;
    if(area < SIZE_9_AREA) return SIZE_9;
    if(area >= SIZE_9_AREA) return SIZE_10;
    
    return SIZE_10;
}



bool get_dPos_ToPoint(const glm::vec3& p1, const glm::vec3& p2, float velocity, glm::vec3& d_pos)
{           
    glm::vec3 dir(p2-p1);

    if (glm::length(dir) > 0)
    {
        dir = glm::normalize(dir);
        d_pos = glm::vec3(dir * velocity);               
        return true;
    }
    else
    {
        d_pos = glm::vec3(0.0);               
        return false;
    }
}


bool get_dPos_ToPoint(const glm::vec3& p1, const glm::vec3& p2, float velocity, glm::vec3& d_pos, float& rTo_angle_inD)
{
    glm::vec3 dir(p2-p1);
    if (glm::length(dir) > 0) {
        dir = glm::normalize(dir);
        d_pos = glm::vec3(dir * velocity);   
        rTo_angle_inD = glm::degrees(atan2(dir.y, dir.x));
        return true;
    } else {
        d_pos = glm::vec3(0.0);
        rTo_angle_inD = glm::degrees(atan2(0.0, 0.0));
        return false;
    }        
}

glm::vec4 getColor4fById(int color_id)
{
    glm::vec4 color;
    switch(color_id)
    {
        case COLOR::YELLOW:
        {
            color.r = 255/255.0;
            color.g = 255/255.0;
            color.b = 235/255.0; // 235
            color.a = 1.0;
            
            break;
        }

        case COLOR::BLUE:
        {
            color.r = 220/255.0; // 220
            color.g = 255/255.0;
            color.b = 255/255.0;
            color.a = 1.0;
            
            break;
        }
    }
    
    return color;
}
