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

#include "ProtectorModuleBuilder.hpp"
#include "../../../items/modules/ProtectorModule.hpp"
#include "../../../common/id.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

ProtectorModuleBuilder& ProtectorModuleBuilder::Instance()
{
	static ProtectorModuleBuilder instance;
	return instance;
}

ProtectorModuleBuilder::~ProtectorModuleBuilder()
{}

ProtectorModule* ProtectorModuleBuilder::GetNewProtectorModuleTemplate(int id) const
{
	ProtectorModule* protector_module = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	protector_module = new ProtectorModule(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(protector_module);
        
        return protector_module;
} 

ProtectorModule* ProtectorModuleBuilder::GetNewProtectorModule(int protection_add) const
{
	ProtectorModule* protector_module = GetNewProtectorModuleTemplate();
	CreateNewInternals(protector_module, protection_add);
        
        return protector_module;
} 
        	
void ProtectorModuleBuilder::CreateNewInternals(ProtectorModule* protector_module, int protection_add) const
{     
    	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    	protection_add = getRandInt(MODULE::PROTECTOR::PROTECTION_MIN, MODULE::PROTECTOR::PROTECTION_MAX);
    
        protector_module->SetParentSubTypeId(ENTITY::PROTECTOR_EQUIPMENT_ID);    
        protector_module->SetTextureOb(texOb);
        protector_module->SetProtectionAdd(protection_add);
}


