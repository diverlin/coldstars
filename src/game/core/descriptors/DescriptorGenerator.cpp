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

#include <meti/RandUtils.hpp>
#include <common/Global.hpp>
#include <common/IdGenerator.hpp>

#include <common/constants.hpp>
#include <items/BaseItem.hpp>

descriptor::Base generateBombDescriptor(int damage, int radius)
{
    if (damage == -1) {
         damage = meti::getRandInt(10, 100);
    }
    if (radius == -1) {
        radius = meti::getRandInt(100, 300);
    }

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::BOMB));
    descriptor.add(descriptor::Base::KEY_DAMAGE, damage);
    descriptor.add(descriptor::Base::KEY_RADIUS, radius);

    return descriptor;
}

descriptor::Base generateStarSystemDescriptor(int race)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::STARSYSTEM));
    descriptor.add(descriptor::Base::KEY_RACE, race);

    return descriptor;
}

// items
descriptor::Base generateBakDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max        = meti::getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    int mass                   = meti::getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    int condition_max          = meti::getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX);
    int deterioration_normal = 1;
    int fuel_max_orig = meti::getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX) * (1 + EQUIPMENT::BAK::FUEL_TECH_RATE * (int)tech_level);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id)

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::BAK));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_FUEL, fuel_max_orig);
    return descriptor;
}

descriptor::Base generateDriveDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max        = meti::getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
    int mass                   = meti::getRandInt(EQUIPMENT::DRIVE::MASS_MIN, EQUIPMENT::DRIVE::MASS_MAX);
    int condition_max          = meti::getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN, EQUIPMENT::DRIVE::CONDITION_MAX);
    int deterioration_normal = 1;

    int speed = meti::getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX) * (1 + EQUIPMENT::DRIVE::SPEED_TECH_RATE * (int)tech_level);
    int hyper = meti::getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX) * (1 + EQUIPMENT::DRIVE::HYPER_TECH_RATE * (int)tech_level);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DRIVE_EQUIPMENT_ID);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::DRIVE));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_SPEED, speed);
    descriptor.add(descriptor::Base::KEY_HYPER, hyper);
    return descriptor;
}

descriptor::Base generateDroidDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX);
    int deterioration_normal = 1;

    int repair = meti::getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX) * (1 + EQUIPMENT::DROID::REPAIR_TECH_RATE*(int)tech_level);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DROID_EQUIPMENT_ID);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::DROID));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_REPAIR, repair);
    return descriptor;
}

descriptor::Base generateGrappleDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::GRAPPLE::MODULES_NUM_MIN, EQUIPMENT::GRAPPLE::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::GRAPPLE::MASS_MIN,        EQUIPMENT::GRAPPLE::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::GRAPPLE::CONDITION_MIN,   EQUIPMENT::GRAPPLE::CONDITION_MAX);
    int deterioration_normal = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID);

    int strength   = meti::getRandInt(EQUIPMENT::GRAPPLE::STRENGTH_MIN, EQUIPMENT::GRAPPLE::STRENGTH_MAX) * (1 + EQUIPMENT::GRAPPLE::STRENGTH_TECH_RATE * (int)tech_level);
    int radius     = meti::getRandInt(EQUIPMENT::GRAPPLE::RADIUS_MIN,   EQUIPMENT::GRAPPLE::RADIUS_MAX)   * (1 + EQUIPMENT::GRAPPLE::RADIUS_TECH_RATE * (int)tech_level);
    int speed      = meti::getRandInt(EQUIPMENT::GRAPPLE::SPEED_MIN,    EQUIPMENT::GRAPPLE::SPEED_MAX)    * (1 + EQUIPMENT::GRAPPLE::SPEED_TECH_RATE * (int)tech_level);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::GRAPPLE));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_STRENGTH, strength);
    descriptor.add(descriptor::Base::KEY_RADIUS, radius);
    descriptor.add(descriptor::Base::KEY_SPEED, speed);

    return descriptor;
}

descriptor::Base generateScanerDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::SCANER::MODULES_NUM_MIN, EQUIPMENT::SCANER::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::SCANER::MASS_MIN,        EQUIPMENT::SCANER::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::SCANER::CONDITION_MIN,   EQUIPMENT::SCANER::CONDITION_MAX);
    int deterioration_normal = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SCANER_EQUIPMENT_ID);

    int scan = meti::getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX) * (1 + EQUIPMENT::SCANER::SCAN_TECH_RATE * (int)tech_level);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::SCANER));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_SCAN, scan);

    return descriptor;
}

descriptor::Base generateRadarDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::RADAR::MASS_MIN,        EQUIPMENT::RADAR::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::RADAR::CONDITION_MIN,   EQUIPMENT::RADAR::CONDITION_MAX);
    int deterioration_normal = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RADAR_EQUIPMENT_ID);

    int radius = meti::getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::RADAR));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_RADIUS, radius);

    return descriptor;
}

descriptor::Base generateProtectorDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }
    if (tech_level == -1) {
        tech_level = int(TYPE::TECH::L0_ID);
    }

    int modules_num_max = meti::getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    int mass            = meti::getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN,        EQUIPMENT::PROTECTOR::MASS_MAX);
    int condition_max   = meti::getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN,   EQUIPMENT::PROTECTOR::CONDITION_MAX);
    int deterioration_normal = 1;

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID);

    int protection = meti::getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX);

    descriptor::Base descriptor;
    descriptor.add(descriptor::Base::KEY_ID, global::get().idGenerator().nextId());
    descriptor.add(descriptor::Base::KEY_TYPE, int(descriptor::Base::Type::PROTECTOR));
    descriptor.add(descriptor::Base::KEY_RACE, race);
    descriptor.add(descriptor::Base::KEY_TECH, tech_level);
    descriptor.add(descriptor::Base::KEY_MODULES_NUM, modules_num_max);
    descriptor.add(descriptor::Base::KEY_MASS, mass);
    descriptor.add(descriptor::Base::KEY_CONDITION, condition_max);
    descriptor.add(descriptor::Base::KEY_DETEORATION, deterioration_normal);
    descriptor.add(descriptor::Base::KEY_PROTECTION, protection);

    return descriptor;
}


