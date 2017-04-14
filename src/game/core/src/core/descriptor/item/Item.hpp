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

namespace descriptor {

class Item : public Base, public ceti::descriptor::BaseView
{
public:
    Item() = default;
    ~Item() = default;

    void setRace(race::Type race) { m_race = race; }
    void setTech(tech::Type tech) { m_tech = tech; }
    void setSlotType(entity::Type slotType) { m_slotType = slotType; }
    void setCondition(int condition) { m_condition = condition; }
    void setDeterioration(int deterioration) { m_deterioration = deterioration; }
    void setMass(int mass) { m_mass = mass; }
    void setPrice(int price) { m_price = price; }

    race::Type race() const { return m_race; }
    tech::Type tech() const { return m_tech; }
    entity::Type slotType() const { return m_slotType; }
    int condition() const { return m_condition; }
    int deterioration() const { return m_deterioration; }
    int mass() const { return m_mass; }
    int price() const { return m_price; }

private:
    race::Type m_race = race::Type::NONE;
    tech::Type m_tech = tech::Type::NONE;
    entity::Type m_slotType = entity::Type::NONE;
    int m_condition = 0;
    int m_deterioration = 0;
    int m_mass = 0;
    int m_price = 0;

protected:
    std::string info() const {
        std::string result = "descriptor::Item:\n";
        result += std::string(" race = ") + to_string(m_race) + "\n";
        result += std::string(" tech = ") + to_string(m_tech) + "\n";
        result += std::string(" slotType = ") + to_string(m_slotType) + "\n";
        result += std::string(" condition = ") + std::to_string(m_condition) + "\n";
        result += std::string(" deterioration = ") + std::to_string(m_deterioration) + "\n";
        result += std::string(" mass = ") + std::to_string(m_mass) + "\n";
        result += std::string(" price = ") + std::to_string(m_price) + "\n";
        result += ceti::descriptor::BaseView::info();
        result += ::descriptor::Base::info();
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::descriptor::Base>(*this);
        ar & boost::serialization::base_object<ceti::descriptor::BaseView>(*this);
        ar & m_race;
        ar & m_tech;
        ar & m_slotType;
        ar & m_condition;
        ar & m_deterioration;
        ar & m_mass;
        ar & m_price;
    }
};

} // namespace descriptor
