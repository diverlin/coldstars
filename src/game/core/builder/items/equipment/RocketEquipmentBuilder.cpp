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

#include <builder/items/equipment/RocketEquipmentBuilder.hpp>
#include <items/equipment/RocketEquipment.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <common/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

RocketEquipmentBuilder& RocketEquipmentBuilder::Instance()
{
    static RocketEquipmentBuilder instance;
    return instance;
}

RocketEquipmentBuilder::~RocketEquipmentBuilder()
{}

RocketEquipment* RocketEquipmentBuilder::GetNewRocketEquipmentTemplate(INTLONGEST id) const
{
    RocketEquipment* rocket_equipment = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

     try 
    { 
        rocket_equipment = new RocketEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    global::get().entitiesManager().RegisterEntity(rocket_equipment);
    
    return rocket_equipment;
} 

RocketEquipment* RocketEquipmentBuilder::GetNewRocketEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int ammo_max_orig, int damage_orig, int radius_orig) const
{
    RocketEquipment* rocket_equipment = GetNewRocketEquipmentTemplate();
    CreateNewInternals(rocket_equipment, tech_level, race_id, ammo_max_orig, damage_orig, radius_orig);
            
    return rocket_equipment;
} 
            
void RocketEquipmentBuilder::CreateNewInternals(RocketEquipment* rocket_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int ammo_max_orig, int damage_orig, int radius_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }
   
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ROCKET_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::ROCKET_EQUIPMENT_ID, revision_id)   
    
    ammo_max_orig = meti::getRandInt(EQUIPMENT::ROCKET::AMMO_MIN, EQUIPMENT::ROCKET::AMMO_MAX)     * (1 + EQUIPMENT::ROCKET::AMMO_TECHLEVEL_RATE * (int)tech_level);
    damage_orig   = meti::getRandInt(EQUIPMENT::ROCKET::DAMAGE_MIN, EQUIPMENT::ROCKET::DAMAGE_MAX) * (1 + EQUIPMENT::ROCKET::DAMAGE_TECHLEVEL_RATE * (int)tech_level);
    radius_orig   = meti::getRandInt(EQUIPMENT::ROCKET::RADIUS_MIN, EQUIPMENT::ROCKET::RADIUS_MAX) * (1 + EQUIPMENT::ROCKET::RADIUS_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max = meti::getRandInt(EQUIPMENT::ROCKET::MODULES_NUM_MIN, EQUIPMENT::ROCKET::MODULES_NUM_MAX);
    
    common_data.mass            = meti::getRandInt(EQUIPMENT::ROCKET::MASS_MIN, EQUIPMENT::ROCKET::MASS_MAX);
    common_data.condition_max   = meti::getRandInt(EQUIPMENT::ROCKET::CONDITION_MIN, EQUIPMENT::ROCKET::CONDITION_MAX);
    
    common_data.deterioration_normal = 1;
    
    BulletData data_bullet;
    data_bullet.damage        = damage_orig;
    data_bullet.armor         = ENTITY::ROCKET::ARMOR;
    data_bullet.speed_init    = ENTITY::ROCKET::START_SPEED;
    data_bullet.speed_max     = ENTITY::ROCKET::SPEED_MAX;
    data_bullet.d_speed       = ENTITY::ROCKET::DELTA_SPEED;
    data_bullet.live_time     = ENTITY::ROCKET::LIFE_TIME;
    data_bullet.angular_speed = ENTITY::ROCKET::ANGULAR_SPEED;
    
    rocket_equipment->SetAmmoMaxOrig(ammo_max_orig);
    rocket_equipment->SetDamageOrig(damage_orig);
    rocket_equipment->SetRadiusOrig(radius_orig);   
    rocket_equipment->SetBulletData(data_bullet); 
    rocket_equipment->SetAmmo(ammo_max_orig*0.6);                
    //alpitodorender rocket_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    rocket_equipment->SetParentSubTypeId(TYPE::ENTITY::WEAPON_SLOT_ID);
    rocket_equipment->SetItemCommonData(common_data);
    rocket_equipment->SetCondition(common_data.condition_max);
    
    rocket_equipment->UpdateProperties();
    rocket_equipment->CountPrice();
}


