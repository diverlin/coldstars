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
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/textureManager.hpp"

GravityArtefactBuilder& GravityArtefactBuilder::Instance()
{
	static GravityArtefactBuilder instance;
	return instance;
}

GravityArtefactBuilder::~GravityArtefactBuilder()
{}

void GravityArtefactBuilder::CreateNewGravityArtefact(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
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
} 
        	
void GravityArtefactBuilder::CreateNewInternals()
{     
        //if (race_id == -1)
       		int race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	//if (revision_id == -1)
       		int revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BAK_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    	int gravity = getRandInt(ARTEFACT::GRAVITY::GRAVITYRATE_MIN, ARTEFACT::GRAVITY::GRAVITYRATE_MAX);

      	ItemCommonData common_data;

    	common_data.deterioration_rate = 1;

        gravity_artefact->SetGravity(gravity);
        gravity_artefact->SetTextureOb(texOb_item);    	
        gravity_artefact->SetFunctionalSlotSubTypeId(ENTITY::ARTEFACT_SLOT_ID);
        gravity_artefact->SetItemCommonData(common_data);
        gravity_artefact->SetCondition(common_data.condition_max);
}


