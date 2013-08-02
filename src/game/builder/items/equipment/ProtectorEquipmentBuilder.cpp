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


#include <builder/items/equipment/ProtectorEquipmentBuilder.hpp>
#include <items/equipment/ProtectorEquipment.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>
#include <common/rand.hpp>
#include <common/constants.hpp>

#include <world/EntityManager.hpp>
#include <resources/TextureManager.hpp>
#include <resources/MeshCollector.hpp>

#include <struct/RaceInformationCollector.hpp>

ProtectorEquipmentBuilder& ProtectorEquipmentBuilder::Instance()
{
	static ProtectorEquipmentBuilder instance;
	return instance;
}

ProtectorEquipmentBuilder::~ProtectorEquipmentBuilder()
{}

ProtectorEquipment* ProtectorEquipmentBuilder::GetNewProtectorEquipmentTemplate(INTLONGEST id) const
{
	ProtectorEquipment* protector_equipment = nullptr;

	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

	try 
    { 
        protector_equipment = new ProtectorEquipment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(protector_equipment);
    
    return protector_equipment;
} 
   
ProtectorEquipment* ProtectorEquipmentBuilder::GetNewProtectorEquipment(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int protection_orig) const
{
	ProtectorEquipment* protector_equipment = GetNewProtectorEquipmentTemplate();
	CreateNewInternals(protector_equipment, tech_level, race_id, protection_orig);
        
    return protector_equipment;
} 
     	
void ProtectorEquipmentBuilder::CreateNewInternals(ProtectorEquipment* protector_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int protection_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID)
    {
        race_id = getRand(RaceInformationCollector::Instance().RACES_GOOD_vec);
	}
	
    if (tech_level == TYPE::TECHLEVEL::NONE_ID)
    {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
	}

    TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID, revision_id) 

    protection_orig = getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX) * (1 + EQUIPMENT::PROTECTOR::PROTECTION_TECHLEVEL_RATE * (int)tech_level);
    
    ItemCommonData common_data;
    common_data.tech_level 	    = tech_level;
    common_data.modules_num_max = getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    common_data.mass            = getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN,        EQUIPMENT::PROTECTOR::MASS_MAX);
    common_data.condition_max   = getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN,   EQUIPMENT::PROTECTOR::CONDITION_MAX);
    common_data.deterioration_normal = 1;

    protector_equipment->SetProtectionOrig(protection_orig);  
    protector_equipment->BindData2D(texOb_item);
    protector_equipment->SetParentSubTypeId(TYPE::ENTITY::PROTECTOR_SLOT_ID);
    protector_equipment->SetItemCommonData(common_data);
    protector_equipment->SetCondition(common_data.condition_max);
            
    protector_equipment->UpdateProperties();
    protector_equipment->CountPrice();
}


