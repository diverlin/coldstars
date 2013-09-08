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

#include <glm/glm.hpp>   

bool checkCollisionDotWithCircle_DIRTY(const glm::vec2& dot, const glm::vec2& center, float radius);
bool checkCollisionDotWithRectangle(const glm::vec2& dot, const glm::vec2& center, const glm::vec2& size);

template <typename AGRESSOR, typename VICTIM>
bool checkCollision2D(AGRESSOR* agressor,  VICTIM* victim, bool show_effect)
{
    if (checkCollisionDotWithCircle_DIRTY(vec3ToVec2(agressor->GetCenter()), vec3ToVec2(victim->GetCenter()), victim->GetCollisionRadius()) == true)
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

#endif 




