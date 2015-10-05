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
#include <ceti/Logger.hpp>

#include "../spaceobjects/Vehicle.hpp"

#include "../parts/Turrel.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"

#include <meti/RandUtils.hpp>

WeaponComplex::WeaponComplex(Vehicle* owner_vehicle)
    :
      owner_vehicle(owner_vehicle)
{}

WeaponComplex::~WeaponComplex()
{}

bool WeaponComplex::AddSlot(ItemSlot* slot)
{
    assert(slot);
    slot_weapon_vec.push_back(slot);
    return true;
}


ItemSlot* WeaponComplex::GetEmptyWeaponSlot() const
{
    for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->item() == nullptr)
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
        if (slot_weapon_vec[i]->item() != nullptr)
        {
            int price = slot_weapon_vec[i]->item()->price();
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
        if (slot_weapon_vec[i]->item() != nullptr)
        {
            if (slot_weapon_vec[i]->item()->isFunctioning() == true)
            {
                if (slot_weapon_vec[i]->checkAmmo() == true)
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
        if (slot_weapon_reloaded_vec[i]->item()->subTypeId() == weapon_subtype_id)
        {
            slot_weapon_reloaded_vec[i]->SelectEvent();
        }
    }
}


void WeaponComplex::DeactivateWeaponsBySubTypeId(TYPE::ENTITY weapon_subtype_id)
{
    for (unsigned int i=0; i<slot_weapon_reloaded_vec.size(); i++)
    {
        if (slot_weapon_reloaded_vec[i]->item()->subTypeId() == weapon_subtype_id)
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

void WeaponComplex::SetTarget(SpaceObject* target, ItemSlot* item_slot)
{                 
    //if (item_slot == nullptr)   Logger::Instance().Log("vehicle_id="+std::to_string(owner_vehicle->id())+" WeaponComplex::SetTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()), WEAPONSTARGET_LOG_DIP);
    //else                        Logger::Instance().Log("vehicle_id="+std::to_string(owner_vehicle->id())+ " WeaponComplex::SetPreciseFireTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()) + " item_subtype_id=" + str(item_slot->item()->subTypeId()) + " id=" + std::to_string(item_slot->item()->id()), WEAPONSTARGET_LOG_DIP);

    target->remeberAgressor(owner_vehicle);

    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        ItemSlot& weapon_slot = *slot_weapon_vec[i]; // shortcut
        if (weapon_slot.GetSelected() == true )
        {
            if (weapon_slot.item() != nullptr)
            {
                if (weapon_slot.item()->isFunctioning() == true)
                {
                    if (weapon_slot.target() == nullptr)
                    {
                        STATUS status = weapon_slot.checkTarget(target);
                        if (status == STATUS::TARGET_OK) {
                            weapon_slot.setTarget(target, item_slot);
                        } else {
                            Logger::Instance().Log(getTargetStatusStr(status), WEAPONSTARGET_LOG_DIP);
                        }
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
            if (weapon_slot.target() != nullptr)
            {
                if (weapon_slot.validateTarget() == STATUS::TARGET_OK)
                {
                    weapon_slot.fireEvent(attack_rate, show_effect);
                    if (weapon_slot.subtarget() == nullptr)
                    {
                        fire_delay += d_fire_delay;
                    }
                }
                else
                {
                    weapon_slot.resetTarget();
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
        if (slot_weapon_vec[i]->target())
        {
            if (slot_weapon_vec[i]->validateTarget() != STATUS::TARGET_OK)
            {
                slot_weapon_vec[i]->resetTarget();
            }
        }
    }
}

void WeaponComplex::UpdateFireAbility()
{
    total_damage = 0;
    total_radius = 0;
    radius_min = 0;
    int z = slot_weapon_vec.size();
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->item() != nullptr)
        {
            if (slot_weapon_vec[i]->item()->isFunctioning() == true)
            {
                int radius = slot_weapon_vec[i]->itemRadius();
                if ( (radius < radius_min) or (radius_min == 0) )
                {
                    radius_min = radius;
                }
                total_damage += slot_weapon_vec[i]->itemDamage();
                total_radius += slot_weapon_vec[i]->itemRadius();
            }
        }
    }
}

void WeaponComplex::RenderTurrels() const
{
    for(unsigned int i=0; i<slot_weapon_vec.size(); i++)
    {
        if (slot_weapon_vec[i]->item() != nullptr)
        {
            if (slot_weapon_vec[i]->item()->isFunctioning() == true)
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
            //slot_weapon_reloaded_vec[i]->UpdateRange(GuiTextureObCollector::Instance().dot_red);
            //slot_weapon_reloaded_vec[i]->drawRange(meti::vec2(owner_vehicle->center()));
        }
    }
}

void WeaponComplex::RenderWeaponIcons() const
{       
    for (unsigned int i=0; i<slot_weapon_vec.size(); i++) {
        if (slot_weapon_vec[i]->item() != nullptr ) //?? ideally this is not needed, if item == nullptr< the target set to nullptr
        {
            if (slot_weapon_vec[i]->target() != nullptr ) {
                //Rect _rect(slot_weapon_vec[i]->GetTarget()->center().x - 40/2 + 23*i, slot_weapon_vec[i]->GetTarget()->center().y + 40/2, 20, 20);
                //drawTexturedRect(slot_weapon_vec[i]->item()->textureOb(), _rect, -2.0);
            }
        }
    }
}
