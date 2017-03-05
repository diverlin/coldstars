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


#include "ShipBuilder.hpp"

#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/model/spaceobject/Ship.hpp>
#include <core/descriptor/DescriptorManager.hpp>

namespace builder {

model::Ship*
Ship::getNew(bool full_equiped)
{
    const auto& descr = core::global::get().descriptors().ship().random();
    model::Ship* ship =  getNew(descr);
    if (full_equiped) {
        assert(false);
        //BaseVehicleBuilder::equip(ship);
    }
    return ship;
}

model::Ship*
Ship::getNew(descriptor::Vehicle* descriptor)
{            
//    descriptor::Vehicle descriptor(descr->data());
//    int_t id = NONE;
//    if (descr->type() == (int_t)descriptor::Type::DESCRIPTOR) {
//        descriptor = core::global::get().descriptors().get(descr->descriptor());
//        id = descr->objId();
//    }

    model::Ship* ship = __getNewTemplate(/*id*/);
    __createInternals(ship, descriptor);
    return ship;
}

//model::Ship*
//Ship::getNew(const std::string& data)
//{
//    return getNew(descriptor::Vehicle(data));
//}

model::Ship*
Ship::__getNewTemplate()
{
    model::Ship* ship = new model::Ship;
    core::global::get().entityManager().reg(ship);
    return ship;
}

void
Ship::__createInternals(model::Ship* ship, descriptor::Vehicle* descr)
{
//    assert(false);
    //assert(descr->type() == (int)descriptor::Type::VEHICLE);
    //jeti::Mesh* mesh = nullptr;
    //jeti::control::TextureOb* texOb = nullptr;
    glm::vec3 size;
    if (true) {
//        mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//        texOb = TextureCollector::Instance().getTextureByDescriptor(TextureDescriptor());
//        assert(mesh);
//        assert(texOb);
//        float scale_comp = meti::getRandInt(40, 100);
//        size = glm::vec3(scale_comp, scale_comp, 1.0);
        //size = texOb->size();
    } else {
//        mesh = MeshCollector::Instance().getMesh(mesh::type::SPACESTATION);
//        texOb = mesh->textureOb();
//        assert(mesh);
//        assert(texOb);
//        float scale_comp = meti::getRandInt(40, 100);
//        size = glm::vec3(scale_comp, scale_comp, scale_comp);
    }
// BROKEN
//    if (mesh == nullptr) {
//        if (texOb->GetMaterial().size_id > size_threshold) {
//            data_korpus.draw_turrels = true;
//        }
//    }

//    assert(false);
    //ship->setSubSubTypeId((entity::Type)descr->type());

//    float scale_comp = meti::getRandInt(ENTITY::SHIP::SCALE_MIN, ENTITY::SHIP::SCALE_MAX);
//    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    
    //float step = getRandInt(10, 20)*0.01;
    //glm::vec3 step3(step, 0.0f, 0.0f);
    //float threshold = 10;
    //AnimationWiggleAxisX* animation_program = new AnimationWiggleAxisX(step3, threshold);
    //ship->SetRenderAnimation(animation_program);
    
    //float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender ship->SetAnimationRotation(animation_rotation);

    //alpitodorender ship->SetRenderData(mesh, texOb, scale);

    LifeData data_life;
    data_life.armor      = descr->armor();
//    assert(false);
//    data_life.dying_time = ship->collisionRadius() * 0.1;
    ship->setLifeData(data_life);
    
//    assert(false);
//    ship->CreateDriveComplexTextureDependedStuff();
//    ship->CreateProtectionComplexTextureDependedStuff();
     
    //AnimationConstantRotation* animation_program = new AnimationConstantRotation(glm::vec3(0.02f, 0.0f, 0.0f));
    //ship->SetRenderAnimation(animation_program);

//    _createSlots(ship);
}

} // namespace builder
