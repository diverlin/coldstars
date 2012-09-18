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
#include "Collision.hpp"


bool collisionBetweenCenters(const Points& points1, const Points& points2, float collision_radius)
{
    	if (std::fabs(points1.GetCenter().x - points2.GetCenter().x) > collision_radius)
       		return false;
    	if (std::fabs(points1.GetCenter().y - points2.GetCenter().y) > collision_radius)
       		return false;

    	return true;
}

bool collisionBetweenCenters(const Points& points1, const vec2f& point2, float collision_radius)
{
    	if(std::fabs(points1.GetCenter().x - point2.x) > collision_radius)
       		return false;
    	if(std::fabs(points1.GetCenter().y - point2.y) > collision_radius)
       		return false;

    	return true;
}

bool collisionBetweenCenters(const Points& points1, float center2_x, float center2_y, float collision_radius)
{
    	if(std::fabs(points1.GetCenter().x - center2_x) > collision_radius)
      		return false;
    	if(std::fabs(points1.GetCenter().y - center2_y) > collision_radius)
       		return false;

    	return true;
}

