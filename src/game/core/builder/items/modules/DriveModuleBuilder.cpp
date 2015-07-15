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
#include <items/modules/DriveModule.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>
//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <meti/RandUtils.hpp>

DriveModuleBuilder& DriveModuleBuilder::Instance()
{
    static DriveModuleBuilder instance;
    return instance;
}

DriveModuleBuilder::~DriveModuleBuilder()
{}

DriveModule* DriveModuleBuilder::GetNewDriveModuleTemplate(INTLONGEST id) const
{
    DriveModule* drive_module = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

        try 
        { 
            drive_module = new DriveModule(id);
        }
        catch(std::bad_alloc)
        {
            Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        global::get().entitiesManager().RegisterEntity(drive_module);
        
        return drive_module;
} 

DriveModule* DriveModuleBuilder::GetNewDriveModule(int speed_add, int hyper_add) const
{
    DriveModule* drive_module = GetNewDriveModuleTemplate();
    CreateNewInternals(drive_module, speed_add, hyper_add);
        
        return drive_module;
} 
            
void DriveModuleBuilder::CreateNewInternals(DriveModule* drive_module, int speed_add, int hyper_add) const
{     
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    speed_add = meti::getRandInt(MODULE::DRIVE::SPEED_MIN, MODULE::DRIVE::SPEED_MAX);
    hyper_add = meti::getRandInt(MODULE::DRIVE::HYPER_MIN, MODULE::DRIVE::HYPER_MAX);
    
    drive_module->SetParentSubTypeId(TYPE::ENTITY::DRIVE_EQUIPMENT_ID);    
    //alpitodorender drive_module->SetRenderData(mesh, texOb, texOb->size());
    drive_module->SetSpeedAdd(speed_add);
    drive_module->SetHyperAdd(hyper_add);
}


