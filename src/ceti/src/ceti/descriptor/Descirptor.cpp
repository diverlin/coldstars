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

#include "Descriptor.hpp"

#include <ceti/StringUtils.hpp>

#include <sstream>

namespace ceti {
namespace descriptor {

std::map<int, Id> Descriptor::m_ids;


Descriptor::Descriptor(int_t type, int_t id)
    :
      Base(type, id)
{
}

Descriptor::Descriptor(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

Descriptor::~Descriptor()
{
}

bool
Descriptor::operator==(const Descriptor& rhs) const
{
    return data() == rhs.data();
}

std::string
Descriptor::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

void
Descriptor::add(const Property& prop)
{
    switch(prop.valueType) {
    case Property::INT: {
        auto it = m_intValues.find(prop.code);
        if ( it == m_intValues.end() ) {
            m_intValues.insert(std::make_pair(prop.code, prop.intValue));
            return;
        }

        break;
    }
    case Property::FLOAT: {
        auto it = m_floatValues.find(prop.code);
        if ( it == m_floatValues.end() ) {
            m_floatValues.insert(std::make_pair(prop.code, prop.floatValue));
            return;
        }

        break;
    }
    case Property::STR: {
        auto it = m_strValues.find(prop.code);
        if ( it == m_strValues.end() ) {
            m_strValues.insert(std::make_pair(prop.code, prop.strValue));
            return;
        }

        break;
    }
    case Property::VEC3: {
        auto it = m_vec3Values.find(prop.code);
        if ( it == m_vec3Values.end() ) {
            m_vec3Values.insert(std::make_pair(prop.code, prop.vec3Value));
            return;
        }

        break;
    }
    } // end switch

    throw std::runtime_error("ERROR CODE: fixme, descriptor already has such prop name[" + prop.name + "]");
}

void
Descriptor::add(const std::vector<Property>& props)
{
    for(const Property& prop: props) {
        add(prop);
    }
}

int_t
Descriptor::get_i(int key) const
{
    auto it = m_intValues.find(key);
    if (it != m_intValues.end()) {
        return it->second;
    }
    throw std::runtime_error("ERROR CODE: FIXME (get request): prop name=[" + m_ids.at(key).name + "] is not found in descriptor");
}

float
Descriptor::get_f(int key) const
{
    auto it = m_floatValues.find(key);
    if (it != m_floatValues.end()) {
        return it->second;
    }
    throw std::runtime_error("ERROR CODE: FIXME (get request): prop name=[" + m_ids.at(key).name + "] is not found in descriptor");
}

const std::string&
Descriptor::get_s(int key) const
{
    auto it = m_strValues.find(key);
    if (it != m_strValues.end()) {
        return it->second;
    }
    throw std::runtime_error("ERROR CODE: FIXME (get request): prop name=[" + m_ids.at(key).name + "] is not found in descriptor");
}


const meti::vec3&
Descriptor::get_v3(int key) const
{
    auto it = m_vec3Values.find(key);
    if (it != m_vec3Values.end()) {
        return it->second;
    }
    throw std::runtime_error("ERROR CODE: FIXME (get request): prop name=[" + m_ids.at(key).name + "] is not found in descriptor");
}

std::string
Descriptor::info() const {
    std::string result("descriptor type=" + std::to_string(type()) + "\n");
    for(auto it = m_intValues.begin(); it != m_intValues.end(); ++it) {
        result += m_ids.at(it->first).name + "=" + std::to_string(it->second) + "\n";
    }
    for(auto it = m_floatValues.begin(); it != m_floatValues.end(); ++it) {
        result += m_ids.at(it->first).name + "=" + std::to_string(it->second) + "\n";
    }
    for(auto it = m_strValues.begin(); it != m_strValues.end(); ++it) {
        result += m_ids.at(it->first).name + "=" + it->second + "\n";
    }
    for(auto it = m_vec3Values.begin(); it != m_vec3Values.end(); ++it) {
        result += m_ids.at(it->first).name + "= " + ceti::to_string(it->second) +"\n";
    }
    return result;
}


} // namespace descriptor
} // namespace ceti

