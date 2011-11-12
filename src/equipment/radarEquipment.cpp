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


RadarEquipment :: RadarEquipment()
{}


RadarEquipment :: RadarEquipment(TextureOb* _texOb_item, 
				 int _radius_orig, 
				 EquipmentCommonData _common_data)
{
   	CommonForEquipment_init(RADAR_ID, RADAR_ID, _texOb_item, _common_data);

    	radius_orig = _radius_orig;
    	radius_add  = 0;

    	updatePropetries();
    	countPrice();
}


RadarEquipment :: ~RadarEquipment()
{
	for (unsigned int mi = 0; mi<modules_vec.size(); mi++)
	{
		delete modules_vec[mi];
	}
}


int RadarEquipment :: getRadius() const { return radius; }



void RadarEquipment :: updatePropetries()
{
    	radius = radius_orig + radius_add;
}

void RadarEquipment :: countPrice()
{
    	float radius_rate         = (float)radius_orig / RADAR_RADIUS_MIN;

    	float modules_num_rate    = (float)common_data.modules_num_max / RADAR_MODULES_NUM_MAX;

    	float effectiveness_rate  = RADAR_RADIUS_WEIGHT * radius_rate +  RADAR_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate           = (float)common_data.mass / RADAR_MASS_MIN;
    	float condition_rate      = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void RadarEquipment :: updateOwnerPropetries()
{
	slot->getOwnerShip()->updateRadarAbility();
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



bool RadarEquipment :: insertModule(RadarModule* _radar_module)
{
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
        	radius_add += _radar_module->getRadiusAdd();
    
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_radar_module->getTexOb());
        	modules_vec.push_back(_radar_module);
        	return true;
    	}
    	else
        	return false;    
}
    
    

RadarEquipment* radarEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.RadarEquipment_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 

    	int radius_orig     = getRandInt(RADAR_RADIUS_MIN, RADAR_RADIUS_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = getRandInt(RADAR_MODULES_NUM_MIN, RADAR_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(RADAR_MASS_MIN, RADAR_MASS_MAX);
    	common_data.condition_max   = getRandInt(RADAR_CONDITION_MIN, RADAR_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	RadarEquipment* radar_equipment = new RadarEquipment(texOb_item, radius_orig, common_data);
    	return radar_equipment;
}

