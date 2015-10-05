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
#include <items/modules/ScanerModule.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

ScanerModuleBuilder::ScanerModuleBuilder()
{}

ScanerModuleBuilder::~ScanerModuleBuilder()
{}

ScanerModule* ScanerModuleBuilder::createTemplate(INTLONGEST id) const
{
    ScanerModule* scaner_module = new ScanerModule(id);
    assert(scaner_module);

    global::get().entitiesManager().RegisterEntity(scaner_module);
    
    return scaner_module;
} 

ScanerModule* ScanerModuleBuilder::create(int scan_add) const
{
    ScanerModule* scaner_module = createTemplate();
    createInternals(scaner_module, scan_add);
        
    return scaner_module;
} 
           
void ScanerModuleBuilder::createInternals(ScanerModule* scaner_module, int scan_add) const
{  
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    scan_add = meti::getRandInt(MODULE::SCANER::SCAN_MIN, MODULE::SCANER::SCAN_MAX);

    scaner_module->setParentSubTypeId(TYPE::ENTITY::SCANER_EQUIPMENT_ID);    
    //alpitodorender scaner_module->SetRenderData(mesh, texOb, texOb->size());
    scaner_module->SetScanAdd(scan_add);
}
