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

#include <ceti/descriptor/BaseView.hpp>
#include <ceti/serialization/macro.hpp>
#include <meti/VectorUtils.hpp>

namespace descriptor {

struct Orientation : public ceti::descriptor::BaseView
{
public:
    Orientation() = default;
    Orientation(const std::string& data)
    {
        MACRO_READ_SERIALIZED_DATA
    }
    virtual ~Orientation() = default;

    std::string info() const override {
        std::string result = "Orientation descriptor: " + ceti::descriptor::BaseView::info();
        result += std::string(" size=") + meti::to_string(m_size);
        return result;
    }

    const meti::vec3& size() const { return m_size; }

    void setSize(const meti::vec3& size) { m_size = size; }

private:
    meti::vec3 m_size;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ceti::descriptor::BaseView>(*this);
        ar & m_size;
    }
}; 

} // namespace descriptor




