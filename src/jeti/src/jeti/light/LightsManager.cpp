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

#include "LightsManager.hpp"

namespace jeti {

void LightsManager::add(const LightPtr& light)
{
    if (m_lights.size() > MAX_ACTIVE_LIGHTS) {
        if (!__killUseLess()) {
            return;
        }
    }
    m_lights.add(light);
    if (!m_globalLight && light->isGlobal()) {
        m_globalLight = light;
    }
}

void LightsManager::update(float time)
{
    //std::cout<<"lights_num="<<m_lights.size()<<std::endl;
    __removeDead();
    for (const LightPtr& light: m_lights) {
        light->update(time);
    }
}

ceti::pack<LightData>
LightsManager::shiningTo(const glm::vec3& position, int num) const
{
    ceti::pack<LightData> result;
    std::set<LightData> lighdataset;
    int counter = 0;

    //pass1
    for (const LightPtr& light: m_lights) {
        if (light->isGlobal()) {
            glm::vec3 dir(light->position() - position);
            float distance = glm::length(dir);
            result.add(LightData{light,distance,dir});
            counter++;
            if (counter>=num) {
                break;
            }
        } else {
            glm::vec3 dir(light->position() - position);
            float distance = glm::length(dir);
            //std::cout<<"distance="<<distance<<std::endl;
            lighdataset.emplace(LightData{light,distance,dir});
        }
    }

    //pass2
    //std::cout<<lighdataset.size()<<std::endl;
    for (const LightData& lightdata: lighdataset) {
        result.add(lightdata);
        counter++;
        if (counter>=num) {
            break;
        }
    }
    return result;
}

bool LightsManager::__killUseLess()
{
    float biggest = 0.0f;
    int index = -1;
    for (unsigned int i=0; i<m_lights.size(); ++i) {
        if (m_lights.at(i)->isEffect()) {
            float lifeTime = m_lights[i]->lifeTime();
            if (lifeTime > biggest) {
                biggest = lifeTime;
                index = int(i);
            }
        }
    }
    if (index != -1) {
        m_lights.at(unsigned(index))->dieSlow();
        return true;
    }

    return false;
}

void LightsManager::__removeDead()
{
    // TODO:: don't call it to often
    ceti::pack<LightPtr> remove_queue;
    for (const LightPtr& light: m_lights) {
        if (!light->isAlive()) {
            remove_queue.add(light);
        }
    }

    for (const LightPtr& light: remove_queue) {
        m_lights.remove(light);
    }
}

} // namespace jeti

