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

#include <meti/VectorUtils.hpp>

#include <vector>

namespace jeti {

namespace control {
class Material;
} // namespace control

class Mesh;
class Render;

namespace view {

class Path
{
    const float INIT_BASE_SIZE = 20.0f;
    const int TURN_STEP = 150;
    const int STEP = TURN_STEP/10;

public:
    Path(control::Material*);
    ~Path();

    void update(const std::vector<glm::vec3>&);
    void update(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
//    void fillData(const std::vector<glm::vec3>&, int step, int point_size);
//    void fillData(control::Material*, int radius, int point_size);
//    void fillData(control::Material*, const glm::vec3&, const glm::vec3&, int step, int point_size);

    //        void Draw(const Renderer&, const glm::vec3&);
    void draw(const Render&) const;

private:
    bool m_debug = false;
    float m_pointSize = INIT_BASE_SIZE;
    Mesh* m_meshMove = nullptr;
    Mesh* m_meshTurn = nullptr;
    Mesh* m_meshDirections = nullptr;
    control::Material* m_material = nullptr;

    void __processPath(const std::vector<glm::vec3>&, Mesh*, const glm::vec4& color, int step, float size);
    void __processMove(const std::vector<glm::vec3>&);
    void __processTurn(const std::vector<glm::vec3>&);
    void __processDirections(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&);
};

} // namespace view
} // namespace jeti


