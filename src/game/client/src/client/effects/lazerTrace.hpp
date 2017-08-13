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

class Mesh;
class Render;

namespace control {
class Material;
} // namespace control

namespace particlesystem {
class Base;
} // namespace particlesystem
} // namespace jeti

namespace effect {

class Beam
{ 
public:
    Beam(jeti::control::Material*);
    ~Beam();

    bool isAlive() const { return m_isAlive; }

    void setParticleSystem(jeti::particlesystem::Base* particleSystem) { m_particleSystem = particleSystem; }

    void setFrom(const glm::vec3& from) { m_from = from; }
    void setTo(const glm::vec3& to) { m_to = to; }

    const glm::vec3& from() const { return m_from; }
    const glm::vec3& to() const { return m_to; }

    const jeti::control::Material& material() const { return *m_material; }

    void update();
    void draw(const jeti::Render&) const;

private:
    bool m_isAlive = true;
    int m_liveTime = 140;

    jeti::control::Material* m_material = nullptr;
    jeti::particlesystem::Base* m_particleSystem = nullptr;

    glm::vec4 m_color;
    glm::vec4 m_overlayColor;

    glm::vec3 m_from;
    glm::vec3 m_to;

    float m_sizeMax = 6.0f;
    float m_size = 1.0f;
    float m_deltaSize = 0.0f;

    glm::mat4 m_matrixModel;
    glm::mat4 m_matrixModelOverlay;
    glm::mat4 m_matrixTranslate;
    glm::mat4 m_matrixRotate;
    glm::mat4 m_matrixScale;
    glm::mat4 m_matrixScaleOverlay;

    void __updateModelMatrix();
};

} // namespace effect

