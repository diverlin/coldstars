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

#include "Light.hpp"

#include "LightsManager.hpp"

namespace jeti {

void LightsManager::add(Light* light)
{
    if (light->isGlobal()) {
        m_globalLights.add(light);
    } else {
        m_localLights.add(light);
    }
}

void LightsManager::update(float time)
{
    __removeDead();
    for (Light* light: m_globalLights) {
        light->update(time);
    }
    for (Light* light: m_localLights) {
        light->update(time);
    }
}

ceti::pack<Light*>
LightsManager::visibleTo(const glm::vec3& position, int num)
{
    ceti::pack<Light*> result;
    int counter = 0;
    for (Light* light: m_globalLights) {
        result.add(light);
        counter++;

        if (counter == num) {
            break;
        }
    }

    for (Light* light: m_localLights) {
        if (glm::length(position-light->position()) < light->radius()) {
            result.add(light);
        }

        if (counter == num) {
            break;
        }
    }

    return result;

}

void LightsManager::__removeDead()
{
    assert(false && "TODO");
}

} // namespace jeti

