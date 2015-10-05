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

#include <meti/RandUtils.hpp>


SpaceStationBuilder::SpaceStationBuilder()
{}

SpaceStationBuilder::~SpaceStationBuilder() {}

SpaceStation* SpaceStationBuilder::createTemplate(INTLONGEST id) const
{           
    SpaceStation* spacestation = new SpaceStation(id);
    assert(spacestation);

    global::get().entitiesManager().RegisterEntity(spacestation);
    
    return spacestation;
}

SpaceStation* SpaceStationBuilder::create() const
{
    SpaceStation* spacestation = createTemplate();
    createInternals(spacestation);
    
    return spacestation;
}

void SpaceStationBuilder::createInternals(SpaceStation* spacestation) const
{
    //jeti::Mesh* mesh = nullptr;
    //jeti::TextureOb* texOb = nullptr;
    glm::vec3 size;

    if (meti::getRandInt(0, 1))
    {
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//        texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SPACESTATION_ID);
//        size = texOb->size();
    }
    else
    {    
//        mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPACESTATION_ID);
//        texOb = mesh->textureOb();
        float scale_comp = meti::getRandInt(ENTITY::SPACESTATION::SCALE_MIN, ENTITY::SPACESTATION::SCALE_MAX);
        size = glm::vec3(scale_comp, scale_comp, scale_comp);
    }
    
    int protection_rate = 50;
    //if (subtype_id == ENTITY::WARRIOR_ID)
    //{
    //protection_rate = 5;
    //}
    
    VehicleDescriptor data_korpus;
    data_korpus.space       = 2500 + meti::getRandInt(0, 1000);
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
    //data_life.dying_time = 10*texOb->GetMaterial().size_id;
    
    int size_threshold = 2; 
    //if ( (texOb->size_id < size_threshold) or (mesh != nullptr) )
    //data_korpus.draw_turrels = false; 
    //else
    //data_korpus.draw_turrels = true; 
    data_korpus.draw_turrels = true;
//    if (texOb->GetMaterial().size_id < size_threshold)
//        data_korpus.draw_turrels = false;


    
    spacestation->setSubSubTypeId(TYPE::ENTITY::SPACESTATION_MILITARY_ID);
    spacestation->SetKorpusData(data_korpus);
    spacestation->setLifeData(data_life);

    //alpitodorender spacestation->SetRenderData(mesh, texOb, size);
        
    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender spacestation->SetAnimationRotation(animation_rotation);

    
    spacestation->setMass(meti::getRandInt(ENTITY::SPACESTATION::MASS_MIN, ENTITY::SPACESTATION::MASS_MAX));
    
    spacestation->CreateDriveComplexTextureDependedStuff();
    spacestation->CreateProtectionComplexTextureDependedStuff();
    
    CreateItemSlots(spacestation);
                
    spacestation->BindLand(global::get().kosmoportBuilder().create());
}
