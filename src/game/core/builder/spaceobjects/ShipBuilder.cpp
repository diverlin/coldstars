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
#include <builder/CommonBuilderHeaders.hpp>
#include <spaceobjects/Ship.hpp>

#include <descriptors/DescriptorManager.hpp>

ShipBuilder::ShipBuilder()
{}

ShipBuilder::~ShipBuilder()
{}

Ship* ShipBuilder::getNew()
{
    const auto& descr = global::get().descriptors().getRand(descriptor::Type::VEHICLE);
    return getNew(descr);
}

Ship* ShipBuilder::getNew(const descriptor::Base& descr)
{            
    Ship* ship = new Ship(global::get().idGenerator().nextId());
    assert(ship);
    global::get().entityManager().reg(ship);
    __createInternals(ship, descr);
    return ship;
}

Ship* ShipBuilder::getNew(const std::string& data)
{
    return getNew(descriptor::Base(data));
}

void ShipBuilder::__createInternals(Ship* ship, const descriptor::Base& descr)
{
    //jeti::Mesh* mesh = nullptr;
    //jeti::TextureOb* texOb = nullptr;
    glm::vec3 size;
    if (true) {
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//        texOb = TextureCollector::Instance().getTextureByDescriptor(TextureDescriptor());
//        assert(mesh);
//        assert(texOb);
//        float scale_comp = meti::getRandInt(40, 100);
//        size = glm::vec3(scale_comp, scale_comp, 1.0);
        //size = texOb->size();
    } else {
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPACESTATION_ID);
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

    ship->setSubSubTypeId((TYPE::ENTITY)descr.type());

    VehicleDescriptor vehicleDescriptor;
    vehicleDescriptor.id = descr.id();
    vehicleDescriptor.race_id = (TYPE::RACE)descr.race();
    vehicleDescriptor.type_id = (TYPE::ENTITY)descr.type();
    vehicleDescriptor.size_id = descr.size();

    vehicleDescriptor.space = descr.space();
    vehicleDescriptor.armor = descr.armor();
    vehicleDescriptor.protection = descr.protection();
    vehicleDescriptor.temperature = descr.temperature();
    vehicleDescriptor.price = descr.price();

    vehicleDescriptor.draw_turrels = descr.drawTurrels();

    vehicleDescriptor.slot_bak_num = descr.bakSlotNum();
    vehicleDescriptor.slot_drive_num = descr.driveSlotNum();
    vehicleDescriptor.slot_droid_num = descr.droidSlotNum();
#ifdef USE_EXTRA_EQUIPMENT
    vehicleDescriptor.slot_energizer_num = descr.energizerSlotNum();
    vehicleDescriptor.slot_freezer_num = descr.freezerSlotNum();
#endif // USE_EXTRA_EQUIPMENT
    vehicleDescriptor.slot_grapple_num = descr.grappleSlotNum();
    vehicleDescriptor.slot_protector_num = descr.protectorSlotNum();
    vehicleDescriptor.slot_radar_num = descr.radarSlotNum();
    vehicleDescriptor.slot_scaner_num = descr.scanerSlotNum();
    vehicleDescriptor.slot_weapon_num = descr.weaponSlotNum();
    vehicleDescriptor.slot_artefact_num = descr.artefactSlotNum();
    vehicleDescriptor.slot_otsec_num = descr.cargoSlotNum();

    ship->setKorpusData(vehicleDescriptor);

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
    data_life.armor      = descr.armor() * 0.1;
    data_life.dying_time = ship->collisionRadius() * 0.1;
    ship->setLifeData(data_life);
    
    ship->CreateDriveComplexTextureDependedStuff();
    ship->CreateProtectionComplexTextureDependedStuff();
     
    //AnimationConstantRotation* animation_program = new AnimationConstantRotation(glm::vec3(0.02f, 0.0f, 0.0f));
    //ship->SetRenderAnimation(animation_program);
                           
    _createItemSlots(ship);
}
