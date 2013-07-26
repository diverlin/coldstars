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
#include "../../../items/modules/RocketModule.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

RocketModuleBuilder& RocketModuleBuilder::Instance()
{
	static RocketModuleBuilder instance;
	return instance;
}

RocketModuleBuilder::~RocketModuleBuilder()
{}

RocketModule* RocketModuleBuilder::GetNewRocketModuleTemplate(INTLONGEST id) const
{
	RocketModule* rocket_module = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        rocket_module = new RocketModule(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(rocket_module);
    
    return rocket_module;
} 
  
RocketModule* RocketModuleBuilder::GetNewRocketModule(int ammo_max_add, int damage_add, int radius_add) const
{
	RocketModule* rocket_module = GetNewRocketModuleTemplate();
	CreateNewInternals(rocket_module, ammo_max_add, damage_add, radius_add);	
        
        return rocket_module;
} 
      	
void RocketModuleBuilder::CreateNewInternals(RocketModule* rocket_module, int ammo_max_add, int damage_add, int radius_add) const
{     
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    ammo_max_add = getRandInt(MODULE::ROCKET::AMMO_MIN, MODULE::ROCKET::AMMO_MAX);
    damage_add = getRandInt(MODULE::ROCKET::DAMAGE_MIN, MODULE::ROCKET::DAMAGE_MAX);
    radius_add = getRandInt(MODULE::ROCKET::RADIUS_MIN, MODULE::ROCKET::RADIUS_MAX);

    rocket_module->SetParentSubTypeId(TYPE::ENTITY::ROCKET_EQUIPMENT_ID);    
    rocket_module->BindData2D(texOb);
    rocket_module->SetAmmoMaxAdd(ammo_max_add);
    rocket_module->SetDamageAdd(damage_add);
    rocket_module->SetRadiusAdd(radius_add);
}


