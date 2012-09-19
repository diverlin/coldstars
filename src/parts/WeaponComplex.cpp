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
#include "../spaceobjects/Vehicle.hpp"
#include "../resources/GuiTextureObCollector.hpp"

#include "../render/Render.hpp"
#include "../parts/Turrel.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"

WeaponComplex::WeaponComplex(Vehicle* vehicle)
{ 
        this->owner_vehicle = vehicle;
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
                       	
bool WeaponComplex::AddItem(BaseItem* item)
{
        for(unsigned int i = 0; i<slot_weapon_vec.size(); i++)
        {
                if (slot_weapon_vec[i]->GetEquiped() == false)
                {
                     slot_weapon_vec[i]->InsertItem(item);
                     return true;   
                }
        }
        
        return false;
}
 
void WeaponComplex::PrepareWeapons()
{       
     	// used once at the begining of turn
	ReloadAllWeapons();
	ValidateAllWeaponsTarget();
}
    
void WeaponComplex::ReloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->GetTurrel()->CheckAmmo() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
        
     	fire_delay = getRandInt(7,15);
     	d_fire_delay = TURN_TIME/(slot_weapon_reloaded_vec.size()+1);   
}
  
//void WeaponComplex::WeaponsControlledFromUpperLevel(const WeaponSelector& weapon_selector)
//{
	//for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
	//{
               	//slot_weapon_vec[i]->GetTurrel()->SetSelectedStatus(weapon_selector.GetSingle(i+1));
	//}
                
        //ResetDeselectedWeaponTargets();
//}

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

//bool WeaponComplex::IsAllPreciseWeaponsSelected() const
//{
	//for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
	//{
		//if (slot_weapon_reloaded_vec[i]->GetItem()->GetSubTypeId() != ENTITY::ROCKET_EQUIPMENT_ID)
		//{
       			//if (slot_weapon_reloaded_vec[i]->GetTurrel()->GetSelectedStatus() == false)
       			//{	 
       				//return false;		
			//}
		//}
	//}
	
	//return true;
//}

void WeaponComplex::SetTarget(BaseGameEntity* target)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target->GetPoints().GetCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
        	if (slot_weapon_equiped_vec[i]->GetSelected() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->GetTurrel()->GetTarget() == NULL )
           		{
         			slot_weapon_equiped_vec[i]->GetTurrel()->SetTarget(target);
                                slot_weapon_equiped_vec[i]->GetTurrel()->CheckTarget();                                        
                        }
                } 
        }
}

void WeaponComplex::SetPreciseFireTarget(BaseGameEntity* target, ItemSlot* item_slot)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().GetCenter(), target->GetPoints().GetCenter());
        
        for (unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
        {
        	if (slot_weapon_equiped_vec[i]->GetSelected() == true)
        	{
           		if (slot_weapon_equiped_vec[i]->GetTurrel()->GetTarget() == NULL)
           		{
         			slot_weapon_equiped_vec[i]->GetTurrel()->SetTarget(target, item_slot);
                                slot_weapon_equiped_vec[i]->GetTurrel()->CheckTarget();                                        
                        }
                } 
        }
}

void WeaponComplex::Fire(int timer, int attack_skill, bool show_effect)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (std::vector<ItemSlot*>::iterator it = slot_weapon_reloaded_vec.begin(); it < slot_weapon_reloaded_vec.end(); it++)
        	{	
                        (*it)->GetTurrel()->CheckTarget();
                        if ((*it)->GetTurrel()->GetSubTarget() != NULL)
           		{
               			(*it)->GetTurrel()->PreciseFireEvent((*it)->GetTurrel()->GetSubTarget(), attack_skill, show_effect);
       				it = slot_weapon_reloaded_vec.erase(it);
            		}
        	}     	
     	
        	for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
        	{	
                        slot_weapon_reloaded_vec[i]->GetTurrel()->CheckTarget();
                        if (slot_weapon_reloaded_vec[i]->GetTurrel()->GetTarget() != NULL)
           		{
               			if (slot_weapon_reloaded_vec[i]->GetTurrel()->FireEvent(attack_skill, show_effect) == true)
               			{
                   			fire_delay += d_fire_delay;
               			}

       				slot_weapon_reloaded_vec.erase(slot_weapon_reloaded_vec.begin() + i);
       				break;
            		}
        	}
        }
}

void WeaponComplex::ValidateAllWeaponsTarget()
{
	for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
        {
                if (slot_weapon_vec[i]->GetTurrel()->GetTarget() != NULL) 
                {
         		if (slot_weapon_vec[i]->GetEquiped() == true) 
                	{
             			slot_weapon_reloaded_vec[i]->GetTurrel()->CheckTarget();
                	}
                	else
                	{
                		slot_weapon_vec[i]->DeselectEvent();
                	}
                }
        }
}

bool WeaponComplex::UpdateFireAbility()
{
     	//total_damage = 0;
     	//avr_damage =
     	//avr_radius =  
     	
     	//int sum_fire_radius = 0;

     	slot_weapon_equiped_vec.clear();     	
     	for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
     	{ 
        	if (slot_weapon_vec[i]->GetEquiped() == true)
        	{
           		if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
           		{
              			slot_weapon_equiped_vec.push_back(slot_weapon_vec[i]);
              			//sum_damage      += slot_weapon_vec[i]->getItemDamage(); 
              			//sum_fire_radius += slot_weapon_vec[i]->getItemRadius(); 
           		}
           	}
     	}

     	//if (slot_weapon_equiped_vec.size() != 0)
     	//{
        	//propetries.average_fire_radius = sum_fire_radius/slot_weapon_equiped_vec.size();
        	//ableTo.FIRE = true;
     	//}
     	//else
     	//{
        	//propetries.average_fire_radius = 0;
        	//ableTo.FIRE = false;
     	//} 
     	
     	if (slot_weapon_equiped_vec.size() != 0)
     	{
        	return true;
     	}
     	else
     	{
        	return false;
     	} 
}

void WeaponComplex::RenderTurrels() const
{
    	for(unsigned int i=0; i<slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->GetTurrel()->Render(owner_vehicle->GetPoints().GetAngleDegree());        
    	} 
}

void WeaponComplex::RenderWeaponsRange()
{
	glPushMatrix();
	{
		glTranslatef(owner_vehicle->GetPoints().GetCenter().x, owner_vehicle->GetPoints().GetCenter().y, 0.0f);
		for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
        	{
         		if (slot_weapon_reloaded_vec[i]->GetSelected() == true)
                	{
                		slot_weapon_reloaded_vec[i]->UpdateRange(GuiTextureObCollector::Instance().dot_red);
             			slot_weapon_reloaded_vec[i]->DrawRange();
             		}
        	}
	}
	glPopMatrix();
}

void WeaponComplex::RenderWeaponIcons() const
{       
        for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
        {
                Turrel* _turrel = slot_weapon_vec[i]->GetTurrel();
                if (_turrel->GetTarget() != NULL )
                {       
                        Rect _rect(_turrel->GetTarget()->GetPoints().GetCenter().x - 40/2 + 23*i, _turrel->GetTarget()->GetPoints().GetCenter().y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[i]->GetItem()->GetTextureOb(), _rect, -2.0);
                }        
        }
}
