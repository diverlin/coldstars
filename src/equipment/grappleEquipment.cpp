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


GrappleEquipment :: GrappleEquipment()
{}

GrappleEquipment :: GrappleEquipment(TextureOb* _texOb_item, 
				     int _strength_orig, 
				     int _radius_orig, 
				     int _speed_orig, 
				     int _maxNumItem_orig, 
				     EquipmentCommonData _common_data)   // joun strength and speed attributes into one
{
    	CommonForEquipment_init(GRAPPLE_ID, _texOb_item, _common_data);

    	//grapple_list = []
    	//grapple_remove_queue = []

    	strength_orig = _strength_orig;
    	strength_add  = 0;

    	radius_orig = _radius_orig;
    	radius_add  = 0;
    
    	speed_orig = _speed_orig;
    	speed_add  = 0;

    	maxNumItem_orig = _maxNumItem_orig;
    	maxNumItem_add  = 0;

    	updatePropetries();
    	countPrice();
}

GrappleEquipment :: ~GrappleEquipment()
{
	for (unsigned int mi = 0; mi<modules_vec.size(); mi++)
	{
		delete modules_vec[mi];
	}
}

int GrappleEquipment :: getStrength()   const { return strength; }
int GrappleEquipment :: getRadius()     const { return radius; }
int GrappleEquipment :: getSpeed()      const { return speed; }
int GrappleEquipment :: getMaxNumItem() const { return maxNumItem; }


void GrappleEquipment :: updatePropetries()
{
    	strength   = strength_orig   + strength_add;
    	radius     = radius_orig     + radius_add;
    	speed      = speed_orig      + speed_add;
    	maxNumItem = maxNumItem_orig + maxNumItem_add;
}

void GrappleEquipment :: countPrice()
{
    	float strength_rate      = (float)strength_orig / GRAPPLE_STRENGTH_MIN;
    	float radius_rate        = (float)radius_orig / GRAPPLE_RADIUS_MIN;
    	float speed_rate         = (float)speed_orig / GRAPPLE_SPEED_MIN;
    	float maxNumItem_rate    = (float)maxNumItem_orig / GRAPPLE_MAXNUMITEM_MIN;

    	float modules_num_rate   = (float)common_data.modules_num_max / GRAPPLE_MODULES_NUM_MAX;

    	float effectiveness_rate = GRAPPLE_STRENGTH_WEIGHT * strength_rate + GRAPPLE_RADIUS_WEIGHT * radius_rate + GRAPPLE_SPEED_WEIGHT * speed_rate + GRAPPLE_MAXNUMITEM_WEIGHT * maxNumItem_rate + GRAPPLE_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / GRAPPLE_MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void GrappleEquipment :: updateOwnerPropetries()
{
    	slot->getShip()->updateGrabAbility();
}


void GrappleEquipment :: addUniqueInfo()
{    	
	info.addTitleStr("GRAPPLE");

    	info.addNameStr("strength:");    info.addValueStr( getStrengthStr() );
    	info.addNameStr("radius:");      info.addValueStr( getRadiusStr() );
    	info.addNameStr("speed:");       info.addValueStr( getSpeedStr() );
    	info.addNameStr("maxNumItem:");  info.addValueStr( getMaxNumItemStr() );
}


std::string GrappleEquipment :: getStrengthStr()
{
     	if (strength_add == 0)
        	return int2str(strength_orig);
     	else
        	return int2str(strength_orig) + "+" + int2str(strength_add);
}

std::string GrappleEquipment :: getRadiusStr()
{
     	if (radius_add == 0)
        	return int2str(radius_orig);
     	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}

std::string GrappleEquipment :: getSpeedStr()
{
     	if (speed_add == 0)
        	return int2str(speed_orig);
     	else
        	return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string GrappleEquipment :: getMaxNumItemStr()
{
     	if (maxNumItem_add == 0)
        	return int2str(maxNumItem_orig);
     	else
        	return int2str(maxNumItem_orig) + "+" + int2str(maxNumItem_add);
}



bool GrappleEquipment :: insertModule(GrappleModule* _grapple_module)
{
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
       	 	strength_add   += _grapple_module->getStrengthAdd();
        	radius_add     += _grapple_module->getRadiusAdd();
        	speed_add      += _grapple_module->getSpeedAdd();
        	maxNumItem_add += _grapple_module->getMaxNumItemAdd();
            
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_grapple_module->getTexOb());
        	modules_vec.push_back(_grapple_module);
        	return true;
    	}
    	else
        	return false;    
}
    


GrappleEquipment* grappleEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.GrappleEquipment_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(GRAPPLE_ITEM_TEXTURE_ID, revision_id) 

    	int strength_orig   = getRandInt(GRAPPLE_STRENGTH_MIN, GRAPPLE_STRENGTH_MAX);
    	int radius_orig     = getRandInt(GRAPPLE_RADIUS_MIN, GRAPPLE_RADIUS_MAX);
    	int speed_orig      = getRandInt(GRAPPLE_SPEED_MIN, GRAPPLE_SPEED_MAX);
    	int maxNumItem_orig = getRandInt(GRAPPLE_MAXNUMITEM_MIN, GRAPPLE_MAXNUMITEM_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = getRandInt(GRAPPLE_MODULES_NUM_MIN, GRAPPLE_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(GRAPPLE_MASS_MIN, GRAPPLE_MASS_MAX);
    	common_data.condition_max   = getRandInt(GRAPPLE_CONDITION_MIN, GRAPPLE_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	GrappleEquipment* grapple_equipment = new GrappleEquipment(texOb_item, 
    								   strength_orig, 
    								   radius_orig, 
    								   speed_orig, 
    								   maxNumItem_orig, 
    								   common_data);
    	return grapple_equipment;
}
