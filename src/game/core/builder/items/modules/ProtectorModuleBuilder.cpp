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
#include <items/modules/ProtectorModule.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../common/Global.hpp"

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <meti/RandUtils.hpp>

ProtectorModuleBuilder::ProtectorModuleBuilder()
{}

ProtectorModuleBuilder::~ProtectorModuleBuilder()
{}

ProtectorModule* ProtectorModuleBuilder::createTemplate(ID id) const
{
    ProtectorModule* protector_module = new ProtectorModule(id);
    assert(protector_module);

    global::get().entitiesManager().registerEntity(protector_module);
    
    return protector_module;
} 

ProtectorModule* ProtectorModuleBuilder::create(int protection_add) const
{
    ProtectorModule* protector_module = createTemplate();
    createInternals(protector_module, protection_add);

    return protector_module;
} 

void ProtectorModuleBuilder::createInternals(ProtectorModule* protector_module, int protection_add) const
{     
    //    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    protection_add = meti::getRandInt(MODULE::PROTECTOR::PROTECTION_MIN, MODULE::PROTECTOR::PROTECTION_MAX);
    
    protector_module->setParentSubTypeId(TYPE::ENTITY::PROTECTOR_EQUIPMENT_ID);
    //alpitodorender protector_module->SetRenderData(mesh, texOb, texOb->size());
    protector_module->SetProtectionAdd(protection_add);
}
