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

Descriptor generateHitDescriptor(const id_type& owner, const id_type& target, int damage)
{
    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_OWNER, std::to_string(owner));
    descriptor.add(Descriptor::KEY_TARGET, std::to_string(target));
    descriptor.add(Descriptor::KEY_DAMAGE, std::to_string(damage));

    return descriptor;
}

Descriptor generateBombDescriptor(int damage, int radius)
{
    id_type id = global::get().idGenerator().nextId();
    if (damage == -1) {
         damage = meti::getRandInt(10, 100);
    }
    if (radius == -1) {
        radius = meti::getRandInt(100, 300);
    }

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_DAMAGE, std::to_string(damage));
    descriptor.add(Descriptor::KEY_RADIUS, std::to_string(radius));

    return descriptor;
}

Descriptor generateStarSystemDescriptor(int race)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));

    return descriptor;
}

// items
Descriptor generateBakDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::BAK_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_FUEL, std::to_string(fuel_max_orig));
    return descriptor;
}

Descriptor generateDriveDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::DRIVE_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_SPEED, std::to_string(speed));
    descriptor.add(Descriptor::KEY_HYPER, std::to_string(hyper));
    return descriptor;
}

Descriptor generateDroidDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::DROID_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_REPAIR, std::to_string(repair));
    return descriptor;
}

Descriptor generateGrappleDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_STRENGTH, std::to_string(strength));
    descriptor.add(Descriptor::KEY_RADIUS, std::to_string(radius));
    descriptor.add(Descriptor::KEY_SPEED, std::to_string(speed));

    return descriptor;
}

Descriptor generateScanerDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::SCANER_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_SCAN, std::to_string(scan));

    return descriptor;
}

Descriptor generateRadarDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::RADAR_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_RADIUS, std::to_string(radius));

    return descriptor;
}

Descriptor generateProtectorDescriptor(int race, int tech_level)
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

    Descriptor descriptor;
    descriptor.add(Descriptor::KEY_ID, std::to_string(global::get().idGenerator().nextId()));
    descriptor.add(Descriptor::KEY_TYPE, std::to_string(int(TYPE::ENTITY::RADAR_EQUIPMENT_ID)));
    descriptor.add(Descriptor::KEY_RACE, std::to_string(race));
    descriptor.add(Descriptor::KEY_TECH, std::to_string(tech_level));
    descriptor.add(Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max));
    descriptor.add(Descriptor::KEY_MASS, std::to_string(mass));
    descriptor.add(Descriptor::KEY_CONDITION, std::to_string(condition_max));
    descriptor.add(Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal));
    descriptor.add(Descriptor::KEY_PROTECTION, std::to_string(protection));

    return descriptor;
}


