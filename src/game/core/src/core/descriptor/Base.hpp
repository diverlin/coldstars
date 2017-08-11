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

#include <core/type/EntityType.hpp>
#include <core/type/DescriptorType.hpp>
#include <core/type/RaceType.hpp>

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
    void setObGroup(const entity::Type& obGroup) { m_obGroup = obGroup; }
    void setObClass(const entity::Type& obClass) { m_obClass = obClass; }
    void setRace(race::Type race) { m_race = race; }
    void setMesh(int_t mesh) { m_mesh = mesh; }
    void setTexture(int_t texture) { m_texture = texture; }

    int_t id() const { return m_id; }
    descriptor::Type type() const { return m_type; }
    const entity::Type& obType() const { return m_obType; }
    const entity::Type& obGroup() const { return m_obGroup; }
    const entity::Type& obSubSubType() const { return m_obClass; }
    race::Type race() const { return m_race; }
    int_t mesh() const { return m_mesh; }
    int_t texture() const { return m_texture; }

    std::string info() const {
        std::string result = "descriptor::Base:\n";
        result += std::string(" id = ") + std::to_string(m_id) + "\n";
        result += std::string(" type = ") + to_string(m_type) + "\n";
        result += std::string(" obType = ") + to_string(m_obType) + "\n";
        result += std::string(" obGroup = ") + to_string(m_obGroup) + "\n";
        result += std::string(" obClass = ") + to_string(m_obClass) + "\n";
        result += std::string(" race = ") + to_string(m_race) + "\n";
        result += std::string(" mesh = ") + std::to_string(m_mesh) + "\n";
        result += std::string(" material = ") + std::to_string(m_texture) + "\n";
        return result;
    }

protected:
    void setObType(descriptor::Type type) { m_type = type; }

private:
    int_t m_id = NONE;
    descriptor::Type m_type = descriptor::Type::NONE;
    entity::Type m_obType = entity::Type::NONE;
    entity::Type m_obGroup = entity::Type::NONE;
    entity::Type m_obClass = entity::Type::NONE;
    race::Type m_race = race::Type::NONE;
    int_t m_mesh = NONE;
    int_t m_texture = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_id;
        ar & m_type;
        ar & m_obType;
        ar & m_obGroup;
        ar & m_obClass;
        ar & m_race;
        ar & m_mesh;
        ar & m_texture;
    }
};

} // namespace descriptor

