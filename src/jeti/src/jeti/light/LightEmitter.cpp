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

#include "LightEmitter.hpp"

#include <jeti/light/Light.hpp>

namespace jeti {

LightEmitter::LightEmitter(int w, int h)
    :
      m_width(w)
    , m_height(h)
{
    m_builder.setSize(w, h);
}

void LightEmitter::resize(int w, int h)
{
    m_builder.setSize(w, h);
}

jeti::Light* LightEmitter::update(float time)
{
    jeti::Light* newLight = nullptr;
    float elapsedTime = time - m_lastCreationTime;
    if (elapsedTime > 0.5f) {
        newLight = m_builder.genEffect().color().radius().moveLinear().take();
        m_lastCreationTime = time;
    }

    return newLight;
}

} // namespace jeti

