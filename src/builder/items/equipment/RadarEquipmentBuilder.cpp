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


RadarEquipmentBuilder& RadarEquipmentBuilder::Instance()
{
	static RadarEquipmentBuilder instance;
	return instance;
}

RadarEquipmentBuilder::~RadarEquipmentBuilder()
{}

void RadarEquipmentBuilder::CreateNewRadarEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
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
} 
        	
void RadarEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::RADAR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	int radius_orig     = getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::RADAR::MASS_MIN,        EQUIPMENT::RADAR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::RADAR::CONDITION_MIN,   EQUIPMENT::RADAR::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        radar_equipment->SetRadiusOrig(radius_orig);
        radar_equipment->SetTextureOb(texOb_item);
        radar_equipment->SetFunctionalSlotSubTypeId(ITEMSLOT::RADAR_ID);
        radar_equipment->SetItemCommonData(common_data);
        
 
    	radar_equipment->UpdatePropetries();
    	radar_equipment->CountPrice();
}


