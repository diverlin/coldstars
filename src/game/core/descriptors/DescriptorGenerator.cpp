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
#include <descriptors/Base.hpp>

#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/StarsystemDescriptor.hpp>
#include <descriptors/StarDescriptor.hpp>

#include <meti/RandUtils.hpp>
#include <common/Global.hpp>
#include <common/IdGenerator.hpp>

#include <common/constants.hpp>
#include <descriptors/RaceDescriptors.hpp>

#include <item/BaseItem.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>

namespace descriptor {

/* world */
descriptor::Galaxy
Generator::getNewGalaxyDescriptor(const std::vector<id_type>& sectors) {
    descriptor::Galaxy descriptor;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descriptor.sectors.push_back(meti::getRand(sectors));
    }
    return descriptor;
}

descriptor::Sector
Generator::getNewSectorDescriptor(const std::vector<id_type>& starsystems) {
    descriptor::Sector descriptor;
    int num = meti::getRandInt(1,3);
    for(int i=0; i<num; ++i) {
        descriptor.starsystems.push_back(meti::getRand(starsystems));
    }
    return descriptor;
}

descriptor::Starsystem
Generator::getNewStarsystemDescriptor(int race)
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

descriptor::Star
Generator::getNewStarDescriptor()
{
    descriptor::Star d;
    d.setArmor(10000000);
//    d.setTexture(TextureCollector::get().getTextureByTypeId(type::TEXTURE::STAR_ID).id());
//    d.setMesh(MeshCollector::get().get(type::mesh::SPHERE_ID).id());

    return d;
}

descriptor::BaseOLD
Generator::getNewPlanetDescriptor()
{
    descriptor::BaseOLD descriptor(descriptor::Type::PLANET);
    descriptor.add(descriptor::Key::ARMOR, 100000);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET_ID);

    return descriptor;
}

descriptor::BaseOLD
Generator::getNewAsteroidDescriptor()
{
    descriptor::BaseOLD descriptor(descriptor::Type::ASTEROID);
    return descriptor;
}

descriptor::BaseOLD
Generator::getNewContainerDescriptor()
{
    descriptor::BaseOLD descriptor(descriptor::Type::CONTAINER);
    return descriptor;
}

descriptor::BaseOLD
Generator::getNewVehicleDescriptor()
{
    type::race race_id = (type::race)0;//meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
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
    int slot_otsec_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;


    descriptor::BaseOLD descriptor(descriptor::Type::VEHICLE);
    descriptor.add(descriptor::Key::RACE, (int)race_id);
    descriptor.add(descriptor::Key::OBJ_TYPE, (int)type_id);
    descriptor.add(descriptor::Key::SIZE, size_id);

    descriptor.add(descriptor::Key::SPACE, space);
    descriptor.add(descriptor::Key::ARMOR, armor);
    descriptor.add(descriptor::Key::PROTECTION, protection);
    descriptor.add(descriptor::Key::TEMPERATURE, temperature);
    descriptor.add(descriptor::Key::PRICE, price);

    descriptor.add(descriptor::Key::BAK_SLOT_NUM, slot_bak_num);
    descriptor.add(descriptor::Key::DRIVE_SLOT_NUM, slot_drive_num);
    descriptor.add(descriptor::Key::DROID_SLOT_NUM, slot_droid_num);
#ifdef USE_EXTRA_EQUIPMENT
    descriptor.add(descriptor::Key::ENERGIZER_SLOT_NUM, slot_energizer_num);
    descriptor.add(descriptor::Key::FREEZER_SLOT_NUM, slot_freezer_num);
#endif
    descriptor.add(descriptor::Key::GRAPPLE_SLOT_NUM, slot_grapple_num);
    descriptor.add(descriptor::Key::PROTECTOR_SLOT_NUM, slot_protector_num);
    descriptor.add(descriptor::Key::RADAR_SLOT_NUM, slot_radar_num);
    descriptor.add(descriptor::Key::SCANER_SLOT_NUM, slot_scaner_num);
    descriptor.add(descriptor::Key::WEAPON_SLOT_NUM, slot_weapon_num);
    descriptor.add(descriptor::Key::ARTEFACT_SLOT_NUM, slot_artefact_num);
    descriptor.add(descriptor::Key::CARGO_SLOT_NUM, slot_otsec_num);

    //int size_threshold = 2;
    descriptor.add(descriptor::Key::DRAW_TURRELS, 0);

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
Generator::getNewBakDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id)

    descriptor::BaseOLD descriptor(descriptor::Type::BAK);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::FUEL_MAX, fuel_max_orig);
    return descriptor;
}

descriptor::BaseOLD
Generator::getNewDriveDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(type::race::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(type::tech::LEVEL0);
    }

    int modules_num_max        = meti::getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
    int mass                   = meti::getRandInt(EQUIPMENT::DRIVE::MASS_MIN, EQUIPMENT::DRIVE::MASS_MAX);
    int condition_max          = meti::getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN, EQUIPMENT::DRIVE::CONDITION_MAX);
    int deterioration = 1;
    int price = meti::getRandInt(100, 1000);

    int speed = meti::getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX) * (1 + EQUIPMENT::DRIVE::SPEED_TECH_RATE * (int)tech_level);
    int hyper = meti::getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX) * (1 + EQUIPMENT::DRIVE::HYPER_TECH_RATE * (int)tech_level);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DRIVE_EQUIPMENT_ID);

    descriptor::BaseOLD descriptor(descriptor::Type::DRIVE);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::SPEED, speed);
    descriptor.add(descriptor::Key::HYPER, hyper);
    return descriptor;
}

descriptor::BaseOLD
Generator::getNewDroidDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT_ID);

    descriptor::BaseOLD descriptor(descriptor::Type::DROID);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::REPAIR, repair);
    return descriptor;
}

descriptor::BaseOLD
Generator::getNewGrappleDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID);

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
Generator::getNewScanerDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT_ID);

    int scan = meti::getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX) * (1 + EQUIPMENT::SCANER::SCAN_TECH_RATE * (int)tech_level);

    descriptor::BaseOLD descriptor(descriptor::Type::SCANER);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::SCAN, scan);

    return descriptor;
}

descriptor::BaseOLD
Generator::getNewRadarDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT_ID);

    int radius = meti::getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);

    descriptor::BaseOLD descriptor(descriptor::Type::RADAR);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::RADIUS, radius);

    return descriptor;
}

descriptor::BaseOLD
Generator::getNewProtectorDescriptor(int race, int tech_level)
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
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID);

    int protection = meti::getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX);

    descriptor::BaseOLD descriptor(descriptor::Type::PROTECTOR);
    addItemCommonFields(descriptor,
                        race, tech_level, modules_num_max, mass, condition_max, deterioration, price);
    descriptor.add(descriptor::Key::PROTECTION, protection);

    return descriptor;
}

descriptor::BaseOLD
Generator::getNewBombDescriptor(int damage, int radius)
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
