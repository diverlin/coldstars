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

#include "ScanerEquipmentBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/textureManager.hpp"

ScanerEquipmentBuilder& ScanerEquipmentBuilder::Instance()
{
	static ScanerEquipmentBuilder instance;
	return instance;
}

ScanerEquipmentBuilder::~ScanerEquipmentBuilder()
{}

void ScanerEquipmentBuilder::CreateNewScanerEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

	try 
        { 
        	scaner_equipment = new ScanerEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(scaner_equipment);
} 
        	
void ScanerEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::SCANER_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::SCANER_EQUIPMENT_ID, revision_id)

    	int scan_orig       = getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::SCANER::MODULES_NUM_MIN, EQUIPMENT::SCANER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::SCANER::MASS_MIN,        EQUIPMENT::SCANER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::SCANER::CONDITION_MIN,   EQUIPMENT::SCANER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;
        
        scaner_equipment->SetScanOrig(scan_orig);  
        scaner_equipment->SetTextureOb(texOb_item);    	
        scaner_equipment->SetFunctionalSlotSubTypeId(ENTITY::SCANER_SLOT_ID);
        scaner_equipment->SetItemCommonData(common_data);
        scaner_equipment->SetCondition(common_data.condition_max);
                   
    	scaner_equipment->UpdatePropetries();
    	scaner_equipment->CountPrice();
}


