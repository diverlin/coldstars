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

#include "FreezerEquipmentBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/textureManager.hpp"

FreezerEquipmentBuilder& FreezerEquipmentBuilder::Instance()
{
	static FreezerEquipmentBuilder instance;
	return instance;
}

FreezerEquipmentBuilder::~FreezerEquipmentBuilder()
{}

void FreezerEquipmentBuilder::CreateNewFreezerEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

 	try 
        { 
        	freezer_equipment = new FreezerEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(freezer_equipment);
} 
        	
void FreezerEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::FREEZER_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	int freeze_orig     = getRandInt(EQUIPMENT::FREEZER::FREEZE_MIN, EQUIPMENT::FREEZER::FREEZE_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::FREEZER::MODULES_NUM_MIN, EQUIPMENT::FREEZER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::FREEZER::MASS_MIN,        EQUIPMENT::FREEZER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::FREEZER::CONDITION_MIN,   EQUIPMENT::FREEZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;
        
        freezer_equipment->SetFreezeOrig(freeze_orig);  
        freezer_equipment->SetTextureOb(texOb_item);    	
        freezer_equipment->SetFunctionalSlotSubTypeId(ENTITY::FREEZER_SLOT_ID);
        freezer_equipment->SetItemCommonData(common_data);
        freezer_equipment->SetCondition(common_data.condition_max);
          
      	freezer_equipment->UpdatePropetries();
    	freezer_equipment->CountPrice();
}


