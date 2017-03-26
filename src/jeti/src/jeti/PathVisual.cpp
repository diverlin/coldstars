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

#include <Mesh.hpp>
#include <Material.hpp>

#include <meti/VectorUtils.hpp>
#include <glm/gtx/transform.hpp>

namespace jeti {

PathVisual::PathVisual()
:
m_TextureOb(nullptr)  
{
    m_Mesh = new Mesh();
    //m_TextureOb = GuiTextureObCollector::Instance().dot_green;

    m_PointSize = 10.0f;
}

PathVisual::~PathVisual() 
{
    delete m_Mesh;
}

void PathVisual::FillData(control::Material* textureOb, const std::vector<glm::vec3>& vec, int step, int point_size)
{  
    m_TextureOb = textureOb; 

    FillData(vec, step, point_size);
}

void PathVisual::FillData(const std::vector<glm::vec3>& vec, int step, int point_size)
{   
    std::vector<glm::vec3> points;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (unsigned int i=0; i<vec.size(); i+=step)
    {
        points.push_back(vec[i]);
        colors.push_back(glm::vec4(1.0f));
        sizes.push_back(m_PointSize);
    }

    m_Mesh->fillPointVertices(points, colors, sizes);
}

void PathVisual::FillData(control::Material* textureOb, int radius, int point_size)
{
    m_TextureOb = textureOb; 

    std::vector<glm::vec3> points;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    float da = glm::radians(4.0f);
    for (float a=0.0f; a<=2*M_PI; a+=da)
    {
        points.push_back(glm::vec3(radius * cos(a), radius * sin(a), 0.0f));
        colors.push_back(glm::vec4(1.0f));
        sizes.push_back(m_PointSize);
    }

    m_Mesh->fillPointVertices(points, colors, sizes);
}

void PathVisual::FillData(control::Material* textureOb, const glm::vec3& start_pos, const glm::vec3& target_pos, int step, int point_size)
{
    m_TextureOb = textureOb; 

    std::vector<glm::vec3> points;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    glm::vec3 point(start_pos);
    glm::vec3 ll(target_pos - start_pos);                
    glm::vec3 vstep = glm::normalize(ll) *(float)step;
    
    unsigned int num = glm::length(ll) / (float)step;
    for (unsigned int i=0; i<num; i++)
    {
        points.push_back(point);
        colors.push_back(glm::vec4(1.0f));
        sizes.push_back(m_PointSize); 

        point += vstep;
    }

    m_Mesh->fillPointVertices(points, colors, sizes);
}


//void PathVisual::Draw(const Renderer& renderer, const glm::vec3& offset)
//{
//    m_ModelMatrix = glm::translate(offset);
//    renderer.DrawParticles(*m_Mesh, *m_TextureOb, m_ModelMatrix);
//}

//void PathVisual::Draw(const Renderer& renderer) const
//{
//    renderer.DrawParticles(*m_Mesh, *m_TextureOb, m_ModelMatrix);
//}

}
