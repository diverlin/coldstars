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

class Render;

namespace control {
class Material;
} // namespace control

} // namespace jeti

namespace view {
namespace effect {

class Shield
{  
public:
    Shield();
    ~Shield();

    void setMaterial(jeti::control::Material* material) { m_material = material; }

    void update();
    void draw(const glm::mat4&, const jeti::Render&) const;

private:
    glm::vec4 m_color;
    glm::mat4 m_scaleMatrix;

    float m_alphaInit = 0.05;
    float m_deltaAlpha = 0.01;

    jeti::control::Material* m_material = nullptr;
};

} // namespace effect
} // namespace view

