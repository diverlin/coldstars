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

#include "DriveModuleBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

DriveModuleBuilder& DriveModuleBuilder::Instance()
{
	static DriveModuleBuilder instance;
	return instance;
}

DriveModuleBuilder::~DriveModuleBuilder()
{}

void DriveModuleBuilder::CreateNewDriveModule(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	drive_module = new DriveModule(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(drive_module);
} 
        	
void DriveModuleBuilder::CreateNewInternals()
{     
    	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    	int speed_add = getRandInt(MODULE::DRIVE::SPEED_MIN, MODULE::DRIVE::SPEED_MAX);
    	int hyper_add = getRandInt(MODULE::DRIVE::HYPER_MIN, MODULE::DRIVE::HYPER_MAX);
    
        drive_module->SetTextureOb(texOb);
    	drive_module->SetSpeedAdd(speed_add);
	drive_module->SetHyperAdd(hyper_add);
}


