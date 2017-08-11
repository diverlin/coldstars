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

#include "PathVisual.hpp"

#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>
#include <jeti/Render.hpp>

#include <meti/VectorUtils.hpp>

#include <glm/gtx/transform.hpp>

namespace jeti {
namespace view {

Path::Path(control::Material* material)
    :
      m_pointSize(10.0f)
    , m_meshMove(new Mesh)
    , m_meshTurn(new Mesh)
    , m_material(material)
{
}


Path::~Path()
{
    delete m_meshMove;
    delete m_meshTurn;
}


void Path::update(const std::vector<glm::vec3>& positions)
{   
    __processMove(positions);
    __processTurn(positions);
}


void Path::__processMove(const std::vector<glm::vec3>& positions)
{
    int step = 10;

    __processPath(positions, m_meshMove, glm::vec4(0.8f, 0.8f, 1.0f, 0.5f), step, m_pointSize);
}


void Path::__processTurn(const std::vector<glm::vec3>& positions)
{
    int step = 100;
    float size = 1.5f*m_pointSize;

    __processPath(positions, m_meshTurn, glm::vec4(0.8f, 1.0f, 0.8f, 0.5f), step, size);
}

void Path::__processPath(const std::vector<glm::vec3>& positions, Mesh* mesh, const glm::vec4& color, int step, float size)
{
    std::vector<glm::vec3> points;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (int i=0; i<positions.size(); i+=step) {
        points.push_back(positions[i]);
        colors.push_back(color);
        sizes.push_back(size);
    }

    mesh->fillPointVertices(points, colors, sizes);
}

//void PathVisual::fillData(control::Material* material, int radius, int point_size)
//{
//    m_material = material;

//    std::vector<glm::vec3> points;
//    std::vector<glm::vec4> colors;
//    std::vector<float> sizes;

//    float da = glm::radians(4.0f);
//    for (float a=0.0f; a<=2*M_PI; a+=da) {
//        points.push_back(glm::vec3(radius * cos(a), radius * sin(a), 0.0f));
//        colors.push_back(glm::vec4(1.0f));
//        sizes.push_back(m_pointSize);
//    }

//    m_mesh->fillPointVertices(points, colors, sizes);
//}

//void PathVisual::fillData(control::Material* material, const glm::vec3& start_pos, const glm::vec3& target_pos, int step, int point_size)
//{
//    m_material = material;

//    std::vector<glm::vec3> points;
//    std::vector<glm::vec4> colors;
//    std::vector<float> sizes;

//    glm::vec3 point(start_pos);
//    glm::vec3 ll(target_pos - start_pos);
//    glm::vec3 vstep = glm::normalize(ll) *(float)step;
    
//    unsigned int num = glm::length(ll) / (float)step;
//    for (unsigned int i=0; i<num; i++) {
//        points.push_back(point);
//        colors.push_back(glm::vec4(1.0f));
//        sizes.push_back(m_pointSize);

//        point += vstep;
//    }

//    m_mesh->fillPointVertices(points, colors, sizes);
//}


//void PathVisual::Draw(const Renderer& renderer, const glm::vec3& offset)
//{
//    m_ModelMatrix = glm::translate(offset);
//    renderer.DrawParticles(*m_Mesh, *m_TextureOb, m_ModelMatrix);
//}

void Path::draw(const Render& render) const
{
    glm::mat4 MM = glm::scale(glm::vec3(1.0f));
    render.drawParticles(*m_meshMove, *m_material, MM);
    render.drawParticles(*m_meshTurn, *m_material, MM);
}

} // namespace view
} // namespace jeti
