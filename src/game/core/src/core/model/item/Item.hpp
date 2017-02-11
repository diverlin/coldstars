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

#pragma once

#include <core/common/Base.hpp>
#include <core/types/TechLevelTypes.hpp>
#include <core/types/RaceTypes.hpp>

#include <ceti/type/IdType.hpp>

//to be removed
#include <core/item/ItemCommonData.hpp>

namespace model {
namespace item {

class Item : public ::model::Base
{
public:
    Item() = default;
    ~Item() = default;

    void setRace(race::type race) { m_race = race; }
    void setTech(tech::type tech) { m_tech = tech; }
    void setSlotType(entity::type slotType) { m_slotType = slotType; }
    void setSlot(int_t slot)  { m_slot = slot; }
    void setLockedTurns(int lockedTurns) { m_lockedTurns = lockedTurns; }
    void setCondition(int condition) { m_condition = condition; }
    void setPrice(int price) { m_price = price; }
    void setMass(int mass) { m_mass = mass; }
    void setDeterioration(int deterioration) { m_deterioration = deterioration; }

    race::type race() const { return m_race; }
    tech::type tech() const { return m_tech; }
    entity::type slotType() const { return m_slotType; }
    int_t slot() const { return m_slot; }
    int lockedTurns() const { return m_lockedTurns; }
    int condition() const { return m_condition; }
    int price() const { return m_price; }
    int mass() const { return m_mass; }
    int deterioration() const { return m_deterioration; }

private:
    race::type m_race = race::type::NONE;
    tech::type m_tech = tech::type::NONE;
    entity::type m_slotType = entity::type::NONE;
    int_t m_slot = NONE;

    int m_lockedTurns = 0;
    int m_condition = 0;
    int m_price = 0;
    int m_mass = 0;
    int m_deterioration = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::model::Base>(*this);
        ar & m_race;
        ar & m_tech;
        ar & m_slotType;
        ar & m_slot;
        ar & m_lockedTurns;
        ar & m_condition;
        ar & m_price;
        ar & m_mass;
        ar & m_deterioration;
    }
};

} // naemspace item
} // namespace model


