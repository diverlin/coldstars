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
#include <core/builder/item/equipment/ALL>
#include <core/item/equipment/ALL>

#include <core/model/spaceobject/Ship.hpp>
#include <core/spaceobject/Ship.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/descriptor/spaceobject/Ship.hpp>

namespace core {

core::control::Ship*
ShipBuilder::gen(core::ShipDescr* descr)
{
    core::control::Ship* ship = __genTemplate(descr);
    __createInternals(ship, descr);
    return ship;
}

core::control::Ship*
ShipBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    core::ShipDescr* descr = core::shortcuts::descriptors()->ship(descriptor_id);
    core::control::Ship* ship = __genTemplate(descr, ob_id);
    __createInternals(ship, descr);
    return ship;
}

core::control::Ship*
ShipBuilder::gen()
{
    core::ShipDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::SHIP)) {
        descr = core::genShip();
    } else {
        descr = core::shortcuts::descriptors()->randShip();
    }
    assert(descr);
    return gen(descr);
}

core::control::Ship*
ShipBuilder::__genTemplate(core::ShipDescr* descr, int_t ob_id)
{
    model::ShipModel* model = new model::ShipModel(descr->id(), ob_id);
    assert(model);

    core::control::Ship* ship = new core::control::Ship(descr, model);
    assert(ship);

    return ship;
}


void
ShipBuilder::__createInternals(core::control::Ship* ship, core::ShipDescr* descr)
{
//    assert(false);
    //assert(descr->type() == (int)Type::VEHICLE);
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

    ship->model()->setArmor(descr->armor());

    // orientation
    ship->setSize(descr->size());

//    _createSlots(ship);
}

} // namespace core
