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
#include <items/modules/BakModule.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../common/Global.hpp"

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <meti/RandUtils.hpp>

BakModuleBuilder& BakModuleBuilder::Instance()
{
    static BakModuleBuilder instance;
    return instance;
}

BakModuleBuilder::~BakModuleBuilder()
{}

BakModule* BakModuleBuilder::GetNewBakModuleTemplate(INTLONGEST id) const
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
    
    global::get().entitiesManager().RegisterEntity(bak_module);
    
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
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    fuel_max_add = meti::getRandInt(MODULE::BAK::FUEL_MIN, MODULE::BAK::FUEL_MAX);

    bak_module->SetParentSubTypeId(TYPE::ENTITY::BAK_EQUIPMENT_ID);    
    // alpitodorender bak_module->SetRenderData(mesh, texOb, texOb->size());
    bak_module->SetFuelMaxAdd(fuel_max_add);
}

