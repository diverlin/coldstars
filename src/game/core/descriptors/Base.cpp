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

#include "Base.hpp"

#include <sstream>

namespace descriptor {

std::string Base::KEY_ID = "id";
std::string Base::KEY_TYPE = "type";
std::string Base::KEY_RACE = "race";
std::string Base::KEY_OWNER = "owner";
std::string Base::KEY_TARGET = "target";
std::string Base::KEY_DAMAGE = "damage";
std::string Base::KEY_RADIUS = "radius";
std::string Base::KEY_TECH = "tech";
std::string Base::KEY_MODULES_NUM = "modules";
std::string Base::KEY_MASS = "mass";
std::string Base::KEY_CONDITION = "condition";
std::string Base::KEY_DETEORATION = "deteoration";
std::string Base::KEY_FUEL = "fuel";
std::string Base::KEY_SPEED = "speed";
std::string Base::KEY_HYPER = "hyper";
std::string Base::KEY_REPAIR = "repair";
std::string Base::KEY_STRENGTH = "strength";
std::string Base::KEY_SCAN = "scan";
std::string Base::KEY_PROTECTION = "protection";

Base::Base()
{
}

Base::Base(const std::map<std::string, std::string>& map)
    : m_map(map)
{
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

std::string
Base::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

void
Base::add(const std::string& key, const std::string& val)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, val));
    } else {
        throw std::runtime_error("CODE ERROR: " + key + " is already existed in descriptor");
    }
}

id_type
Base::id() const
{
    return get<id_type>(KEY_ID);
}

int
Base::type() const
{
    return get<int>(KEY_TYPE);
}

int
Base::race() const
{
    return get<int>(KEY_RACE);
}

id_type
Base::owner() const
{
    return get<id_type>(KEY_OWNER);
}

id_type
Base::target() const
{
    return get<id_type>(KEY_TARGET);
}

int
Base::damage() const
{
    return get<int>(KEY_DAMAGE);
}

int
Base::radius() const
{
    return get<int>(KEY_RADIUS);
}

int
Base::tech() const
{
    return get<int>(KEY_TECH);
}

int
Base::modules() const
{
    return get<int>(KEY_MODULES_NUM);
}

int
Base::mass() const
{
    return get<int>(KEY_MASS);
}

int
Base::condition() const
{
    return get<int>(KEY_CONDITION);
}

int
Base::deteoration() const
{
    return get<int>(KEY_DETEORATION);
}

int
Base::fuel() const
{
    return get<int>(KEY_FUEL);
}

int
Base::speed() const
{
    return get<int>(KEY_SPEED);
}

int
Base::hyper() const
{
    return get<int>(KEY_HYPER);
}

int
Base::repair() const
{
    return get<int>(KEY_REPAIR);
}

int
Base::strength() const
{
    return get<int>(KEY_STRENGTH);
}

int
Base::scan() const
{
    return get<int>(KEY_SCAN);
}

int
Base::protection() const
{
    return get<int>(KEY_PROTECTION);
}

bool
Base::operator==(const Base& rhs) const
{
    return data() == rhs.data();
}

const std::string&
Base::get_raw(const std::string& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + key + " is not found in descriptor");
}

} // namespace descriptor

