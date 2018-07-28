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

#include <memory>

namespace jeti {

class LightBuilder;

const float GLOBAL_LIGHT_RADIUS = 999999.0f;

class Light
{      
public:
    ~Light() = default;

    void dieSlow() { m_isDying = true; }
    bool isAlive() const { return m_isAlive; }
    bool isGlobal() const { return (m_role == Role::GLOBAL); }
    bool isEffect() const { return (m_role == Role::EFFECT); }

    void update(float time);

    const glm::vec4& ambient() const { return m_ambient; }
    const glm::vec4& diffuse() const { return m_diffuse; }
    const glm::vec4& specular() const { return m_specular; }
    const glm::vec3& attenuation() const { return m_attenuation; }

    const glm::vec3& position() const { return m_position; }
    float radius() const { return m_radius; }

    float attenuationFactor(float) const;
    float lifeTime() const { return m_lifeTime; }

    bool operator==(const Light&) const { return false; } // to be able to use with ceti::pack

private:
    enum class Move : int { STATIC, LINEAR, LINEARCYCLIC, CIRCULAR };
    enum class Role : int { GLOBAL, LOCAL, EFFECT };

    Light(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float ambient_factor=0.4f);

    void __makeGlobal();
    void __makeLocal();
    void __makeEffect();

    void __setColor(const glm::vec4&, float ambient_factor=0.4f);
    void __setRadius(float radius);
    void __setPosition(const glm::vec3& position);
    void __moveLinear(const glm::vec3& dir, float speed);
    void __moveLinearCyclic(float distance, const glm::vec3& dir, float speed);
    void __moveCircular(float radius, float speed);
    void __useVariadicRadius(float min, float max, float step);

    bool m_isInitialized = false;
    bool m_isAlive = true;
    bool m_isDying = false;
    float m_bornTime = 0.0f;
    float m_lifeTime = 0.0f;

    glm::vec4 m_ambient;
    glm::vec4 m_diffuse;
    glm::vec4 m_specular;
    glm::vec3 m_attenuation;

    glm::vec3 m_positionOrig;
    glm::vec3 m_position;

    Move m_moveType = Move::STATIC;
    Role m_role = Role::LOCAL;

    float m_speed = 0.0f;
    float m_radiusOrigin = 0;
    float m_radius = 0;
    float m_distance = 0.0f;
    glm::vec3 m_moveDir = glm::vec3(1.0, 0.0, 0.0);

    float m_radiusMin = 0.0f;
    float m_radiusMax = 0.0f;
    float m_radiusSpeed = 0.0f;
    bool m_useVariadicRadius = false;

    void __init(float);
    void __updateMovement(float);
    void __updateRadius(float);
    void __updateLifeTime(float);

    friend LightBuilder;
};

using LightPtr = std::shared_ptr<Light>;

} // namespace jeti

