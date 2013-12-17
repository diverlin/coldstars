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

#include "GrappleModuleBuilder.hpp"
#include "../../../items/modules/GrappleModule.hpp"

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"

#include <resources/TextureManager.hpp>
#include <resources/MeshCollector.hpp>
#include <resources/textureOb.hpp>

GrappleModuleBuilder& GrappleModuleBuilder::Instance()
{
    static GrappleModuleBuilder instance;
    return instance;
}

GrappleModuleBuilder::~GrappleModuleBuilder()
{}

GrappleModule* GrappleModuleBuilder::GetNewGrappleModuleTemplate(INTLONGEST id) const
{
    GrappleModule* grapple_module = nullptr;

    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        grapple_module = new GrappleModule(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(grapple_module);
    
    return grapple_module;
} 

GrappleModule* GrappleModuleBuilder::GetNewGrappleModule(int strength_add, int radius_add, int speed_add) const
{
    GrappleModule* grapple_module = GetNewGrappleModuleTemplate();
    CreateNewInternals(grapple_module, strength_add, radius_add, speed_add);
        
    return grapple_module;
} 
            
void GrappleModuleBuilder::CreateNewInternals(GrappleModule* grapple_module, int strength_add, int radius_add, int speed_add) const
{   
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);   
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::MODULE_ID);   
    strength_add   = getRandInt(MODULE::GRAPPLE::STRENGTH_MIN, MODULE::GRAPPLE::STRENGTH_MAX);
    radius_add     = getRandInt(MODULE::GRAPPLE::RADIUS_MIN, MODULE::GRAPPLE::RADIUS_MAX);
    speed_add      = getRandInt(MODULE::GRAPPLE::SPEED_MIN, MODULE::GRAPPLE::SPEED_MAX);

    grapple_module->SetParentSubTypeId(TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID);    
    grapple_module->SetRenderData(mesh, texOb, texOb->GetSize());
    grapple_module->SetStrengthAdd(strength_add);
    grapple_module->SetRadiusAdd(radius_add);
    grapple_module->SetSpeedAdd(speed_add);
}


