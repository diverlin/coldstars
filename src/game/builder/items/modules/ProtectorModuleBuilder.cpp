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

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"

#include <resources/TextureManager.hpp>
#include <resources/MeshCollector.hpp>
#include <resources/textureOb.hpp>

ProtectorModuleBuilder& ProtectorModuleBuilder::Instance()
{
    static ProtectorModuleBuilder instance;
    return instance;
}

ProtectorModuleBuilder::~ProtectorModuleBuilder()
{}

ProtectorModule* ProtectorModuleBuilder::GetNewProtectorModuleTemplate(INTLONGEST id) const
{
    ProtectorModule* protector_module = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
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
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);   
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::MODULE_ID);   
    protection_add = getRandInt(MODULE::PROTECTOR::PROTECTION_MIN, MODULE::PROTECTOR::PROTECTION_MAX);
    
    protector_module->SetParentSubTypeId(TYPE::ENTITY::PROTECTOR_EQUIPMENT_ID);    
    //alpitodorender protector_module->SetRenderData(mesh, texOb, texOb->GetSize());
    protector_module->SetProtectionAdd(protection_add);
}


