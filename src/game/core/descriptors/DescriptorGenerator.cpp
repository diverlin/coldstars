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

Descriptor generateHitDescriptor(const id_type& owner, const id_type& target, int damage)
{
    id_type id = global::get().idGenerator().nextId();
    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_OWNER, std::to_string(owner)},
        {Descriptor::KEY_TARGET, std::to_string(target)},
        {Descriptor::KEY_DAMAGE, std::to_string(damage)}
    };

    Descriptor descriptor(map);
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

    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_DAMAGE, std::to_string(damage)},
        {Descriptor::KEY_RADIUS, std::to_string(radius)}
    };

    Descriptor descriptor(map);
    return descriptor;
}

Descriptor generateStarSystemDescriptor(int race)
{
    if (race == -1) {
        race = int(TYPE::RACE::R0_ID);
    }

    id_type id = global::get().idGenerator().nextId();
    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_RACE, std::to_string(race)}
    };

    Descriptor descriptor(map);
    return descriptor;
}

// items
Descriptor generateBakDescriptor(int race, int tech_level)
{
    if (race == -1) {
        race = race = int(TYPE::RACE::R0_ID);
    }

    if (tech_level == -1) {
        tech_level = int(TYPE::TECHLEVEL::L0_ID);
    }

    int modules_num_max        = meti::getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    int mass                   = meti::getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    int condition_max          = meti::getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX);
    int deterioration_normal = 1;
    int fuel_max_orig = meti::getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX) * (1 + EQUIPMENT::BAK::FUEL_TECHLEVEL_RATE * (int)tech_level);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id)

    id_type id = global::get().idGenerator().nextId();
    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_RACE, std::to_string(race)},
        {Descriptor::KEY_TECH, std::to_string(tech_level)},
        {Descriptor::KEY_MODULES_NUM, std::to_string(modules_num_max)},
        {Descriptor::KEY_MASS, std::to_string(mass)},
        {Descriptor::KEY_CONDITION, std::to_string(condition_max)},
        {Descriptor::KEY_DETEORATION, std::to_string(deterioration_normal)},
        {Descriptor::KEY_FUEL, std::to_string(fuel_max_orig)}
    };

    Descriptor descriptor(map);
    return descriptor;
}
