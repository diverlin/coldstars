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

   	//TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
   	texOb_turrel	  = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::TURREL_ID); 
   	texOb_lazerEffect = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::LAZER_EFFECT_ID);
}

LazerEquipment :: ~LazerEquipment() /* virtual */
{}

int LazerEquipment :: getDamage() const { return damage; }
int LazerEquipment :: getRadius() const { return radius; }
		
/* virtual */		
void LazerEquipment :: updatePropetries()
{
   	damage_add  = 0;
   	radius_add  = 0;
   	
   	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	damage_add   += ((LazerModule*)modules_vec[i])->getDamageAdd();
        	radius_add   += ((LazerModule*)modules_vec[i])->getRadiusAdd();        	
    	}
    	
    	damage = damage_orig + damage_add;
    	radius = radius_orig + radius_add;
} 

void LazerEquipment :: countPrice()
{
   	float damage_rate        = (float)damage_orig / EQUIPMENT::LAZER::DAMAGE_MIN;
   	float radius_rate        = (float)radius_orig / EQUIPMENT::LAZER::RADIUS_MIN;
   	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::LAZER::MODULES_NUM_MAX;

   	float effectiveness_rate = EQUIPMENT::LAZER::DAMAGE_WEIGHT * damage_rate + 
   				   EQUIPMENT::LAZER::RADIUS_WEIGHT * radius_rate + 
   				   EQUIPMENT::LAZER::MODULES_NUM_WEIGHT * modules_num_rate;

   	float mass_rate          = (float)data_item.mass / EQUIPMENT::LAZER::MASS_MIN;
   	float condition_rate     = (float)condition / data_item.condition_max;

   	price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


/* virtual */    
void LazerEquipment :: updateOwnerAbilities()
{ 
    	slot->getOwnerVehicle()->UpdateFireAbility();
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
                                                              slot->getTurrel()->getTarget()->GetPoints().getpCenter());
        }
    	else
    	{
        	_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
                                                              slot->getOwnerVehicle()->GetPoints().getpCenter(), 
                                                              slot->getTurrel()->getTarget()->GetPoints().getpCenter());
        }
    
    	// DAMAGE effect
	DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, slot->getTurrel()->getTarget());
    	_lazer_trace_effect->setDamageEffect(_damage_effect);
    	
    	deterioration();
    	
    	slot->getOwnerVehicle()->GetStarSystem()->addToSpace(_lazer_trace_effect);
    	slot->getOwnerVehicle()->GetStarSystem()->addToSpace(_damage_effect);
} 



void LazerEquipment :: fireEvent_FALSE()
{ 
    	deterioration();
} 


LazerEquipment* getNewLazerEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

   	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::LAZER_EQUIPMENT_ID, revision_id)
    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::LAZER_EQUIPMENT_ID);     

    	int damage_orig     = getRandInt(EQUIPMENT::LAZER::DAMAGE_MIN, EQUIPMENT::LAZER::DAMAGE_MAX);
    	int radius_orig     = getRandInt(EQUIPMENT::LAZER::RADIUS_MIN, EQUIPMENT::LAZER::RADIUS_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::LAZER::MODULES_NUM_MIN, EQUIPMENT::LAZER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::LAZER::MASS_MIN, EQUIPMENT::LAZER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::LAZER::CONDITION_MIN, EQUIPMENT::LAZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::LAZER_ID;
        
    	LazerEquipment* lazer_equipment = new LazerEquipment(damage_orig, 
    							     radius_orig);
                                                             
        lazer_equipment->setIdData(data_id);  
        lazer_equipment->setTextureOb(texOb_item);    	
        lazer_equipment->setFunctionalSlotSubTypeId(SLOT::WEAPON_ID);
        lazer_equipment->setItemCommonData(common_data);
        
   	lazer_equipment->updatePropetries();
   	lazer_equipment->countPrice();
   	
    	return lazer_equipment;
}










