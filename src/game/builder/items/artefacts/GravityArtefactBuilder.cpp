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


#include "GravityArtefactBuilder.hpp"
#include "../../../items/artefacts/GravityArtefact.hpp"

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <common/rand.hpp>
#include <common/constants.hpp>

#include "../../../world/EntityManager.hpp"
#include "../../../resources/TextureManager.hpp"

#include <struct/RaceInformationCollector.hpp>


GravityArtefactBuilder& GravityArtefactBuilder::Instance()
{
	static GravityArtefactBuilder instance;
	return instance;
}

GravityArtefactBuilder::~GravityArtefactBuilder()
{}

GravityArtefact* GravityArtefactBuilder::GetNewGravityArtefactTemplate(INTLONGEST id) const
{
	GravityArtefact* gravity_artefact = nullptr;

	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        gravity_artefact = new GravityArtefact(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(gravity_artefact);
    
    return gravity_artefact;
} 
    
GravityArtefact* GravityArtefactBuilder::GetNewGravityArtefact(int gravity) const
{
	GravityArtefact* gravity_artefact = GetNewGravityArtefactTemplate();
	CreateNewInternals(gravity_artefact, gravity);	
        
    return gravity_artefact;
} 
    	
void GravityArtefactBuilder::CreateNewInternals(GravityArtefact* gravity_artefact, int gravity) const
{     
    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::BAK_EQUIPMENT_ID);    
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    gravity = getRandInt(ARTEFACT::GRAVITY::GRAVITYRATE_MIN, ARTEFACT::GRAVITY::GRAVITYRATE_MAX);

    ItemCommonData common_data;
    common_data.deterioration_normal = 1;

    gravity_artefact->SetGravity(gravity);
    gravity_artefact->BindData2D(texOb_item);    	
    gravity_artefact->SetParentSubTypeId(TYPE::ENTITY::ARTEFACT_SLOT_ID);
    gravity_artefact->SetItemCommonData(common_data);
    gravity_artefact->SetCondition(common_data.condition_max);
}


