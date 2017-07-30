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

#include "DistantStarEffect.hpp"
//#include <common/constants.hpp>

#include <meti/RandUtils.hpp>

//#include <client/resources/TextureCollector.hpp>
#include <client/resources/Utils.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Render.hpp>

#include <glm/gtx/transform.hpp>

namespace effect {

DistantStars::DistantStars(const std::vector<glm::vec3>& positions,
                           const std::vector<glm::vec4>& colors,
                           const std::vector<float>& sizes,
                           float scale)
{
    //assert(positions.size()==colors.size()==sizes.size());
    for (unsigned int i=0; i<positions.size(); i++) {
        m_positions.push_back(positions[i]);
        m_colors.push_back(colors[i]);
        m_sizes.push_back(sizes[i]);
    }

    m_mesh = new jeti::Mesh();
    m_mesh->fillPointVertices(m_positions, m_colors, m_sizes);

    m_Mm = glm::scale(glm::vec3(scale));
}

DistantStars::~DistantStars()
{
    delete m_mesh;
}

void DistantStars::draw(const jeti::Render& render) const
{
    render.drawBlinkingParticles(*m_mesh, *m_material, m_Mm);
}

DistantStars* genDistantStars(int color_id)
{
    int distStar_num = meti::getRandInt(DISTANT_STAR_MIN, DISTANT_STAR_MAX);

    jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    assert(material);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (int i=0; i<distStar_num; i++) {
        float z = -meti::getRandInt(200, 499);
        glm::vec3 position = meti::getRandXYVec3f(0, 3000, z);

        float r = meti::getRandFloat(0.5, 1.0);
        float g = meti::getRandFloat(0.5, 1.0);
        float b = meti::getRandFloat(0.5, 1.0);
        
        positions.push_back(position);
        colors.push_back(glm::vec4(r, g, b, 1.0f));
        sizes.push_back(meti::getRandFloat(3.0, 10.0));
    }
            
    DistantStars* ds = new DistantStars(positions, colors, sizes);
    ds->setMaterial(material);
    
    return ds;
}

} // namespace effect
