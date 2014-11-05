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

#include "DroidModuleBuilder.hpp"
#include "../../../items/modules/DroidModule.hpp"

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"

#include <resources/TextureCollector.hpp>
#include <resources/MeshCollector.hpp>
#include <jeti/TextureOb.hpp>

DroidModuleBuilder& DroidModuleBuilder::Instance()
{
    static DroidModuleBuilder instance;
    return instance;
}

DroidModuleBuilder::~DroidModuleBuilder()
{}

DroidModule* DroidModuleBuilder::GetNewDroidModuleTemplate(INTLONGEST id) const
{
    DroidModule* droid_module = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        droid_module = new DroidModule(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(droid_module);
    
    return droid_module;
} 
       
DroidModule* DroidModuleBuilder::GetNewDroidModule(int repair_add) const
{
    DroidModule* droid_module = GetNewDroidModuleTemplate();
    CreateNewInternals(droid_module, repair_add);
            
    return droid_module;
} 
     
void DroidModuleBuilder::CreateNewInternals(DroidModule* droid_module, int repair_add) const
{
    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    jeti::TextureOb* texOb = TextureCollector::Instance().GetRandomTextureOb(TYPE::TEXTURE::MODULE_ID);
    repair_add  = getRandInt(MODULE::DROID::REPAIR_MIN, MODULE::DROID::REPAIR_MAX);

    droid_module->SetParentSubTypeId(TYPE::ENTITY::DROID_EQUIPMENT_ID);    
    //alpitodorender droid_module->SetRenderData(mesh, texOb, texOb->GetSize());
    droid_module->SetRepairAdd(repair_add);
}


