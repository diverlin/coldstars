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

#include <ceti/Pack.hpp>

#include <glm/glm.hpp>

namespace jeti {

class Light;

class LightsManager {
public:
    void add(Light*);
    void update(float);

    ceti::pack<Light*> visibleTo(const glm::vec3& pos, int num=3);

private:
    ceti::pack<Light*> m_lights;

    void __removeDead();
};

} // namespace jeti

