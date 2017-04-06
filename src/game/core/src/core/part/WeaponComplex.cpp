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
#include <ceti/Logger.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/model/item/equipment/Weapon.hpp>
#include <core/descriptor/item/Item.hpp>

#include <core/item/Item.hpp>
#include <core/slot/ItemSlot.hpp>

namespace complex {

Weapon::Weapon(control::Vehicle* vehicle)
    :
      Base(vehicle)
{}

bool
Weapon::addSlot(slot::Item* slot)
{
    assert(slot);
    m_slots.push_back(slot);
    return true;
}


slot::Item*
Weapon::freeSlot() const
{
    for(slot::Item* slot: m_slots) {
        if (!slot->item()) {
            return slot;
        }
    }

    return nullptr;
}

slot::Item*
Weapon::equipedWeakestSlot() const
{
    int price_min = 0;
    slot::Item* result = nullptr;
    for(slot::Item* slot: m_slots) {
        if (slot->item()) {
//            int price = slot->item()->price();
//            if ((price_min > price) || (price_min == 0)) {
//                price_min = price;
//                result = slot;
//            }
        }
    }

    return result;
}

void Weapon::prepareWeapons()
{       
    // used once at the begining of turn
    __reload();
    __validateTargets();
}

void Weapon::__reload()
{
    m_slots_reloaded.clear();
    for (slot::Item* slot: m_slots) {
        if (slot->item()) {
            if (slot->item()->isFunctioning()) {
                if (slot->checkAmmo()) {
                    m_slots_reloaded.push_back(slot);
                }
            }
        }
    }
    
//    fire_delay = meti::getRandInt(7,15);
//    d_fire_delay = TURN_TIME/(m_slots_reloaded.size()+1);
}

void Weapon::selectAllWeapons()
{
    for (slot::Item* slot: m_slots_reloaded) {
        slot->selectEvent();
    }
}

void Weapon::deactivateWeapons()
{
    for (slot::Item* slot: m_slots_reloaded) {
        slot->deselectEvent();
    }
}

void Weapon::selectAllWeapons(const entity::Type& weapon_subtype_id)
{
    for (slot::Item* slot: m_slots_reloaded) {
        if (slot->item()->descriptor()->obSubType() == weapon_subtype_id) {
            slot->selectEvent();
        }
    }
}

void Weapon::deactivateWeapons(const entity::Type& weapon_subtype_id)
{
    for (slot::Item* slot: m_slots_reloaded) {
        if (slot->item()->descriptor()->obSubType() == weapon_subtype_id) {
            slot->deselectEvent();
        }
    }
}

bool Weapon::isAnyWeaponSelected() const
{
    for (slot::Item* slot: m_slots_reloaded) {
        if (slot->isSelected() == true) {
            return true;
        }
    }    
    return false;
}

//int WeaponComplex::itemsNum() const
//{
//    int itemsNum = 0;
//    for (slot::ItemSlot* slot: m_slots) {
//        if (slot->item()) {
//            itemsNum++;
//        }
//    }
//    return itemsNum;
//}

void Weapon::setTarget(control::SpaceObject* target, slot::Item* subtarget)
{                 
    //if (item_slot == nullptr)   LOG("vehicle_id="+std::to_string(owner_vehicle->id())+" WeaponComplex::SetTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()));
    //else                        LOG("vehicle_id="+std::to_string(owner_vehicle->id())+ " WeaponComplex::SetPreciseFireTarget type_id= " + str(target->typeId()) + " id=" + std::to_string(target->id()) + " item_subtype_id=" + str(item_slot->item()->subTypeId()) + " id=" + std::to_string(item_slot->item()->id()));

    //target->remeberAgressor(owner_vehicle);

    for (slot::Item* slot: m_slots) {
        if (slot->isSelected()) {
            control::item::Weapon* weapon = slot->weapon();
            if (weapon) {
                if (weapon->isFunctioning()) {
                    if (!weapon->target()) {
                        STATUS status = _validateTarget(target, weapon->radius());
                        if (status == STATUS::TARGET_OK) {
                            weapon->setTarget(target, subtarget);
                        } else {
                            LOG(getTargetStatusStr(status));
                        }
                    }
                }
            }
        }
    }
}

int Weapon::guessDamage(int dist = 0)
{
    int damage = 0;
    for (slot::Item* slot: m_slots_reloaded) {
        if (slot->weapon()->model()->radius() >= dist) {
            damage += slot->weapon()->model()->damage();
        }
    }
    return damage;
}

void Weapon::fire(int timer, float attack_rate, bool show_effect)
{
    //if (timer < TURN_TIME - fire_delay) {
    std::vector<slot::Item*>::iterator it=m_slots_reloaded.begin();
        while(it!=m_slots_reloaded.end()) {
            control::item::Weapon* weapon = (*it)->weapon(); // shortcut
            if (weapon->target()) {
                if (_validateTarget(weapon->target(), weapon->radius()) == STATUS::TARGET_OK) {
                    (*it)->fireEvent(attack_rate, show_effect);
//                    if (slot.subtarget()) {
//                        fire_delay += d_fire_delay;
//                    }
                } else {
                    weapon->resetTarget();
                }
                it = m_slots_reloaded.erase(it);
            } else {
                ++it;
            }
        }
    //}
}

void Weapon::__validateTargets()
{
    for (slot::Item* slot: m_slots) {
        control::item::Weapon* weapon = slot->weapon();
        if (weapon) {
            if (weapon->target()) {
                if (!weapon->validateSubTarget()) {
                    weapon->resetSubTarget();
                }
                if (_validateTarget(weapon->target(), weapon->radius()) != STATUS::TARGET_OK) {
                    weapon->resetTarget();
                }
            }
        }
    }
}

void Weapon::updateFireAbility()
{
    m_damage = 0;
    m_radiusMax = 0;
    m_radiusMin = 0;
    for (slot::Item* slot: m_slots) {
        if (slot->item()) {
            if (slot->item()->isFunctioning()) {
                int radius = slot->itemRadius();
                if (m_radiusMin == 0) {
                    m_radiusMin = radius;
                }
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
//    for (slot::ItemSlot* slot: m_slots_reloaded) {
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

} // namespace complex
