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
#include <item/BaseItem.hpp>
#include "../slots/ItemSlot.hpp"
#include <meti/RandUtils.hpp>

WeaponComplex::WeaponComplex(Vehicle* owner_vehicle)
    :
      owner_vehicle(owner_vehicle)
{}

WeaponComplex::~WeaponComplex()
{}

bool WeaponComplex::addSlot(ItemSlot* slot)
{
    assert(slot);
    m_slots.push_back(slot);
    return true;
}


ItemSlot* WeaponComplex::freeSlot() const
{
    for(unsigned int i=0; i<m_slots.size(); i++)
    {
        if (m_slots[i]->item() == nullptr)
        {
            return m_slots[i];
        }
    }
    
    return nullptr;
}

ItemSlot* WeaponComplex::equipedWeakestSlot() const
{
    int min_price = 0;
    unsigned int i_min = NONE;

    for(unsigned int i=0; i<m_slots.size(); i++)
    {
        if (m_slots[i]->item() != nullptr)
        {
            int price = m_slots[i]->item()->price();
            if ((min_price > price) or (min_price == 0))
            {
                min_price = price;
                i_min = i;
            }
        }
    }
    
    if (i_min != NONE)
    {
        return m_slots[i_min];
    }
    else
    {
        return nullptr;
    }
}

void WeaponComplex::prepareWeapons()
{       
    // used once at the begining of turn
    __reloadAllWeapons();
    __validateAllWeaponsTarget();
}

void WeaponComplex::__reloadAllWeapons()
{
    m_slots_reloaded.clear();
    for (unsigned int i=0; i<m_slots.size(); i++)
    {
        if (m_slots[i]->item() != nullptr)
        {
            if (m_slots[i]->item()->isFunctioning() == true)
            {
                if (m_slots[i]->checkAmmo() == true)
                {
                    m_slots_reloaded.push_back(m_slots[i]);
                }
            }
        }
    }
    
    fire_delay = meti::getRandInt(7,15);
    d_fire_delay = TURN_TIME/(m_slots_reloaded.size()+1);
}

void WeaponComplex::activateWeapons()
{
    for (ItemSlot* slot: m_slots_reloaded) {
        slot->selectEvent();
    }
}

void WeaponComplex::deactivateWeapons()
{
    for (ItemSlot* slot: m_slots_reloaded) {
        slot->deselectEvent();
    }
}

void WeaponComplex::activateWeapons(const type::entity& weapon_subtype_id)
{
    for (ItemSlot* slot: m_slots_reloaded) {
        if (slot->item()->subtype() == weapon_subtype_id) {
            slot->selectEvent();
        }
    }
}

void WeaponComplex::deactivateWeapons(const type::entity& weapon_subtype_id)
{
    for (ItemSlot* slot: m_slots_reloaded) {
        if (slot->item()->subtype() == weapon_subtype_id) {
            slot->deselectEvent();
        }
    }
}

bool WeaponComplex::isAnyWeaponSelected() const
{
    for (ItemSlot* slot: m_slots_reloaded) {
        if (slot->isSelected() == true) {
            return true;
        }
    }    
    return false;
}

void WeaponComplex::setTarget(SpaceObject* target, ItemSlot* item_slot)
{                 
    //if (item_slot == nullptr)   LOG("vehicle_id="+std::to_string(owner_vehicle->id())+" WeaponComplex::SetTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()));
    //else                        LOG("vehicle_id="+std::to_string(owner_vehicle->id())+ " WeaponComplex::SetPreciseFireTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()) + " item_subtype_id=" + str(item_slot->item()->subTypeId()) + " id=" + std::to_string(item_slot->item()->id()));

    target->remeberAgressor(owner_vehicle);

    for (ItemSlot* slot: m_slots) {
        if (slot->isSelected()) {
            if (slot->item()) {
                if (slot->item()->isFunctioning()) {
                    if (slot->target() == nullptr)                     {
                        STATUS status = slot->checkTarget(target);
                        if (status == STATUS::TARGET_OK) {
                            slot->setTarget(target, item_slot);
                        } else {
                            LOG(getTargetStatusStr(status));
                        }
                    }
                }
            }
        }
    }
}

void WeaponComplex::Fire(int timer, float attack_rate, bool show_effect)
{
    if (timer < TURN_TIME - fire_delay) {
        for (std::vector<ItemSlot*>::iterator it=m_slots_reloaded.begin(); it<m_slots_reloaded.end(); ++it) {
            ItemSlot& slot = **it; // shortcut
            if (slot.target()) {
                if (slot.validateTarget() == STATUS::TARGET_OK) {
                    slot.fireEvent(attack_rate, show_effect);
                    if (slot.subtarget()) {
                        fire_delay += d_fire_delay;
                    }
                } else {
                    slot.resetTarget();
                }
                it = m_slots_reloaded.erase(it);
            }
        }
    }
}

void WeaponComplex::__validateAllWeaponsTarget()
{
    for (ItemSlot* slot: m_slots) {
        if (slot->target()) {
            if (slot->validateTarget() != STATUS::TARGET_OK) {
                slot->resetTarget();
            }
        }
    }
}

void WeaponComplex::updateFireAbility()
{
    m_damage = 0;
    m_radiusMax = 0;
    m_radiusMin = 0;
    for (ItemSlot* slot: m_slots) {
        if (slot->item()) {
            if (slot->item()->isFunctioning()) {
                int radius = slot->itemRadius();
                m_radiusMin = std::min(m_radiusMin, radius);
                m_radiusMax = std::max(m_radiusMax, radius);
                m_damage += slot->itemDamage();
            }
        }
    }
}

//void WeaponComplex::RenderTurrels() const
//{
//    for(unsigned int i=0; i<m_slots.size(); i++)
//    {
//        if (m_slots[i]->item() != nullptr)
//        {
//            if (m_slots[i]->item()->isFunctioning() == true)
//            {
//                //slot_weapon_vec[i]->GetTurrel()->Render(owner_vehicle->GetAngle().z);    // angle
//            }
//        }
//    }
//}

//void WeaponComplex::RenderWeaponsRange()
//{
//    for (ItemSlot* slot: m_slots_reloaded) {
//        if (slot->isSelected()) {
//            //slot->UpdateRange(GuiTextureObCollector::Instance().dot_red);
//            //slot->drawRange(meti::vec2(owner_vehicle->center()));
//        }
//    }
//}

//void WeaponComplex::RenderWeaponIcons() const
//{
//    for (unsigned int i=0; i<m_slots.size(); i++) {
//        if (m_slots[i]->item() != nullptr ) //?? ideally this is not needed, if item == nullptr< the target set to nullptr
//        {
//            if (m_slots[i]->target() != nullptr ) {
//                //Rect _rect(slot_weapon_vec[i]->GetTarget()->center().x - 40/2 + 23*i, slot_weapon_vec[i]->GetTarget()->center().y + 40/2, 20, 20);
//                //drawTexturedRect(slot_weapon_vec[i]->item()->textureOb(), _rect, -2.0);
//            }
//        }
//    }
//}
