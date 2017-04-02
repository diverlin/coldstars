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
#include <core/model/spaceobject/Satellite.hpp>
#include <core/spaceobject/Satellite.hpp>
#include <core/descriptor/spaceobject/Satellite.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

control::Satellite*
Satellite::__genTemplate(descriptor::Satellite* descr)
{
    model::Satellite* model = new model::Satellite(descr->id());
    assert(model);

    control::Satellite* satellite = new control::Satellite(descr, model);
    assert(satellite);

    EntityManager::get().reg(satellite);
    
    return satellite;
}

control::Satellite*
Satellite::gen(descriptor::Satellite* descr)
{
    control::Satellite* satellite = __genTemplate(descr);
    __createInternals(satellite, descr);
    return satellite;
}

control::Satellite*
Satellite::gen()
{
    descriptor::Satellite* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::SATELLITE)) {
        descr = descriptor::genSatellite();
    } else {
        descr = descriptor::Manager::get().randSatellite();
    }
    assert(descr);
    return gen(descr);
}

void Satellite::__createInternals(control::Satellite* satellite, descriptor::Satellite* descr)
{
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SATELLITE);

//    int protection_rate = 1;
//    //if (subtype_id == ENTITY::WARRIOR)
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
