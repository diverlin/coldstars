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
#include "../../../common/id.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

GrappleModuleBuilder& GrappleModuleBuilder::Instance()
{
	static GrappleModuleBuilder instance;
	return instance;
}

GrappleModuleBuilder::~GrappleModuleBuilder()
{}

void GrappleModuleBuilder::CreateNewGrappleModule(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
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
} 
        	
void GrappleModuleBuilder::CreateNewInternals()
{     
    	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::MODULE_ID);   
    	int strength_add   = getRandInt(MODULE::GRAPPLE::STRENGTH_MIN, MODULE::GRAPPLE::STRENGTH_MAX);
    	int radius_add     = getRandInt(MODULE::GRAPPLE::RADIUS_MIN, MODULE::GRAPPLE::RADIUS_MAX);
    	int speed_add      = getRandInt(MODULE::GRAPPLE::SPEED_MIN, MODULE::GRAPPLE::SPEED_MAX);
    
        grapple_module->SetTextureOb(texOb);
        grapple_module->SetStrengthAdd(strength_add);
        grapple_module->SetRadiusAdd(radius_add);
        grapple_module->SetSpeedAdd(speed_add);
}


