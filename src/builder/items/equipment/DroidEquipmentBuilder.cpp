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


DroidEquipmentBuilder& DroidEquipmentBuilder::Instance()
{
	static DroidEquipmentBuilder instance;
	return instance;
}

DroidEquipmentBuilder::~DroidEquipmentBuilder()
{}

void DroidEquipmentBuilder::CreateNewDroidEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	droid_equipment = new DroidEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(droid_equipment);
} 
        	
void DroidEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
       	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::DROID_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::DROID_EQUIPMENT_ID, revision_id)

    	int repair_orig     = getRandInt(EQUIPMENT::DROID::REPAIR_MIN, EQUIPMENT::DROID::REPAIR_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::DROID::MODULES_NUM_MIN, EQUIPMENT::DROID::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::DROID::MASS_MIN,        EQUIPMENT::DROID::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::DROID::CONDITION_MIN,   EQUIPMENT::DROID::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;
       
        droid_equipment->SetRepairOrig(repair_orig);  
        droid_equipment->SetTextureOb(texOb_item);    	
        droid_equipment->SetFunctionalSlotSubTypeId(ITEMSLOT::DROID_ID);
        droid_equipment->SetItemCommonData(common_data);
        droid_equipment->SetCondition(common_data.condition_max);
                
    	droid_equipment->UpdatePropetries();
    	droid_equipment->CountPrice();
}


