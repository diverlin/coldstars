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

#include <boost/property_tree/ptree.hpp>
#include <glm/glm.hpp>

namespace jeti {
namespace control {
class Material;
} // namespace control
class Mesh;
}

class BaseBackGroundEffect
{
public:
    BaseBackGroundEffect();
    ~BaseBackGroundEffect();

    void validateResources() const;
    void setTextureOb(jeti::control::Material* textureOb, const glm::vec3& scale_factor = glm::vec3(1.0, 1.0, 1.0));

    void setCenter(const glm::vec3& center)     { m_center = center; }
    void setSize(const glm::vec3& size)         { m_size = size; }

    void setAngle(float angle)              { m_angle = angle; }
    void setDeltaAngle(float delta_angle)   { m_deltaAngle = delta_angle; }

    const glm::vec3& center() const { return m_center; }
    const jeti::control::Material& textureOb() const { return *m_textureOb; }

    const glm::vec4& color() const { return m_color; }

    const jeti::Mesh& mesh() const { return *m_mesh; }

    const glm::mat4& actualModelMatrix();

protected:
    unsigned long int id;

    static unsigned long int counter;

    jeti::control::Material* m_textureOb = nullptr;
    std::string m_textureObPath;

    glm::vec3 m_center;
    glm::vec3 m_size;
    glm::vec4 m_color;

    float m_angle;
    float m_deltaAngle;

    glm::mat4 m_Mm;
    glm::mat4 m_Tm;
    glm::mat4 m_Rm;
    glm::mat4 m_Sm;

    jeti::Mesh* m_mesh = nullptr;
};


