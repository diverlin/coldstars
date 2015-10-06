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
#include <items/modules/GrappleModule.hpp>
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

GrappleModuleBuilder::GrappleModuleBuilder()
{}

GrappleModuleBuilder::~GrappleModuleBuilder()
{}

GrappleModule* GrappleModuleBuilder::createTemplate(IDTYPE id) const
{
    GrappleModule* grapple_module = new GrappleModule(id);
    assert(grapple_module);

    global::get().entitiesManager().registerEntity(grapple_module);
    
    return grapple_module;
} 

GrappleModule* GrappleModuleBuilder::create(int strength_add, int radius_add, int speed_add) const
{
    GrappleModule* grapple_module = createTemplate();
    createInternals(grapple_module, strength_add, radius_add, speed_add);
        
    return grapple_module;
} 
            
void GrappleModuleBuilder::createInternals(GrappleModule* grapple_module, int strength_add, int radius_add, int speed_add) const
{   
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MODULE_ID);
    strength_add   = meti::getRandInt(MODULE::GRAPPLE::STRENGTH_MIN, MODULE::GRAPPLE::STRENGTH_MAX);
    radius_add     = meti::getRandInt(MODULE::GRAPPLE::RADIUS_MIN, MODULE::GRAPPLE::RADIUS_MAX);
    speed_add      = meti::getRandInt(MODULE::GRAPPLE::SPEED_MIN, MODULE::GRAPPLE::SPEED_MAX);

    grapple_module->setParentSubTypeId(TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID);    
    //alpitodorender grapple_module->SetRenderData(mesh, texOb, texOb->size());
    grapple_module->SetStrengthAdd(strength_add);
    grapple_module->SetRadiusAdd(radius_add);
    grapple_module->SetSpeedAdd(speed_add);
}


