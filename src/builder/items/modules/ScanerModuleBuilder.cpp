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

#include "ScanerModuleBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

ScanerModuleBuilder& ScanerModuleBuilder::Instance()
{
	static ScanerModuleBuilder instance;
	return instance;
}

ScanerModuleBuilder::~ScanerModuleBuilder()
{}

void ScanerModuleBuilder::CreateNewScanerModule(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	scaner_module = new ScanerModule(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(scaner_module);
} 
        	
void ScanerModuleBuilder::CreateNewInternals()
{     
    	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    	int scan_add = getRandInt(MODULE::SCANER::SCAN_MIN, MODULE::SCANER::SCAN_MAX);
    
        scaner_module->SetTextureOb(texOb);
        scaner_module->SetScanAdd(scan_add);
}


