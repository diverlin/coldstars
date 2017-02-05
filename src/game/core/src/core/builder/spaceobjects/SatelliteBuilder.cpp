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
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/spaceobjects/Satellite.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

Satellite::Satellite()
{}

Satellite::~Satellite()
{}

model::Satellite*
Satellite::__createTemplate()
{
    model::Satellite* model = new model::Satellite;
    assert(model);

    core::global::get().entityManager().reg(model);
    
    return model;
}

model::Satellite*
Satellite::getNew()
{
    model::Satellite* satellite = __createTemplate();
    __createInternals(satellite);
    
    return satellite;
}

void Satellite::__createInternals(model::Satellite* model)
{
    assert(false);
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE_ID);
//    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SATELLITE_ID);

//    int protection_rate = 1;
//    //if (subtype_id == ENTITY::WARRIOR_ID)
//    //{
//    //protection_rate = 1;
//    //}
    
//    descriptor::Vehicle data_korpus;
//    data_korpus.setSpace(60 + meti::getRandInt(20));
//    data_korpus.setArmor(10*data_korpus.space());
//    data_korpus.setProtection(2*protection_rate);
//#ifdef USE_EXTRA_EQUIPMENT
//    data_korpus.setTemperature(100);
//#endif // USE_EXTRA_EQUIPMENT
//    data_korpus.setPrice(1000);

//    data_korpus.setBakSlotNum(0);
//    data_korpus.setDriveSlotNum(0);
//    data_korpus.setDroidSlotNum(1);
//#ifdef USE_EXTRA_EQUIPMENT
//    data_korpus.setEnergizerSlotNum(1);
//    data_korpus.setFreezerSlotNum(0);
//#endif // USE_EXTRA_EQUIPMENT
//    data_korpus.setGrappleSlotNum(0);
//    data_korpus.setProtectorSlotNum(1);
//    data_korpus.setRadarSlotNum(1);
//    data_korpus.setScanerSlotNum(0);
//    data_korpus.setWeaponSlotNum(2);
//    data_korpus.setArtefactSlotNum(0);
//    data_korpus.setCargoSlotNum(1);
    
//    LifeData data_life;
//    data_life.armor      = data_korpus.armor();
//    //data_life.dying_time = 10*texOb->GetMaterial().size_id;
    
//    //int size_threshold = 2;
//    data_korpus.setDrawTurrels(true);

//    float delta_angle = 0.0001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender satellite->SetAnimationRotation(animation_rotation);
    
//    assert(false);
//    //model->setKorpusData(data_korpus);
//    model->setLifeData(data_life);
//    //alpitodorender satellite->SetRenderData(mesh, texOb, texOb->size());

//    assert(false);
////    satellite->CreateDriveComplexTextureDependedStuff();
////    satellite->CreateProtectionComplexTextureDependedStuff();
////    _createSlots(satellite);
}

} // namespace builder
