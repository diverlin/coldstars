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
#include <math/rand.hpp>
#include "../common/Logger.hpp"
//#include <ceti/StringUtils.hpp>
#include "../spaceobjects/Vehicle.hpp"
#include "../resources/GuiTextureObCollector.hpp"

#include <jeti/Render.hpp>
#include "../parts/Turrel.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"

#include <meti/RandUtils.hpp>

WeaponComplex::WeaponComplex()
{ 
        owner_vehicle = nullptr;
}

WeaponComplex::~WeaponComplex()
{}

bool WeaponComplex::AddSlot(ItemSlot* slot)
{
    slot_weapon_vec.push_back(slot); 
    
    return true;
}

                           
ItemSlot* WeaponComplex::GetEmptyWeaponSlot() const
{
    for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() == nullptr)
        {
            return slot_weapon_vec[i];
        }
    }
    
    return nullptr;
}

ItemSlot* WeaponComplex::GetEquipedWeakestWeaponSlot() const
{
    int min_price = 0;
    unsigned int i_min = NONE_ID;
        
    for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() != nullptr)
        {
            int price = slot_weapon_vec[i]->GetItem()->GetPrice();
            if ((min_price > price) or (min_price == 0))
            {
                min_price = price;
                i_min = i;
            }
        }
    }
    
    if (i_min != NONE_ID)
    {
        return slot_weapon_vec[i_min];
    }
    else
    {
        return nullptr;
    }
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
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() != nullptr)
        {
            if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
            {
                if (slot_weapon_vec[i]->CheckAmmo() == true)
                {
                    slot_weapon_reloaded_vec.push_back(slot_weapon_vec[i]);
                }
            }
        }
    }
    
    fire_delay = meti::getRandInt(7,15);
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
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        slot_weapon_vec[i]->DeselectEvent();
    }
}

void WeaponComplex::ActivateWeaponsBySubTypeId(TYPE::ENTITY weapon_subtype_id)
{
    for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
    {
        if (slot_weapon_reloaded_vec[i]->GetItem()->subTypeId() == weapon_subtype_id)
        {
            slot_weapon_reloaded_vec[i]->SelectEvent();        
        }
    }
}


void WeaponComplex::DeactivateWeaponsBySubTypeId(TYPE::ENTITY weapon_subtype_id)
{
    for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
    {
        if (slot_weapon_reloaded_vec[i]->GetItem()->subTypeId() == weapon_subtype_id)
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

void WeaponComplex::SetTarget(BaseSpaceEntity* target, ItemSlot* item_slot)
{                 
    #if WEAPONSTARGET_LOG_ENABLED == 1 
    if (item_slot == nullptr)   Logger::Instance().Log("vehicle_id="+std::to_string(owner_vehicle->id())+" WeaponComplex::SetTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()), WEAPONSTARGET_LOG_DIP);
    else                        Logger::Instance().Log("vehicle_id="+std::to_string(owner_vehicle->id())+ " WeaponComplex::SetPreciseFireTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()) + " item_subtype_id=" + str(item_slot->GetItem()->subTypeId()) + " id=" + std::to_string(item_slot->GetItem()->id()), WEAPONSTARGET_LOG_DIP);
    #endif   

    target->TakeIntoAccountAgressor(owner_vehicle);

    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        ItemSlot& weapon_slot = *slot_weapon_vec[i]; // shortcut
        if (weapon_slot.GetSelected() == true )
        {
            if (weapon_slot.GetItem() != nullptr)
            {
                if (weapon_slot.GetItem()->GetFunctioning() == true)
                {
                    if (weapon_slot.GetTarget() == nullptr)
                    {
                        STATUS status = weapon_slot.CheckTarget(target);
                        if (status == STATUS::TARGET_OK)
                        {
                            weapon_slot.SetTarget(target, item_slot);
                        }
                        #if WEAPONSTARGET_LOG_ENABLED == 1 
                        else
                        {
                            Logger::Instance().Log(getTargetStatusStr(status), WEAPONSTARGET_LOG_DIP); 
                        }
                        #endif 
                    }
                } 
            }
        }
    }
}

void WeaponComplex::Fire(int timer, float attack_rate, bool show_effect)
{
    if (timer < TURN_TIME - fire_delay)
    {
        for (std::vector<ItemSlot*>::iterator it=slot_weapon_reloaded_vec.begin(); it<slot_weapon_reloaded_vec.end(); ++it)
        {    
            ItemSlot& weapon_slot = **it; // shortcut
            if (weapon_slot.GetTarget() != nullptr)
            {
                if (weapon_slot.ValidateTarget() == STATUS::TARGET_OK)
                {
                    weapon_slot.FireEvent(attack_rate, show_effect);
                    if (weapon_slot.GetSubTarget() == nullptr)
                    {
                        fire_delay += d_fire_delay;
                    }
                }
                else
                {                  
                    weapon_slot.ResetTarget();
                }    
                    
                it = slot_weapon_reloaded_vec.erase(it);
            }
        }
    }     
}

void WeaponComplex::ValidateAllWeaponsTarget()
{
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetTarget() != nullptr) 
        {
            if (slot_weapon_vec[i]->ValidateTarget() != STATUS::TARGET_OK)
            {
                slot_weapon_vec[i]->ResetTarget();
            }
        }
    }
}

void WeaponComplex::UpdateFireAbility()
{
    total_damage = 0;
    total_radius = 0;
    radius_min = 0;

    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() != nullptr)
        { 
            if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
            {        
                int radius = slot_weapon_vec[i]->GetItemRadius();
                if ( (radius < radius_min) or (radius_min == 0) )
                {
                    radius_min = radius;
                }
                total_damage += slot_weapon_vec[i]->GetItemDamage(); 
                total_radius += slot_weapon_vec[i]->GetItemRadius(); 
            }
        }
    }
}

void WeaponComplex::RenderTurrels() const
{
    for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() != nullptr)
        { 
            if (slot_weapon_vec[i]->GetItem()->GetFunctioning() == true)
            {    
                //slot_weapon_vec[i]->GetTurrel()->Render(owner_vehicle->GetAngle().z);    // angle    
            }
        }
    } 
}

void WeaponComplex::RenderWeaponsRange()
{
    for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
    {
        if (slot_weapon_reloaded_vec[i]->GetSelected() == true)
        {
           slot_weapon_reloaded_vec[i]->UpdateRange(GuiTextureObCollector::Instance().dot_red);
           slot_weapon_reloaded_vec[i]->DrawRange(meti::vec2(owner_vehicle->GetCenter()));
        }
    }
}

void WeaponComplex::RenderWeaponIcons() const
{       
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->GetItem() != nullptr ) //?? ideally this is not needed, if item == nullptr< the target set to nullptr
        {  
            if (slot_weapon_vec[i]->GetTarget() != nullptr )
            {       
                //Rect _rect(slot_weapon_vec[i]->GetTarget()->GetCenter().x - 40/2 + 23*i, slot_weapon_vec[i]->GetTarget()->GetCenter().y + 40/2, 20, 20);
                //drawTexturedRect(slot_weapon_vec[i]->GetItem()->GetTextureOb(), _rect, -2.0);
            }        
        }
    }
}
