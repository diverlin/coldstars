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

#include "BakEquipmentBuilder.hpp"
#include "../../../items/equipment/BakEquipment.hpp"
#include "../../../common/IdGenerator.hpp"
#include "../../../common/Logger.hpp"
#include "../../../world/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../struct/gameStruct.hpp"
#include "../../../resources/TextureManager.hpp"

BakEquipmentBuilder& BakEquipmentBuilder::Instance()
{
	static BakEquipmentBuilder instance;
	return instance;
}

BakEquipmentBuilder::~BakEquipmentBuilder()
{}

BakEquipment* BakEquipmentBuilder::GetNewBakEquipmentTemplate(unsigned long int id) const
{
	BakEquipment* bak_equipment = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	bak_equipment = new BakEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(bak_equipment);
        
        return bak_equipment;
} 
       
BakEquipment* BakEquipmentBuilder::GetNewBakEquipment(int tech_level, TYPE::RACE race_id, int fuel_max) const
{
	BakEquipment* bak_equipment = GetNewBakEquipmentTemplate();
	CreateNewInternals(bak_equipment, tech_level, race_id, fuel_max);
	
	return bak_equipment;
}
                      	
void BakEquipmentBuilder::CreateNewInternals(BakEquipment* bak_equipment, int tech_level, TYPE::RACE race_id, int fuel_max_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    if (tech_level == NONE_ID)
    {
        tech_level = 1; 
	}

    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BAK_EQUIPMENT_ID);    
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    
    fuel_max_orig = getRandInt(EQUIPMENT::BAK::FUEL_MIN, EQUIPMENT::BAK::FUEL_MAX) * (1 + EQUIPMENT::BAK::FUEL_TECHLEVEL_RATE*tech_level);

    ItemCommonData common_data;
    common_data.tech_level 		= tech_level;
    common_data.modules_num_max    	= getRandInt(EQUIPMENT::BAK::MODULES_NUM_MIN, EQUIPMENT::BAK::MODULES_NUM_MAX);
    common_data.mass               	= getRandInt(EQUIPMENT::BAK::MASS_MIN, EQUIPMENT::BAK::MASS_MAX);
    common_data.condition_max      	= getRandInt(EQUIPMENT::BAK::CONDITION_MIN, EQUIPMENT::BAK::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    bak_equipment->SetFuelMaxOrig(fuel_max_orig);
    bak_equipment->SetFuel(fuel_max_orig);
    bak_equipment->BindData2D(texOb_item);    	
    bak_equipment->SetParentSubTypeId(TYPE::ENTITY::BAK_SLOT_ID);
    bak_equipment->SetItemCommonData(common_data);
    bak_equipment->SetCondition(common_data.condition_max);
                                    
    bak_equipment->UpdateProperties();
    bak_equipment->CountPrice();
}


