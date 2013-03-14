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
#include "../../../items/equipment/DriveEquipment.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../common/Logger.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

DriveEquipmentBuilder& DriveEquipmentBuilder::Instance()
{
	static DriveEquipmentBuilder instance;
	return instance;
}

DriveEquipmentBuilder::~DriveEquipmentBuilder()
{}

DriveEquipment* DriveEquipmentBuilder::GetNewDriveEquipmentTemplate(unsigned long int id) const
{
	DriveEquipment* drive_equipment = NULL;
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
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
        
        return drive_equipment;
} 
        
DriveEquipment* DriveEquipmentBuilder::GetNewDriveEquipment(int tech_level, int race_id, int speed_orig, int hyper_orig) const
{
	DriveEquipment* drive_equipment = GetNewDriveEquipmentTemplate();
	CreateNewInternals(drive_equipment, tech_level, race_id, speed_orig, hyper_orig);
        
        return drive_equipment;
}        
        	
void DriveEquipmentBuilder::CreateNewInternals(DriveEquipment* drive_equipment, int tech_level, int race_id, int speed_orig, int hyper_orig) const
{     
        if (race_id == NONE_ID)
        {
       		race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    	if (tech_level == NONE_ID)
    	{
       		tech_level = 1; 
	}

        TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::DRIVE_EQUIPMENT_ID);   
        //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::DRIVE_EQUIPMENT_ID, revision_id) 

        speed_orig      = getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX) * (1 + EQUIPMENT::DRIVE::SPEED_TECHLEVEL_RATE*tech_level);
        hyper_orig      = getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX) * (1 + EQUIPMENT::DRIVE::HYPER_TECHLEVEL_RATE*tech_level);
    
        ItemCommonData common_data;
        common_data.tech_level 		= tech_level;
        common_data.modules_num_max 	= getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
        common_data.mass            	= getRandInt(EQUIPMENT::DRIVE::MASS_MIN,        EQUIPMENT::DRIVE::MASS_MAX);
        common_data.condition_max   	= getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN,   EQUIPMENT::DRIVE::CONDITION_MAX);
    	common_data.deterioration_normal = 1;
    	common_data.deterioration_overload_rate = EQUIPMENT::DRIVE::OVERLOAD_DETERIORATION_RATE;
    
        drive_equipment->SetSpeedOrig(speed_orig);  
        drive_equipment->SetHyperOrig(hyper_orig);
        drive_equipment->SetTextureOb(texOb_item);    	
        drive_equipment->SetParentSubTypeId(ENTITY::DRIVE_SLOT_ID);
        drive_equipment->SetItemCommonData(common_data);
        drive_equipment->SetCondition(common_data.condition_max);
        
        drive_equipment->UpdateProperties();
     	drive_equipment->CountPrice();
}


