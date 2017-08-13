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

#include "AnimationEffect2D.hpp"

#include <ceti/Box2D.hpp>

namespace jeti {

void AnimationEffect2D::Update(ceti::Box2D& box)
{
    if ((scale.x < scale_min.x) and (scale.y < scale_min.y)) {
        scale_up = true;
    } else if ((scale.x > scale_max.x) and (scale.y > scale_max.y)) {
        scale_up = false;
    }
    
    if (scale_up) {
        scale += d_scale;
    } else {
        scale -= d_scale;
    }
    
    box.SetScale(meti::vec2(scale));
}

void AnimationEffect2D::Reset()
{
    scale = glm::vec3(1.0f);
    angle = 0.0f;
    scale_up = true;
}

} // namespace jeti
