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

#include "RocketModuleBuilder.hpp"
#include <items/modules/RocketModule.hpp>
#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

RocketModuleBuilder::RocketModuleBuilder()
{}

RocketModuleBuilder::~RocketModuleBuilder()
{}

RocketModule* RocketModuleBuilder::createTemplate(INTLONGEST id) const
{
    RocketModule* rocket_module = nullptr;
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try {
        rocket_module = new RocketModule(id);
    } catch(std::bad_alloc) {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    global::get().entitiesManager().RegisterEntity(rocket_module);
    
    return rocket_module;
} 

RocketModule* RocketModuleBuilder::create(int ammo_max_add, int damage_add, int radius_add) const
{
    RocketModule* rocket_module = createTemplate();
    createInternals(rocket_module, ammo_max_add, damage_add, radius_add);

    return rocket_module;
} 

void RocketModuleBuilder::createInternals(RocketModule* rocket_module, int ammo_max_add, int damage_add, int radius_add) const
{     
    //    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    ammo_max_add    = meti::getRandInt(MODULE::ROCKET::AMMO_MIN, MODULE::ROCKET::AMMO_MAX);
    damage_add      = meti::getRandInt(MODULE::ROCKET::DAMAGE_MIN, MODULE::ROCKET::DAMAGE_MAX);
    radius_add      = meti::getRandInt(MODULE::ROCKET::RADIUS_MIN, MODULE::ROCKET::RADIUS_MAX);

    rocket_module->SetParentSubTypeId(TYPE::ENTITY::ROCKET_EQUIPMENT_ID);
    // alpitodorender rocket_module->SetRenderData(mesh, texOb, texOb->size());
    rocket_module->SetAmmoMaxAdd(ammo_max_add);
    rocket_module->SetDamageAdd(damage_add);
    rocket_module->SetRadiusAdd(radius_add);
}
