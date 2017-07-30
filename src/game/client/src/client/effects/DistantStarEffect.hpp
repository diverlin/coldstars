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

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace jeti {
class Render;
class Mesh;
namespace control {
class Material;
} // namespace control
} // namespace jeti

const int DISTANT_STAR_MIN = 500;
const int DISTANT_STAR_MAX = 1000;

namespace effect {

class DistantStars
{
public:
    DistantStars(const std::vector<glm::vec3>&,
                      const std::vector<glm::vec4>&,
                      const std::vector<float>&,
                      float scale = 1.0f);
    ~DistantStars();

    void setMaterial(jeti::control::Material* material) { m_material = material; }

    void draw(const jeti::Render&) const;

private:
    jeti::control::Material* m_material = nullptr;
    jeti::Mesh* m_mesh = nullptr;

    glm::mat4 m_Mm;
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<float> m_sizes;
}; 

DistantStars* genDistantStars(int color_id = NONE);

} // namespace effect
