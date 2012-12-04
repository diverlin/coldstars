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

#include "Turrel.hpp"
#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../slots/ItemSlot.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"

#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../pilots/Npc.hpp"

Turrel::Turrel(ItemSlot* slot)
{
        this->slot = slot;
      
        target    = NULL;
        subtarget = NULL;
}

Turrel::~Turrel()
{}

void Turrel::ValidateTarget()
{
        #if WEAPONSTARGET_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(slot->GetOwnerVehicle()->GetId())+" Turrel::ValidateTarget", WEAPONSTARGET_LOG_DIP); 
	#endif 
	
        if (target != NULL)
        {
                if (slot->CheckTarget(target) == false)
                {
                        ResetTarget();
                }
        }
}

void Turrel::ResetTarget()
{ 
        #if WEAPONSTARGET_LOG_ENABLED == 1 
	Logger::Instance().Log("vehicle_id="+int2str(slot->GetOwnerVehicle()->GetId())+" Turrel::ResetTarget", WEAPONSTARGET_LOG_DIP); 
	#endif 
	
	target    = NULL; 
	subtarget = NULL; 
}

bool Turrel::CheckAmmo() const
{
	switch(slot->GetItem()->GetSubTypeId())
	{
    		case ENTITY::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
    		case ENTITY::ROCKET_EQUIPMENT_ID: { if (slot->GetRocketEquipment()->GetAmmo() > 0) return true; break; }
	}
	
    	return false;           
}


bool Turrel::FireEvent(int attack_skill, bool show_effect)
{    
        #if WEAPONSTARGET_LOG_ENABLED == 1 
        if (subtarget == NULL)
        Logger::Instance().Log("vehicle_id="+int2str(slot->GetOwnerVehicle()->GetId())+" Turrel::FireEvent type_id= " + getTypeStr(target->GetTypeId()) + " id=" + int2str(target->GetId()), WEAPONSTARGET_LOG_DIP); 
        else
	Logger::Instance().Log("vehicle_id="+int2str(slot->GetOwnerVehicle()->GetId())+" Turrel::FireEvent type_id= " + getTypeStr(target->GetTypeId()) + " id=" + int2str(target->GetId()) + " itemslot_subtype_id=" + getTypeStr(subtarget->GetItem()->GetSubTypeId()) + " id=" + int2str(subtarget->GetItem()->GetId()), WEAPONSTARGET_LOG_DIP); 
	#endif   
	   			
	switch(slot->GetItem()->GetSubTypeId())
	{
    		case ENTITY::LAZER_EQUIPMENT_ID:
    		{   
			int damage = slot->GetLazerEquipment()->GetDamage() * attack_skill * SKILL::ATTACK_NORMALIZED_RATE;						
			if (subtarget != NULL) // precise fire
			{
				if (target->GetTypeId() == ENTITY::VEHICLE_ID)
				{			       		
					//if (getRandInt(1, 2) == 1)
					{
						((Vehicle*)target)->LockItemInItemSlot(subtarget, 1);
					}
					damage /= 3; // lower damage is used for precise fire
				}	
			}
       			slot->GetLazerEquipment()->FireEvent(show_effect); 
			target->Hit(damage, show_effect);
									       			
       			if (target->GetAlive() == false)
       			{
       				slot->GetOwnerVehicle()->GetOwnerNpc()->AddExpirience(target->GetGivenExpirience(), show_effect);
       				ResetTarget();
       			}
       			
       			return true; break;  
    		}

    		case ENTITY::ROCKET_EQUIPMENT_ID:
    		{       
                	slot->GetRocketEquipment()->FireEvent(attack_skill * SKILL::ATTACK_NORMALIZED_RATE);
                	return true; break;              
    		}

	}
	
    	return false;
}


void Turrel::Render(float _tur_angle_inD)
{        
        if (target != NULL)
        {
        	float _tur_xl = target->GetPoints().GetCenter().x - points.GetCenter().x;
        	float _tur_yl = target->GetPoints().GetCenter().y - points.GetCenter().y;

        	float _tur_angle_inR = atan2(_tur_yl, _tur_xl);
        	_tur_angle_inD = _tur_angle_inR * RADIAN_TO_DEGREE_RATE;
        }

    	points.SetAngle(_tur_angle_inD);
    	points.Update();        

    	drawFlatQuadPerVertexIn2D(textureOb,
    				  points.GetBottomLeft(), 
                                  points.GetBottomRight(), 
                                  points.GetTopRight(), 
                                  points.GetTopLeft(), 
                                  points.GetPosZ());
}        
                
