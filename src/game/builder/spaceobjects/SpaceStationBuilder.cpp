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


#include <builder/spaceobjects/SpaceStationBuilder.hpp>
#include <builder/dock/KosmoportBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <spaceobjects/SpaceStation.hpp>

#include <dock/Kosmoport.hpp>

#include <render/Mesh.hpp>


SpaceStationBuilder& SpaceStationBuilder::Instance()
{    
    static SpaceStationBuilder instance;
    return instance;
}    

SpaceStationBuilder::~SpaceStationBuilder() {}

SpaceStation* SpaceStationBuilder::GetNewSpaceStationTemplate(INTLONGEST id) const
{
    SpaceStation* spacestation = nullptr;
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }
            
    try 
    { 
        spacestation = new SpaceStation(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(spacestation);
    
    return spacestation;
}

SpaceStation* SpaceStationBuilder::GetNewSpaceStation() const
{
    SpaceStation* spacestation = GetNewSpaceStationTemplate();
    CreateNewInternals(spacestation);
    
    return spacestation;
}

void SpaceStationBuilder::CreateNewInternals(SpaceStation* spacestation) const
{
    Mesh* mesh = nullptr;
    TextureOb* texOb = nullptr;
    if (getRandInt(0, 1))
    {
        texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::SPACESTATION_ID); 
    }
    else
    {    
        mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPACESTATION_ID);
        texOb = mesh->GetTextureOb(); 
    }
    
    int protection_rate = 50;
    //if (subtype_id == ENTITY::WARRIOR_ID)
    //{
    //protection_rate = 5;
    //}
    
    VehicleKorpusData data_korpus;
    data_korpus.space       = 2500 + getRandInt(0, 1000);
    data_korpus.armor       = data_korpus.space;
    data_korpus.protection  = protection_rate;
    data_korpus.temperature = 100;
    data_korpus.price       = 10000000;
    
    data_korpus.slot_bak_num       = 1;
    data_korpus.slot_drive_num     = 1;
    data_korpus.slot_droid_num     = 1;
    data_korpus.slot_energizer_num = 1;
    data_korpus.slot_grapple_num   = 0;
    data_korpus.slot_protector_num = 1;
    data_korpus.slot_radar_num     = 1;
    data_korpus.slot_scaner_num    = 1;
    data_korpus.slot_freezer_num   = 0;
    data_korpus.slot_weapon_num    = 7; 
    data_korpus.slot_artefact_num  = 0;  
    data_korpus.slot_otsec_num     = 10;
    
    LifeData data_life;
    data_life.armor      = data_korpus.armor;
    data_life.dying_time = 10*texOb->size_id;
    
    int size_threshold = 2; 
    //if ( (texOb->size_id < size_threshold) or (mesh != nullptr) )
    //data_korpus.draw_turrels = false; 
    //else
    //data_korpus.draw_turrels = true; 
    
    if (texOb->size_id < size_threshold)
        data_korpus.draw_turrels = false; 
    else
        data_korpus.draw_turrels = true; 
    
    spacestation->SetSubSubTypeId(TYPE::ENTITY::SPACESTATION_MILITARY_ID);
    spacestation->SetKorpusData(data_korpus);
    spacestation->SetLifeData(data_life);

    if (mesh != nullptr)
    {
        float scale_comp = getRandInt(ENTITY::SPACESTATION::SCALE_MIN, ENTITY::SPACESTATION::SCALE_MAX);
        glm::vec3 scale(scale_comp, scale_comp, scale_comp);
        spacestation->BindData3D(mesh, mesh->GetTextureOb(), scale);
        
        spacestation->SetOrientation(glm::normalize(glm::vec3(1.0f)));
        
        float delta_angle = 0.0001*getRandInt(20, 60);
        AnimationConstantRotation* animation_rotation = new AnimationConstantRotation(delta_angle);
        spacestation->SetAnimationRotation(animation_rotation);
    }
    else
    {
        spacestation->BindData2D(texOb);            
    }
    
    spacestation->SetMass(getRandInt(ENTITY::SPACESTATION::MASS_MIN, ENTITY::SPACESTATION::MASS_MAX));
    
    spacestation->CreateDriveComplexTextureDependedStuff();
    spacestation->CreateProtectionComplexTextureDependedStuff();
    
    CreateItemSlots(spacestation);
                
    spacestation->BindLand(KosmoportBuilder::Instance().GetNewKosmoport());
}
