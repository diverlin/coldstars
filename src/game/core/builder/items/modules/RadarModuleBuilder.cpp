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

#include "RadarModuleBuilder.hpp"
#include <items/modules/RadarModule.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include "../../../common/Global.hpp"

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

RadarModuleBuilder& RadarModuleBuilder::Instance()
{
    static RadarModuleBuilder instance;
    return instance;
}

RadarModuleBuilder::~RadarModuleBuilder()
{}

RadarModule* RadarModuleBuilder::GetNewRadarModuleTemplate(INTLONGEST id) const
{
    RadarModule* radar_module = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        radar_module = new RadarModule(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    global::get().entitiesManager().RegisterEntity(radar_module);
    
    return radar_module;
} 

RadarModule* RadarModuleBuilder::GetNewRadarModule(int radius_add) const
{
    RadarModule* radar_module = GetNewRadarModuleTemplate();
    CreateNewInternals(radar_module, radius_add);    
        
    return radar_module;
} 
            
void RadarModuleBuilder::CreateNewInternals(RadarModule* radar_module, int radius_add) const
{  
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    radius_add  = meti::getRandInt(MODULE::RADAR::RADIUS_MIN, MODULE::RADAR::RADIUS_MAX);

    radar_module->SetParentSubTypeId(TYPE::ENTITY::RADAR_EQUIPMENT_ID);    
    //alpitodorender radar_module->SetRenderData(mesh, texOb, texOb->size());
    radar_module->SetRadiusAdd(radius_add);
}

