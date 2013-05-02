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

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "points.hpp"

template <typename AGRESSOR, typename VICTIM>
bool checkCollision(AGRESSOR* agressor,  VICTIM* victim, bool show_effect)
{
	if (collisionBetweenCenters(agressor->GetPoints(), victim->GetPoints(), victim->GetCollisionRadius()) == true)
        {
        	victim->Hit(agressor->GetDamage(), show_effect);
                agressor->CollisionEvent(show_effect);
                
                return true;
        }
        else
        {
        	return false;
        }
}

bool collisionBetweenCenters(const Points& points1, const Points& points2, float collision_radius);
bool collisionBetweenCenters(const Points& points1, const Vec2<float>& point2, float collision_radius);
bool collisionBetweenCenters(const Points& points1, float center2_x, float center2_y, float collision_radius);

#endif 




