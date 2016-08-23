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

#include "DescriptorBase.hpp"

#include <sstream>

namespace ceti {
namespace descriptor {

IdGenerator Base::m_idGenerator;
std::map<int, Id> Base::m_ids;


Base::Base(const int_t& type, const int_t& id)
    :
      m_type(type)
    , m_id(id)
{
    if (id == -1) {
        m_id = m_idGenerator.nextId();
    }
}

Base::Base(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

Base::~Base()
{
}

bool
Base::operator==(const Base& rhs) const
{
    return data() == rhs.data();
}

std::string
Base::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

void
Base::add(const Property& prop)
{
    if (prop.valueType == Property::INT) {
        auto it = m_intValues.find(prop.code);
        if ( it == m_intValues.end() ) {
            m_intValues.insert(std::make_pair(prop.code, prop.intValue));
            return;
        }
    } else {
        auto it = m_strValues.find(prop.code);
        if ( it == m_strValues.end() ) {
            m_strValues.insert(std::make_pair(prop.code, prop.strValue));
            return;
        }
    }

    throw std::runtime_error("ERROR CODE: fixme, descriptor already has such prop name[" + prop.name + "]");
}

void
Base::add(const std::vector<Property>& props)
{
    for(const Property& prop: props) {
        add(prop);
    }
}

const int_t&
Base::get(int key) const
{
    auto it = m_intValues.find(key);
    if (it != m_intValues.end()) {
        return it->second;
    }
    throw std::runtime_error("ERROR CODE: FIXME (get request): prop name=[" + m_ids.at(key).name + "] is not found in descriptor");
}

std::string
Base::info() const {
    std::string result("descriptor type=" + std::to_string(m_type) + "\n");
    for(auto it = m_intValues.begin(); it != m_intValues.end(); ++it) {
        result += m_ids.at(it->first).name + "=" + std::to_string(it->second) + "\n";
    }
    for(auto it = m_strValues.begin(); it != m_strValues.end(); ++it) {
        result += m_ids.at(it->first).name + "=" + it->second + "\n";
    }
    return result;
}


} // namespace descriptor
} // namespace ceti

