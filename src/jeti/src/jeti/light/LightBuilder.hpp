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

namespace jeti {

class Light;

class LightBuilder {
    const float LIGHT_DEFAULT_ZPOZ = 0.0f;
public:
    LightBuilder(int, int);
    ~LightBuilder();

    LightBuilder& genGlobal();
    LightBuilder& genLocal();
    LightBuilder& genEffect();

    LightBuilder& position();
    LightBuilder& position(const glm::vec3&);
    LightBuilder& radius();
    LightBuilder& radius(float);
    LightBuilder& radiusVar();
    LightBuilder& radiusVar(float, float, float);
    LightBuilder& color();
    LightBuilder& color(const glm::vec4&);
    LightBuilder& moveCircular();
    LightBuilder& moveCircular(float, float);
    LightBuilder& moveLinear();
    LightBuilder& moveLinear(const glm::vec3&, float);
    LightBuilder& moveLinearCyclic();
    LightBuilder& moveLinearCyclic(float, const glm::vec3&, float);

    Light* take();

    //    static Light* genGlobal(const glm::vec4&, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));
//    static Light* genLocal(const glm::vec4&, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));
//    static Light* genEffect(const glm::vec4&, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));

private:
    int m_width = 0;
    int m_height = 0;
    Light* m_light = nullptr;

    float __getScreenWorldSize() const;
};

} // namespace jeti

