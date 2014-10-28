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

#include "LazerModuleBuilder.hpp"
#include "../../../items/modules/LazerModule.hpp"

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"

#include <resources/TextureManager.hpp>
#include <resources/MeshCollector.hpp>
#include <render/textureOb.hpp>


LazerModuleBuilder& LazerModuleBuilder::Instance()
{
    static LazerModuleBuilder instance;
    return instance;
}

LazerModuleBuilder::~LazerModuleBuilder()
{}

LazerModule* LazerModuleBuilder::GetNewLazerModuleTemplate(INTLONGEST id) const
{
    LazerModule* lazer_module = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        lazer_module = new LazerModule(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(lazer_module);
    
    return lazer_module;
} 

LazerModule* LazerModuleBuilder::GetNewLazerModule(int damage_add, int radius_add) const
{
    LazerModule* lazer_module = GetNewLazerModuleTemplate();
    CreateNewInternals(lazer_module, damage_add, radius_add);
        
    return lazer_module;
} 
            
void LazerModuleBuilder::CreateNewInternals(LazerModule* lazer_module, int damage_add, int radius_add) const
{  
    jeti::Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);
    jeti::TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::MODULE_ID);
  
    damage_add = getRandInt(MODULE::LAZER::DAMAGE_MIN, MODULE::LAZER::DAMAGE_MAX);
    radius_add = getRandInt(MODULE::LAZER::RADIUS_MIN, MODULE::LAZER::RADIUS_MAX);

    lazer_module->SetParentSubTypeId(TYPE::ENTITY::LAZER_EQUIPMENT_ID);    
    //alpitodorender lazer_module->SetRenderData(mesh, texOb, texOb->GetSize());
    lazer_module->SetDamageAdd(damage_add);
    lazer_module->SetRadiusAdd(radius_add);
}


