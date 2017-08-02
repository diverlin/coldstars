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


DistantStars::DistantStars(const std::vector<DistantStarsLayer*>& layers)
{
    for (auto layer: layers) {
        m_layers.push_back(layer);
    }
}
DistantStars::~DistantStars() {
    for (auto layer: m_layers) {
        delete layer;
    }
    m_layers.clear();
}

void DistantStars::update(const glm::vec3& offset) {
    for (auto layer: m_layers) {
        layer->update(offset);
    }
}

void DistantStars::draw(const jeti::Render& render) const {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//    /glBlendFunc(GL_ONE, GL_ONE);
    for (auto layer: m_layers) {
        layer->draw(render);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
}


DistantStarsLayer::DistantStarsLayer(const std::vector<glm::vec3>& positions,
                           const std::vector<glm::vec4>& colors,
                           const std::vector<float>& sizes,
                           float paralaxFactor)
    :
      m_paralaxFactor(paralaxFactor)
{
    //assert(positions.size()==colors.size()==sizes.size());
    for (unsigned int i=0; i<positions.size(); i++) {
        m_positions.push_back(positions[i]);
        m_colors.push_back(colors[i]);
        m_sizes.push_back(sizes[i]);
    }

    m_mesh = new jeti::Mesh();
    m_mesh->fillPointVertices(m_positions, m_colors, m_sizes);
}

DistantStarsLayer::~DistantStarsLayer()
{
    delete m_mesh;
}

void DistantStarsLayer::update(const glm::vec3& camera_pos) {
    if (m_offset != camera_pos) {
        m_offset = camera_pos;
        m_Mm = glm::translate(m_offset/m_paralaxFactor);
    }
}

void DistantStarsLayer::draw(const jeti::Render& render) const
{
    render.drawBlinkingParticles(*m_mesh, *m_material, m_Mm);
}

DistantStars* genDistantStars(int color_id)
{
    std::vector<DistantStarsLayer*> layers;
    int iterations = 5;
    for (int i=0; i<iterations; ++i) {
        int distStar_num = meti::getRandInt(DISTANT_STAR_MIN/iterations, DISTANT_STAR_MAX/iterations);

        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
        assert(material);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec4> colors;
        std::vector<float> sizes;

        for (int i=0; i<distStar_num; i++) {
            float z = -meti::getRandInt(799, 999);
            glm::vec3 position = meti::getRandXYVec3f(0, 3000, z);

            float min = 0.5;
            float mid = 0.8;
            glm::vec4 color(1.0f);
            int choice = meti::getRandInt(0,3);
            if (choice == 0) {
                color.r = meti::getRandFloat(min, 1.0);
                color.g = meti::getRandFloat(mid, 1.0);
                color.b = meti::getRandFloat(mid, 1.0);
            }
            if (choice == 1) {
                color.r = meti::getRandFloat(mid, 1.0);
                color.g = meti::getRandFloat(min, 1.0);
                color.b = meti::getRandFloat(mid, 1.0);
            }
            if (choice == 2) {
                color.r = meti::getRandFloat(mid, 1.0);
                color.g = meti::getRandFloat(mid, 1.0);
                color.b = meti::getRandFloat(min, 1.0);
            }

            positions.push_back(position);
            colors.push_back(color);
            sizes.push_back(meti::getRandFloat(3.0, 10.0));
        }

        float paralaxFactor = meti::getRandFloat(1.005, 1.02);
        DistantStarsLayer* layer = new DistantStarsLayer(positions, colors, sizes, paralaxFactor);
        layer->setMaterial(material);

        layers.push_back(layer);
    }

    DistantStars* ds = new DistantStars(layers);
    return ds;
}

} // namespace effect
