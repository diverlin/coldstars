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


#include <core/builder/spaceobject/SpaceStationBuilder.hpp>
#include <core/builder/dock/KosmoportBuilder.hpp>
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/model/spaceobject/SpaceStation.hpp>
#include <core/descriptor/spaceobject/SpaceStation.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/dock/Kosmoport.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

model::SpaceStation*
SpaceStation::__genTemplate(int_t descriptor_id)
{           
    model::SpaceStation* spacestation = new model::SpaceStation(descriptor_id);
    assert(spacestation);

    core::global::get().entityManager().reg(spacestation);
    
    return spacestation;
}

model::SpaceStation*
SpaceStation::gen(descriptor::SpaceStation* descr)
{
//    descriptor::Vehicle descriptor(descr->data());
//    int_t id = NONE;
//    if (descr->type() == (int_t)descriptor::Type::DESCRIPTOR) {
//        descriptor = descriptor::Manager::get().get(descr->descriptor());
//        id = descr->objId();
//    }

    model::SpaceStation* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}

model::SpaceStation*
SpaceStation::gen()
{
    descriptor::SpaceStation* descr = descriptor::Manager::get().randSpaceStation();
    model::SpaceStation* spacestation = __genTemplate(descr->id());
    __createInternals(spacestation, descr);
    
    return spacestation;
}

void
SpaceStation::__createInternals(model::SpaceStation* model, descriptor::SpaceStation* descr)
{
    assert(false);

//    //jeti::Mesh* mesh = nullptr;
//    //jeti::control::TextureOb* texOb = nullptr;
//    glm::vec3 size;

//    if (meti::getRandInt(1))
//    {
//        //        mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//        //        texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SPACESTATION);
//        //        size = texOb->size();
//    }
//    else
//    {
//        //        mesh = MeshCollector::Instance().getMesh(mesh::type::SPACESTATION);
//        //        texOb = mesh->textureOb();
//        float scale_comp = meti::getRandInt(ENTITY::SPACESTATION::SCALE_MIN, ENTITY::SPACESTATION::SCALE_MAX);
//        size = glm::vec3(scale_comp, scale_comp, scale_comp);
//    }
    
//    int protection_rate = 50;
//    //if (subtype_id == ENTITY::WARRIOR)
//    //{
//    //protection_rate = 5;
//    //}
    
//    descriptor::Vehicle data_korpus;
//    data_korpus.setSpace(2500 + meti::getRandInt(1000));
//    data_korpus.setArmor(data_korpus.space());
//    data_korpus.setProtection(protection_rate);
//#ifdef USE_EXTRA_EQUIPMENT
//    data_korpus.setTemperature(100);
//#endif // USE_EXTRA_EQUIPMENT
//    data_korpus.setPrice(10000000);
    
//    data_korpus.setBakSlotNum(1);
//    data_korpus.setDriveSlotNum(1);
//    data_korpus.setDroidSlotNum(1);
//#ifdef USE_EXTRA_EQUIPMENT
//    data_korpus.setEnergizerSlotNum(0);
//    data_korpus.setFreezerSlotNum(0);
//#endif // USE_EXTRA_EQUIPMENT
//    data_korpus.setGrappleSlotNum(0);
//    data_korpus.setProtectorSlotNum(1);
//    data_korpus.setRadarSlotNum(1);
//    data_korpus.setScanerSlotNum(1);
//    data_korpus.setWeaponSlotNum(7);
//    data_korpus.setArtefactSlotNum(0);
//    data_korpus.setCargoSlotNum(10);
    
//    LifeData data_life;
//    data_life.armor      = data_korpus.armor();
//    //data_life.dying_time = 10*texOb->GetMaterial().size_id;
    
//    int size_threshold = 2;
//    //if ( (texOb->size_id < size_threshold) or (mesh != nullptr) )
//    //data_korpus.draw_turrels = false;
//    //else
//    //data_korpus.draw_turrels = true;
//    data_korpus.setDrawTurrels(true);
//    //    if (texOb->GetMaterial().size_id < size_threshold)
//    //        data_korpus.draw_turrels = false;


//    assert(false);
//    //spacestation->setSubSubTypeId(entity::Type::SPACESTATION_MILITARY);
//    //spacestation->setKorpusData(data_korpus);
//    spacestation->setLifeData(data_life);

//    //alpitodorender spacestation->SetRenderData(mesh, texOb, size);

//    float delta_angle = 0.0001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender spacestation->SetAnimationRotation(animation_rotation);

    
//    spacestation->setMass(meti::getRandInt(ENTITY::SPACESTATION::MASS_MIN, ENTITY::SPACESTATION::MASS_MAX));
    
//    assert(false);
////    spacestation->CreateDriveComplexTextureDependedStuff();
////    spacestation->CreateProtectionComplexTextureDependedStuff();
    
////    _createSlots(spacestation);

////    spacestation->bindLand(core::global::get().kosmoportBuilder().create());
}

} // namespace builder
