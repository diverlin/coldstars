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


RadarEquipment :: RadarEquipment(int radius_orig)
{
    	this->radius_orig = radius_orig;
}


RadarEquipment :: ~RadarEquipment() /* virtual */
{}


int RadarEquipment :: getRadius() const { return radius; }


/* virtual */
void RadarEquipment :: updatePropetries()
{
    	radius_add  = 0;
    	
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	radius_add   += ((RadarModule*)modules_vec[i])->getRadiusAdd();        	
    	}
    	
    	radius = radius_orig + radius_add;
}

void RadarEquipment :: countPrice()
{
    	float radius_rate         = (float)radius_orig / EQUIPMENT::RADAR::RADIUS_MIN;

    	float modules_num_rate    = (float)data_item.modules_num_max / EQUIPMENT::RADAR::MODULES_NUM_MAX;

    	float effectiveness_rate  = EQUIPMENT::RADAR::RADIUS_WEIGHT * radius_rate + EQUIPMENT::RADAR::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate           = (float)data_item.mass / EQUIPMENT::RADAR::MASS_MIN;
    	float condition_rate      = (float)condition / data_item.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void RadarEquipment :: updateOwnerAbilities()
{
	slot->getOwnerVehicle()->UpdateRadarAbility();
}
      

void RadarEquipment :: addUniqueInfo()
{
    	info.addTitleStr("RADAR");
    	info.addNameStr("radius:");     info.addValueStr( getRadiusStr() );
}
     		
     		
std::string RadarEquipment :: getRadiusStr()
{
    	if (radius_add == 0)
        	return int2str(radius_orig);
    	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}


    

RadarEquipment* getNewRadarEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::RADAR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	int radius_orig     = getRandInt(EQUIPMENT::RADAR::RADIUS_MIN, EQUIPMENT::RADAR::RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::RADAR::MODULES_NUM_MIN, EQUIPMENT::RADAR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::RADAR::MASS_MIN, EQUIPMENT::RADAR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::RADAR::CONDITION_MIN, EQUIPMENT::RADAR::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::RADAR_ID;
        
    	RadarEquipment* radar_equipment = new RadarEquipment(radius_orig);
                        
        radar_equipment->setIdData(data_id);  
        radar_equipment->setTextureOb(texOb_item);    	
        radar_equipment->setFunctionalSlotSubTypeId(SLOT::RADAR_ID);
        radar_equipment->setItemCommonData(common_data);
        
 
    	radar_equipment->updatePropetries();
    	radar_equipment->countPrice();
    	
    	return radar_equipment;
}

