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

#include <core/spaceobject/SpaceObject.hpp>

#include <ceti/type/IdType.hpp>

namespace core {

class ContainerModel : public SpaceObjectModel {

public:
    ContainerModel(int_t, int_t id = NONE);
    ~ContainerModel() = default;
    ContainerModel(const std::string& data);
    std::string data() const;

    int_t item() const { return m_item; }
    void setItem(int_t item) { m_item = item; }
    void setTargetPos(const glm::vec3& target_pos, float velocity)
    { m_targetPos = target_pos; m_velocity = velocity; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = SpaceObjectModel::info();
        result.add("Container");
        result.add("item", m_item);
        result.add("targetPos", m_targetPos);
        result.add("velocity", m_velocity);
        return result;
    }

private:
    int_t m_item = NONE;
    meti::vec3 m_targetPos;
    float m_velocity = 0.0f;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObjectModel>(*this);
        ar & m_item;
        ar & m_targetPos;
        ar & m_velocity;
    }
};

} // namespace core

