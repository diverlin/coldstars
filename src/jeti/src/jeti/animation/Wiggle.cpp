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

#include "Wiggle.hpp"

#include <meti/QuaternionUtils.hpp>

#include <cmath>

namespace jeti {

namespace animation {

Wiggle::Wiggle(const glm::vec3& axis, float delta, float threshold)
    :
      BaseRotation(axis, delta),
      m_threshold(threshold)
{}

Wiggle::~Wiggle()
{}

void Wiggle::update(glm::quat& quat)
{
    if (m_clockwise) {
        m_angle += _deltaAngle();
        if (m_angle > m_threshold) {
            m_clockwise = false;
        }
    } else {
        m_angle -= _deltaAngle();
        if (m_angle < -m_threshold) {
            m_clockwise = true;
        }
    }
    
    meti::quatFromAngleAndAxis(quat, m_angle, m_axis);
}

} // namespace animation

} // namespace jeti
