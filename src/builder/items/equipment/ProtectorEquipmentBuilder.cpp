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


ProtectorEquipmentBuilder& ProtectorEquipmentBuilder::Instance()
{
	static ProtectorEquipmentBuilder instance;
	return instance;
}

ProtectorEquipmentBuilder::~ProtectorEquipmentBuilder()
{}

void ProtectorEquipmentBuilder::CreateNewProtectorEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        protector_equipment = new ProtectorEquipment(id);
        EntityManager::Instance().RegisterEntity(protector_equipment);
} 
        	
void ProtectorEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::PROTECTOR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, revision_id) 

    	int protection_orig = getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN,        EQUIPMENT::PROTECTOR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN,   EQUIPMENT::PROTECTOR::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        protector_equipment->SetProtectionOrig(protection_orig);  
        protector_equipment->SetTextureOb(texOb_item);
        protector_equipment->SetFunctionalSlotSubTypeId(SLOT::PROTECTOR_ID);
        protector_equipment->SetItemCommonData(common_data);
        
        protector_equipment->UpdatePropetries();
    	protector_equipment->CountPrice();
}


