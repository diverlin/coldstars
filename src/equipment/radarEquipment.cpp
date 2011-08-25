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


#include "radarEquipment.h"

RadarEquipment :: RadarEquipment()
{}


RadarEquipment :: RadarEquipment(TextureOb* _pTo_itemTexOb, 
				 int _radius_orig, 
				 int _modules_num_max, 
				 int _mass, 
				 int _condition_max, 
				 int _deterioration_rate)
{
   	CommonForEquipment_init(RADAR_ID, _pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

    	radius_orig = _radius_orig;
    	radius_add  = 0;

    	updatePropetries();
    	countPrice();
}


RadarEquipment :: ~RadarEquipment()
{}


int RadarEquipment :: getRadius() const { return radius; }



void RadarEquipment :: updatePropetries()
{
    	radius = radius_orig + radius_add;
}

void RadarEquipment :: countPrice()
{
    	float radius_rate         = (float)radius_orig / RADAR_RADIUS_MIN;

    	float modules_num_rate    = (float)modules_num_max / RADAR_MODULES_NUM_MAX;

    	float effectiveness_rate  = RADAR_RADIUS_WEIGHT * radius_rate +  RADAR_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate           = (float)mass / RADAR_MASS_MIN;
    	float condition_rate      = (float)condition / condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void RadarEquipment :: updateOwnerPropetries()
{
          //self.owner.updateRadarAbility()
}
      


void RadarEquipment :: updateInfo()
{
    	info_title_pList.clear();
    	info_value_pList.clear();

    	info_title_0 = "RADAR";
    	info_title_1 = "radius:";     info_value_1 = returnRadiusStr();

    	info_title_2 = "modules:";    info_value_2 = int2str(modules_num_max);
    	info_title_3 = "condition:";  info_value_3 = int2str(condition) + "/" + int2str(condition_max);
    	info_title_4 = "mass:";       info_value_4 = int2str(mass);
    	info_title_5 = "price:";      info_value_5 = int2str(price);

    	info_title_pList.push_back(&info_title_0);  
    	info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    	info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    	info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    	info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    	info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
}


std::string RadarEquipment :: returnRadiusStr()
{
    	if (radius_add == 0)
        	return int2str(radius_orig);
    	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}



bool RadarEquipment :: insertModule(RadarModule* pTo_radarModule)
{
    	if (modules_pList.size() < modules_num_max)
    	{
        	radius_add += pTo_radarModule->getRadiusAdd();
    
        	updatePropetries();
        
        	texOb_modules_pList.push_back(pTo_radarModule->getTexOb());
        	modules_pList.push_back(pTo_radarModule);
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

    	TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.RadarEquipment_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 

    	int radius_orig     = randIntInRange(RADAR_RADIUS_MIN, RADAR_RADIUS_MAX);
    	int modules_num_max = randIntInRange(RADAR_MODULES_NUM_MIN, RADAR_MODULES_NUM_MAX);

    	int mass            = randIntInRange(RADAR_MASS_MIN, RADAR_MASS_MAX);
    	int condition_max   = randIntInRange(RADAR_CONDITION_MIN, RADAR_CONDITION_MAX) * tech_rate;

    	int deterioration_rate = 1;

    	RadarEquipment* _radar = new RadarEquipment(pTo_itemTexOb, radius_orig, modules_num_max, mass, condition_max, deterioration_rate);
    	return _radar;
}

