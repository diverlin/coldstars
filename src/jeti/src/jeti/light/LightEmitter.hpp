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

#include "LightBuilder.hpp"

#include <vector>

namespace jeti {

class LightEmitter {
public:
    LightEmitter(int w=0, int h=0);
    ~LightEmitter() = default;

    void resize(int w, int h);
    jeti::Light* update(float time);

private:
    bool m_width = 0;
    bool m_height = 0;
    float m_lastCreationTime = 0.0f;

    LightBuilder m_builder;
};

} // namespace jeti

