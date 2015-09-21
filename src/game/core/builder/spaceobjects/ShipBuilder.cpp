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

#include <common/RaceDescriptors.hpp>

#include <common/constants.hpp>
#include <math/rand.hpp>
#include <meti/RandUtils.hpp>


ShipBuilder::ShipBuilder()
{}

ShipBuilder::~ShipBuilder() {}

Ship* ShipBuilder::createTemplate(INTLONGEST id) const
{
    Ship* ship = nullptr;
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try {
        ship = new Ship(id);
    } catch(std::bad_alloc) {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }    
    global::get().entitiesManager().RegisterEntity(ship);
    
    return ship;
}

Ship* ShipBuilder::create(TYPE::RACE race_id, TYPE::ENTITY subsubtype_id, int size_id, int weapons_num) const
{
    Ship* ship = createTemplate();
    _CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);
    
    return ship;
}

Ship* ShipBuilder::create() const
{
    TYPE::RACE race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    TYPE::ENTITY subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;
            
    Ship* ship = createTemplate();
    _CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);
    
    return ship;
}

void ShipBuilder::_CreateNewInternals(Ship* ship, TYPE::RACE race_id, TYPE::ENTITY subsubtype_id, int size_id, int weapons_num) const
{
    //jeti::Mesh* mesh = nullptr;
    //jeti::TextureOb* texOb = nullptr;
    glm::vec3 size;
    if (true)
    {
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//        texOb = TextureCollector::Instance().getTextureByDescriptor(TextureDescriptor());
//        assert(mesh);
//        assert(texOb);
        float scale_comp = meti::getRandInt(40, 100);
        size = glm::vec3(scale_comp, scale_comp, 1.0);
        //size = texOb->size();
    }
    else
    {    
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPACESTATION_ID);
//        texOb = mesh->textureOb();
//        assert(mesh);
//        assert(texOb);
        float scale_comp = meti::getRandInt(40, 100);
        size = glm::vec3(scale_comp, scale_comp, scale_comp);
    }

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (subsubtype_id)
    {
        case TYPE::ENTITY::WARRIOR_ID: { protection_rate = 2; break; }
        case TYPE::ENTITY::TRADER_ID:  { otsec_rate = 1.5; break; }
    }
    
    VehicleKorpusData data_korpus;
    data_korpus.space       = size_id*100 + meti::getRandInt(0, 100);
    data_korpus.armor       = data_korpus.space;
    data_korpus.protection  = protection_rate*size_id/(SIZE_1_ID);
    data_korpus.temperature = 100;
    data_korpus.price       = meti::getRandInt(200, 400)*size_id;

    data_korpus.slot_bak_num       = 1;
    data_korpus.slot_drive_num     = 1;
    data_korpus.slot_droid_num     = 1;
    data_korpus.slot_energizer_num = 1;
    data_korpus.slot_grapple_num   = 1;
    data_korpus.slot_protector_num = 1;
    data_korpus.slot_radar_num     = 1;
    data_korpus.slot_scaner_num    = 1;
    data_korpus.slot_freezer_num   = 1;
    data_korpus.slot_weapon_num   = weapons_num;  
    data_korpus.slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
    data_korpus.slot_otsec_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;
    
    int size_threshold = 2; 
    data_korpus.draw_turrels = false;
//    if (mesh == nullptr)      // BROKEN
//    {
//        if (texOb->GetMaterial().size_id > size_threshold)
//        {
//            data_korpus.draw_turrels = true;
//        }
//    }

    ship->setSubSubTypeId(subsubtype_id);
    ship->SetKorpusData(data_korpus);


    float scale_comp = meti::getRandInt(ENTITY::SHIP::SCALE_MIN, ENTITY::SHIP::SCALE_MAX);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    
    //float step = getRandInt(10, 20)*0.01;
    //glm::vec3 step3(step, 0.0f, 0.0f);
    //float threshold = 10;
    //AnimationWiggleAxisX* animation_program = new AnimationWiggleAxisX(step3, threshold);
    //ship->SetRenderAnimation(animation_program);
    
    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender ship->SetAnimationRotation(animation_rotation);

    //alpitodorender ship->SetRenderData(mesh, texOb, scale);

    LifeData data_life;
    data_life.armor      = data_korpus.armor * 0.1;
    data_life.dying_time = ship->collisionRadius() * 0.1;
    ship->setLifeData(data_life);
    
    ship->CreateDriveComplexTextureDependedStuff();
    ship->CreateProtectionComplexTextureDependedStuff();
     
    //AnimationConstantRotation* animation_program = new AnimationConstantRotation(glm::vec3(0.02f, 0.0f, 0.0f));
    //ship->SetRenderAnimation(animation_program);
                           
    CreateItemSlots(ship);
}
