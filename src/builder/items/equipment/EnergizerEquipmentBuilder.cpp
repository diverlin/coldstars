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

#include "EnergizerEquipmentBuilder.hpp"
#include "../../../common/id.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/EntityManager.hpp"
#include "../../../common/rand.hpp"
#include "../../../resources/TextureManager.hpp"

EnergizerEquipmentBuilder& EnergizerEquipmentBuilder::Instance()
{
	static EnergizerEquipmentBuilder instance;
	return instance;
}

EnergizerEquipmentBuilder::~EnergizerEquipmentBuilder()
{}

void EnergizerEquipmentBuilder::CreateNewEnergizerEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

 	try 
        { 
        	energizer_equipment = new EnergizerEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(energizer_equipment);
} 
        	
void EnergizerEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
        if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ENERGIZER_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(ENERGIZER_ITEM_TEXTURE_ID, revision_id)

    	int energy_max_orig  = getRandInt(EQUIPMENT::ENERGIZER::ENERGY_MIN,      EQUIPMENT::ENERGIZER::ENERGY_MAX);
    	int restoration_orig = getRandInt(EQUIPMENT::ENERGIZER::RESTORATION_MIN, EQUIPMENT::ENERGIZER::RESTORATION_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max  = getRandInt(EQUIPMENT::ENERGIZER::MODULES_NUM_MIN, EQUIPMENT::ENERGIZER::MODULES_NUM_MAX);
    	common_data.mass             = getRandInt(EQUIPMENT::ENERGIZER::MASS_MIN,        EQUIPMENT::ENERGIZER::MASS_MAX);
    	common_data.condition_max    = getRandInt(EQUIPMENT::ENERGIZER::CONDITION_MIN,   EQUIPMENT::ENERGIZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_normal = 1;

        energizer_equipment->SetEnergyMaxOrig(energy_max_orig);
        energizer_equipment->SetRestorationOrig(restoration_orig);
        energizer_equipment->SetEnergy(energy_max_orig);
        energizer_equipment->SetTextureOb(texOb_item);    	
        energizer_equipment->SetFunctionalSlotSubTypeId(ENTITY::ENERGIZER_SLOT_ID);
        energizer_equipment->SetItemCommonData(common_data);
        energizer_equipment->SetCondition(common_data.condition_max);
                        
        energizer_equipment->UpdatePropetries();
    	energizer_equipment->CountPrice();
}


