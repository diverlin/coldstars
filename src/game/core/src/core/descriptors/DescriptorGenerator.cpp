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


#include "DescriptorGenerator.hpp"
#include <core/descriptors/Base.hpp>
#include <core/descriptors/GalaxyDescriptor.hpp>
#include <core/descriptors/SectorDescriptor.hpp>
#include <core/descriptors/StarsystemDescriptor.hpp>
#include <core/descriptors/StarDescriptor.hpp>
#include <core/descriptors/PlanetDescriptor.hpp>
#include <core/descriptors/AsteroidDescriptor.hpp>
#include <core/descriptors/RaceDescriptors.hpp>
#include <core/descriptors/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/common/constants.hpp>
#include <core/types/MeshTypes.hpp>
#include <core/types/TextureTypes.hpp>
#include <core/item/BaseItem.hpp>

#include <meti/RandUtils.hpp>

#include <ceti/IdGenerator.hpp>


namespace descriptor {

namespace {

glm::vec3 randDirection() {
    return glm::normalize(glm::vec3(meti::getRandFloat(0.1, 0.3), 1.0, -1.0));
}

} // namespace

/* world */
descriptor::Galaxy
getNewGalaxy(const std::vector<int_t>& sectors) {
    descriptor::Galaxy descriptor;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descriptor.sectors.push_back(meti::getRand(sectors));
    }
    return descriptor;
}

descriptor::Sector
getNewSector(const std::vector<int_t>& starsystems) {
    descriptor::Sector descriptor;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descriptor.starsystems.push_back(meti::getRand(starsystems));
    }
    return descriptor;
}

descriptor::Starsystem
getNewStarsystem(int race)
{
    descriptor::Starsystem descriptor;
    if (race == -1) {
        race = int(type::race::R0_ID);
    }

//    descriptor::Base descriptor(descriptor::Type::STARSYSTEM);
//    descriptor.add(descriptor::Key::RACE, race);

    return descriptor;
}

/* spaceobjects */

namespace {

int_t meshDescriptorIdFromType(const type::mesh& type) {
    auto& collector = core::global::get().descriptors().mesh();
    descriptor::Mesh* descriptor = collector.random(int_t(type));
    assert(descriptor->id() != -1);
    return descriptor->id();
}

int_t textureDescriptorIdFromType(const type::texture& type) {
    auto& collector = core::global::get().descriptors().material();
    descriptor::Material* descriptor = collector.random(int_t(type));
    assert(descriptor->id() != -1);
    return descriptor->id();
}

} // namespace

descriptor::Star
getNewStar()
{
    descriptor::Star descr;
    descr.setArmor(10000000);

    int orbit_radius = meti::getRandInt(descriptor::Star::DISTANCE_MIN,
                                        descriptor::Star::DISTANCE_MAX);
    descr.setRadiusA(orbit_radius);
    descr.setRadiusB(orbit_radius);
    descr.setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Star::SPEED_MIN,
                                   descriptor::Star::SPEED_MAX) / float(orbit_radius);
    descr.setSpeed(speed);
    descr.setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Star::SCALE_MIN,
                                  descriptor::Star::SCALE_MAX);
    descr.setSize(meti::vec3(size));
    descr.setDirection(randDirection());

    descr.setTexture(textureDescriptorIdFromType(type::texture::STAR_ID));
    descr.setMesh(meshDescriptorIdFromType(type::mesh::SPHERE_ID));

    assert(descr.texture() != -1);
    assert(descr.mesh() != -1);

    return descr;
}

descriptor::Planet
getNewPlanet()
{
    descriptor::Planet descr;
    descr.setArmor(100000);

    int orbit_radius = meti::getRandInt(descriptor::Planet::DISTANCE_MIN,
                                        descriptor::Planet::DISTANCE_MAX);
    descr.setRadiusA(orbit_radius);
    descr.setRadiusB(orbit_radius);
    descr.setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Planet::SPEED_MIN,
                                   descriptor::Planet::SPEED_MAX) / float(orbit_radius);
    descr.setSpeed(speed);
    descr.setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Planet::SCALE_MIN,
                                  descriptor::Planet::SCALE_MAX);
    descr.setSize(meti::vec3(size));
    descr.setDirection(randDirection());
    descr.setTexture(textureDescriptorIdFromType(type::texture::PLANET_ID));
    descr.setMesh(meshDescriptorIdFromType(type::mesh::SPHERE_ID));

    assert(descr.texture() != -1);
    assert(descr.mesh() != -1);

    return descr;



    //model::Planet*
    //Planet::getNew(const descriptor::BaseOLD& descr)
    //{
    //    model::Planet* model = __createTemplate();

    //    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
    //    //jeti::control::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET_ID);

    //    int orbit_radius = 1000; // hack
    //    //model->setOrbitCenter(glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
    //    model->setRadiusA(orbit_radius);
    //    model->setRadiusB(orbit_radius);
    //    model->setOrbitPhi(0);
    //    model->setSpeed(meti::getRandInt(model::Planet::SPEED_MIN, model::Planet::SPEED_MAX) / float(orbit_radius));
    //    model->setClockwise(meti::getRandBool());

    //    LifeData data_life;
    //    data_life.armor = descr.armor();
    //    model->setLifeData(data_life);

    //    float scale_comp = meti::getRandInt(model::Planet::SCALE_MIN, model::Planet::SCALE_MAX);
    //    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);

    //    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //    //alpitodorender planet->SetAnimationRotation(animation_rotation);

    //    //if (getRandBool())
    //    {
    //        //jeti::control::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE_ID);
    //        //Atmosphere* atmosphere = new Atmosphere();
    //        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
    //        //alpitodorender planet->AddDecoration(atmosphere);
    //    }

    //   /*
    //   {
    //        Mesh* mesh_plane = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);

    //        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING_ID);
    //        Ring* ring = new Ring();
    //        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
    //        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
    //        ring->setDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
    //        planet->AddDecoration(ring);
    //    }
    //    */
    //    return model;
    //}

}

descriptor::Asteroid
getNewAsteroid()
{
    descriptor::Asteroid descr;
    descr.setArmor(meti::getRandInt(descriptor::Asteroid::ARMOR_MIN,
                                    descriptor::Asteroid::ARMOR_MAX));

    int orbit_radiusA = meti::getRandInt(descriptor::Asteroid::DISTANCE_MIN,
                                        descriptor::Asteroid::DISTANCE_MAX);
    int orbit_radiusB = meti::getRandInt(descriptor::Asteroid::DISTANCE_MIN,
                                        descriptor::Asteroid::DISTANCE_MAX);
    descr.setRadiusA(orbit_radiusA);
    descr.setRadiusB(orbit_radiusB);
    descr.setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Asteroid::SPEED_MIN,
                                   descriptor::Asteroid::SPEED_MAX) / float((orbit_radiusA+orbit_radiusB)/2.0);
    descr.setSpeed(speed);
    descr.setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Asteroid::SCALE_MIN,
                                  descriptor::Asteroid::SCALE_MAX);
    descr.setSize(meti::vec3(size));
    descr.setDirection(randDirection());
    descr.setTexture(textureDescriptorIdFromType(type::texture::ASTEROID_ID));
    descr.setMesh(meshDescriptorIdFromType(type::mesh::SPHERE_DEFORMED_ID));

    assert(descr.texture() != -1);
    assert(descr.mesh() != -1);

    return descr;
}

descriptor::BaseOLD
getNewContainer()
{
    descriptor::BaseOLD descriptor(descriptor::Type::CONTAINER);
    return descriptor;
}

//descriptor::BaseOLD
//getNewVehicleDescriptor()
//{
//    type::race race_id = (type::race)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
//    type::entity type_id = type::entity::WARRIOR_ID;
//    int size_id = meti::getRandInt(1, 9);
//    int weapons_num = size_id;

//    float protection_rate = 1;
//    float otsec_rate      = 1;
//    switch (type_id) {
//        case type::entity::WARRIOR_ID: { protection_rate = 2; break; }
//        case type::entity::TRADER_ID:  { otsec_rate = 1.5; break; }
//    }

//    int space       = size_id*100 + meti::getRandInt(100);
//    int armor       = space;
//    int protection  = protection_rate*meti::getRandInt(size_id);
//    int temperature = 100;
//    int price       = meti::getRandInt(200, 400)*size_id;

//    int slot_bak_num       = 1;
//    int slot_drive_num     = 1;
//    int slot_droid_num     = 1;
//#ifdef USE_EXTRA_EQUIPMENT
//    int slot_energizer_num = 1;
//    int slot_freezer_num   = 1;
//#endif
//    int slot_grapple_num   = 1;
//    int slot_protector_num = 1;
//    int slot_radar_num     = 1;
//    int slot_scaner_num    = 1;
//    int slot_weapon_num   = weapons_num;
//    int slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
//    int slot_otsec_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;


//    descriptor::BaseOLD descriptor(descriptor::Type::VEHICLE);
//    descriptor.add(descriptor::Key::RACE, (int)race_id);
//    descriptor.add(descriptor::Key::OBJ_TYPE, (int)type_id);
//    descriptor.add(descriptor::Key::SIZE, size_id);

//    descriptor.add(descriptor::Key::SPACE, space);
//    descriptor.add(descriptor::Key::ARMOR, armor);
//    descriptor.add(descriptor::Key::PROTECTION, protection);
//    descriptor.add(descriptor::Key::TEMPERATURE, temperature);
//    descriptor.add(descriptor::Key::PRICE, price);

//    descriptor.add(descriptor::Key::BAK_SLOT_NUM, slot_bak_num);
//    descriptor.add(descriptor::Key::DRIVE_SLOT_NUM, slot_drive_num);
//    descriptor.add(descriptor::Key::DROID_SLOT_NUM, slot_droid_num);
//#ifdef USE_EXTRA_EQUIPMENT
//    descriptor.add(descriptor::Key::ENERGIZER_SLOT_NUM, slot_energizer_num);
//    descriptor.add(descriptor::Key::FREEZER_SLOT_NUM, slot_freezer_num);
//#endif
//    descriptor.add(descriptor::Key::GRAPPLE_SLOT_NUM, slot_grapple_num);
//    descriptor.add(descriptor::Key::PROTECTOR_SLOT_NUM, slot_protector_num);
//    descriptor.add(descriptor::Key::RADAR_SLOT_NUM, slot_radar_num);
//    descriptor.add(descriptor::Key::SCANER_SLOT_NUM, slot_scaner_num);
//    descriptor.add(descriptor::Key::WEAPON_SLOT_NUM, slot_weapon_num);
//    descriptor.add(descriptor::Key::ARTEFACT_SLOT_NUM, slot_artefact_num);
//    descriptor.add(descriptor::Key::CARGO_SLOT_NUM, slot_otsec_num);

//    //int size_threshold = 2;
//    descriptor.add(descriptor::Key::DRAW_TURRELS, 0);

//    return descriptor;
//}



descriptor::Ship
getNewShip()
{
    type::race race_id = (type::race)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    type::entity type_id = type::entity::WARRIOR_ID;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case type::entity::WARRIOR_ID: { protection_rate = 2; break; }
        case type::entity::TRADER_ID:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::getRandInt(100);
    int armor       = space;
    int protection  = protection_rate*meti::getRandInt(size_id);
    int temperature = 100;
    int price       = meti::getRandInt(200, 400)*size_id;

    int slot_bak_num       = 1;
    int slot_drive_num     = 1;
    int slot_droid_num     = 1;
#ifdef USE_EXTRA_EQUIPMENT
    int slot_energizer_num = 1;
    int slot_freezer_num   = 1;
#endif
    int slot_grapple_num   = 1;
    int slot_protector_num = 1;
    int slot_radar_num     = 1;
    int slot_scaner_num    = 1;
    int slot_weapon_num   = weapons_num;
    int slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
    int slot_cargo_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;


    descriptor::Ship descriptor;
    descriptor.setRace(int_t(race_id));
    //descriptor.setType(int_t(type_id));
    descriptor.setSize(size_id);

    descriptor.setSpace(space);
    descriptor.setArmor(armor);
    descriptor.setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setPrice(price);

    descriptor.setBakSlotNum(slot_bak_num);
    descriptor.setDriveSlotNum(slot_drive_num);
    descriptor.setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setEnergizerSlotNum(slot_energizer_num);
    descriptor.setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setGrappleSlotNum(slot_grapple_num);
    descriptor.setProtectorSlotNum(slot_protector_num);
    descriptor.setRadarSlotNum(slot_radar_num);
    descriptor.setScanerSlotNum(slot_scaner_num);
    descriptor.setWeaponSlotNum(slot_weapon_num);
    descriptor.setArtefactSlotNum(slot_artefact_num);
    descriptor.setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descriptor.setDrawTurrels(false);

    return descriptor;
}


descriptor::SpaceStation
getNewSpaceStation()
{
    type::race race_id = (type::race)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    type::entity type_id = type::entity::WARRIOR_ID;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case type::entity::WARRIOR_ID: { protection_rate = 2; break; }
        case type::entity::TRADER_ID:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::getRandInt(100);
    int armor       = space;
    int protection  = protection_rate*meti::getRandInt(size_id);
    int temperature = 100;
    int price       = meti::getRandInt(200, 400)*size_id;

    int slot_bak_num       = 1;
    int slot_drive_num     = 1;
    int slot_droid_num     = 1;
#ifdef USE_EXTRA_EQUIPMENT
    int slot_energizer_num = 1;
    int slot_freezer_num   = 1;
#endif
    int slot_grapple_num   = 1;
    int slot_protector_num = 1;
    int slot_radar_num     = 1;
    int slot_scaner_num    = 1;
    int slot_weapon_num   = weapons_num;
    int slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
    int slot_cargo_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;


    descriptor::SpaceStation descriptor;
    descriptor.setRace(int_t(race_id));
    //descriptor.setType(int_t(type_id));
    descriptor.setSize(size_id);

    descriptor.setSpace(space);
    descriptor.setArmor(armor);
    descriptor.setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setPrice(price);

    descriptor.setBakSlotNum(slot_bak_num);
    descriptor.setDriveSlotNum(slot_drive_num);
    descriptor.setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setEnergizerSlotNum(slot_energizer_num);
    descriptor.setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setGrappleSlotNum(slot_grapple_num);
    descriptor.setProtectorSlotNum(slot_protector_num);
    descriptor.setRadarSlotNum(slot_radar_num);
    descriptor.setScanerSlotNum(slot_scaner_num);
    descriptor.setWeaponSlotNum(slot_weapon_num);
    descriptor.setArtefactSlotNum(slot_artefact_num);
    descriptor.setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descriptor.setDrawTurrels(false);

    return descriptor;
}

descriptor::Satellite
getNewSatellite()
{
    type::race race_id = (type::race)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    type::entity type_id = type::entity::WARRIOR_ID;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case type::entity::WARRIOR_ID: { protection_rate = 2; break; }
        case type::entity::TRADER_ID:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::getRandInt(100);
    int armor       = space;
    int protection  = protection_rate*meti::getRandInt(size_id);
    int temperature = 100;
    int price       = meti::getRandInt(200, 400)*size_id;

    int slot_bak_num       = 1;
    int slot_drive_num     = 1;
    int slot_droid_num     = 1;
#ifdef USE_EXTRA_EQUIPMENT
    int slot_energizer_num = 1;
    int slot_freezer_num   = 1;
#endif
    int slot_grapple_num   = 1;
    int slot_protector_num = 1;
    int slot_radar_num     = 1;
    int slot_scaner_num    = 1;
    int slot_weapon_num   = weapons_num;
    int slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
    int slot_cargo_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;


    descriptor::Satellite descriptor;
    descriptor.setRace(int_t(race_id));
    //descriptor.setType(int_t(type_id));
    descriptor.setSize(size_id);

    descriptor.setSpace(space);
    descriptor.setArmor(armor);
    descriptor.setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setPrice(price);

    descriptor.setBakSlotNum(slot_bak_num);
    descriptor.setDriveSlotNum(slot_drive_num);
    descriptor.setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.setEnergizerSlotNum(slot_energizer_num);
    descriptor.setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descriptor.setGrappleSlotNum(slot_grapple_num);
    descriptor.setProtectorSlotNum(slot_protector_num);
    descriptor.setRadarSlotNum(slot_radar_num);
    descriptor.setScanerSlotNum(slot_scaner_num);
    descriptor.setWeaponSlotNum(slot_weapon_num);
    descriptor.setArtefactSlotNum(slot_artefact_num);
    descriptor.setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descriptor.setDrawTurrels(false);

    return descriptor;
}


/* items */
namespace {
void addItemCommonFields(descriptor::BaseOLD& descriptor,
                         int race,
                         int tech_level,
                         int modules_num_max,
                         int mass,
                         int condition_max,
                         int deterioration,
                         int price) {
    descriptor.add(descriptor::Key::RACE, race);
    descriptor.add(descriptor::Key::TECH, tech_level);
    descriptor.add(descriptor::Key::MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Key::MASS, mass);
    descriptor.add(descriptor::Key::CONDITION_MAX, condition_max);
    descriptor.add(descriptor::Key::DETERIORATION, deterioration);
    descriptor.add(descriptor::Key::PRICE, price);
}
} // namespace

descriptor::BaseOLD
getNewBak(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max        = meti::getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    int mass                   = meti::getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    int condition_max          = meti::getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    int fuel_max_orig = meti::getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX) * (1 + EQUIPMENT::BAK::FUEL_TECH_RATE * (int)tech_level);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id)

    descriptor::BaseOLD descriptor(descriptor::Type::BAK);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::FUEL_MAX, fuel_max_orig);
    return descriptor;
}

namespace item {

descriptor::item::Drive
getNewDrive(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules       = meti::getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
    int mass          = meti::getRandInt(EQUIPMENT::DRIVE::MASS_MIN, EQUIPMENT::DRIVE::MASS_MAX);
    int condition     = meti::getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN, EQUIPMENT::DRIVE::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    int speed = meti::getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX) * (1 + EQUIPMENT::DRIVE::SPEED_TECH_RATE * (int)tech_level);
    int hyper = meti::getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX) * (1 + EQUIPMENT::DRIVE::HYPER_TECH_RATE * (int)tech_level);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DRIVE_EQUIPMENT_ID);

    descriptor::item::Drive descr;
    // descriptor::item::Base
    descr.setMass(mass);
    descr.setCondition(condition);
    descr.setDeterioration(deterioration);
    descr.setPrice(price);

    // descriptor::item::BaseEquipment
    descr.setModules(modules);

    // descriptor::Drive
    descr.setSpeed(speed);
    descr.setHyper(hyper);

    return descr;
}

} // anemspace item

descriptor::BaseOLD
getNewDroid(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    int repair = meti::getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX) * (1 + EQUIPMENT::DROID::REPAIR_TECH_RATE*(int)tech_level);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT_ID);

    descriptor::BaseOLD descriptor(descriptor::Type::DROID);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::REPAIR, repair);
    return descriptor;
}

descriptor::BaseOLD
getNewGrapple(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::GRAPPLE::MODULES_NUM_MIN, EQUIPMENT::GRAPPLE::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::GRAPPLE::MASS_MIN,        EQUIPMENT::GRAPPLE::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::GRAPPLE::CONDITION_MIN,   EQUIPMENT::GRAPPLE::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID);

    int strength   = meti::getRandInt(EQUIPMENT::GRAPPLE::STRENGTH_MIN, EQUIPMENT::GRAPPLE::STRENGTH_MAX) * (1 + EQUIPMENT::GRAPPLE::STRENGTH_TECH_RATE * (int)tech_level);
    int radius     = meti::getRandInt(EQUIPMENT::GRAPPLE::RADIUS_MIN,   EQUIPMENT::GRAPPLE::RADIUS_MAX)   * (1 + EQUIPMENT::GRAPPLE::RADIUS_TECH_RATE * (int)tech_level);
    int speed      = meti::getRandInt(EQUIPMENT::GRAPPLE::SPEED_MIN,    EQUIPMENT::GRAPPLE::SPEED_MAX)    * (1 + EQUIPMENT::GRAPPLE::SPEED_TECH_RATE * (int)tech_level);

    descriptor::BaseOLD descriptor(descriptor::Type::GRAPPLE);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::STRENGTH, strength);
    descriptor.add(descriptor::Key::RADIUS, radius);
    descriptor.add(descriptor::Key::SPEED, speed);

    return descriptor;
}

descriptor::BaseOLD
getNewScaner(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::SCANER::MODULES_NUM_MIN, EQUIPMENT::SCANER::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::SCANER::MASS_MIN,        EQUIPMENT::SCANER::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::SCANER::CONDITION_MIN,   EQUIPMENT::SCANER::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT_ID);

    int scan = meti::getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX) * (1 + EQUIPMENT::SCANER::SCAN_TECH_RATE * (int)tech_level);

    descriptor::BaseOLD descriptor(descriptor::Type::SCANER);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::SCAN, scan);

    return descriptor;
}

descriptor::BaseOLD
getNewRadar(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::RADAR::MASS_MIN,        EQUIPMENT::RADAR::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::RADAR::CONDITION_MIN,   EQUIPMENT::RADAR::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT_ID);

    int radius = meti::getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);

    descriptor::BaseOLD descriptor(descriptor::Type::RADAR);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::RADIUS, radius);

    return descriptor;
}

descriptor::BaseOLD
getNewProtector(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN,        EQUIPMENT::PROTECTOR::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN,   EQUIPMENT::PROTECTOR::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID);

    int protection = meti::getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX);

    descriptor::BaseOLD descriptor(descriptor::Type::PROTECTOR);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::PROTECTION, protection);

    return descriptor;
}

descriptor::BaseOLD
getNewBomb(int damage, int radius)
{
    if (damage == -1) {
         damage = meti::getRandInt(10, 100);
    }
    if (radius == -1) {
        radius = meti::getRandInt(100, 300);
    }

    descriptor::BaseOLD descriptor(descriptor::Type::BOMB);
    descriptor.add(descriptor::Key::DAMAGE, damage);
    descriptor.add(descriptor::Key::RADIUS, radius);

    return descriptor;
}

} // namespace descriptor
