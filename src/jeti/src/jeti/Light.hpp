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

const float GLOBAL_LIGHT_RADIUS = 999999.0f;

class Light
{      
public:
    Light(const glm::vec4& color, float ambient_factor=0.4f);
    ~Light() = default;

    bool isGlobal() const { return ((GLOBAL_LIGHT_RADIUS - m_radius) < 1.0f); }
    void setRadius(float radius);
    void setPosition(const glm::vec3& position);
    void moveLinear(float radius, float speed, const glm::vec3& dir = glm::vec3(1.0f, 0.0f, 0.0f));
    void moveCircular(float radius, float speed);
    void update(float time);

    void useVariadicRadius(float min, float max, float step);

    const glm::vec4 ambient() const { return m_ambient; }
    const glm::vec4 diffuse() const { return m_diffuse; }
    const glm::vec4 specular() const { return m_specular; }
    const glm::vec3 attenuation() const { return m_attenuation; }

    const glm::vec3 position() const { return m_position; }
    float radius() const { return m_radius; }

    float attenuationFactor(float) const;

    bool operator==(const Light&) const { return false; } // to be able to use with ceti::pack

private:
    enum class Type : int { STATIC, MOVE_LINEAR, MOVE_CIRCULAR };

    glm::vec4 m_ambient;
    glm::vec4 m_diffuse;
    glm::vec4 m_specular;
    glm::vec3 m_attenuation;

    glm::vec3 m_positionOrig;
    glm::vec3 m_position;

    Type m_type = Type::STATIC;
    float m_speed = 0.0f;
    float m_radiusOrigin = 0;
    float m_radius = 0;
    float m_amplitude = 0.0f;
    glm::vec3 m_moveDir = glm::vec3(1.0, 0.0, 0.0);

    float m_radiusMin = 0.0f;
    float m_radiusMax = 0.0f;
    float m_radiusSpeed = 0.0f;
    bool m_useVariadicRadius = false;
};

} // namespace jeti

