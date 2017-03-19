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

#include <core/type/EntityTypes.hpp>
#include <core/type/DescriptorTypes.hpp>
#include <core/type/RaceTypes.hpp>

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {

class Base
{
public:
    Base() = default;
    ~Base() = default;

    void setId(int_t id) { m_id = id; }
    void setType(const descriptor::Type& type)   { m_type = type; }
    void setObType(const entity::Type& obType)   { m_obType = obType; }
    void setObSubType(const entity::Type& obSubType) { m_obSubType = obSubType; }
    void setObSubSubType(const entity::Type& obSubSubType) { m_obSubSubType = obSubSubType; }
    void setRace(race::Type race) { m_race = race; }

    int_t id() const { return m_id; }
    descriptor::Type type() const { return m_type; }
    const entity::Type& obType() const { return m_obType; }
    const entity::Type& obSubType() const { return m_obSubType; }
    const entity::Type& obSubSubType() const { return m_obSubSubType; }
    race::Type race() const { return m_race; }

    std::string info() const {
        std::string result = "descriptor::Base:\n";
        result += std::string(" id = ") + std::to_string(m_id) + "\n";
        result += std::string(" type = ") + to_string(m_type) + "\n";
        result += std::string(" obType = ") + to_string(m_obType) + "\n";
        result += std::string(" obSubtype = ") + to_string(m_obSubType) + "\n";
        result += std::string(" obSubsubtype = ") + to_string(m_obSubSubType) + "\n";
        result += std::string(" race = ") + to_string(m_race) + "\n";
        return result;
    }

protected:
    void setObType(descriptor::Type type) { m_type = type; }

private:
    int_t m_id = NONE;
    descriptor::Type m_type = descriptor::Type::NONE;
    entity::Type m_obType = entity::Type::NONE;
    entity::Type m_obSubType = entity::Type::NONE;
    entity::Type m_obSubSubType = entity::Type::NONE;
    race::Type m_race = race::Type::NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_id;
        ar & m_type;
        ar & m_obType;
        ar & m_obSubType;
        ar & m_obSubSubType;
        ar & m_race;
    }
};

} // namespace descriptor

