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

#include <core/descriptor/Base.hpp>
#include <ceti/descriptor/BaseView.hpp>

#include <core/type/TechLevelType.hpp>
#include <core/type/RaceType.hpp>

namespace core {

class ItemDescr : public BaseDescr
{
public:
    ItemDescr() = default;
    ~ItemDescr() = default;

    void setRace(race::Type race) { m_race = race; }
    void setTech(tech::Type tech) { m_tech = tech; }
    void setSlotType(const core::SlotType& slotType) { m_slotType = slotType; }
    void setCondition(int condition) { m_condition = condition; }
    void setDeterioration(int deterioration) { m_deterioration = deterioration; }
    void setMass(int mass) { m_mass = mass; }
    void setPrice(int price) { m_price = price; }

    race::Type race() const { return m_race; }
    tech::Type tech() const { return m_tech; }
    const core::SlotType& slotType() const { return m_slotType; }
    int condition() const { return m_condition; }
    int deterioration() const { return m_deterioration; }
    int mass() const { return m_mass; }
    int price() const { return m_price; }

private:
    race::Type m_race = race::Type::NONE;
    tech::Type m_tech = tech::Type::NONE;
    core::SlotType m_slotType = core::SlotType::NONE;
    int m_condition = 0;
    int m_deterioration = 0;
    int m_mass = 0;
    int m_price = 0;

protected:
    ceti::InfoTable info() const override {
        ceti::InfoTable result = ::core::BaseDescr::info();
        result.add("Item");
        result.add("race", race::to_string(m_race));
        result.add("tech", tech::to_string(m_tech));
        result.add("slotType", core::to_string(m_slotType));
        result.add("condition", m_condition);
        result.add("deterioration", m_deterioration);
        result.add("mass", m_mass);
        result.add("price", m_price);
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::core::BaseDescr>(*this);
        ar & m_race;
        ar & m_tech;
        ar & m_slotType;
        ar & m_condition;
        ar & m_deterioration;
        ar & m_mass;
        ar & m_price;
    }
};

} // namespace core
