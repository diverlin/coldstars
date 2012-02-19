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


LazerEquipment :: LazerEquipment(int damage_orig, 
				 int radius_orig)
{
   	this->damage_orig = damage_orig;
   	this->radius_orig = radius_orig;
        
   	damage_add  = 0;
   	radius_add  = 0;

   	//TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
   	texOb_turrel	  = g_TEXTURE_MANAGER.getRandomTexOb(TURREL_TEXTURE_ID); 
   	texOb_lazerEffect = g_TEXTURE_MANAGER.getRandomTexOb(LAZER_EFFECT_TEXTURE_ID);
   	   
   	updatePropetries();
   	countPrice();
}

LazerEquipment :: ~LazerEquipment() /* virtual */
{
	for (unsigned int i = 0; i < modules_vec.size(); i++)
	{
		delete modules_vec[i];
	}
}

int LazerEquipment :: getDamage() const { return damage; }
int LazerEquipment :: getRadius() const { return radius; }
		
		
void LazerEquipment :: updatePropetries()
{
    	damage = damage_orig + damage_add;
    	radius = radius_orig + radius_add;
} 

void LazerEquipment :: countPrice()
{
   	float damage_rate        = (float)damage_orig / LAZER_DAMAGE_MIN;
   	float radius_rate        = (float)radius_orig / LAZER_RADIUS_MIN;
   	float modules_num_rate   = (float)common_data.modules_num_max / LAZER_MODULES_NUM_MAX;

   	float effectiveness_rate = LAZER_DAMAGE_WEIGHT * damage_rate + LAZER_RADIUS_WEIGHT * radius_rate + LAZER_MODULES_NUM_WEIGHT * modules_num_rate;

   	float mass_rate          = (float)common_data.mass / LAZER_MASS_MIN;
   	float condition_rate     = (float)condition / common_data.condition_max;

   	price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


    
void LazerEquipment :: updateOwnerAbilities()
{ 
    	slot->getOwnerVehicle()->updateFireAbility();
}


void LazerEquipment :: addUniqueInfo()
{
    	info.addTitleStr("LAZER");

    	info.addNameStr("damage:");     info.addValueStr( getDamageStr() );
    	info.addNameStr("radius:");     info.addValueStr( getRadiusStr() );
}
     		

std::string LazerEquipment :: getDamageStr()
{
      	if (damage_add == 0)
         	return int2str(damage_orig);
      	else
         	return int2str(damage_orig) + "+" + int2str(damage_add);
}

std::string LazerEquipment :: getRadiusStr()
{
       	if (radius_add == 0)
          	return int2str(radius_orig);
       	else
          	return int2str(radius_orig) + "+" + int2str(radius_add);
}



void LazerEquipment :: fireEvent_TRUE()
{ 
    	LazerTraceEffect* _lazer_trace_effect;
    	if (slot->getOwnerVehicle()->data_korpus.render_TURRELS == true)
    	{
        	_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
                                                     	      slot->getTurrel()->getPoints()->getpCenter(), 
                                                              slot->getTurrel()->getTarget()->getPoints()->getpCenter());
        }
    	else
    	{
        	_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
                                                              slot->getOwnerVehicle()->getPoints()->getpCenter(), 
                                                              slot->getTurrel()->getTarget()->getPoints()->getpCenter());
        }
    
    	// DAMAGE effect
	DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, slot->getTurrel()->getTarget());
    	_lazer_trace_effect->setDamageEffect(_damage_effect);
    	
    	deterioration();
    	
    	slot->getOwnerVehicle()->getStarSystem()->addToSpace(_lazer_trace_effect);
    	slot->getOwnerVehicle()->getStarSystem()->addToSpace(_damage_effect);
} 



void LazerEquipment :: fireEvent_FALSE()
{ 
    	deterioration();
} 




bool LazerEquipment :: insertModule(LazerModule* _lazer_module)
{
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
       		damage_add += _lazer_module->getDamageAdd();
       		radius_add += _lazer_module->getRadiusAdd();
        
       		updatePropetries();
    
       		texOb_modules_pList.push_back(_lazer_module->getTextureOb());
       		modules_vec.push_back(_lazer_module);
       		return true;
    	}
    	else
       		return false;   
}
    



LazerEquipment* getNewLazerEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

   	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(LAZER_ITEM_TEXTURE_ID, revision_id)
    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(LAZER_ITEM_TEXTURE_ID);     

    	int damage_orig     = getRandInt(LAZER_DAMAGE_MIN, LAZER_DAMAGE_MAX);
    	int radius_orig     = getRandInt(LAZER_RADIUS_MIN, LAZER_RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(LAZER_MODULES_NUM_MIN, LAZER_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(LAZER_MASS_MIN, LAZER_MASS_MAX);
    	common_data.condition_max   = getRandInt(LAZER_CONDITION_MIN, LAZER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT_ID;
        data_id.subtype_id = LAZER_EQUIPMENT_ID;
        
    	LazerEquipment* lazer_equipment = new LazerEquipment(damage_orig, 
    							     radius_orig);
                                                             
        lazer_equipment->setIdData(data_id);  
        lazer_equipment->setTextureOb(texOb_item);    	
        lazer_equipment->setFunctionalSlotSubTypeId(WEAPON_SLOT_ID);
        lazer_equipment->setItemCommonData(common_data);
        
    	return lazer_equipment;
}










