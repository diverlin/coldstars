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
#include <ceti/serialization/macro.hpp>
#include <ceti/StringUtils.hpp>

#include <meti/VectorUtils.hpp>

namespace descriptor {

struct Orientation : public Base
{
public:
    Orientation() = default;
    ~Orientation() = default;

    ceti::InfoTable info() const {
        ceti::InfoTable result = Base::info();
        result.add("descriptor::Orientation");
        result.add("size", m_size);
        result.add("direction", m_direction);
        return result;
    }

    const meti::vec3& size() const { return m_size; }
    const meti::vec3& direction() const { return m_direction; }

    void setSize(const meti::vec3& size) { m_size = size; }
    void setDirection(const meti::vec3& direction) { m_direction = direction; }

private:
    meti::vec3 m_size;
    meti::vec3 m_direction;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_size;
        ar & m_direction;
    }
}; 

} // namespace descriptor





