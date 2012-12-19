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

#include "LazerEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../resources/TextureManager.hpp"
#include "../../items/modules/LazerModule.hpp"
#include "../../effects/lazerTrace.hpp"
#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../world/starsystem.hpp"
#include "../../parts/Turrel.hpp"

LazerEquipment::LazerEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = ENTITY::LAZER_EQUIPMENT_ID;
        
   	damage_orig = 0;
   	radius_orig = 0;

   	//TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
   	texOb_turrel	  = TextureManager::Instance().GetRandomTextureOb(TEXTURE::TURREL_ID); 
   	texOb_lazerEffect = TextureManager::Instance().GetRandomTextureOb(TEXTURE::LAZER_EFFECT_ID);
}

/* virtual */
LazerEquipment::~LazerEquipment() 
{}

/* virtual */
void LazerEquipment::UpdateProperties()
{
   	damage_add  = 0;
   	radius_add  = 0;
   	
   	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	damage_add   += ((LazerModule*)modules_vec[i])->GetDamageAdd();
        	radius_add   += ((LazerModule*)modules_vec[i])->GetRadiusAdd();        	
    	}
    	
    	damage = damage_orig + damage_add;
    	radius = radius_orig + radius_add;
} 
      		
void LazerEquipment::CountPrice()
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

void LazerEquipment::AddUniqueInfo()
{
    	info.addTitleStr("LAZER");

    	info.addNameStr("damage:");     info.addValueStr(GetDamageStr());
    	info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string LazerEquipment::GetDamageStr()
{
      	if (damage_add == 0)
         	return int2str(damage_orig);
      	else
         	return int2str(damage_orig) + "+" + int2str(damage_add);
}

std::string LazerEquipment::GetRadiusStr()
{
       	if (radius_add == 0)
          	return int2str(radius_orig);
       	else
          	return int2str(radius_orig) + "+" + int2str(radius_add);
}

void LazerEquipment::FireEvent(BaseSpaceEntity* target, ItemSlot* subtarget, float damage_rate, bool show_effect)
{ 
	if (item_slot->GetOwnerVehicle()->GetProperties().energy > damage)
	{
		//item_slot->GetOwnerVehicle()->GetProperties().energy -= damage;
		
		if (subtarget != NULL) // precise fire
		{
			//if (getRandInt(1, 2) == 1)
			{
				subtarget->GetItem()->LockEvent(1);
			}
			damage_rate /= 3; // lower damage is used for precise fire
			
		}
		 
		target->Hit(damage*damage_rate, show_effect);
		DeteriorationEvent();
	
		if (show_effect)
		{
			// LazerTraceEffect
	    		LazerTraceEffect* _lazer_trace_effect;
	    		if (item_slot->GetOwnerVehicle()->GetKorpusData().draw_turrels == true)
	    		{
	        		_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
	                        	                             	      item_slot->GetTurrel()->GetPoints().GetpCenter(), 
	                                	                              item_slot->GetTarget()->GetPoints().GetpCenter());
	        	}
	    		else
	    		{
	        		_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect, 
	                        	                                      item_slot->GetOwnerVehicle()->GetPoints().GetpCenter(), 
	                                	                              item_slot->GetTarget()->GetPoints().GetpCenter());
	        	}
	    		item_slot->GetOwnerVehicle()->GetStarSystem()->Add(_lazer_trace_effect);
	    	    
	    		// DamageEffect
			DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, item_slot->GetTarget());
	    		_lazer_trace_effect->setDamageEffect(_damage_effect);
	    		item_slot->GetOwnerVehicle()->GetStarSystem()->Add(_damage_effect);
		}
	}
} 

/*virtual*/
void LazerEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "lazer_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueLazerEquipment(save_ptree, root);
}

/*virtual*/
void LazerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueLazerEquipment(load_ptree);
}

/*virtual*/
void LazerEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueLazerEquipment();
}

void LazerEquipment::SaveDataUniqueLazerEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueLazerEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        save_ptree.put(root+"damage_orig", damage_orig);
        save_ptree.put(root+"radius_orig", radius_orig);
}
                
void LazerEquipment::LoadDataUniqueLazerEquipment(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueLazerEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        damage_orig = load_ptree.get<int>("damage_orig");     
        radius_orig = load_ptree.get<int>("radius_orig");   
}                

void LazerEquipment::ResolveDataUniqueLazerEquipment()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueLazerEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}

