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
#include "../../../items/equipment/ScanerEquipment.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../managers/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

ScanerEquipmentBuilder& ScanerEquipmentBuilder::Instance()
{
	static ScanerEquipmentBuilder instance;
	return instance;
}

ScanerEquipmentBuilder::~ScanerEquipmentBuilder()
{}

ScanerEquipment* ScanerEquipmentBuilder::GetNewScanerEquipmentTemplate(int id) const
{
	ScanerEquipment* scaner_equipment = NULL;

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
        
        return scaner_equipment;
} 

ScanerEquipment* ScanerEquipmentBuilder::GetNewScanerEquipment(int tech_level, int race_id, int scan_orig) const
{
	ScanerEquipment* scaner_equipment = GetNewScanerEquipmentTemplate();
	CreateNewInternals(scaner_equipment, tech_level, race_id, scan_orig);
        
        return scaner_equipment;
} 
        	
void ScanerEquipmentBuilder::CreateNewInternals(ScanerEquipment* scaner_equipment, int tech_level, int race_id, int scan_orig) const
{     
        if (race_id == NONE_ID)
        {
       		race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    	if (tech_level == NONE_ID)
    	{
       		tech_level = 1; 
	}

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::SCANER_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::SCANER_EQUIPMENT_ID, revision_id)

    	scan_orig       = getRandInt(EQUIPMENT::SCANER::SCAN_MIN, EQUIPMENT::SCANER::SCAN_MAX) * (1 + EQUIPMENT::SCANER::SCAN_TECHLEVEL_RATE * tech_level);
    	
    	ItemCommonData common_data;
        common_data.tech_level 	    = tech_level;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::SCANER::MODULES_NUM_MIN, EQUIPMENT::SCANER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::SCANER::MASS_MIN,        EQUIPMENT::SCANER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::SCANER::CONDITION_MIN,   EQUIPMENT::SCANER::CONDITION_MAX);
    	common_data.deterioration_normal = 1;
        
        scaner_equipment->SetScanOrig(scan_orig);  
        scaner_equipment->SetTextureOb(texOb_item);    	
        scaner_equipment->SetParentSubTypeId(ENTITY::SCANER_SLOT_ID);
        scaner_equipment->SetItemCommonData(common_data);
        scaner_equipment->SetCondition(common_data.condition_max);
                   
    	scaner_equipment->UpdateProperties();
    	scaner_equipment->CountPrice();
}


