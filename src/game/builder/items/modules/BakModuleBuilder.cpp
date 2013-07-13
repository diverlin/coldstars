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

#include "BakModuleBuilder.hpp"
#include "../../../items/modules/BakModule.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

BakModuleBuilder& BakModuleBuilder::Instance()
{
	static BakModuleBuilder instance;
	return instance;
}

BakModuleBuilder::~BakModuleBuilder()
{}

BakModule* BakModuleBuilder::GetNewBakModuleTemplate(unsigned long int id) const
{
	BakModule* bak_module = nullptr;

	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	bak_module = new BakModule(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(bak_module);
        
        return bak_module;
} 
  
BakModule* BakModuleBuilder::GetNewBakModule(int fuel_max_add) const
{
	BakModule* bak_module = GetNewBakModuleTemplate();
	CreateNewInternals(bak_module, fuel_max_add);
	  
    return bak_module;
} 
         	
void BakModuleBuilder::CreateNewInternals(BakModule* bak_module, int fuel_max_add) const
{     
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    fuel_max_add = getRandInt(MODULE::BAK::FUEL_MIN, MODULE::BAK::FUEL_MAX);

    bak_module->SetParentSubTypeId(ENTITY::eTYPE::BAK_EQUIPMENT_ID);    
    bak_module->BindData2D(texOb);
    bak_module->SetFuelMaxAdd(fuel_max_add);
}


