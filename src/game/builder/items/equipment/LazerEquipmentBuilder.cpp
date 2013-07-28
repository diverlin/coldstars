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

#include "LazerEquipmentBuilder.hpp"
#include "../../../items/equipment/LazerEquipment.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../common/Logger.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

LazerEquipmentBuilder& LazerEquipmentBuilder::Instance()
{
	static LazerEquipmentBuilder instance;
	return instance;
}

LazerEquipmentBuilder::~LazerEquipmentBuilder()
{}

LazerEquipment* LazerEquipmentBuilder::GetNewLazerEquipmentTemplate(INTLONGEST id) const
{
	LazerEquipment* lazer_equipment = nullptr; 
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        lazer_equipment = new LazerEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }

    EntityManager::Instance().RegisterEntity(lazer_equipment);
    
    return lazer_equipment;
} 
      
LazerEquipment* LazerEquipmentBuilder::GetNewLazerEquipment(int tech_level, TYPE::RACE race_id, int damage_orig, int radius_orig) const
{
	LazerEquipment* lazer_equipment = GetNewLazerEquipmentTemplate(); 
	CreateNewInternals(lazer_equipment, tech_level, race_id, damage_orig, radius_orig);
        
    return lazer_equipment;
} 
  	
void LazerEquipmentBuilder::CreateNewInternals(LazerEquipment* lazer_equipment, int tech_level, TYPE::RACE race_id, int damage_orig, int radius_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    if (tech_level == NONE_ID)
    {
        tech_level = 1; 
	}

    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::LAZER_EQUIPMENT_ID, revision_id)
    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::LAZER_EQUIPMENT_ID);     

    damage_orig     = getRandInt(EQUIPMENT::LAZER::DAMAGE_MIN, EQUIPMENT::LAZER::DAMAGE_MAX) * (1 + EQUIPMENT::LAZER::DAMAGE_TECHLEVEL_RATE * tech_level);
    radius_orig     = getRandInt(EQUIPMENT::LAZER::RADIUS_MIN, EQUIPMENT::LAZER::RADIUS_MAX) * (1 + EQUIPMENT::LAZER::RADIUS_TECHLEVEL_RATE * tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level 	    = tech_level;
    common_data.modules_num_max = getRandInt(EQUIPMENT::LAZER::MODULES_NUM_MIN, EQUIPMENT::LAZER::MODULES_NUM_MAX);
    common_data.mass            = getRandInt(EQUIPMENT::LAZER::MASS_MIN, EQUIPMENT::LAZER::MASS_MAX);
    common_data.condition_max   = getRandInt(EQUIPMENT::LAZER::CONDITION_MIN, EQUIPMENT::LAZER::CONDITION_MAX);
    common_data.deterioration_normal = 1;
                                                   
    lazer_equipment->SetDamageOrig(damage_orig);  
    lazer_equipment->SetRadiusOrig(radius_orig);  
    lazer_equipment->BindData2D(texOb_item);    	
    lazer_equipment->SetParentSubTypeId(TYPE::ENTITY::WEAPON_SLOT_ID);
    lazer_equipment->SetItemCommonData(common_data);
    lazer_equipment->SetCondition(common_data.condition_max);
                
   	lazer_equipment->UpdateProperties();
   	lazer_equipment->CountPrice();
}


