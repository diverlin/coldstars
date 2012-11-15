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
#include "../../../items/equipment/FreezerEquipment.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

FreezerEquipmentBuilder& FreezerEquipmentBuilder::Instance()
{
	static FreezerEquipmentBuilder instance;
	return instance;
}

FreezerEquipmentBuilder::~FreezerEquipmentBuilder()
{}

FreezerEquipment* FreezerEquipmentBuilder::GetNewFreezerEquipmentTemplate(int id) const
{
	FreezerEquipment* freezer_equipment = NULL;

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
        
        return freezer_equipment;
} 
    
FreezerEquipment* FreezerEquipmentBuilder::GetNewFreezerEquipment(int tech_level, int race_id, int freeze_orig) const
{
	FreezerEquipment* freezer_equipment = GetNewFreezerEquipmentTemplate();
        CreateNewInternals(freezer_equipment, tech_level, race_id, freeze_orig);
        
        return freezer_equipment;
} 
    	
void FreezerEquipmentBuilder::CreateNewInternals(FreezerEquipment* freezer_equipment, int tech_level, int race_id, int freeze_orig) const
{     
        if (race_id == NONE_ID)
        {
       		race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    	if (tech_level == NONE_ID)
    	{
       		tech_level = 1; 
	}

	float tech_rate = 1.0f;
	if (tech_level > 1)
	{
		tech_rate = tech_level * EQUIPMENT::TECHLEVEL_RATE;
	}
	
    	tech_rate *= 1; //getRaceTechRate(race_id); 

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::FREEZER_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	freeze_orig     = getRandInt(EQUIPMENT::FREEZER::FREEZE_MIN, EQUIPMENT::FREEZER::FREEZE_MAX);
    	
    	ItemCommonData common_data;
    	common_data.tech_level 	    = tech_level;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::FREEZER::MODULES_NUM_MIN, EQUIPMENT::FREEZER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::FREEZER::MASS_MIN,        EQUIPMENT::FREEZER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::FREEZER::CONDITION_MIN,   EQUIPMENT::FREEZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_normal = 1;
        
        freezer_equipment->SetFreezeOrig(freeze_orig);  
        freezer_equipment->SetTextureOb(texOb_item);    	
        freezer_equipment->SetParentSubTypeId(ENTITY::FREEZER_SLOT_ID);
        freezer_equipment->SetItemCommonData(common_data);
        freezer_equipment->SetCondition(common_data.condition_max);
          
      	freezer_equipment->UpdatePropetries();
    	freezer_equipment->CountPrice();
}


