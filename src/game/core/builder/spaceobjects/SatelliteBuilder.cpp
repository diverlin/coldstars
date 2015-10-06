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

#include "SatelliteBuilder.hpp"
#include <builder/CommonBuilderHeaders.hpp>
#include <spaceobjects/Satellite.hpp>

#include <meti/RandUtils.hpp>


SatelliteBuilder::SatelliteBuilder()
{}

SatelliteBuilder::~SatelliteBuilder()
{}

Satellite* SatelliteBuilder::createTemplate(ID id) const
{
    Satellite* satellite = new Satellite(id);
    assert(satellite);

    global::get().entityManager().reg(satellite);
    
    return satellite;
}

Satellite* SatelliteBuilder::create() const
{
    Satellite* satellite = createTemplate();
    createInternals(satellite);
    
    return satellite;
}

void SatelliteBuilder::createInternals(Satellite* satellite) const
{
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SATELLITE_ID);

    int protection_rate = 1;
    //if (subtype_id == ENTITY::WARRIOR_ID)
    //{
        //protection_rate = 1;
    //}
    
    VehicleDescriptor data_korpus;
    data_korpus.space       = 60 + meti::getRandInt(0, 20);
    data_korpus.armor       = 10*data_korpus.space;
    data_korpus.protection  = 2*protection_rate;
    data_korpus.temperature = 100;
    data_korpus.price       = 1000;

    data_korpus.slot_bak_num       = 0;
    data_korpus.slot_drive_num     = 0;
    data_korpus.slot_droid_num     = 1;
    data_korpus.slot_energizer_num = 1;
    data_korpus.slot_grapple_num   = 0;
    data_korpus.slot_protector_num = 1;
    data_korpus.slot_radar_num     = 1;
    data_korpus.slot_scaner_num    = 0;
    data_korpus.slot_freezer_num   = 0;
    data_korpus.slot_weapon_num   = 2; 
     data_korpus.slot_artefact_num = 0;  
    data_korpus.slot_otsec_num    = 1;
    
    LifeData data_life;
    data_life.armor      = data_korpus.armor;
    //data_life.dying_time = 10*texOb->GetMaterial().size_id;
    
    //int size_threshold = 2; 
    data_korpus.draw_turrels = true;       
 
    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender satellite->SetAnimationRotation(animation_rotation);
    
    satellite->SetKorpusData(data_korpus);
    satellite->setLifeData(data_life);
    //alpitodorender satellite->SetRenderData(mesh, texOb, texOb->size());

    satellite->CreateDriveComplexTextureDependedStuff();
    satellite->CreateProtectionComplexTextureDependedStuff();
        
    CreateItemSlots(satellite);
}
