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

#include <sstream>

std::string Descriptor::KEY_ID = "id";
std::string Descriptor::KEY_TYPE = "type";
std::string Descriptor::KEY_RACE = "race";
std::string Descriptor::KEY_OWNER = "owner";
std::string Descriptor::KEY_TARGET = "target";
std::string Descriptor::KEY_DAMAGE = "damage";
std::string Descriptor::KEY_RADIUS = "radius";
std::string Descriptor::KEY_TECH = "tech";
std::string Descriptor::KEY_MODULES_NUM = "modules";
std::string Descriptor::KEY_MASS = "mass";
std::string Descriptor::KEY_CONDITION = "condition";
std::string Descriptor::KEY_DETEORATION = "deteoration";
std::string Descriptor::KEY_FUEL = "fuel";

Descriptor::Descriptor()
{
}

Descriptor::Descriptor(const std::map<std::string, std::string>& map)
    : m_map(map)
{
}

Descriptor::Descriptor(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

std::string
Descriptor::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

void Descriptor::add(const std::string& key, const std::string& val)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, val));
    } else {
        throw std::runtime_error("CODE ERROR: " + key + " is already existed in descriptor");
    }
}

id_type
Descriptor::id() const
{
    return get<id_type>(KEY_ID);
}

int
Descriptor::type() const
{
    return get<int>(KEY_TYPE);
}

int
Descriptor::race() const
{
    return get<int>(KEY_RACE);
}

id_type
Descriptor::owner() const
{
    return get<id_type>(KEY_OWNER);
}

id_type
Descriptor::target() const
{
    return get<id_type>(KEY_TARGET);
}

int
Descriptor::damage() const
{
    return get<int>(KEY_DAMAGE);
}

int
Descriptor::radius() const
{
    return get<int>(KEY_RADIUS);
}

int
Descriptor::tech() const
{
    return get<int>(KEY_TECH);
}

int
Descriptor::modules() const
{
    return get<int>(KEY_MODULES_NUM);
}

int
Descriptor::mass() const
{
    return get<int>(KEY_MASS);
}

int
Descriptor::condition() const
{
    return get<int>(KEY_CONDITION);
}

int
Descriptor::deteoration() const
{
    return get<int>(KEY_DETEORATION);
}

int
Descriptor::fuel() const
{
    return get<int>(KEY_FUEL);
}

bool
Descriptor::operator==(const Descriptor& rhs) const
{
    return data() == rhs.data();
}

const std::string&
Descriptor::get_raw(const std::string& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + key + " is not found in descriptor");
}
    



