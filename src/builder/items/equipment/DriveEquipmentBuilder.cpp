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

#include "DriveEquipmentBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

DriveEquipmentBuilder& DriveEquipmentBuilder::Instance()
{
	static DriveEquipmentBuilder instance;
	return instance;
}

DriveEquipmentBuilder::~DriveEquipmentBuilder()
{}

void DriveEquipmentBuilder::CreateNewDriveEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	drive_equipment = new DriveEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(drive_equipment);
} 
        	
void DriveEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
        if (race_id == -1)
                race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

        if (revision_id == -1)
                revision_id = TECHLEVEL::L0_ID; 

        int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

        TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::DRIVE_EQUIPMENT_ID);   
        //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::DRIVE_EQUIPMENT_ID, revision_id) 

        int speed_orig      = getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX);
        int hyper_orig      = getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX);
    
        ItemCommonData common_data;
        common_data.modules_num_max = getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
        common_data.mass            = getRandInt(EQUIPMENT::DRIVE::MASS_MIN,        EQUIPMENT::DRIVE::MASS_MAX);
        common_data.condition_max   = getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN,   EQUIPMENT::DRIVE::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_normal = 1;
    	common_data.deterioration_overload_rate = EQUIPMENT::DRIVE::OVERLOAD_DETERIORATION_RATE;
    
        drive_equipment->SetSpeedOrig(speed_orig);  
        drive_equipment->SetHyperOrig(hyper_orig);
        drive_equipment->SetTextureOb(texOb_item);    	
        drive_equipment->SetFunctionalSlotSubTypeId(ENTITY::DRIVE_SLOT_ID);
        drive_equipment->SetItemCommonData(common_data);
        drive_equipment->SetCondition(common_data.condition_max);
        
        drive_equipment->UpdatePropetries();
     	drive_equipment->CountPrice();
}


