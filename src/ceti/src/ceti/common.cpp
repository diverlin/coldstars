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


#include "common.hpp"

#include <cmath>

//#include "constants.hpp"
//#include "Logger.hpp"

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

    if (glm::length(dir) > 0)
    {             
        dir = glm::normalize(dir);
        d_pos = glm::vec3(dir * velocity);   
        rTo_angle_inD = glm::degrees(atan2(dir.y, dir.x));
        
        return true;
    }
    else
    {
        d_pos = glm::vec3(0.0);
        rTo_angle_inD = glm::degrees(atan2(0.0, 0.0));
        
        return false;
    }        
}
