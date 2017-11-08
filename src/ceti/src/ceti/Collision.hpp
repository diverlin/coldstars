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

#pragma once

#include <glm/glm.hpp>   

#include <iostream>

namespace ceti {

bool isPointInCircle(const glm::vec3& c1, const glm::vec3& c2, float radius);
bool isPointInCircle(const glm::vec2& c1, const glm::vec2& c2, float radius);
bool isPointInRectangle(const glm::vec2& dot, const glm::vec2& center, const glm::vec2& size);

template <typename AGRESSOR, typename VICTIM>
bool checkCollision(AGRESSOR* agressor, VICTIM* victim)
{
    if (isPointInCircle(agressor->position(),
                        victim->position(),
                        agressor->collisionRadius()+victim->collisionRadius())) {
        return true;
    }

    return false;
}

bool isLineInCircle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& observer_pos, float radius);

} // namespace ceti







