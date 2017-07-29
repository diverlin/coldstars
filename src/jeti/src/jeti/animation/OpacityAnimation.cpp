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

#include "OpacityAnimation.hpp"

#include <cassert>

namespace jeti {
namespace animation {

Opacity::Opacity(float min, float max, float downFactor, float upFactor)
    :
      m_min(min)
    , m_max(max)
    , m_downFactor(downFactor)
    , m_upFactor(upFactor)
{
    assert(downFactor<1.0f);
    assert(upFactor>1.0f);
    m_opacity = m_min;
}

void Opacity::update()
{      
    if (m_move == STOP) {
        return;
    }

    if (m_move == UP) {
        m_opacity *= m_upFactor;
    } else if (m_move == DOWN) {
        m_opacity *= m_downFactor;
    }

    if (m_opacity > m_max) {
        m_move = DOWN;
        m_opacity = m_max;
    } else if (m_opacity < m_min) {
        m_opacity = m_min;
        if (m_cyclic) {
            run();
        } else {
            m_move = STOP;
        }
    }
}

} // namespace effect
} // namespace view

