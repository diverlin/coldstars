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
#include "../CommonBuilderHeaders.hpp"
#include <spaceobjects/Ship.hpp>

#include <render/Mesh.hpp>

#include <struct/RaceInformationCollector.hpp>

#include <common/constants.hpp>


ShipBuilder& ShipBuilder::Instance()
{    
    static ShipBuilder instance;
    return instance;
}

ShipBuilder::~ShipBuilder() {}

Ship* ShipBuilder::GetNewShipTemplate(INTLONGEST id) const
{
    Ship* ship = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        ship = new Ship(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(ship);
    
    return ship;
}

Ship* ShipBuilder::GetNewShip(TYPE::RACE race_id, TYPE::ENTITY subsubtype_id, int size_id, int weapons_num) const
{
    Ship* ship = GetNewShipTemplate();
    CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);     
    
    return ship;
}

Ship* ShipBuilder::GetNewShip() const
{
    TYPE::RACE race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
    TYPE::ENTITY subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
    int size_id = getRandInt(1, 9);
    int weapons_num = size_id;
            
    Ship* ship = GetNewShipTemplate();
    CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);     
    
    return ship;
}

void ShipBuilder::CreateNewInternals(Ship* ship, TYPE::RACE race_id,  TYPE::ENTITY subsubtype_id, int size_id, int weapons_num) const
{
    Mesh* mesh = nullptr;
    TextureOb* texOb = nullptr;
    //if (getRandBool() == true)
    //{
        //texOb = TextureManager::Instance().GetRandomShipTexObWithFollowingAtrributes(race_id, subsubtype_id, size_id); 
   //}
   //else
   //{    
        mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPACESTATION_ID);
    //}

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (subsubtype_id)
    {
            case TYPE::ENTITY::WARRIOR_ID: { protection_rate = 2; break; }
            case TYPE::ENTITY::TRADER_ID:  { otsec_rate = 1.5; break; }
    }
    
    VehicleKorpusData data_korpus;
    data_korpus.space       = size_id*100 + getRandInt(0, 100);
    data_korpus.armor       = data_korpus.space;
    data_korpus.protection  = protection_rate*size_id/(SIZE_1_ID);
    data_korpus.temperature = 100;
    data_korpus.price       = getRandInt(200, 400)*size_id;

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
    data_korpus.slot_artefact_num = getRandInt(1, SLOT_ARTEFACT_TYPES.size());  
    data_korpus.slot_otsec_num    = getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;
    
    int size_threshold = 2; 
    data_korpus.draw_turrels = false;
    if (mesh == nullptr)
    {
        if (texOb->GetData().size_id > size_threshold)
        {
            data_korpus.draw_turrels = true; 
        }
    }

    ship->SetSubSubTypeId(subsubtype_id);
    ship->SetKorpusData(data_korpus);
    if (mesh != nullptr)
    {
        float scale_comp = getRandInt(ENTITY::SHIP::SCALE_MIN, ENTITY::SHIP::SCALE_MAX);
        glm::vec3 scale(scale_comp, scale_comp, scale_comp);
        
        //float step = getRandInt(10, 20)*0.01;
        //glm::vec3 step3(step, 0.0f, 0.0f);
        //float threshold = 10;
        //AnimationWiggleAxisX* animation_program = new AnimationWiggleAxisX(step3, threshold);
        //ship->SetRenderAnimation(animation_program);
        
        float delta_angle = 0.001*getRandInt(20, 60);
        AnimationConstantRotation* animation_rotation = new AnimationConstantRotation(delta_angle);
        ship->SetAnimationRotation(animation_rotation);
        
        ship->SetDirectionOrigin(glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
        ship->SetDirection(glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
        //ship->SetOrientation(glm::normalize(glm::vec3()));    

        ship->BindData3D(mesh, mesh->GetTextureOb(), scale);
    }
    else
    {
        ship->BindData2D(texOb);    
    }

    LifeData data_life;
    data_life.armor      = data_korpus.armor * 0.1;
    data_life.dying_time = ship->GetCollisionRadius() * 0.1;
    ship->SetLifeData(data_life);
    
    ship->CreateDriveComplexTextureDependedStuff();
    ship->CreateProtectionComplexTextureDependedStuff();
     
    //AnimationConstantRotation* animation_program = new AnimationConstantRotation(glm::vec3(0.02f, 0.0f, 0.0f));
    //ship->SetRenderAnimation(animation_program);
                           
    CreateItemSlots(ship);
}
