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

class PathVisual
{
    public:
        PathVisual();
        ~PathVisual();

        void FillData(control::Material*, const std::vector<glm::vec3>&, int step, int point_size);
        void FillData(const std::vector<glm::vec3>&, int step, int point_size);
        void FillData(control::Material*, int radius, int point_size);
        void FillData(control::Material*, const glm::vec3&, const glm::vec3&, int step, int point_size);
        
//        void Draw(const Renderer&, const glm::vec3&);
//        void Draw(const Renderer&) const;

    private:
        Mesh* m_Mesh;
        control::Material* m_TextureOb;
        glm::mat4 m_ModelMatrix;

        float m_PointSize;
};

}


