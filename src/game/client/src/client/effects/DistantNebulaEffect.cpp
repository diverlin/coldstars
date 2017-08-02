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

#include "DistantNebulaEffect.hpp"
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>

#include <client/resources/Utils.hpp>

#include <jeti/Render.hpp>
#include <jeti/Material.hpp>

#include <glm/gtx/transform.hpp>

namespace effect {


DistantNebulas::DistantNebulas(const std::vector<DistantNebula*>& nebulas)
{
    for (auto nebula: nebulas) {
        m_nebulas.push_back(nebula);
    }
}
DistantNebulas::~DistantNebulas() {
    for (auto nebula: m_nebulas) {
        delete nebula;
    }
    m_nebulas.clear();
}

void DistantNebulas::update(const glm::vec3& camera_pos) {
    for (auto nebula: m_nebulas) {
        nebula->update(camera_pos);
    }
}

void DistantNebulas::draw(const jeti::Render& render) const {
    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (auto nebula: m_nebulas) {
        nebula->draw(render);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
}



DistantNebula::DistantNebula(float paralaxFactor):
    m_paralaxFactor(paralaxFactor)
{}
   
DistantNebula::~DistantNebula()
{}     

void DistantNebula::update(const glm::vec3& camera_pos) {
    if (m_offset != camera_pos) {
        m_offset = camera_pos;
        jeti::view::BaseView::update();
        glm::mat4 trans = glm::translate(m_offset/m_paralaxFactor);
         _overrideModelMatrix(matrixTranslate()*trans*matrixScale());
    }
}

DistantNebulas* genDistantNebulas(int color_id)
{
    float num = 10;
    std::vector<DistantNebula*> nebulas;
    for (int i=0; i<num; ++i) {
        jeti::Mesh* mesh = utils::createMeshByDescriptorType(mesh::Type::PLANE);
        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::NEBULA_BACKGROUND);

        float angle = meti::getRandInt(0, 360);
        float delta_angle = 0.0;
        if(material->model()->is_rotated) {
            delta_angle = meti::getRandInt(8,12)*0.001 * meti::getRandSign();
        }

        float z = -meti::getRandInt(799, 999);

        glm::vec3 position = meti::getRandXYVec3f(400, 2000, z);

        float paralaxFactor = meti::getRandFloat(1.005, 1.02);
        DistantNebula* dn = new DistantNebula(paralaxFactor);

        dn->setOrientation(new ceti::control::Orientation(new ceti::model::Orientation()));
        dn->setMaterial(material);
        dn->setMesh(mesh);
        dn->setPosition(position);
        dn->setSize(meti::getRandFloat(20.f, 25.f)*material->size());
        //dn->SetAngle(angle);
        //dn->SetDeltaAngle(delta_angle);
        nebulas.push_back(dn);
    }

    DistantNebulas* dn = new DistantNebulas(nebulas);
    return dn;
}

} // namespace effect
