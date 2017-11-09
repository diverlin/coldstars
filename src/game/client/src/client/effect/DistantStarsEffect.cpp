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

#include "DistantStarsEffect.hpp"

#include <client/resources/Utils.hpp>

#include <meti/RandUtils.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Render.hpp>

#include <glm/gtx/transform.hpp>

namespace effect {

DistantStars::DistantStars(const std::vector<glm::vec3>& positions,
                           const std::vector<glm::vec4>& colors,
                           const std::vector<float>& sizes)
{
    assert((positions.size()==colors.size())&&(positions.size()==sizes.size()));
    for (unsigned int i=0; i<positions.size(); i++) {
        m_positions.push_back(positions[i]);
        m_colors.push_back(colors[i]);
        m_sizes.push_back(sizes[i]);
    }

    m_mesh = new jeti::Mesh();
    m_mesh->fillPointVertices(m_positions, m_colors, m_sizes);
}

DistantStars::~DistantStars()
{
    delete m_mesh;
    delete m_material;
}

void DistantStars::draw(const jeti::Render& render) const
{
    render.drawBlinkingParticles(*m_mesh, *m_material);
}

DistantStars* genDistantStars(int color_id)
{
    int distStar_num = meti::rand::gen_int(DISTANT_STAR_MIN, DISTANT_STAR_MAX);

    jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    assert(material);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (int i=0; i<distStar_num; i++) {
        //float z = -meti::rand::gen_int(799, 999);
        float z = meti::rand::gen_int(-1000, 1000);
        glm::vec3 position = meti::rand::gen_vec3xy(0, 3000);

        float min = 0.5f;
        float mid = 0.8f;
        glm::vec4 color(1.0f);
        int choice = meti::rand::gen_int(0,3);
        if (choice == 0) {
            color.r = meti::rand::gen_float(min, 1.0);
            color.g = meti::rand::gen_float(mid, 1.0);
            color.b = meti::rand::gen_float(mid, 1.0);
        }
        if (choice == 1) {
            color.r = meti::rand::gen_float(mid, 1.0);
            color.g = meti::rand::gen_float(min, 1.0);
            color.b = meti::rand::gen_float(mid, 1.0);
        }
        if (choice == 2) {
            color.r = meti::rand::gen_float(mid, 1.0);
            color.g = meti::rand::gen_float(mid, 1.0);
            color.b = meti::rand::gen_float(min, 1.0);
        }
        float size = meti::rand::gen_float(5.0, 10.0)*10;
        if (meti::rand::gen_int(15) == 1) {
            size = meti::rand::gen_float(13.0, 16.0f);
            color *= 1.2;
        }

        positions.push_back(position);
        colors.push_back(color);
        sizes.push_back(size);
    }

    DistantStars* ds = new DistantStars(positions, colors, sizes);
    ds->setMaterial(material);

    return ds;
}

} // namespace effect
