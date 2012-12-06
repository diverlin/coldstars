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

#include "WeaponComplex.hpp"
#include "../common/rand.hpp"
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../resources/GuiTextureObCollector.hpp"

#include "../render/Render.hpp"
#include "../parts/Turrel.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"

WeaponComplex::WeaponComplex()
{ 
        owner_vehicle = NULL;
}

WeaponComplex::~WeaponComplex()
{}

bool WeaponComplex::AddSlot(ItemSlot* slot)
{
        slot_weapon_vec.push_back(slot); 
}
        
TextureOb* WeaponComplex::GetItemTextureOb(int index) const
{
	index--;
	if (index < slot_weapon_vec.size())
	{
		if (slot_weapon_vec[index]->GetEquiped() == true)
                {
                     	return slot_weapon_vec[index]->GetItem()->GetTextureOb();   
                }
	}

	return NULL;	
}
                       	
ItemSlot* WeaponComplex::GetEmptyWeaponSlot() const
{
        for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
        {
                if (slot_weapon_vec[i]->GetEquiped() == false)
                {
                    	return slot_weapon_vec[i];
                }
        }
        
        return NULL;
}

ItemSlot* WeaponComplex::GetEquipedWeakestWeaponSlot() const
{
	int min_price = 0;
	int i_min = 0;
	
	if (slot_weapon_equiped_vec.size() == 1)
	{
		return slot_weapon_equiped_vec[0];
        }

	if (slot_weapon_equiped_vec.size() > 1)
	{
		min_price = slot_weapon_equiped_vec[0]->GetItem()->GetPrice();
		
		for(unsigned int i=1; i<slot_weapon_equiped_vec.size(); i++)
        	{
        		int price = slot_weapon_equiped_vec[i]->GetItem()->GetPrice();
                	if (min_price > price)
                	{
                		min_price = price;
                		i_min = i;
                	}
        	}
        	
        	return slot_weapon_equiped_vec[i_min];
        }
        
        return NULL;
}
                
void WeaponComplex::PrepareWeapons()
{       
     	// used once at the begining of turn
     	slot_weapon_equiped_vec.clear();     	
     	for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
     	{ 
        	if (slot_weapon_vec[i]->GetEquiped() == true)
        	{
           		if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
           		{
              			slot_weapon_equiped_vec.push_back(slot_weapon_vec[i]); 
           		}
           	}
     	}     	
     	
	ReloadAllWeapons();
	ValidateAllWeaponsTarget(); // cause bug during loading, anyway this step looks like useless here
}
    
void WeaponComplex::ReloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->CheckAmmo() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
        
     	fire_delay = getRandInt(7,15);
     	d_fire_delay = TURN_TIME/(slot_weapon_reloaded_vec.size()+1);   
}
  
void WeaponComplex::ActivateAllWeapons()
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	{
               	slot_weapon_reloaded_vec[i]->SelectEvent();
	}
}

void WeaponComplex::DeactivateAllWeapons()
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	{
               	slot_weapon_reloaded_vec[i]->DeselectEvent();
	}
}

void WeaponComplex::ActivateWeaponsBySubTypeId(int weapon_subtype_id)
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	{
		if (slot_weapon_reloaded_vec[i]->GetItem()->GetSubTypeId() == weapon_subtype_id)
		{
               		slot_weapon_reloaded_vec[i]->SelectEvent();		
		}
	}
}


void WeaponComplex::DeactivateWeaponsBySubTypeId(int weapon_subtype_id)
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	{
		if (slot_weapon_reloaded_vec[i]->GetItem()->GetSubTypeId() == weapon_subtype_id)
		{
               		slot_weapon_reloaded_vec[i]->DeselectEvent();	
		}
	}
}


bool WeaponComplex::IsAnyWeaponSelected() const
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	{
       		if (slot_weapon_reloaded_vec[i]->GetSelected() == true)
       		{ 
       			return true;		
		}
	}
	
	return false;
}

void WeaponComplex::SetTarget(BaseSpaceEntity* target)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target->GetPoints().GetCenter());
        
        #if WEAPONSTARGET_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" WeaponComplex::SetTarget type_id= " + getTypeStr(target->GetTypeId()) + " id=" + int2str(target->GetId()), WEAPONSTARGET_LOG_DIP); 
	#endif   
	
        for (unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
        {
        	if (slot_weapon_equiped_vec[i]->GetSelected() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->GetTarget() == NULL )
           		{
           			if (slot_weapon_equiped_vec[i]->CheckTarget(target) == true)
         			{
         				slot_weapon_equiped_vec[i]->SetTarget(target);
                                }
                        }
                } 
        }
}

void WeaponComplex::SetPreciseFireTarget(BaseSpaceEntity* target, ItemSlot* item_slot)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target->GetPoints().GetCenter());
        
        #if WEAPONSTARGET_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+ " WeaponComplex::SetPreciseFireTarget type_id= " + getTypeStr(target->GetTypeId()) + " id=" + int2str(target->GetId()) + " item_subtype_id=" + getTypeStr(item_slot->GetItem()->GetSubTypeId()) + " id=" + int2str(item_slot->GetItem()->GetId()), WEAPONSTARGET_LOG_DIP); 
	#endif   
	
        for (unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
        {
        	if (slot_weapon_equiped_vec[i]->GetSelected() == true)
        	{
           		if (slot_weapon_equiped_vec[i]->GetTarget() == NULL)
           		{
           		        if (slot_weapon_equiped_vec[i]->CheckTarget(target, item_slot) == true)
         			{
         				slot_weapon_equiped_vec[i]->SetTarget(target, item_slot);
                        	}
                        }
                } 
        }
}

void WeaponComplex::Fire(int timer, int attack_skill, bool show_effect)
{
        #if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" WeaponComplex::Fire START", WEAPONSTARGET_LOG_DIP); 
        #endif   
	
     	//if (timer < TURN_TIME - fire_delay)
     	{
        	for (std::vector<ItemSlot*>::iterator it=slot_weapon_reloaded_vec.begin(); it<slot_weapon_reloaded_vec.end(); ++it)
        	{	
                        if ((*it)->ValidateTarget() == true)
                        {
      				(*it)->FireEvent(attack_skill, show_effect);
				//if ((*it)->GetSubTarget() == NULL)
           			//{
           				//fire_delay += d_fire_delay;
               			//}
        		}
        		else
        		{
        			(*it)->ResetTarget();
        		}    
        		
        		it = slot_weapon_reloaded_vec.erase(it);
        	}
        } 	
        
        #if WEAPONSTARGET_LOG_ENABLED == 1 
        Logger::Instance().Log("vehicle_id="+int2str(owner_vehicle->GetId())+" WeaponComplex::Fire END", WEAPONSTARGET_LOG_DIP); 
        #endif   
}

void WeaponComplex::ValidateAllWeaponsTarget()
{
	for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
        {
                if (slot_weapon_vec[i]->GetTarget() != NULL) 
                {
         		if (slot_weapon_vec[i]->GetEquiped() == true) 
                	{
             			slot_weapon_vec[i]->ValidateTarget();
                	}
                	else
                	{
                		slot_weapon_vec[i]->DeselectEvent();
                	}
                }
        }
}

//bool WeaponComplex::UpdateFireAbility()
//{
     	//total_damage = 0;
     	//avr_damage =
     	//avr_radius =  
     	
     	//int sum_fire_radius = 0;
	
	//weapon_radius_min = 0;
     	
     	//slot_weapon_equiped_vec.clear();     	
     	//for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
     	//{ 
        	//if (slot_weapon_vec[i]->GetEquiped() == true)
        	//{
           		//if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
           		//{
              			//slot_weapon_equiped_vec.push_back(slot_weapon_vec[i]); 
              			
              			//int weapon_radius = slot_weapon_vec[i]->GetItemRadius();
              			//if ( (weapon_radius < weapon_radius_min) or (weapon_radius_min == 0) )
              			//{
              				//weapon_radius_min = weapon_radius;
              			//}
              			////sum_damage      += slot_weapon_vec[i]->getItemDamage(); 
              			////sum_fire_radius += slot_weapon_vec[i]->getItemRadius(); 
           		//}
           	//}
     	//}
 	
     	//if (slot_weapon_equiped_vec.size() != 0)
     	//{
        	//return true;
     	//}
     	//else
     	//{
        	//return false;
     	//} 
//}

void WeaponComplex::RenderTurrels() const
{
    	for(unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->GetTurrel()->Render(owner_vehicle->GetPoints().GetAngleDegree());        
    	} 
}

void WeaponComplex::RenderWeaponsRange()
{
	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
       	{
       		if (slot_weapon_reloaded_vec[i]->GetSelected() == true)
               	{
               		slot_weapon_reloaded_vec[i]->UpdateRange(GuiTextureObCollector::Instance().dot_red);
       			slot_weapon_reloaded_vec[i]->DrawRange(owner_vehicle->GetPoints().GetCenter());
        	}
	}
}

void WeaponComplex::RenderWeaponIcons() const
{       
        for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
        {
                if (slot_weapon_vec[i]->GetTarget() != NULL )
                {       
                        Rect _rect(slot_weapon_vec[i]->GetTarget()->GetPoints().GetCenter().x - 40/2 + 23*i, slot_weapon_vec[i]->GetTarget()->GetPoints().GetCenter().y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[i]->GetItem()->GetTextureOb(), _rect, -2.0);
                }        
        }
}
