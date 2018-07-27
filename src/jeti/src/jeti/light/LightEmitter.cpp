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
#include <jeti/Render.hpp>

namespace jeti {

LightEmitter::LightEmitter(Render* render)
    :
      m_render(render)
{}

void LightEmitter::update(float time)
{
    __init();

    float elapsedTime = time - m_lastCreationTime;
    if (elapsedTime > 0.1f) {
        Light* light = m_builder.genEffect().color().radius().moveLinear().take();
        m_render->addLight(light);
        m_lastCreationTime = time;
    }
}

void LightEmitter::__init()
{
    if (m_isInitialized) {
        return;
    }

    m_builder.setSize(m_render->width(), m_render->height());

    m_isInitialized= true;
}

} // namespace jeti

