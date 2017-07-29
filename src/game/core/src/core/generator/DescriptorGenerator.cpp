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

#include <core/descriptor/item/equipment/ALL>
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

#include <core/manager/DescriptorManager.hpp>

#include <meti/RandUtils.hpp>

#include <ceti/IdGenerator.hpp>


namespace descriptor {

namespace {

glm::vec3 randPlanetoidDirection() {
    return glm::normalize(glm::vec3(meti::getRandFloat(0.1, 0.3), 1.0, -1.0));
}

} // namespace

/* world */
descriptor::Galaxy*
genGalaxy(const std::vector<int_t>& sectors) {
    descriptor::Galaxy* descr = new descriptor::Galaxy;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descr->sectors.push_back(meti::getRand(sectors));
    }
    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::Sector*
genSector(const std::vector<int_t>& starsystems) {
    descriptor::Sector* descr = new descriptor::Sector;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descr->starsystems.push_back(meti::getRand(starsystems));
    }
    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::StarSystem*
genStarSystem(race::Type race)
{
    descriptor::StarSystem* descr = new descriptor::StarSystem;
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    descr->setRace(race);

    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::HyperSpace*
genHyperSpace()
{
    descriptor::HyperSpace* descr = new descriptor::HyperSpace;
    descriptor::Manager::get().add(descr);
    return descr;
}

/* spaceobjects */

namespace {

int_t meshDescriptorIdFromType(const mesh::Type& type) {
    descriptor::Mesh* descr = descriptor::Manager::get().randMesh(type);
    if (type == mesh::Type::PLANE) {
        descr->setIsPlane();
    }
    assert(descr->id() != NONE);
    return descr->id();
}

int_t textureDescriptorIdFromType(const texture::Type& type) {
    descriptor::Material* descr = descriptor::Manager::get().randMaterial(type);
    assert(descr->id() != NONE);
    return descr->id();
}

} // namespace

descriptor::Star*
genStar()
{
    descriptor::Star* descr = new descriptor::Star;
    descr->setArmor(10000000);

    int orbit_radius = meti::getRandInt(descriptor::Star::DISTANCE_MIN,
                                        descriptor::Star::DISTANCE_MAX);
    descr->setRadiusA(orbit_radius);
    descr->setRadiusB(orbit_radius);
    descr->setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Star::SPEED_MIN,
                                   descriptor::Star::SPEED_MAX) / float(orbit_radius);
    descr->setSpeed(speed);
    descr->setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Star::SCALE_MIN,
                                  descriptor::Star::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());

    descr->setTexture(textureDescriptorIdFromType(texture::Type::STAR));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE));

    descriptor::Manager::get().add(descr);

    assert(descr->texture() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}

descriptor::Planet*
genPlanet()
{
    descriptor::Planet* descr = new descriptor::Planet;
    descr->setArmor(100000);

    int orbit_radius = meti::getRandInt(descriptor::Planet::DISTANCE_MIN,
                                        descriptor::Planet::DISTANCE_MAX);
    descr->setRadiusA(orbit_radius);
    descr->setRadiusB(orbit_radius);
    descr->setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Planet::SPEED_MIN,
                                   descriptor::Planet::SPEED_MAX) / float(orbit_radius);
    descr->setSpeed(speed);
    descr->setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Planet::SCALE_MIN,
                                  descriptor::Planet::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());
    descr->setTexture(textureDescriptorIdFromType(texture::Type::PLANET));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE));

    descriptor::Manager::get().add(descr);

    assert(descr->texture() != NONE);
    assert(descr->mesh() != NONE);

    return descr;

    //model::Planet*
    //Planet::gen(descriptor::BaseOLD* descr)
    //{
    //    model::Planet* model = __genTemplate();

    //    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::SPHERE);
    //    //jeti::control::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET);

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

descriptor::Asteroid*
genAsteroid()
{
    descriptor::Asteroid* descr = new descriptor::Asteroid;
    descr->setArmor(meti::getRandInt(descriptor::Asteroid::ARMOR_MIN,
                                    descriptor::Asteroid::ARMOR_MAX));

    int orbit_radiusA = meti::getRandInt(descriptor::Asteroid::DISTANCE_MIN,
                                        descriptor::Asteroid::DISTANCE_MAX);
    int orbit_radiusB = meti::getRandInt(descriptor::Asteroid::DISTANCE_MIN,
                                        descriptor::Asteroid::DISTANCE_MAX);
    descr->setRadiusA(orbit_radiusA);
    descr->setRadiusB(orbit_radiusB);
    descr->setOrbitPhi(0);
    float speed = meti::getRandInt(descriptor::Asteroid::SPEED_MIN,
                                   descriptor::Asteroid::SPEED_MAX) / float((orbit_radiusA+orbit_radiusB)/2.0);
    descr->setSpeed(speed);
    descr->setClockwise(meti::getRandBool());

    float size = meti::getRandInt(descriptor::Asteroid::SCALE_MIN,
                                  descriptor::Asteroid::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());
    descr->setTexture(textureDescriptorIdFromType(texture::Type::ASTEROID));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::SPHERE_DEFORMED));

    descriptor::Manager::get().add(descr);

    assert(descr->texture() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}

descriptor::WormHole*
genWormHole()
{
    descriptor::WormHole* descr = new descriptor::WormHole;

    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::Container*
genContainer()
{
    descriptor::Container* descr = new descriptor::Container;

    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::Npc*
genNpc()
{
    descriptor::Npc* descr = new descriptor::Npc;

    descriptor::Manager::get().add(descr);
    return descr;
}

descriptor::Ship*
genShip()
{
    race::Type race_id =  race::Type::R0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case entity::Type::WARRIOR: { protection_rate = 2; break; }
        case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
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

    descriptor::Ship* descr = new descriptor::Ship;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        float length = meti::getRandFloat(-0.8f, 0.8f);
        float angle = meti::getRandAngle();
        descr->addTurrelPoint(meti::genVec3f(length, angle));
    }
//    for(int i=0; i<slot_drive_num; ++i) {
//        int length = meti::getRandInt(100);
//        float angle = meti::getRandAngle();
//        descr->addDrivePoint(meti::genVec3f(length, angle));
//    }
//    for(int i=0; i<slot_protector_num; ++i) {
//        int length = meti::getRandInt(100);
//        float angle = meti::getRandAngle();
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
    descr->setTexture(textureDescriptorIdFromType(texture::Type::SHIP));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));
    //descr->setSize(meti::vec3(meti::getRandInt(100, 100))); // TODO: take from image

    descriptor::Manager::get().add(descr);

    return descr;
}


descriptor::SpaceStation*
genSpaceStation()
{
    race::Type race_id =  race::Type::R0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case entity::Type::WARRIOR: { protection_rate = 2; break; }
        case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
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

    descriptor::SpaceStation* descr = new descriptor::SpaceStation;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addTurrelPoint(meti::genVec3f(length, angle));
    }
    for(int i=0; i<slot_drive_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addDrivePoint(meti::genVec3f(length, angle));
    }
    for(int i=0; i<slot_protector_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addProtectorPoint(meti::genVec3f(length, angle));
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

    descriptor::Manager::get().add(descr);

    return descr;
}

descriptor::Satellite*
genSatellite()
{
    race::Type race_id =  (race::Type)0;//meti::getRand(core::global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    entity::Type type_id = entity::Type::WARRIOR;
    int size_id = meti::getRandInt(1, 9);
    int weapons_num = size_id;

    float protection_rate = 1;
    float otsec_rate      = 1;
    switch (type_id) {
        case entity::Type::WARRIOR: { protection_rate = 2; break; }
        case entity::Type::TRADER:  { otsec_rate = 1.5; break; }
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

    descriptor::Satellite* descr = new descriptor::Satellite;
    descr->setRace(race_id);
    for(int i=0; i<slot_weapon_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addTurrelPoint(meti::genVec3f(length, angle));
    }
    for(int i=0; i<slot_drive_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addDrivePoint(meti::genVec3f(length, angle));
    }
    for(int i=0; i<slot_protector_num; ++i) {
        int length = meti::getRandInt(100);
        float angle = meti::getRandAngle();
        descr->addProtectorPoint(meti::genVec3f(length, angle));
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

    descriptor::Manager::get().add(descr);

    return descr;
}


// dock
Kosmoport*
genKosmoport(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    Kosmoport* descr = new Kosmoport;
    descr->setRace(race);

    descriptor::Manager::get().add(descr);

    return descr;
}

NatureLand*
genNatureLand()
{
    NatureLand* descr = new NatureLand;

    descriptor::Manager::get().add(descr);

    return descr;
}


Angar*
genAngar(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    Angar* descr = new Angar;
    descr->setRace(race);

    descriptor::Manager::get().add(descr);

    return descr;
}

Store*
genStore(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    Store* descr = new Store;
    descr->setRace(race);

    descriptor::Manager::get().add(descr);

    return descr;
}

Shop*
genShop(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    Shop* descr = new Shop;
    descr->setRace(race);

    descriptor::Manager::get().add(descr);

    return descr;
}

Goverment*
genGoverment(race::Type race)
{
    if (race == race::Type::NONE) {
        race = race::Type::R0;
    }

    Goverment* descr = new Goverment;
    descr->setRace(race);

    descriptor::Manager::get().add(descr);

    return descr;
}



namespace item {

Bak*
genBak(int race, int tech_level)
{
    if (race == NONE) {
        race = int (race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int (tech::Type::LEVEL0);
    }

    int modules       = meti::getRandInt(Bak::MODULES_NUM_MIN, Bak::MODULES_NUM_MAX);
    int mass          = meti::getRandInt(Bak::MASS_MIN, Bak::MASS_MAX);
    int condition     = meti::getRandInt(Bak::CONDITION_MIN, Bak::CONDITION_MAX);
    int deterioration = 1;

    int fuel = meti::getRandInt(Bak::FUEL_MIN, Bak::FUEL_MAX) * (1 + int(Bak::FUEL_TECH_RATE * tech_level));

    auto funcCountPrice = [](int fuel, int modules, int mass, int condition) {
        float fuel_rate          = float(fuel) / Bak::FUEL_MIN;
        float modules_num_rate   = float(modules) / Bak::MODULES_NUM_MAX;

        float effectiveness_rate = Bak::FUEL_WEIGHT * fuel_rate +
                Bak::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / Bak::MASS_MIN;
        float condition_rate     = float(condition) / Bak::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(fuel, modules, mass, condition);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT, revision_id)

    Bak* descr = new Bak;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Bak
    descr->setFuel(fuel);

    descriptor::Manager::get().add(descr);

    return descr;
}


Drive*
genDrive(int race, int tech_level)
{
    if (race == NONE) {
        race = int (race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int (tech::Type::LEVEL0);
    }

    int modules       = meti::getRandInt(Drive::MODULES_NUM_MIN, Drive::MODULES_NUM_MAX);
    int mass          = meti::getRandInt(Drive::MASS_MIN, Drive::MASS_MAX);
    int condition     = meti::getRandInt(Drive::CONDITION_MIN, Drive::CONDITION_MAX);
    int deterioration = 1;

    int speed = meti::getRandInt(Drive::SPEED_MIN, Drive::SPEED_MAX) * (1 + int(Drive::SPEED_TECH_RATE * tech_level));
    int hyper = meti::getRandInt(Drive::HYPER_MIN, Drive::HYPER_MAX) * (1 + int(Drive::HYPER_TECH_RATE * tech_level));
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DRIVE_EQUIPMENT);

    auto funcCountPrice = [](int speed, int hyper, int modules, int mass, int condition) {
        float speed_rate         = float(speed) / Drive::SPEED_MIN;
        float hyper_rate         = float(hyper) / Drive::HYPER_MIN;
        float modules_num_rate   = float(modules) / Drive::MODULES_NUM_MAX;

        float effectiveness_rate = Drive::SPEED_WEIGHT * speed_rate +
                Drive::HYPER_WEIGHT * hyper_rate +
                Drive::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / Drive::MASS_MIN;
        float condition_rate     = float(condition) / Drive::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(speed, hyper, modules, mass, condition);


    Drive* descr = new Drive;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Drive
    descr->setSpeed(speed);
    descr->setHyper(hyper);

    descriptor::Manager::get().add(descr);

    return descr;
}

Droid*
genDroid(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules       = meti::getRandInt(Droid::MODULES_NUM_MIN, Droid::MODULES_NUM_MAX);
    int mass          = meti::getRandInt(Droid::MASS_MIN,        Droid::MASS_MAX);
    int condition     = meti::getRandInt(Droid::CONDITION_MIN,   Droid::CONDITION_MAX);
    int deterioration = 1;

    int repair = meti::getRandInt(Droid::REPAIR_MIN, Droid::REPAIR_MAX) * (1 + int(Droid::REPAIR_TECH_RATE * tech_level));
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT);

    auto funcCountPrice = [](int repair, int modules, int mass, int condition) {
        float repair_rate        = float(repair) / Droid::REPAIR_MIN;
        float modules_num_rate   = float(modules) / Droid::MODULES_NUM_MAX;

        float effectiveness_rate = Droid::REPAIR_WEIGHT * repair_rate +
                Droid::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / descriptor::item::Droid::MASS_MIN;
        float condition_rate     = float(condition) / descriptor::item::Droid::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(repair, modules, mass, condition);

    Droid* descr = new Droid;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Droid
    descr->setRepair(repair);

    descriptor::Manager::get().add(descr);

    return descr;
}


Grapple*
genGrapple(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::getRandInt(Grapple::MODULES_NUM_MIN, Grapple::MODULES_NUM_MAX);
    int mass = meti::getRandInt(Grapple::MASS_MIN,        Grapple::MASS_MAX);
    int condition = meti::getRandInt(Grapple::CONDITION_MIN,   Grapple::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GRAPPLE_EQUIPMENT);

    int strength   = meti::getRandInt(Grapple::STRENGTH_MIN, Grapple::STRENGTH_MAX) * (1 + int(Grapple::STRENGTH_TECH_RATE * tech_level));
    int radius     = meti::getRandInt(Grapple::RADIUS_MIN,   Grapple::RADIUS_MAX)   * (1 + int(Grapple::RADIUS_TECH_RATE * tech_level));
    int speed      = meti::getRandInt(Grapple::SPEED_MIN,    Grapple::SPEED_MAX)    * (1 + int(Grapple::SPEED_TECH_RATE * tech_level));

    auto funcCountPrice = [](int strength, int radius, int speed, int modules, int mass, int condition) {
        float strength_rate      = float(strength) / Grapple::STRENGTH_MIN;
        float radius_rate        = float(radius) / Grapple::RADIUS_MIN;
        float speed_rate         = float(speed) / Grapple::SPEED_MIN;

        float modules_num_rate   = float(modules) / Grapple::MODULES_NUM_MAX;

        float effectiveness_rate = Grapple::STRENGTH_WEIGHT * strength_rate +
                Grapple::RADIUS_WEIGHT * radius_rate +
                Grapple::SPEED_WEIGHT * speed_rate +
                Grapple::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / Grapple::MASS_MIN;
        float condition_rate     = float(condition) / Grapple::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(strength, radius, speed, modules, mass, condition);

    Grapple* descr = new Grapple;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Grapple
    descr->setStrength(strength);
    descr->setRadius(radius);
    descr->setSpeed(speed);

    descriptor::Manager::get().add(descr);

    return descr;
}

Lazer*
genLazer(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules       = meti::getRandInt(Lazer::MODULES_NUM_MIN, Lazer::MODULES_NUM_MAX);
    int mass          = meti::getRandInt(Lazer::MASS_MIN,        Lazer::MASS_MAX);
    int condition     = meti::getRandInt(Lazer::CONDITION_MIN,   Lazer::CONDITION_MAX);
    int deterioration = 1;

    int damage = meti::getRandInt(Lazer::DAMAGE_MIN, Lazer::DAMAGE_MAX) * (1 + int(Lazer::DAMAGE_TECH_RATE * tech_level));
    int radius = meti::getRandInt(Lazer::RADIUS_MIN, Lazer::RADIUS_MAX) * (1 + int(Lazer::RADIUS_TECH_RATE * tech_level));
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT);

    auto funcCountPrice = [](int damage, int radius, int modules, int mass, int condition) {
        float damage_rate        = float(damage) / Lazer::DAMAGE_MIN;
        float radius_rate        = float(radius) / Lazer::RADIUS_MIN;
        float modules_num_rate   = float(modules) / Lazer::MODULES_NUM_MAX;

        float effectiveness_rate = Lazer::DAMAGE_WEIGHT * damage_rate +
                Lazer::RADIUS_WEIGHT * radius_rate +
                Lazer::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / Lazer::MASS_MIN;
        float condition_rate = float(condition) / Lazer::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(damage, radius, modules, mass, condition);

    Lazer* descr = new Lazer;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Lazer
    descr->setDamage(damage);
    descr->setRadius(radius);

    descriptor::Manager::get().add(descr);

    return descr;
}

Protector*
genProtector(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::getRandInt(Protector::MODULES_NUM_MIN, Protector::MODULES_NUM_MAX);
    int mass    = meti::getRandInt(Protector::MASS_MIN,        Protector::MASS_MAX);
    int condition = meti::getRandInt(Protector::CONDITION_MIN, Protector::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PROTECTOR_EQUIPMENT);

    int protection = meti::getRandInt(Protector::PROTECTION_MIN, Protector::PROTECTION_MAX);

    auto funcCountPrice = [](int protection, int modules, int mass, int condition) {
        float protection_rate    = float(protection) / Protector::PROTECTION_MIN;
        float modules_num_rate   = float(modules) / Protector::MODULES_NUM_MAX;

        float effectiveness_rate = Protector::PROTECTION_WEIGHT * protection_rate +
                Protector::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / Protector::MASS_MIN;
        float condition_rate = float(condition) / Protector::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(protection, modules, mass, condition);

    Protector* descr = new Protector;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Protector
    descr->setProtection(protection);

    descriptor::Manager::get().add(descr);

    return descr;
}

Radar*
genRadar(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::getRandInt(Radar::MODULES_NUM_MIN, Radar::MODULES_NUM_MAX);
    int mass    = meti::getRandInt(Radar::MASS_MIN,        Radar::MASS_MAX);
    int condition = meti::getRandInt(Radar::CONDITION_MIN, Radar::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT);

    int radius = meti::getRandInt(Radar::RADIUS_MIN, Radar::RADIUS_MAX);

    auto funcCountPrice = [](int radius, int modules, int mass, int condition) {
        float radius_rate      = float(radius) / Radar::RADIUS_MIN;
        float modules_num_rate = float(modules) / Radar::MODULES_NUM_MAX;

        float effectiveness_rate = Radar::RADIUS_WEIGHT * radius_rate + Radar::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / Radar::MASS_MIN;
        float condition_rate = float(condition) / Radar::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(radius, modules, mass, condition);

    Radar* descr = new Radar;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Radar
    descr->setRadius(radius);

    descriptor::Manager::get().add(descr);

    return descr;
}

Rocket*
genRocket(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::getRandInt(Rocket::MODULES_NUM_MIN, Rocket::MODULES_NUM_MAX);
    int mass    = meti::getRandInt(Rocket::MASS_MIN,        Rocket::MASS_MAX);
    int condition = meti::getRandInt(Rocket::CONDITION_MIN, Rocket::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT);

    int ammo = meti::getRandInt(Rocket::AMMO_MIN, Rocket::AMMO_MAX);
    int damage = meti::getRandInt(Rocket::DAMAGE_MIN, Rocket::DAMAGE_MAX);
    int radius = meti::getRandInt(Rocket::RADIUS_MIN, Rocket::RADIUS_MAX);

    auto funcCountPrice = [](int ammo, int damage, int radius, int modules, int mass, int condition) {
        float ammo_rate     = float(ammo) / Rocket::AMMO_MIN;
        float damage_rate   = float(damage) / Rocket::DAMAGE_MIN;
        float radius_rate   = float(radius) / Rocket::RADIUS_MIN;
        float modules_num_rate   = float(modules) / Rocket::MODULES_NUM_MAX;

        float effectiveness_rate = Rocket::AMMO_WEIGHT * ammo_rate +
                Rocket::DAMAGE_WEIGHT * damage_rate +
                Rocket::RADIUS_WEIGHT * radius_rate +
                Rocket::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate      = float(mass) / Rocket::MASS_MIN;
        float condition_rate = float(condition) / Rocket::CONDITION_MAX;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(ammo, damage, radius, modules, mass, condition);

    Rocket* descr = new Rocket;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Rocket
    descr->setAmmo(ammo);
    descr->setDamage(damage);
    descr->setRadius(radius);

    descriptor::Manager::get().add(descr);

    return descr;
}

Scaner*
genScaner(int race, int tech_level)
{
    if (race == NONE) {
        race = int(race::Type::R0);
    }
    if (tech_level == NONE) {
        tech_level = int(tech::Type::LEVEL0);
    }

    int modules = meti::getRandInt(Scaner::MODULES_NUM_MIN, Scaner::MODULES_NUM_MAX);
    int mass = meti::getRandInt(Scaner::MASS_MIN,        Scaner::MASS_MAX);
    int condition = meti::getRandInt(Scaner::CONDITION_MIN,   Scaner::CONDITION_MAX);
    int deterioration = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
    //jeti::control::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT);

    int scan = meti::getRandInt(Scaner::SCAN_MIN, Scaner::SCAN_MAX) * (1 + int(Scaner::SCAN_TECH_RATE * tech_level));

    auto funcCountPrice = [](int scan, int modules, int mass, int condition) {
        float scan_rate          = float(scan) / Scaner::SCAN_MIN;
        float modules_num_rate   = float(modules) / Scaner::MODULES_NUM_MAX;

        float effectiveness_rate = Scaner::SCAN_WEIGHT * scan_rate +
                Scaner::MODULES_NUM_WEIGHT * modules_num_rate;

        float mass_rate          = float(mass) / Scaner::MASS_MIN;
        float condition_rate     = float(condition) / Scaner::CONDITION_MIN;

        return int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
    };
    int price = funcCountPrice(scan, modules, mass, condition);

    Scaner* descr = new Scaner;

    // descriptor::Item
    descr->setMass(mass);
    descr->setCondition(condition);
    descr->setDeterioration(deterioration);
    descr->setPrice(price);

    // descriptor::Equipment
    descr->setModules(modules);

    // descriptor::item::Radar
    descr->setScan(scan);

    descriptor::Manager::get().add(descr);

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

//    descriptor::Manager::get().reg(descr);

//    return descr;
//}

} // anemspace item



descriptor::Turrel*
genTurrel()
{
    descriptor::Turrel* descr = new descriptor::Turrel;

    float size = meti::getRandInt(descriptor::Asteroid::SCALE_MIN,
                                  descriptor::Asteroid::SCALE_MAX);
    descr->setSize(meti::vec3(size));
    descr->setDirection(randPlanetoidDirection());
    descr->setTexture(textureDescriptorIdFromType(texture::Type::TURREL));
    descr->setMesh(meshDescriptorIdFromType(mesh::Type::PLANE));

    descriptor::Manager::get().add(descr);

    assert(descr->texture() != NONE);
    assert(descr->mesh() != NONE);

    return descr;
}


} // namespace descriptor


