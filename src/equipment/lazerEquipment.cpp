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


#include "lazerEquipment.h"

LazerEquipment :: LazerEquipment(TextureOb* _itemTexOb, 
				 int _damage_orig, 
				 int _radius_orig, 
				 EquipmentCommonData _common_data)
{
   	CommonForEquipment_init(LAZER_ID, _itemTexOb, _common_data);

   	damage_orig = _damage_orig;
   	damage_add  = 0;

   	radius_orig = _radius_orig;
   	radius_add  = 0;

   	//TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
   	//TextureOb particle_texOb = TEXTURE_MANAGER.returnParticleTexObBy_ColorID(self.item_texOb.color_id);
   	texOb_turrel	  = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.turrel_texOb_pList); 
   	texOb_lazerEffect = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.lazerEffect_texOb_pList);
   	//texOb_particle    = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList);
   	texOb_particle    = g_TEXTURE_MANAGER.returnParticleTexObByColorId(texOb_lazerEffect->color_id);
   	if (texOb_particle == NULL)
   		printf("trololo\n");
   	
   
   	updatePropetries();
   	countPrice();
}

LazerEquipment :: ~LazerEquipment()
{}


int LazerEquipment :: getDamage() const { return damage; }
int LazerEquipment :: getRadius() const { return radius; }
		
		
void LazerEquipment :: updatePropetries()
{
    	damage = damage_orig + damage_add;
    	radius = radius_orig + radius_add;

    	particle_Size = 60;   //# needs for lazer effect
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


    
void LazerEquipment :: updateOwnerPropetries()
{ 
    	slot->getShip()->updateFireAbility();
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



void LazerEquipment :: fireEvent(Turrel* _turrel)
{ 
        
     //if l_owner.energy > (WEAPON_ENERGY_CONSUMPTION_RATE * self.damage):
        //lazer.play()
        //l = lazerEffect((self.l_tex, (self.l_w, self.l_h)), l_owner, l_target, self.particle_texOb, self.pSize)
        //l.starsystem.effect_LAZER_list.append(l)

        //l_owner.energy       -= WEAPON_ENERGY_CONSUMPTION_RATE * self.damage

        //l_target.hit(l_owner, self)
             
        //if l_target.type == SHIP_ID:
           //l_target.temperature  += WEAPON_HEATING_RATE * self.damage

    	// LAZER TRACE EFFECT
    	LazerTraceEffect* _lazer_trace_effect;
    	if (slot->getShip()->render_TURRELS == true)
    	{
        	_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
                                                      	      texOb_particle, 
                                                     	      100, 
                                                     	      _turrel->get_pCenterX(), 
                                                              _turrel->get_pCenterY(), 
                                                              _turrel->getTarget_pCenterX(), 
                                                              _turrel->getTarget_pCenterY());
        }
    	else
    	{
        	_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
                                                              texOb_particle, 
                                                              100, 
                                                              &(slot->getShip()->getPoints()->getpCenter()->x), 
                                                              &(slot->getShip()->getPoints()->getpCenter()->y), 
                                                              _turrel->getTarget_pCenterX(), 
                                                              _turrel->getTarget_pCenterY());
        }
    
    	// DAMAGE effect
    	DamageEffect* _damage_effect = new DamageEffect(texOb_particle, 
                                                        _turrel->getTarget_pCenterX(), 
                                                        _turrel->getTarget_pCenterY(), 5, 30, 1.3, 1.0, 0.1, 0.001);               


    	_lazer_trace_effect->pTo_damageEffect = _damage_effect;
    	
    	deterioration();
    	
    	slot->getShip()->getStarSystem()->addLazerTraceEffect(_lazer_trace_effect);
    	slot->getShip()->getStarSystem()->addDamageEffect(_damage_effect);
} 




bool LazerEquipment :: insertModule(LazerModule* _lazer_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
       		damage_add += _lazer_module->getDamageAdd();
       		radius_add += _lazer_module->getRadiusAdd();
        
       		updatePropetries();
    
       		texOb_modules_pList.push_back(_lazer_module->getTexOb());
       		modules_pList.push_back(_lazer_module);
       		return true;
    	}
    	else
       		return false;   
}
    



LazerEquipment* lazerEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

   	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(LAZER_ITEM_TEXTURE_ID, revision_id)
    	TextureOb* itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.LazerEquipment_texOb_pList);     

    	int damage_orig     = randIntInRange(LAZER_DAMAGE_MIN, LAZER_DAMAGE_MAX);
    	int radius_orig     = randIntInRange(LAZER_RADIUS_MIN, LAZER_RADIUS_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = randIntInRange(LAZER_MODULES_NUM_MIN, LAZER_MODULES_NUM_MAX);
    	common_data.mass            = randIntInRange(LAZER_MASS_MIN, LAZER_MASS_MAX);
    	common_data.condition_max   = randIntInRange(LAZER_CONDITION_MIN, LAZER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	LazerEquipment* _lazer_equipment = new LazerEquipment(itemTexOb, 
    							      damage_orig, 
    							      radius_orig, 
							      common_data);
    	return _lazer_equipment;
}










