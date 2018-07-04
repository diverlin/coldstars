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
#include <core/descriptor/Base.hpp>
#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/descriptor/world/SectorDescriptor.hpp>
#include <core/descriptor/world/StarSystemDescriptor.hpp>
#include <core/descriptor/world/HyperSpace.hpp>
#include <core/descriptor/pilot/Npc.hpp>

#include <core/descriptor/item/ALL>
#include <core/descriptor/spaceobject/ALL>
#include <core/descriptor/dock/ALL>
#include <core/descriptor/part/Turrel.hpp>

#include <core/descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/common/constants.hpp>
#include <core/type/MeshType.hpp>
#include <core/type/TextureType.hpp>
#include <core/item/Item.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <meti/RandUtils.hpp>

#include <ceti/IdGenerator.hpp>


namespace core {

namespace {

glm::vec3 randPlanetoidDirection() {
    return glm::normalize(glm::vec3(meti::rand::gen_float(0.1, 0.3), 1.0, -1.0));
}

} // namespace

/* world */
core::GalaxyDescr*
genGalaxy(const std::vector<int_t>& sectors) {
    core::GalaxyDescr* descr = new core::GalaxyDescr;
    int num = meti::rand::gen_int(1,3);
    for(int i=0; i<num; ++i) {
        descr->sectors.push_back(meti::rand::get_element_or_die(sectors));
    }
    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::SectorDescr*
genSector(const std::vector<int_t>& starsystems) {
    core::SectorDescr* descr = new core::SectorDescr;
    int num = meti::rand::gen_int(1,3);
    for(int i=0; i<num; ++i) {
        descr->starsystems.push_back(meti::rand::get_element_or_die(starsystems));
    }
    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::StarSystemDescr*
genStarSystem(race::Type race)
{
    core::StarSystemDescr* descr = new core::StarSystemDescr;
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::HyperSpaceDescr*
genHyperSpace()
{
    core::HyperSpaceDescr* descr = new core::HyperSpaceDescr;
    core::shortcuts::descriptors()->add(descr);
    return descr;
}

/* spaceobjects */

namespace {

int_t meshDescriptorIdFromType(const mesh::Type& type) {
    core::MeshDescr* descr = core::shortcuts::descriptors()->randMesh(type);
    if (type == mesh::Type::PLANE) {
        descr->setIsPlane();
    }
    assert(descr->id() != NONE);
    return descr->id();
}

int_t textureDescriptorIdFromType(const texture::Type& type) {
    core::MaterialDescr* descr = core::shortcuts::descriptors()->randMaterial(type);
    assert(descr->id() != NONE);
    return descr->id();
}

} // namespace

core::StarDescr*
genStar()
{
    core::StarDescr* descr = new core::StarDescr;
    descr->setArmor(10000000);

    int orbit_radius = meti::rand::gen_int(core::StarDescr::DISTANCE_MIN,
                                           core::StarDescr::DISTANCE_MAX);
    descr->setRadiusA(orbit_radius);
    descr->setRadiusB(orbit_radius);
    descr->setOrbitPhi(0);
    float speed = meti::rand::gen_int(core::StarDescr::SPEED_MIN,
                                      core::StarDescr::SPEED_MAX) / float(orbit_radius);
    descr->setSpeed(speed);
    descr->setClockwise(meti::rand::gen_bool());

    float size = meti::rand::gen_int(core::StarDescr::SCALE_MIN,
                                     core::StarDescr::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());

    descr->setMaterial(textureDescriptorIdFromType(texture::Type::STAR));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE));

    core::shortcuts::descriptors()->add(descr);

    assert(descr->material() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}

core::PlanetDescr*
genPlanet()
{
    core::PlanetDescr* descr = new core::PlanetDescr;
    descr->setArmor(100000);

    int orbit_radius = meti::rand::gen_int(core::PlanetDescr::DISTANCE_MIN,
                                           core::PlanetDescr::DISTANCE_MAX);
    descr->setRadiusA(orbit_radius);
    descr->setRadiusB(orbit_radius);
    descr->setOrbitPhi(0);
    float speed = meti::rand::gen_int(core::PlanetDescr::SPEED_MIN,
                                      core::PlanetDescr::SPEED_MAX) / float(orbit_radius);
    descr->setSpeed(speed);
    descr->setClockwise(meti::rand::gen_bool());

    float size = meti::rand::gen_int(core::PlanetDescr::SCALE_MIN,
                                     core::PlanetDescr::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::PLANET));
    descr->setAtmosphereMaterial(textureDescriptorIdFromType(texture::Type::ATMOSPHERE));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE));

    core::shortcuts::descriptors()->add(descr);

    assert(descr->material() != NONE);
    assert(descr->mesh() != NONE);

    return descr;

    //Planet*
    //Planet::gen(BaseOLD* descr)
    //{
    //    Planet* model = __genTemplate();

    //    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::SPHERE);
    //    //jeti::control::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET);

    //    int orbit_radius = 1000; // hack
    //    //model->setOrbitCenter(glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
    //    model->setRadiusA(orbit_radius);
    //    model->setRadiusB(orbit_radius);
    //    model->setOrbitPhi(0);
    //    model->setSpeed(meti::getRandInt(Planet::SPEED_MIN, Planet::SPEED_MAX) / float(orbit_radius));
    //    model->setClockwise(meti::getRandBool());

    //    LifeData data_life;
    //    data_life.armor = descr.armor();
    //    model->setLifeData(data_life);

    //    float scale_comp = meti::getRandInt(Planet::SCALE_MIN, Planet::SCALE_MAX);
    //    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);

    //    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //    //alpitodorender planet->SetAnimationRotation(animation_rotation);

    //    //if (getRandBool())
    //    {
    //        //jeti::control::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE);
    //        //Atmosphere* atmosphere = new Atmosphere();
    //        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
    //        //alpitodorender planet->AddDecoration(atmosphere);
    //    }

    //   /*
    //   {
    //        Mesh* mesh_plane = MeshCollector::Instance().getMesh(mesh::type::PLANE);

    //        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING);
    //        Ring* ring = new Ring();
    //        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
    //        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
    //        ring->setDirection(glm::normalize(meti::OY));
    //        planet->AddDecoration(ring);
    //    }
    //    */
    //    return model;
    //}

}

core::AsteroidDescr*
genAsteroid()
{
    core::AsteroidDescr* descr = new core::AsteroidDescr;
    descr->setArmor(meti::rand::gen_int(core::AsteroidDescr::ARMOR_MIN,
                                        core::AsteroidDescr::ARMOR_MAX));

    int orbit_radiusA = meti::rand::gen_int(core::AsteroidDescr::DISTANCE_MIN,
                                            core::AsteroidDescr::DISTANCE_MAX);
    int orbit_radiusB = meti::rand::gen_int(core::AsteroidDescr::DISTANCE_MIN,
                                            core::AsteroidDescr::DISTANCE_MAX);
    descr->setRadiusA(orbit_radiusA);
    descr->setRadiusB(orbit_radiusB);
    descr->setOrbitPhi(0);
    float speed = meti::rand::gen_int(core::AsteroidDescr::SPEED_MIN,
                                      core::AsteroidDescr::SPEED_MAX) / float((orbit_radiusA+orbit_radiusB)/2.0);
    descr->setSpeed(speed);
    descr->setClockwise(meti::rand::gen_bool());

    float size = meti::rand::gen_int(core::AsteroidDescr::SCALE_MIN,
                                     core::AsteroidDescr::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::ASTEROID));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE_DEFORMED));

    core::shortcuts::descriptors()->add(descr);

    assert(descr->material() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}

core::WormHoleDescr*
genWormHole()
{
    core::WormHoleDescr* descr = new core::WormHoleDescr;

    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::ContainerDescr*
genContainer()
{
    core::ContainerDescr* descr = new core::ContainerDescr;

    descr->setSize(meti::vec3(1.0f));
    descr->setDirection(randPlanetoidDirection());
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::MINERAL));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));

    assert(descr->material() != NONE);
    assert(descr->mesh() != NONE);

    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::BulletDescr*
genBullet()
{
    BulletDescr* descriptor = new BulletDescr;

    texture::Type material_type;
    if (meti::rand::gen_bool()) {
        material_type = texture::Type::ROCKET_BULLET;
    } else {
        material_type = texture::Type::TORPEDO_BULLET;
    }
    descriptor->setMaterial(textureDescriptorIdFromType(material_type));
    descriptor->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));
    descriptor->setArmor(1);

    core::shortcuts::descriptors()->add(descriptor);

    assert(descriptor->material() != NONE);
    assert(descriptor->mesh() != NONE);

    return descriptor;
}

core::NpcDescr*
genNpc()
{
    core::NpcDescr* descr = new core::NpcDescr;

    core::shortcuts::descriptors()->add(descr);
    return descr;
}

core::ShipDescr*
genShip()
{
    race::Type race_id =  race::Type::R0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::rand::gen_int(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
    case entity::Type::WARRIOR: { protection_rate = 2; break; }
    case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::rand::gen_int(100);
    int armor       = space;
    int protection  = protection_rate*meti::rand::gen_int(size_id);
    int temperature = 100;
    int price       = meti::rand::gen_int(200, 400)*size_id;

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
    int slot_artefact_num = meti::rand::gen_int(1, 4);
    int slot_cargo_num    = meti::rand::gen_int(5, 10) * otsec_rate;

    core::ShipDescr* descr = new core::ShipDescr;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        float length = meti::rand::gen_float(-0.8f, 0.8f);
        float angle = meti::rand::gen_angle();
        descr->addTurrelPoint(meti::get_vec3(length, angle));
    }
    //    for(int i=0; i<slot_drive_num; ++i) {
    //        int length = meti::getRandInt(100);
    //        float angle = meti::rand::get_angle();
    //        descr->addDrivePoint(meti::genVec3f(length, angle));
    //    }
    //    for(int i=0; i<slot_protector_num; ++i) {
    //        int length = meti::getRandInt(100);
    //        float angle = meti::rand::get_angle();
    //        descr->addProtectorPoint(meti::genVec3f(length, angle));
    //    }
    descr->setSize(size_id);

    descr->setSpace(space);
    descr->setArmor(armor);
    descr->setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descr->setPrice(price);

    descr->setBakSlotNum(slot_bak_num);
    descr->setDriveSlotNum(slot_drive_num);
    descr->setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setEnergizerSlotNum(slot_energizer_num);
    descr->setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descr->setGrappleSlotNum(slot_grapple_num);
    descr->setProtectorSlotNum(slot_protector_num);
    descr->setRadarSlotNum(slot_radar_num);
    descr->setScanerSlotNum(slot_scaner_num);
    descr->setWeaponSlotNum(slot_weapon_num);
    descr->setArtefactSlotNum(slot_artefact_num);
    descr->setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descr->setDrawTurrels(false);

    // 3d
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::SHIP));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));
    //descr->setSize(meti::vec3(meti::getRandInt(100, 100))); // TODO: take from image

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


core::SpaceStationDescr*
genSpaceStation()
{
    race::Type race_id =  race::Type::R0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::rand::gen_int(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
    case entity::Type::WARRIOR: { protection_rate = 2; break; }
    case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::rand::gen_int(100);
    int armor       = space;
    int protection  = protection_rate*meti::rand::gen_int(size_id);
    int temperature = 100;
    int price       = meti::rand::gen_int(200, 400)*size_id;

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
    int slot_artefact_num = meti::rand::gen_int(1, 4);
    int slot_cargo_num    = meti::rand::gen_int(5, 10) * otsec_rate;

    core::SpaceStationDescr* descr = new core::SpaceStationDescr;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addTurrelPoint(meti::get_vec3(length, angle));
    }
    for(int i=0; i<slot_drive_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addDrivePoint(meti::get_vec3(length, angle));
    }
    for(int i=0; i<slot_protector_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addProtectorPoint(meti::get_vec3(length, angle));
    }
    descr->setSize(size_id);

    descr->setSpace(space);
    descr->setArmor(armor);
    descr->setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descr->setPrice(price);

    descr->setBakSlotNum(slot_bak_num);
    descr->setDriveSlotNum(slot_drive_num);
    descr->setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setEnergizerSlotNum(slot_energizer_num);
    descr->setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descr->setGrappleSlotNum(slot_grapple_num);
    descr->setProtectorSlotNum(slot_protector_num);
    descr->setRadarSlotNum(slot_radar_num);
    descr->setScanerSlotNum(slot_scaner_num);
    descr->setWeaponSlotNum(slot_weapon_num);
    descr->setArtefactSlotNum(slot_artefact_num);
    descr->setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descr->setDrawTurrels(false);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

core::SatelliteDescr*
genSatellite()
{
    race::Type race_id =  (race::Type)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::rand::gen_int(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
    case entity::Type::WARRIOR: { protection_rate = 2; break; }
    case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
    }

    int space       = size_id*100 + meti::rand::gen_int(100);
    int armor       = space;
    int protection  = protection_rate*meti::rand::gen_int(size_id);
    int temperature = 100;
    int price       = meti::rand::gen_int(200, 400)*size_id;

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
    int slot_artefact_num = meti::rand::gen_int(1, 4);
    int slot_cargo_num    = meti::rand::gen_int(5, 10) * otsec_rate;

    core::SatelliteDescr* descr = new core::SatelliteDescr;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addTurrelPoint(meti::get_vec3(length, angle));
    }
    for(int i=0; i<slot_drive_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addDrivePoint(meti::get_vec3(length, angle));
    }
    for(int i=0; i<slot_protector_num; ++i) {
        int length = meti::rand::gen_int(100);
        float angle = meti::rand::gen_angle();
        descr->addProtectorPoint(meti::get_vec3(length, angle));
    }
    descr->setSize(size_id);

    descr->setSpace(space);
    descr->setArmor(armor);
    descr->setProtection(protection);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setTemperature(temperature);
#endif // USE_EXTRA_EQUIPMENT
    descr->setPrice(price);

    descr->setBakSlotNum(slot_bak_num);
    descr->setDriveSlotNum(slot_drive_num);
    descr->setDroidSlotNum(slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descr->setEnergizerSlotNum(slot_energizer_num);
    descr->setFreezerSlotNum(slot_freezer_num);
#endif // USE_EXTRA_EQUIPMENT
    descr->setGrappleSlotNum(slot_grapple_num);
    descr->setProtectorSlotNum(slot_protector_num);
    descr->setRadarSlotNum(slot_radar_num);
    descr->setScanerSlotNum(slot_scaner_num);
    descr->setWeaponSlotNum(slot_weapon_num);
    descr->setArtefactSlotNum(slot_artefact_num);
    descr->setCargoSlotNum(slot_cargo_num);

    //int size_threshold = 2;
    descr->setDrawTurrels(false);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


// dock
KosmoportDescr*
genKosmoport(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    KosmoportDescr* descr = new KosmoportDescr;
    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

NatureLandDescr*
genNatureLand()
{
    NatureLandDescr* descr = new NatureLandDescr;

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


AngarDescr*
genAngar(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    AngarDescr* descr = new AngarDescr;
    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

StoreDescr*
genStore(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    StoreDescr* descr = new StoreDescr;
    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

ShopDescr*
genShop(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    ShopDescr* descr = new ShopDescr;
    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

GovermentDescr*
genGoverment(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    GovermentDescr* descr = new GovermentDescr;
    descr->setRace(race);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


BakDescr*
genBak(int race, int tech_level)
{
    if (race == NONE) {
        race = int (race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int (tech::Type::LEVEL0);
    }

    int modules       = meti::rand::gen_int(BakDescr::MODULES_NUM_MIN, BakDescr::MODULES_NUM_MAX);
    int mass          = meti::rand::gen_int(BakDescr::MASS_MIN, BakDescr::MASS_MAX);
    int condition     = meti::rand::gen_int(BakDescr::CONDITION_MIN, BakDescr::CONDITION_MAX);
    int deterioration = 1;

    int fuel = meti::rand::gen_int(BakDescr::FUEL_MIN, BakDescr::FUEL_MAX) * (1 + int(BakDescr::FUEL_TECH_RATE * tech_level));

    auto funcCountPrice = [](int fuel, int modules, int mass, int condition) {
        float fuel_rate          = float(fuel) / BakDescr::FUEL_MIN;
        float modules_num_rate   = float(modules) / BakDescr::MODULES_NUM_MAX;

        float effectiveness_rate = BakDescr::FUEL_WEIGHT * fuel_rate +
                BakDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / BakDescr::MASS_MIN;
        float condition_rate     = float(condition) / BakDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(fuel, modules, mass, condition);

    BakDescr* descr = new BakDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::BAK_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Bak
    descr->setFuel(fuel);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


DriveDescr*
genDrive(int race, int tech_level)
{
    if (race == NONE) {
        race = int (race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int (tech::Type::LEVEL0);
    }

    int modules       = meti::rand::gen_int(DriveDescr::MODULES_NUM_MIN, DriveDescr::MODULES_NUM_MAX);
    int mass          = meti::rand::gen_int(DriveDescr::MASS_MIN, DriveDescr::MASS_MAX);
    int condition     = meti::rand::gen_int(DriveDescr::CONDITION_MIN, DriveDescr::CONDITION_MAX);
    int deterioration = 1;

    int speed = meti::rand::gen_int(DriveDescr::SPEED_MIN, DriveDescr::SPEED_MAX) * (1 + int(DriveDescr::SPEED_TECH_RATE * tech_level));
    int hyper = meti::rand::gen_int(DriveDescr::HYPER_MIN, DriveDescr::HYPER_MAX) * (1 + int(DriveDescr::HYPER_TECH_RATE * tech_level));

    auto funcCountPrice = [](int speed, int hyper, int modules, int mass, int condition) {
        float speed_rate         = float(speed) / DriveDescr::SPEED_MIN;
        float hyper_rate         = float(hyper) / DriveDescr::HYPER_MIN;
        float modules_num_rate   = float(modules) / DriveDescr::MODULES_NUM_MAX;

        float effectiveness_rate = DriveDescr::SPEED_WEIGHT * speed_rate +
                DriveDescr::HYPER_WEIGHT * hyper_rate +
                DriveDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / DriveDescr::MASS_MIN;
        float condition_rate     = float(condition) / DriveDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(speed, hyper, modules, mass, condition);


    DriveDescr* descr = new DriveDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::DRIVE_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Drive
    descr->setSpeed(speed);
    descr->setHyper(hyper);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

DroidDescr*
genDroid(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules       = meti::rand::gen_int(DroidDescr::MODULES_NUM_MIN, DroidDescr::MODULES_NUM_MAX);
    int mass          = meti::rand::gen_int(DroidDescr::MASS_MIN,        DroidDescr::MASS_MAX);
    int condition     = meti::rand::gen_int(DroidDescr::CONDITION_MIN,   DroidDescr::CONDITION_MAX);
    int deterioration = 1;

    int repair = meti::rand::gen_int(DroidDescr::REPAIR_MIN, DroidDescr::REPAIR_MAX) * (1 + int(DroidDescr::REPAIR_TECH_RATE * tech_level));
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT);

    auto funcCountPrice = [](int repair, int modules, int mass, int condition) {
        float repair_rate        = float(repair) / DroidDescr::REPAIR_MIN;
        float modules_num_rate   = float(modules) / DroidDescr::MODULES_NUM_MAX;

        float effectiveness_rate = DroidDescr::REPAIR_WEIGHT * repair_rate +
                DroidDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / core::DroidDescr::MASS_MIN;
        float condition_rate     = float(condition) / core::DroidDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(repair, modules, mass, condition);

    DroidDescr* descr = new DroidDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::DROID_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Droid
    descr->setRepair(repair);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}


GrappleDescr*
genGrapple(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::rand::gen_int(GrappleDescr::MODULES_NUM_MIN, GrappleDescr::MODULES_NUM_MAX);
    int mass = meti::rand::gen_int(GrappleDescr::MASS_MIN,        GrappleDescr::MASS_MAX);
    int condition = meti::rand::gen_int(GrappleDescr::CONDITION_MIN,   GrappleDescr::CONDITION_MAX);
    int deterioration = 1;

    int strength   = meti::rand::gen_int(GrappleDescr::STRENGTH_MIN, GrappleDescr::STRENGTH_MAX) * (1 + int(GrappleDescr::STRENGTH_TECH_RATE * tech_level));
    int radius     = meti::rand::gen_int(GrappleDescr::RADIUS_MIN,   GrappleDescr::RADIUS_MAX)   * (1 + int(GrappleDescr::RADIUS_TECH_RATE * tech_level));
    int speed      = meti::rand::gen_int(GrappleDescr::SPEED_MIN,    GrappleDescr::SPEED_MAX)    * (1 + int(GrappleDescr::SPEED_TECH_RATE * tech_level));

    auto funcCountPrice = [](int strength, int radius, int speed, int modules, int mass, int condition) {
        float strength_rate      = float(strength) / GrappleDescr::STRENGTH_MIN;
        float radius_rate        = float(radius) / GrappleDescr::RADIUS_MIN;
        float speed_rate         = float(speed) / GrappleDescr::SPEED_MIN;

        float modules_num_rate   = float(modules) / GrappleDescr::MODULES_NUM_MAX;

        float effectiveness_rate = GrappleDescr::STRENGTH_WEIGHT * strength_rate +
                GrappleDescr::RADIUS_WEIGHT * radius_rate +
                GrappleDescr::SPEED_WEIGHT * speed_rate +
                GrappleDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / GrappleDescr::MASS_MIN;
        float condition_rate     = float(condition) / GrappleDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(strength, radius, speed, modules, mass, condition);

    GrappleDescr* descr = new GrappleDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::GRAPPLE_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Grapple
    descr->setStrength(strength);
    descr->setRadius(radius);
    descr->setSpeed(speed);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

LazerDescr*
genLazer(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules       = meti::rand::gen_int(LazerDescr::MODULES_NUM_MIN, LazerDescr::MODULES_NUM_MAX);
    int mass          = meti::rand::gen_int(LazerDescr::MASS_MIN,        LazerDescr::MASS_MAX);
    int condition     = meti::rand::gen_int(LazerDescr::CONDITION_MIN,   LazerDescr::CONDITION_MAX);
    int deterioration = 1;

    int damage = meti::rand::gen_int(LazerDescr::DAMAGE_MIN, LazerDescr::DAMAGE_MAX) * (1 + int(LazerDescr::DAMAGE_TECH_RATE * tech_level));
    int radius = meti::rand::gen_int(LazerDescr::RADIUS_MIN, LazerDescr::RADIUS_MAX) * (1 + int(LazerDescr::RADIUS_TECH_RATE * tech_level));

    auto funcCountPrice = [](int damage, int radius, int modules, int mass, int condition) {
        float damage_rate        = float(damage) / LazerDescr::DAMAGE_MIN;
        float radius_rate        = float(radius) / LazerDescr::RADIUS_MIN;
        float modules_num_rate   = float(modules) / LazerDescr::MODULES_NUM_MAX;

        float effectiveness_rate = LazerDescr::DAMAGE_WEIGHT * damage_rate +
                LazerDescr::RADIUS_WEIGHT * radius_rate +
                LazerDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / LazerDescr::MASS_MIN;
        float condition_rate = float(condition) / LazerDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(damage, radius, modules, mass, condition);

    LazerDescr* descr = new LazerDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::LAZER_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Lazer
    descr->setDamage(damage);
    descr->setRadius(radius);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

ProtectorDescr*
genProtector(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::rand::gen_int(ProtectorDescr::MODULES_NUM_MIN, ProtectorDescr::MODULES_NUM_MAX);
    int mass    = meti::rand::gen_int(ProtectorDescr::MASS_MIN,        ProtectorDescr::MASS_MAX);
    int condition = meti::rand::gen_int(ProtectorDescr::CONDITION_MIN, ProtectorDescr::CONDITION_MAX);
    int deterioration = 1;

    int protection = meti::rand::gen_int(ProtectorDescr::PROTECTION_MIN, ProtectorDescr::PROTECTION_MAX);

    auto funcCountPrice = [](int protection, int modules, int mass, int condition) {
        float protection_rate    = float(protection) / ProtectorDescr::PROTECTION_MIN;
        float modules_num_rate   = float(modules) / ProtectorDescr::MODULES_NUM_MAX;

        float effectiveness_rate = ProtectorDescr::PROTECTION_WEIGHT * protection_rate +
                ProtectorDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / ProtectorDescr::MASS_MIN;
        float condition_rate = float(condition) / ProtectorDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(protection, modules, mass, condition);

    ProtectorDescr* descr = new ProtectorDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::PROTECTOR_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Protector
    descr->setProtection(protection);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

RadarDescr*
genRadar(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::rand::gen_int(RadarDescr::MODULES_NUM_MIN, RadarDescr::MODULES_NUM_MAX);
    int mass    = meti::rand::gen_int(RadarDescr::MASS_MIN,        RadarDescr::MASS_MAX);
    int condition = meti::rand::gen_int(RadarDescr::CONDITION_MIN, RadarDescr::CONDITION_MAX);
    int deterioration = 1;

    int radius = meti::rand::gen_int(RadarDescr::RADIUS_MIN, RadarDescr::RADIUS_MAX);

    auto funcCountPrice = [](int radius, int modules, int mass, int condition) {
        float radius_rate      = float(radius) / RadarDescr::RADIUS_MIN;
        float modules_num_rate = float(modules) / RadarDescr::MODULES_NUM_MAX;

        float effectiveness_rate = RadarDescr::RADIUS_WEIGHT * radius_rate + RadarDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / RadarDescr::MASS_MIN;
        float condition_rate = float(condition) / RadarDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(radius, modules, mass, condition);

    RadarDescr* descr = new RadarDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::RADAR_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Radar
    descr->setRadius(radius);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

RocketDescr*
genRocket(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::rand::gen_int(RocketDescr::MODULES_NUM_MIN, RocketDescr::MODULES_NUM_MAX);
    int mass    = meti::rand::gen_int(RocketDescr::MASS_MIN,        RocketDescr::MASS_MAX);
    int condition = meti::rand::gen_int(RocketDescr::CONDITION_MIN, RocketDescr::CONDITION_MAX);
    int deterioration = 1;

    int ammo = meti::rand::gen_int(RocketDescr::AMMO_MIN, RocketDescr::AMMO_MAX);
    int damage = meti::rand::gen_int(RocketDescr::DAMAGE_MIN, RocketDescr::DAMAGE_MAX);
    int radius = meti::rand::gen_int(RocketDescr::RADIUS_MIN, RocketDescr::RADIUS_MAX);

    auto funcCountPrice = [](int ammo, int damage, int radius, int modules, int mass, int condition) {
        float ammo_rate     = float(ammo) / RocketDescr::AMMO_MIN;
        float damage_rate   = float(damage) / RocketDescr::DAMAGE_MIN;
        float radius_rate   = float(radius) / RocketDescr::RADIUS_MIN;
        float modules_num_rate   = float(modules) / RocketDescr::MODULES_NUM_MAX;

        float effectiveness_rate = RocketDescr::AMMO_WEIGHT * ammo_rate +
                RocketDescr::DAMAGE_WEIGHT * damage_rate +
                RocketDescr::RADIUS_WEIGHT * radius_rate +
                RocketDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / RocketDescr::MASS_MIN;
        float condition_rate = float(condition) / RocketDescr::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(ammo, damage, radius, modules, mass, condition);

    RocketDescr* descr = new RocketDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::ROCKET_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Weapon
    descr->setDamage(damage);
    descr->setRadius(radius);

    // Rocket
    descr->setBulletDescriptor(core::shortcuts::descriptors()->randBullet()->id());
    descr->setAmmo(ammo);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

ScanerDescr*
genScaner(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::rand::gen_int(ScanerDescr::MODULES_NUM_MIN, ScanerDescr::MODULES_NUM_MAX);
    int mass = meti::rand::gen_int(ScanerDescr::MASS_MIN,        ScanerDescr::MASS_MAX);
    int condition = meti::rand::gen_int(ScanerDescr::CONDITION_MIN,   ScanerDescr::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT);

    int scan = meti::rand::gen_int(ScanerDescr::SCAN_MIN, ScanerDescr::SCAN_MAX) * (1 + int(ScanerDescr::SCAN_TECH_RATE * tech_level));

    auto funcCountPrice = [](int scan, int modules, int mass, int condition) {
        float scan_rate          = float(scan) / ScanerDescr::SCAN_MIN;
        float modules_num_rate   = float(modules) / ScanerDescr::MODULES_NUM_MAX;

        float effectiveness_rate = ScanerDescr::SCAN_WEIGHT * scan_rate +
                ScanerDescr::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / ScanerDescr::MASS_MIN;
        float condition_rate     = float(condition) / ScanerDescr::CONDITION_MIN;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(scan, modules, mass, condition);

    ScanerDescr* descr = new ScanerDescr;
    descr->setMaterial(textureDescriptorIdFromType(texture::Type::SCANER_EQUIPMENT));

    // Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // Equipment
    descr->setModules(modules);

    // Radar
    descr->setScan(scan);

    core::shortcuts::descriptors()->add(descr);

    return descr;
}

//Bomb*
//genBomb(int damage, int radius)
//{
//    if (damage == NONE) {
//        damage = meti::getRandInt(10, 100);
//    }
//    if (radius == NONE) {
//        radius = meti::getRandInt(100, 300);
//    }

//    Bomb* descr = new Bomb;
//    descr->setDamage(damage);
//    descr->setRadius(radius);

//    core::shortcuts::descriptors()->reg(descr);

//    return descr;
//}

// other
GoodsDescr*
genGoods()
{
    GoodsDescr* descriptor = new GoodsDescr;

    descriptor->setMaterial(textureDescriptorIdFromType(texture::Type::GOODS));
    descriptor->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));

    core::shortcuts::descriptors()->add(descriptor);

    return descriptor;
}

core::TurrelDescr*
genTurrel()
{
    core::TurrelDescr* descr = new core::TurrelDescr;

    descr->setMaterial(textureDescriptorIdFromType(texture::Type::TURREL));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));

    core::shortcuts::descriptors()->add(descr);

    assert(descr->material() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}


} // namespace core


