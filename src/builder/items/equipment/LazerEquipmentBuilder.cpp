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


LazerEquipmentBuilder& LazerEquipmentBuilder::Instance()
{
	static LazerEquipmentBuilder instance;
	return instance;
}

LazerEquipmentBuilder::~LazerEquipmentBuilder()
{}

void LazerEquipmentBuilder::CreateNewLazerEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
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
} 
        	
void LazerEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
     	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

   	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::LAZER_EQUIPMENT_ID, revision_id)
    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::LAZER_EQUIPMENT_ID);     

    	int damage_orig     = getRandInt(EQUIPMENT::LAZER::DAMAGE_MIN, EQUIPMENT::LAZER::DAMAGE_MAX);
    	int radius_orig     = getRandInt(EQUIPMENT::LAZER::RADIUS_MIN, EQUIPMENT::LAZER::RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::LAZER::MODULES_NUM_MIN, EQUIPMENT::LAZER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::LAZER::MASS_MIN, EQUIPMENT::LAZER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::LAZER::CONDITION_MIN, EQUIPMENT::LAZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;
                                                       
        lazer_equipment->SetDamageOrig(damage_orig);  
        lazer_equipment->SetRadiusOrig(radius_orig);  
        lazer_equipment->SetTextureOb(texOb_item);    	
        lazer_equipment->SetFunctionalSlotSubTypeId(ITEMSLOT::WEAPON_ID);
        lazer_equipment->SetItemCommonData(common_data);
        
   	lazer_equipment->UpdatePropetries();
   	lazer_equipment->CountPrice();
}


