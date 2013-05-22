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

#include "RadarEquipmentBuilder.hpp"
#include "../../../items/equipment/RadarEquipment.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../common/Logger.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

RadarEquipmentBuilder& RadarEquipmentBuilder::Instance()
{
	static RadarEquipmentBuilder instance;
	return instance;
}

RadarEquipmentBuilder::~RadarEquipmentBuilder()
{}

RadarEquipment* RadarEquipmentBuilder::GetNewRadarEquipmentTemplate(unsigned long int id) const
{
	RadarEquipment* radar_equipment = NULL;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

       	try 
        { 
		radar_equipment = new RadarEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(radar_equipment);
        
        return radar_equipment;
} 
  
RadarEquipment* RadarEquipmentBuilder::GetNewRadarEquipment(int tech_level, int race_id, int radius_orig) const
{
	RadarEquipment* radar_equipment = GetNewRadarEquipmentTemplate();
	CreateNewInternals(radar_equipment, tech_level, race_id, radius_orig);
        
        return radar_equipment;
} 
    	
void RadarEquipmentBuilder::CreateNewInternals(RadarEquipment* radar_equipment, int tech_level, int race_id, int radius_orig) const
{     
        if (race_id == NONE_ID)
        {
       		race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    	if (tech_level == NONE_ID)
    	{
       		tech_level = 1; 
	}

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::RADAR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	radius_orig     = getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX) * (1 + EQUIPMENT::RADAR::RADIUS_TECHLEVEL_RATE * tech_level);
    	
    	ItemCommonData common_data;
        common_data.tech_level      = tech_level;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::RADAR::MASS_MIN,        EQUIPMENT::RADAR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::RADAR::CONDITION_MIN,   EQUIPMENT::RADAR::CONDITION_MAX);
    	common_data.deterioration_normal = 1;

        radar_equipment->SetRadiusOrig(radius_orig);
        radar_equipment->BindData2D(texOb_item);
        radar_equipment->SetParentSubTypeId(ENTITY::RADAR_SLOT_ID);
        radar_equipment->SetItemCommonData(common_data);
        radar_equipment->SetCondition(common_data.condition_max);
 
    	radar_equipment->UpdateProperties();
    	radar_equipment->CountPrice();
}


