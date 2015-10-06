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
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include "../../../common/Global.hpp"

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

RadarModuleBuilder::RadarModuleBuilder()
{}

RadarModuleBuilder::~RadarModuleBuilder()
{}

RadarModule* RadarModuleBuilder::createTemplate(ID id) const
{  
    RadarModule* radar_module = new RadarModule(id);
    assert(radar_module);

    global::get().entitiesManager().reg(radar_module);
    
    return radar_module;
} 

RadarModule* RadarModuleBuilder::create(int radius_add) const
{
    RadarModule* radar_module = createTemplate();
    createInternals(radar_module, radius_add);
        
    return radar_module;
} 
            
void RadarModuleBuilder::createInternals(RadarModule* radar_module, int radius_add) const
{  
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    radius_add  = meti::getRandInt(MODULE::RADAR::RADIUS_MIN, MODULE::RADAR::RADIUS_MAX);

    radar_module->setParentSubTypeId(TYPE::ENTITY::RADAR_EQUIPMENT_ID);    
    //alpitodorender radar_module->SetRenderData(mesh, texOb, texOb->size());
    radar_module->SetRadiusAdd(radius_add);
}
