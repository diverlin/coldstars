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

namespace core {
namespace complex {

Weapon::Weapon(core::control::Vehicle* vehicle)
    :
      Base(vehicle)
{}


std::vector<int>
Weapon::radiusesOfSelectedWeapons() const
{
    std::vector<int> radiuses;
    for (slot::ItemSlot* slot: m_slots) {
        if (slot->item() && slot->isSelected()) {
            radiuses.push_back(slot->weapon()->radius());
        }
    }
    return radiuses;
}

bool
Weapon::addSlot(slot::ItemSlot* slot)
{
    assert(slot);
    m_slots.push_back(slot);
    return true;
}


slot::ItemSlot*
Weapon::freeSlot() const
{
    for(slot::ItemSlot* slot: m_slots) {
        if (!slot->item()) {
            return slot;
        }
    }

    return nullptr;
}

slot::ItemSlot*
Weapon::equipedWeakestSlot() const
{
    int price_min = 0;
    slot::ItemSlot* result = nullptr;
    for(slot::ItemSlot* slot: m_slots) {
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

void Weapon::prepare()
{       
    // used once at the begining of turn
    __reload();
    __validateTargets();
}

void Weapon::__reload()
{
    m_slots_reloaded.clear();
    for (slot::ItemSlot* slot: m_slots) {
        core::control::item::Weapon* weapon = slot->weapon();
        if (weapon) {
            if (weapon->isFunctioning()) {
                if (weapon->checkAmmo()) {
                    m_slots_reloaded.add(slot);
                }
            }
        }
    }
    
//    fire_delay = meti::getRandInt(7,15);
//    d_fire_delay = TURN_TIME/(m_slots_reloaded.size()+1);
}

void Weapon::activate()
{
    for (slot::ItemSlot* slot: m_slots_reloaded) {
        slot->selectEvent();
    }
}

void Weapon::deactivate()
{
    for (slot::ItemSlot* slot: m_slots_reloaded) {
        slot->deselectEvent();
    }
}

void Weapon::activate(const entity::Type& weapon_group)
{
    for (slot::ItemSlot* slot: m_slots_reloaded) {
        if (slot->item()->descriptor()->obGroup() == weapon_group) {
            slot->selectEvent();
        }
    }
}

void Weapon::deactivate(const entity::Type& weapon_group)
{
    for (slot::ItemSlot* slot: m_slots_reloaded) {
        if (slot->item()->descriptor()->obGroup() == weapon_group) {
            slot->deselectEvent();
        }
    }
}

bool Weapon::isAnyWeaponSelected() const
{
    for (slot::ItemSlot* slot: m_slots/*_reloaded*/) {
        if (slot->isSelected()) {
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

bool Weapon::setTarget(core::control::SpaceObject* target, slot::ItemSlot* subtarget)
{
    STATUS status = _checkTarget(target);
    if (status != STATUS::TARGET_OK) {
        return false;
    }

    bool result = false;
    for (slot::ItemSlot* slot: m_slots) {
        if (slot->isSelected()) {
            core::control::item::Weapon* weapon = slot->weapon();
            if (weapon) {
                if (weapon->isFunctioning()) {
                    if (!slot->target()) {
                        if (_checkDistanceToTarget(target, weapon->radius())) {
                            slot->setTarget(target, subtarget);
                            result = true;
                        }
                    }
                }
            }
        }
    }

    return result;
}

int Weapon::guessDamage(int dist)
{
    int damage = 0;
    for (slot::ItemSlot* slot: m_slots_reloaded) {
        if (slot->weapon()->radius() >= dist) {
            damage += slot->weapon()->damage();
        }
    }
    return damage;
}

slot::ItemSlot*
Weapon::__nextSlotReadyToFire() const {
    for(slot::ItemSlot* slot: m_slots_reloaded) {
        core::control::item::Weapon* weapon = slot->weapon(); // shortcut
        if (_checkDistanceToTarget(slot->target(), weapon->radius())) {
            return slot;
        }
    }
    return nullptr;
}

void Weapon::updateFire(int timer, float attack_rate)
{
    //if (timer < TURN_TIME - fire_delay) {
    slot::ItemSlot* slot = __nextSlotReadyToFire();
    if (slot) {
        slot->weapon()->fire(slot->target(), attack_rate);
        m_slots_reloaded.remove(slot);
    }
    //}
}

void Weapon::__validateTargets()
{
    for (slot::ItemSlot* slot: m_slots) {
        control::item::Weapon* weapon = slot->weapon();
        if (weapon) {
            if (slot->target()) {
                if (!slot->validateSubTarget()) {
                    slot->resetSubTarget();
                }
                if (!_checkDistanceToTarget(slot->target(), weapon->radius())) {
                    slot->reset();
                }
            }
        }
    }
}

std::vector<control::item::Weapon*> Weapon::rockets() const {
    return __functionalWeapons(entity::Type::ROCKET_EQUIPMENT);
}

std::vector<control::item::Weapon*>
Weapon::__functionalWeapons(entity::Type requested_type) const
{
    std::vector<control::item::Weapon*> result;
    for (slot::ItemSlot* slot: m_slots) {
        control::item::Weapon* weapon = slot->weapon();
        if (weapon) {
            if (weapon->isFunctioning()) {
                if (weapon->type() == requested_type || entity::Type::ANY == requested_type)
                    result.push_back(weapon);
            }
        }
    }
    return result;
}

void Weapon::updateFireAbility()
{
    m_damage = 0;
    m_radiusMax = 0;
    m_radiusMin = 0;
    for (slot::ItemSlot* slot: m_slots) {
        control::item::Weapon* weapon = slot->weapon();
        if (weapon) {
            if (weapon->isFunctioning()) {
                int radius = weapon->radius();
                if (m_radiusMin == 0) {
                    m_radiusMin = radius;
                }
                m_radiusMin = std::min(m_radiusMin, radius);
                m_radiusMax = std::max(m_radiusMax, radius);
                m_damage += weapon->damage();
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
} // namespace core
