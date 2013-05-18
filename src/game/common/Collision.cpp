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

bool collisionDotCircle_FAST(const Vec2<float>& center1, const Vec2<float>& center2, float collision_radius)
{
    	if (std::fabs(center1.x - center2.x) > collision_radius/2)
       		return false;
    	if (std::fabs(center1.y - center2.y) > collision_radius/2)
       		return false;

    	return true;
}

bool collisionDotCircle_FAST(const Vec2<float>& center1, float center2_x, float center2_y, float collision_radius)
{
	return collisionDotCircle_FAST(center1, Vec2<float>(center2_x, center2_y), collision_radius);
}
