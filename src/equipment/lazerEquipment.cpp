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


LazerEquipment :: LazerEquipment(TextureOb* _pTo_itemTexOb, int _damage_orig, int _radius_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate)
{
   CommonForEquipment_init(_pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

   subtype_id = LAZER_ID;

   damage_orig = _damage_orig;
   damage_add  = 0;

   radius_orig = _radius_orig;
   radius_add  = 0;

   //TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
   //TextureOb particle_texOb = TEXTURE_MANAGER.returnParticleTexObBy_ColorID(self.item_texOb.color_id);
   pTo_lazerEffectTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.lazerEffect_texOb_pList);
   pTo_particleTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList);

   turrelTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.turrel_texOb_pList); 
   
   updatePropetries();
   countPrice();
   updateInfo();
}

LazerEquipment :: ~LazerEquipment()
{}

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
   float modules_num_rate   = (float)modules_num_max / LAZER_MODULES_NUM_MAX;

   float effectiveness_rate = LAZER_DAMAGE_WEIGHT * damage_rate + LAZER_RADIUS_WEIGHT * radius_rate + LAZER_MODULES_NUM_WEIGHT * modules_num_rate;

   float mass_rate          = (float)mass / LAZER_MASS_MIN;
   float condition_rate     = (float)condition / condition_max;

   price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


    
void LazerEquipment :: updateOwnerPropetries()
{ 
    //(*pTo_owner).updateFireAbility();
}


void LazerEquipment :: updateInfo()
{   
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "LAZER";
    info_title_1 = "damage:";      info_value_1 = returnDamageStr();
    info_title_2 = "radius:";      info_value_2 = returnRadiusStr();

    info_title_3 = "max modules:"; info_value_3 = int2str(modules_num_max);
    info_title_4 = "condition:";   info_value_4 = int2str(condition) + "/" + int2str(condition_max);
    info_title_5 = "mass:";        info_value_5 = int2str(mass);
    info_title_6 = "price:";       info_value_6 = int2str(price);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
    info_title_pList.push_back(&info_title_6);   info_value_pList.push_back(&info_value_6);
}     

std::string LazerEquipment :: returnDamageStr()
{
      if (damage_add == 0)
         return int2str(damage_orig);
      else
         return int2str(damage_orig) + "+" + int2str(damage_add);
}

std::string LazerEquipment :: returnRadiusStr()
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
    LazerTraceEffect* pTo_lazer_trace_effect;

    if (slot->getShip()->render_TURRELS == true)
        pTo_lazer_trace_effect = new LazerTraceEffect(pTo_lazerEffectTexOb, 
                                                      pTo_particleTexOb, 
                                                      100, 
                                                      _turrel->get_pCenterX(), 
                                                      _turrel->get_pCenterY(), 
                                                      _turrel->getTarget_pCenterX(), 
                                                      _turrel->getTarget_pCenterY());
    else
        pTo_lazer_trace_effect = new LazerTraceEffect(pTo_lazerEffectTexOb, 
                                                      pTo_particleTexOb, 
                                                      100, 
                                                      &(slot->getShip()->points.center_x), 
                                                      &(slot->getShip()->points.center_y), 
                                                      _turrel->getTarget_pCenterX(), 
                                                      _turrel->getTarget_pCenterY());

    slot->getShip()->pTo_starsystem->effect_LAZERTRACE_pList.push_back(pTo_lazer_trace_effect);
    
    // DAMAGE effct
    TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);  
    //TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(pTo_lazer_trace_effect->pTo_texOb->color_id);   SEGFAULT
    DamageEffect* pTo_damage_effect = new DamageEffect(pTo_particleTexOb, 
                                                       slot->getShip()->pTo_starsystem, 
                                                       _turrel->getTarget_pCenterX(), 
                                                       _turrel->getTarget_pCenterY(), 5, 30, 1.3, 1.0, 0.1, 0.001);
    slot->getShip()->pTo_starsystem->effect_DAMAGE_pList.push_back(pTo_damage_effect);

    pTo_lazer_trace_effect->pTo_damageEffect = pTo_damage_effect;
} 




bool LazerEquipment :: insertModule(LazerModule* pTo_lazerModule)
{
    if (modules_pList.size() < modules_num_max)
    {
       damage_add += pTo_lazerModule->damage_add;
       radius_add += pTo_lazerModule->radius_add;
        
       updatePropetries();
       updateInfo();     // ??
    
       texOb_modules_pList.push_back(pTo_lazerModule->pTo_texOb);
       modules_pList.push_back(pTo_lazerModule);
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
    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.LazerEquipment_texOb_pList);     

    int damage_orig     = randIntInRange(LAZER_DAMAGE_MIN, LAZER_DAMAGE_MAX);
    int radius_orig     = randIntInRange(LAZER_RADIUS_MIN, LAZER_RADIUS_MAX);
    int modules_num_max = randIntInRange(LAZER_MODULES_NUM_MIN, LAZER_MODULES_NUM_MAX);

    int mass            = randIntInRange(LAZER_MASS_MIN, LAZER_MASS_MAX);
    int condition_max   = randIntInRange(LAZER_CONDITION_MIN, LAZER_CONDITION_MAX) * tech_rate;
    int deterioration_rate = 1;

    LazerEquipment* pTo_lazer = new LazerEquipment(pTo_itemTexOb, damage_orig, radius_orig, modules_num_max, mass, condition_max, deterioration_rate);
    return pTo_lazer;
}










