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
#include <ceti/InfoTable.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace core {

class BaseDescr
{
protected:
    BaseDescr() = default;

public:
    virtual ~BaseDescr() = default;
    //virtual std::string data() const = 0;
    virtual std::string data() const { return ""; }

    void setId(int_t id) { m_id = id; }
    void setType(const core::Type& type)   { m_type = type; }
    void setObType(const entity::Type& obType)   { m_obType = obType; }
    void setObGroup(const entity::Type& obGroup) { m_obGroup = obGroup; }
    void setObClass(const entity::Type& obClass) { m_obClass = obClass; }
    void setRace(race::Type race) { m_race = race; }
    void setMesh(int_t mesh) { m_mesh = mesh; }
    void setMaterial(int_t texture) { m_texture = texture; }

    int_t id() const { return m_id; }
    core::Type type() const { return m_type; }
    const entity::Type& obType() const { return m_obType; }
    const entity::Type& obGroup() const { return m_obGroup; }
    const entity::Type& obClass() const { return m_obClass; }
    race::Type race() const { return m_race; }
    int_t mesh() const { return m_mesh; }
    int_t material() const { return m_texture; }

    virtual ceti::InfoTable info() const {
        ceti::InfoTable result;
        result.add("Base");
        result.add("id", m_id);
        result.add("type", core::to_string(m_type));
        result.add("obType", entity::to_string(m_obType));
        result.add("obGroup", entity::to_string(m_obGroup));
        result.add("obClass", entity::to_string(m_obClass));
        result.add("race", race::to_string(m_race));
        result.add("mesh", m_mesh);
        result.add("material", m_texture);
        return result;
    }

protected:
    void setObType(core::Type type) { m_type = type; }

private:
    int_t m_id = NONE;
    core::Type m_type = core::Type::NONE;
    entity::Type m_obType = entity::Type::NONE;
    entity::Type m_obGroup = entity::Type::NONE;
    entity::Type m_obClass = entity::Type::NONE;
    race::Type m_race = race::Type::NONE;
    int_t m_mesh = NONE;
    int_t m_texture = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
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

} // namespace core

