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
#include <jeti/animation/ConstantRotation.hpp>

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

void DistantNebulas::update() {
    for (auto nebula: m_nebulas) {
        nebula->update();
    }
}

void DistantNebulas::draw(const jeti::Render& render) const {
    for (auto nebula: m_nebulas) {
        nebula->draw(render);
    }
}


DistantNebula::DistantNebula()
    :
      Base()
{
}
   
DistantNebula::~DistantNebula()
{}     

void DistantNebula::update() {
    _updateModelMatrix();
}




DistantNebulas* genDistantNebulas(int color_id)
{
    float num = meti::rand::gen_int(3, 5);
    float angle_base = 0.0;
    float angle_step = 360/num;
    std::vector<DistantNebula*> nebulas;
    for (int i=0; i<num; ++i) {
        angle_base += angle_step;

        jeti::Mesh* mesh = utils::createMeshByDescriptorType(mesh::Type::PLANE);
        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::NEBULA_BACKGROUND);

//        float angle = meti::getRandInt(0, 360);
//        float delta_angle = 0.0;
//        if(material->model()->is_rotated) {
//            delta_angle = meti::getRandInt(8,12)*0.001 * meti::getRandSign();
//        }

        float radius_base = 2000.f;
        float rate = 0.2f;
        float radius_delta = radius_base*meti::rand::gen_float(-rate, rate);
        float radius = radius_base + radius_delta;
        float angle_delta = angle_base*meti::rand::gen_float(-rate, rate);
        float angle = angle_base + angle_delta;
        glm::vec3 position = meti::xy_vec3(radius, angle);
        position.z = -meti::rand::gen_float(799.0f, 999.0f);

        DistantNebula* dn = new DistantNebula();

        dn->setMaterial(material);
        dn->setMesh(mesh);
        dn->setPosition(position);
        dn->setSize(2*meti::rand::gen_float(10.f, 15.f)*material->size());
        //dn->SetAngle(angle);
        //dn->SetDeltaAngle(delta_angle);
        nebulas.push_back(dn);

        if (material->model()->is_rotated) {
            float delta_angle = meti::rand::gen_sign() * meti::rand::gen_float(0.001f, 0.005f);
            jeti::animation::ConstantRotation* animation = new jeti::animation::ConstantRotation(meti::OZ, delta_angle);
            dn->setAnimationRotation(animation);
        }
    }

    DistantNebulas* dn = new DistantNebulas(nebulas);
    return dn;
}


//DistantNebulas* genDistantNebulas2(int color_id)
//{
//    float num = 3;
//    float angle_base = 0.0;
//    float angle_step = 360/num;
//    std::vector<DistantNebula*> nebulas;
//    for (int i=0; i<num; ++i) {
//        angle_base += angle_step;

//        jeti::Mesh* mesh = utils::createMeshByDescriptorType(mesh::Type::PLANE);
//        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::NEBULA_BACKGROUND);
//        glm::vec3 base_size = meti::getRandFloat(10.f, 15.f)*material->size();

//        float z = -meti::getRandInt(799, 999);

//        float radius_base = 500;
//        float rate = 0.2;
//        float radius_delta = radius_base*meti::getRandFloat(-rate, rate);
//        float radius = radius_base + radius_delta;
//        float angle_delta = angle_base*meti::getRandFloat(-rate, rate);
//        float angle = angle_base + angle_delta;
//        glm::vec3 position = meti::getXYVec3(radius, angle);

//        float paralaxFactor = meti::getRandFloat(1.005, 1.02);
//        for (int j=0; j<2; ++j) {
//            glm::vec3 size = base_size*paralaxFactor;
//            DistantNebula* dn = new DistantNebula(paralaxFactor);

//            dn->setOrientation(new ceti::control::Orientation(new ceti::model::Orientation()));
//            dn->setMaterial(material);
//            dn->setMesh(mesh);
//            dn->setPosition(position);
//            dn->setSize(size);
//            //dn->SetAngle(angle);
//            //dn->SetDeltaAngle(delta_angle);
//            nebulas.push_back(dn);
//        }
//    }

//    DistantNebulas* dn = new DistantNebulas(nebulas);
//    return dn;
//}

} // namespace effect
